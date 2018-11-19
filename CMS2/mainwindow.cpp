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
    changeSetup(bitrate, sampleRate * 1000);
    ui->recSamRateBox->setCurrentIndex(1);
    ui->recBitrateBox->setCurrentIndex(1);
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

    // init send message list
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

// checksum function: returns checksum (8bit). Returns 0 if there is a valid checksum at end
unsigned char MainWindow::checksum (unsigned char *data, size_t dataLen) {
    unsigned char check = 0;
    while (dataLen-- != 0) {
        check -= *data++;
    }
    return check;
}

// creates header structure for
Header * MainWindow::createHeader(Msg * msg, unsigned char rID, unsigned char sID){
    // new header
    Header * newHeader = new Header;

    newHeader->recAddr = rID;
    newHeader->sendAddr = sID;
    newHeader->compEncrpyt[0] = 0x00;
    newHeader->compEncrpyt[1] = 0x00;
    newHeader->compEncrpyt[2] = 0x00;
    newHeader->compEncrpyt[3] = 0x00;
    newHeader->dataLen = msg->bufSize;

    newHeader->checkSum = checksum((unsigned char *)msg->buf, msg->bufSize);

    qDebug() << "checksum: " << newHeader->checkSum;

    return newHeader;
}


void MainWindow::writeData(struct Msg * m, int n)
{
    unsigned char ID = 0x00;
    if (ui->sIDBox->currentIndex() == 0) {
        ID = 0x69;
    } else {
        ID = 0x42;
    }

    Header * mHeader = createHeader(m, ID, thisID);

    qDebug() << "Buffer size: " << m->bufSize + sizeof(*mHeader);

    unsigned char * dataBuf = (unsigned char *)malloc(m->bufSize + sizeof(*mHeader));

    qDebug() << "mHeader size: " << sizeof(*mHeader);

    memcpy(dataBuf, mHeader, sizeof((*mHeader)));
    memcpy(dataBuf+sizeof((*mHeader)), m->buf, m->bufSize);

    QByteArray sendData;
    sendData.setRawData((char *)dataBuf, m->bufSize + sizeof(*mHeader));
    m_serial->write(sendData);
}

const char * MainWindow::readData()
{
    m_serial->waitForReadyRead(1000);
    m_serial->waitForBytesWritten(20);
    const QByteArray data = m_serial->readAll();

    if (data.size() > 0) {
        qDebug() << "Recieved data size: " << data.size();

        if (data.size() > 138) {
            qDebug() << "Audio mesage received.";
            memcpy((short *)playRecBuf, data, data.size());
            //startPlayback();
            return NULL;
        } else {
            qDebug() << "New serial data: "  << data;

            unsigned char sig[4] = {data[0],data[1],data[2],data[3]};
            unsigned char rID = data[5];
            unsigned char sID = data[6];
            unsigned long dLen = (unsigned long)data[8];
            unsigned char compEcrypt[4] = {data[11],data[12],data[13],data[14]};
            unsigned char patt[4] = {data[16],data[17],data[18],data[19]};
            unsigned char cSum = data[20];

            char * ID = (char *)malloc(5);
            sprintf(ID, "%d", ID);

            QString label;
            label.append("Reciever:");
            label.append(ID);
            label.append("  Sender:");
            label.append(sID);
            label.append("  Size:");
            label.append((int)dLen);

            qDebug() << "Sig: " << sig[0];
            qDebug() << sig[1];
            qDebug() << sig[2];
            qDebug() << sig[3];

            qDebug() << "Reciever ID: " << rID;
            qDebug() << "Sender ID: " << sID;

            qDebug() << "Data length: "<< dLen;

            qDebug() << "Comp: "<< compEcrypt[0];

            qDebug() << "Pattern: "<< patt[0];
            qDebug() << patt[1];
            qDebug() << patt[2];
            qDebug() << patt[3];

            int checkSumFailed = 0;
            if (dLen > 0) {
                if (checksum((unsigned char *)playRecBuf+21, dLen) != 0) {
                    checkSumFailed = 1;
                    qDebug() << "CHECKSUM FAILURE";
                    label.append("  CHECKSUM FAILED");
                } else {
                    qDebug() << "GOOD CHECKSUM";
                }
            }

            qDebug() << "Checksum: "<< cSum;

            ui->recMsgList->addItem(label);

            return data.data();
        }

        QString str = QString(data);
        if (str.contains("0x6F8C32E90A")) {
            qDebug() << "TEST SUCCESSFUL!";
        }
        //m_serial->flush();

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

            bufSize = recSec * (sampleRate * 1000); // calculate buffer size

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

    Link * tempLink = lTraverse(sendMsgList, selAMsg);
    Msg * tempAMsg = (Msg *)tempLink->data;

    PlayBuffer((short *)tempAMsg->buf, (tempAMsg->bufSize)/2);	// play buffer

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
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    ui->sendTab->setEnabled(false);
    ui->setTab->setEnabled(false);
    ui->radioHome->setChecked(false);
    ui->radioRec->setChecked(true);
}

void MainWindow::on_radioHome_clicked()
{
    disconnect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
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
        bitrate = 16;
    }
    changeSetup(bitrate, sampleRate * 1000);
}

void MainWindow::on_recSamRateBox_currentIndexChanged(int index)
{
    if (index == 0) {
        sampleRate = 4;
    } else if (index == 1) {
        sampleRate = 8;
    } else if (index == 2) {
        sampleRate = 16;
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
    newAMsg->bufSize = bufSize *2;     // size in BYTES
    newAMsg->len = recSec;
    newAMsg->buf = malloc((size_t)bufSize*2);
    memcpy(newAMsg->buf, playRecBuf, (size_t)bufSize*2);

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

    #define testSize 2000

    Link * tempLink = lTraverse(sendMsgList, selAMsg);
    Msg * tempMsg = (Msg *)tempLink->data;

    if (tempMsg->bufSize > 138) {       // audio
        //memset(tempMsg->buf, 'c', testSize);
        //writeData((unsigned char *)tempMsg->buf, testSize);
        writeData(tempMsg, testSize);
    } else {                            // text
        //writeData((unsigned char *)tempMsg->buf, tempMsg->bufSize);
        writeData(tempMsg, tempMsg->bufSize);
    }
}

void MainWindow::on_sendRecList_currentRowChanged(int currentRow)
{
}

void MainWindow::on_actionTest_1_triggered()
{
    char testStr[13] = "0x6F8C32E90A";
    //writeData(testStr, 13);
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

void MainWindow::on_IDBox_currentIndexChanged(int index)
{
    switch(index) {
        case 0:
            thisID = 0xAA;
            break;
        case 1:
            thisID = 0x25;
            break;
        default:
            thisID = 0xAA;
            break;
    }
}
