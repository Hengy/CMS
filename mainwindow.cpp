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

            Msg * newAMsg = new Msg;
            newAMsg->type = 0;  // audio message type
            newAMsg->bitrate = bitrate;
            newAMsg->samplerate = sampleRate;
            newAMsg->bufSize = bufSize;
            newAMsg->len = recSec;
            newAMsg->buf = (short *)malloc((size_t)bufSize);
            memcpy(newAMsg->buf, playRecBuf, (size_t)bufSize);

            lPushToEnd(sendMsgList, newAMsg, sizeof(Msg));

            ui->sendRecList->addItem(QString(text));
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

    int selAMsg = ui->sendRecList->currentRow();

    qDebug() << selAMsg;

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
    char * msgText;

    qDebug() << msgQText.size();

    memcpy(msgText, msgQText.toStdString().c_str(), 2);

    /*
    qDebug() << msgText;

    int msgTextSize = msgQText.size();

    qDebug() << msgText;

    if (msgTextSize > 139) {
        msgTextSize = 139;
    }

    qDebug() << msgText;

    Msg * newTextMsg = new Msg;
    newTextMsg->type = 1;  // text message type
    newTextMsg->bitrate = 0;
    newTextMsg->samplerate = 0;
    newTextMsg->bufSize = bufSize;
    newTextMsg->len = 0;
    newTextMsg->buf = (char *)malloc((size_t)bufSize);
    memcpy((char *)newTextMsg->buf, msgText, (size_t)msgTextSize);

    lPushToEnd(sendMsgList, newTextMsg, sizeof(Msg));

    ui->sendRecList->addItem((char *)newTextMsg->buf);
    */
}
