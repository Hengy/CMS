#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include "L2L.h"
#include "sound.h"
#include <string.h>
#include "bst.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new QSerialPort(this))
{
    //connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    //connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

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

    for (short i=0; i<256; i+=10) {
        ui->sPriorityBox->addItem(QString::number(i));
    }

    // recieved message sort order
    ui->timeRadioButton->setChecked(false);
    ui->priRadioButton->setChecked(true);

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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readData()));
    timer->start(1000);

    // init send message list
    sendMsgList = new LList;
    lInit(sendMsgList);

    startTime = getTime();
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

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

unsigned long MainWindow::getTime() {
   time_t seconds;

   seconds = time(NULL);

   return (unsigned long)seconds;
}

void MainWindow::refreshListHelper(struct Leaf* root, int* n) {
    if (root != NULL) {
        traverseBST(root->left);

        //qDebug() << "Key: " << root->key;

        (*n)++;

        QString labelStr;

        labelStr = QString("%1   Key: %2").arg(QString::number(*n), QString::number(root->key));

        ui->recMsgList->addItem(QString(root->key));

        traverseBST(root->right);
    }
}

void MainWindow::refreshList() {
    int treeSize = sizeOfBST(recMsgTreePri);
    qDebug() << "Tree size: " << treeSize;
    ui->treeCount->setText(QString::number(treeSize));

    ui->recMsgList->clear();

    int* n;
    *n = 0;

    if (sortOrder) {    // priority
        refreshListHelper(recMsgTreePri, n);
    } else {
        refreshListHelper(recMsgTreeTime, n);
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
Header * MainWindow::createHeader(Msg * msg, unsigned char pri, unsigned char rID, unsigned char sID){
    // new header
    Header * newHeader = new Header;

    if (msg->type) {
        newHeader->type = 0xF0; // type 1: text
    } else {
        newHeader->type = 0x0F; // type 0: audio
    }
    newHeader->priority = pri;
    newHeader->recAddr = rID;
    newHeader->sendAddr = sID;
    newHeader->dataLen = msg->bufSize;
    newHeader->timestamp = (int)(getTime() - startTime);
    qDebug() << "Timestamp: " << newHeader->timestamp;

    newHeader->checkSum = checksum((unsigned char *)msg->buf, msg->bufSize);

    qDebug() << "checksum: " << newHeader->checkSum;

    return newHeader;
}


void MainWindow::writeData(Msg * m)
{
    unsigned char ID = 0x00;
    if (ui->sIDBox->currentIndex() == 0) {
        ID = 0x69;
    } else if (ui->sIDBox->currentIndex() == 1){
        ID = 0x42;
    } else {
        ID = 0xFF;
    }

    unsigned char priority = ui->sPriorityBox->currentIndex() * 10;

    Header * mHeader = createHeader(m, priority, ID, thisID);

    qDebug() << "Buffer size: " << m->bufSize + sizeof(*mHeader);

    unsigned char * dataBuf = (unsigned char *)malloc(m->bufSize + sizeof(*mHeader));

    qDebug() << "mHeader size: " << sizeof(*mHeader);

    memcpy(dataBuf, mHeader, sizeof((*mHeader)));
    memcpy(dataBuf+sizeof((*mHeader))+1, m->buf, m->bufSize);

    QByteArray sendData;
    sendData.setRawData((char *)dataBuf, m->bufSize + sizeof(*mHeader));
    m_serial->write(sendData);
}

const char * MainWindow::readData() {
    //m_serial->waitForReadyRead(1000);
    m_serial->waitForBytesWritten(160);
    const QByteArray data = m_serial->readAll();

    const char* tempData;

    if (data.size() > 0) {

        tempData = data.data();
        int BERtest = memcmp(tempData+21, BERarray, 4);
        if (!BERtest) {
            qDebug() << "Bit Error Rate test";

            int errors = 0;
            for (int i=0; i<20; i++) {
                for (int j=0; j<8; j++) {
                    qDebug() << "Compare: " << (tempData[i] & (0x01 << j)) << ":" << (BERarray[i] & (0x01 << j));
                    if ((tempData[i] & (0x01 << j)) != (BERarray[i] & (0x01 << j))) {
                        errors++;
                    }
                }
            }
            qDebug() << "BER: " << errors << "/160";
        } else {
            qDebug() << "Raw data: "  << data;

            Header* newRHead = new Header;
            memcpy(newRHead, data, sizeof(Header));

            if (newRHead->recAddr == 0xFF || newRHead->recAddr == thisID) {
                int typeErr = 0;
                if ( ( (newRHead->type & 0xF0) > 0x20) && (newRHead->dataLen <= ( sizeof(Header) + 140 ) ) ) {      // if type is valid & size of data is less than 140
                    newRHead->type = 1;  // text
                } else if ((newRHead->type & 0x0F) < 0x0E){ // if type is valid & size of data is greater than 140
                    newRHead->type = 0;  // audio
                } else {
                    typeErr = 1;
                }

                if (!typeErr) {
                    Msg* newRMsg = new Msg;
                    RecMsg* newRecMsg = new RecMsg;

                    newRMsg->type = newRHead->type;
                    newRMsg->bufSize = newRHead->dataLen;
                    unsigned char* temp = (unsigned char *)malloc(newRHead->dataLen);
                    tempData = data.data();
                    memcpy(temp, ((unsigned char*)tempData) + sizeof(Header) + 1, newRHead->dataLen);
                    newRMsg->buf = temp;

                    newRecMsg->head = newRHead;
                    newRecMsg->message = newRMsg;

                    if (newRHead->dataLen > 0) {
                        if (( checksum( (unsigned char*)newRMsg->buf, newRHead->dataLen) - newRHead->checkSum) != 0) {
                            newRHead->checkSum = 1; // checksum bad
                            qDebug() << "Bad checkum!";
                        } else {
                            newRHead->checkSum = 0;
                        }
                    }

                    //                    insertToBST(recMsgTreePri, newRHead->priority, newRecMsg);
                    //                    insertToBST(recMsgTreeTime, (int)newRHead->timestamp, newRecMsg);

                    // add message to trees
                    if (recMsgTreePri == NULL) {
                        recMsgTreePri = initBST(newRHead->priority, newRecMsg);      // priority sorted
                        recMsgTreeTime = initBST((int)newRHead->timestamp, newRecMsg);     // time sorted
                    } else {
                        insertToBST(recMsgTreePri, newRHead->priority, newRecMsg);   // priority sorted
                        insertToBST(recMsgTreeTime, (int)newRHead->timestamp, newRecMsg);  // time sorted
                    }
                }


//                tempData = data.data();
//                QString labelStr;
//                if (newRHead->type) {
//                    labelStr = QString("Priority: %1   Timestamp: %2   Reciever: %3   Sender: %4   Size: %5   Text: \"%6\"").arg(QString::number(newRHead->priority), QString::number((int)newRHead->timestamp), QString::number((int)newRHead->recAddr), QString::number((int)newRHead->sendAddr), QString::number((int)newRHead->dataLen-1), tempData+sizeof(Header) + 1);
//                } else {
//                    labelStr = QString("Priority: %1   Timestamp: %2   Reciever: %3   Sender: %4   Size: %5").arg(QString::number(newRHead->priority), QString::number((int)newRHead->timestamp), QString::number((int)newRHead->recAddr), QString::number((int)newRHead->sendAddr), QString::number((int)newRHead->dataLen-1));
//                }
//                ui->recMsgList->addItem(labelStr);



//                qDebug() << "Priority sorted: ";
//                traverseBST(recMsgTreePri);
//                qDebug() << "Time sorted: ";
//                traverseBST(recMsgTreeTime);

                refreshList();
            }
        }

        m_serial->clear(QSerialPort::AllDirections);
        return data.data();

    }
    return NULL;
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
    int selAMsg = ui->sendRecList->currentRow();

    qDebug() << selAMsg;

    Link * tempLink = lTraverse(sendMsgList, selAMsg);
    Msg * tempMsg = (Msg *)tempLink->data;
    //Msg * tempMsg = new Msg;
    //memcpy(tempMsg, tempLink->data, sizeof(tempLink->data));
    //(Msg *)tempLink->data;

    qDebug() << "Write size: " << tempMsg->bufSize;
    qDebug() << "Text: " << (char *)tempMsg->buf;

    writeData(tempMsg);
}

void MainWindow::on_sendRecList_currentRowChanged(int currentRow)
{
}

void MainWindow::on_actionTest_1_triggered()
{

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
            thisID = 0x69;
            break;
        case 1:
            thisID = 0x25;
            break;
        case 2:
            thisID = 0xAA;
            break;
        case 3:
            thisID = 0x43;
            break;
        default:
            thisID = 0x69;
            break;
    }
}

void MainWindow::on_actionBER_Test_triggered()
{
    Msg * BERmsg = new Msg;
    BERmsg->buf = (unsigned char *)malloc(20);
    memcpy(BERmsg->buf, BERarray, 20);
    BERmsg->bufSize = 20;

    writeData(BERmsg);
}

void MainWindow::on_priRadioButton_released()
{
    ui->timeRadioButton->setChecked(false);
    ui->priRadioButton->setChecked(true);
    sortOrder = 1;  // priority
}

void MainWindow::on_timeRadioButton_released()
{
    ui->timeRadioButton->setChecked(true);
    ui->priRadioButton->setChecked(false);
    sortOrder = 0;  // time
}

void MainWindow::on_textMsg_textChanged()
{
    int charCount = ui->textMsg->toPlainText().length();
    ui->sendMsgCount->setText(QString::number(charCount));
}
