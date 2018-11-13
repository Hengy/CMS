#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include "L2L.h"
#include "sound.h"
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new QSerialPort(this))
{
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);

    ui->setupUi(this);

    // set defaults
    recSec = 1;
    ui->recLenSlider->setValue(1);
    bitrate = 16;
    sampleRate = 8;
    ui->timeoutDropbox->setCurrentIndex(3);

    // disable Home station controls
    ui->sendTab->setEnabled(false);
    ui->setTab->setEnabled(false);
    ui->radioHome->setChecked(false);
    ui->radioRec->setChecked(true);

    // get available COM ports and select the first one
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports)
            ui->serialPortDropbox->addItem(info.portName());
    if (ui->serialPortDropbox->count() > 0) {
        ui->serialPortDropbox->setCurrentIndex(0);
    }
    currPort.setPortName(ui->serialPortDropbox->itemText(0));
    currPort.setBaudRate(STD_BAUDRATE);
    // ALL OTHER PARAMETERS ARE SET TO DEFAULT: No Parity, 8 bits, 1 stop bit

    sendMsgList = new LList;
    lInit(sendMsgList);
}

MainWindow::~MainWindow()
{
    closeSerialPort();
    delete ui;
}

int MainWindow::openSerialPort()
{
    m_serial->setPortName(currPort.portName());
    m_serial->setBaudRate(currPort.baudRate());
    m_serial->setDataBits(currPort.dataBits());
    m_serial->setParity(currPort.parity());
    m_serial->setStopBits(currPort.stopBits());
    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Port open.\n";
        return 1;
    } else {
        qDebug() << "Port open error!\n";
        return 0;
    }
}

void MainWindow::writeData(char * data, int n)
{
    QByteArray sendData;
    sendData.setRawData(data,(unsigned int)n);
    m_serial->write(data);
}

const char * MainWindow::readData()
{
    m_serial->waitForReadyRead(timeout);
    const QByteArray data = m_serial->readAll();
    if (data.size() > 0) {
        if (data.size() > 100) {
            qDebug() << "Audio mesage received.";
            memcpy((short*)playRecBuf, data, data.size());
            startPlayback();
            return NULL;
        } else {
            qDebug() << "New serial data: "  << data;
            return data.data();
        }

        QString str = QString(data);
        if (str.contains("0x6F8C32E90A")) {
            qDebug() << "TEST SUCCESSFUL!";
        }

    } else {
        return NULL;
    }
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    qDebug() << "Port disconnected.\n";
}

void MainWindow::disableCtrls()
{
    ui->bttnAudioRec->setEnabled(false);
    ui->bttnAudioPlay->setEnabled(false);
    ui->bttnAudioDel->setEnabled(false);
}

void MainWindow::enableCtrls()
{
    ui->bttnAudioRec->setEnabled(true);
    ui->bttnAudioPlay->setEnabled(true);
    ui->bttnAudioDel->setEnabled(true);
}

void MainWindow::startRecording()
{
    disableCtrls();

    bool ok;
    QString text = QInputDialog::getText(this, tr("Recording"),
                                         tr("Recording name:"), QLineEdit::Normal,
                                         "Message name", &ok);

    QString msg = text + " will be recorded.";

    QMessageBox errBox;
    errBox.setText(msg);
    errBox.setStandardButtons(QMessageBox::Ok);
    errBox.setWindowTitle("Error!");

    if (ok && !text.isEmpty()) {
        // Ok was clicked

        if (InitializeRecording() == 0) {
            errBox.setInformativeText("Error initializing recording!");
            errBox.exec();
        } else {

            ui->recSign->setText(QString("RECORDING"));
            ui->recSign->repaint();

            bufSize = recSec * (sampleRate * 1000) /2; // calculate buffer size

            if (RecordBuffer(playRecBuf, bufSize) == 0) {	// record into buffer
                errBox.setInformativeText("Error recording!");
                errBox.exec();
            } else {
                CloseRecording();
            }

            ui->recSign->setText(QString("IDLE"));
            ui->recSign->repaint();

            ui->sendRecList->addItem(QString("Audio: ") + QString(text));
        }

    }

    enableCtrls();
}

void MainWindow::startPlayback()
{
    disableCtrls();

    InitializePlayback();

    ui->recSign->setText(QString("PLAYING"));
    ui->recSign->repaint();

    int selAMsg = ui->sendRecList->currentRow()-1;

    //qDebug() << selAMsg;

    Link * tempLink = lTraverse(sendMsgList, selAMsg);
    Msg * tempAMsg = (Msg *)tempLink->data;

    PlayBuffer((short *)tempAMsg->buf, tempAMsg->bufSize);	// play buffer
    //PlayBuffer(iBigBuf, bufSize);	// play buffer

    ui->recSign->setText(QString("IDLE"));
    ui->recSign->repaint();

    ClosePlayback();	// close playback

    enableCtrls();
}

void MainWindow::on_bttnAudioDel_released()
{
    lPopEnd(sendMsgList);

    int listSize = ui->sendRecList->count();

    if (listSize > 1) {
        ui->sendRecList->takeItem(listSize-1);
    }
}

void MainWindow::on_radioRec_clicked()
{
    ui->sendTab->setEnabled(false);
    ui->setTab->setEnabled(false);
    ui->radioHome->setChecked(false);
    ui->radioRec->setChecked(true);
}

void MainWindow::on_radioHome_clicked()
{
    ui->radioHome->setChecked(true);
    ui->radioRec->setChecked(false);
    ui->sendTab->setEnabled(true);
    ui->setTab->setEnabled(true);
}

void MainWindow::on_recLenSlider_valueChanged(int value)
{
    recSec = value;
    QString val = QString::number(value);
    ui->recLenLabel->setText(val);
}

void MainWindow::on_recBitrateBox_currentIndexChanged(int index)
{
    if (index == 0) {
        bitrate = 8;
    } else if (index == 1) {
        bitrate = 16;
    } else {
        bitrate = 8;
    }
    changeSetup(bitrate, sampleRate * 1000);
}

void MainWindow::on_recSamRateBox_currentIndexChanged(int index)
{
    if (index == 0) {
        sampleRate = 8;
    } else if (index == 1) {
        sampleRate = 16;
    } else if (index == 1) {
        sampleRate = 32;
    } else {
        sampleRate = 8;
    }
    changeSetup(bitrate, sampleRate * 1000);
}

void MainWindow::on_bttnAudioRec_released()
{
    startRecording();

    Msg * newAMsg = new Msg;
    newAMsg->type = 0;  // audio message type
    newAMsg->bitrate = bitrate;
    newAMsg->samplerate = sampleRate;
    newAMsg->bufSize = bufSize;
    newAMsg->len = recSec;
    newAMsg->buf = (short *)malloc((size_t)bufSize);
    memcpy(newAMsg->buf, playRecBuf, (size_t)bufSize);

    lPushToEnd(sendMsgList, newAMsg, sizeof(Msg));
}

void MainWindow::on_bttnAudioPlay_released()
{
    startPlayback();
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionRecord_Audio_triggered()
{
    startRecording();
}

void MainWindow::on_actionPlay_Audio_triggered()
{
    startRecording();
}

void MainWindow::on_baudrateDropbox_currentIndexChanged(int index)
{
    closeSerialPort();

    switch (index) {
        case 0:
            currPort.setBaudRate(4800);
            break;
        case 1:
            currPort.setBaudRate(9600);
            break;
        case 2:
            currPort.setBaudRate(19200);
            break;
        case 3:
            currPort.setBaudRate(38400);
            break;
        case 4:
            currPort.setBaudRate(57600);
            break;
        case 5:
            currPort.setBaudRate(115200);
            break;
        default:
            currPort.setBaudRate(4800);
            break;
    }

    openSerialPort();
}

void MainWindow::on_serialPortDropbox_currentIndexChanged(int index)
{
    closeSerialPort();

    currPort.setPortName(ui->serialPortDropbox->itemText(index));

    openSerialPort();
}

void MainWindow::on_bttnSaveText_released()
{
    QString msgQText = ui->textMsg->toPlainText();
    size_t textSize = (size_t)msgQText.size() +1;

    if (textSize > 139) {
        textSize = 139;
    }

    char * msgText = (char *)malloc(textSize);

    memcpy(msgText, msgQText.toLocal8Bit().constData(), textSize);

    msgText[textSize-1] = '\0';

    if (textSize > 1) {
        Msg * newTextMsg = new Msg;
        newTextMsg->type = 1;  // text message type
        newTextMsg->bitrate = 0;
        newTextMsg->samplerate = 0;
        newTextMsg->bufSize = (int)textSize;
        newTextMsg->len = 0;
        newTextMsg->buf = (char *)malloc(textSize);
        memcpy((char *)newTextMsg->buf, (char *)msgText, textSize);

        lPushToEnd(sendMsgList, newTextMsg, sizeof(Msg));

        char * msgNameText = (char *)malloc(textSize+6);

        memcpy(msgNameText+6,(char *)newTextMsg->buf,textSize);
        memcpy(msgNameText,"Text: ", 6);

        ui->sendRecList->addItem((char *)msgNameText);

        ui->textMsg->clear();
    }
}

void MainWindow::on_bttnSendMsg_released()
{
    int selAMsg = ui->sendRecList->currentRow()-1;

    //qDebug() << selAMsg;

    Link * tempLink = lTraverse(sendMsgList, selAMsg);
    Msg * tempMsg = (Msg *)tempLink->data;

    writeData((char *)tempMsg->buf, tempMsg->bufSize);
}

void MainWindow::on_sendRecList_currentRowChanged(int currentRow)
{
}

void MainWindow::on_actionTest_1_triggered()
{
    char testStr[13] = "0x6F8C32E90A";
    writeData(testStr, 13);
}

void MainWindow::on_timeoutDropbox_currentIndexChanged(int index)
{
    switch (index) {
        case 0:
            timeout = 500;
            break;
        case 1:
            timeout = 1000;
            break;
        case 2:
            timeout = 1500;
            break;
        case 3:
            timeout = 2000;
            break;
        case 4:
            timeout = 2500;
            break;
        case 5:
            timeout = 3000;
            break;
        default:
            timeout = 2000;
            break;
    }
}
