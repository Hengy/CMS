/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionRecord_Audio;
    QAction *actionPlay_Audio;
    QAction *actionSend_Audio_Message;
    QAction *actionSend_Text_Message;
    QAction *actionView_Play_Message;
    QAction *actionMessage_Details;
    QAction *actionDelete_Message;
    QAction *actionHome_Station_Mode;
    QAction *actionReceiver_Mode;
    QAction *actionDelete_Audio;
    QAction *actionBER_Test;
    QWidget *centralWidget;
    QGroupBox *recGroup;
    QPushButton *bttnRecDel;
    QPushButton *bttnRecDetails;
    QPushButton *bttnRecView;
    QListWidget *recMsgList;
    QLabel *label_15;
    QLabel *treeCount;
    QRadioButton *timeRadioButton;
    QRadioButton *priRadioButton;
    QFrame *line_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *modeGroup;
    QRadioButton *radioHome;
    QRadioButton *radioRec;
    QTabWidget *sendTabWidget;
    QWidget *sendTab;
    QPushButton *bttnSaveText;
    QTextEdit *textMsg;
    QListWidget *sendRecList;
    QPushButton *bttnSendMsg;
    QPushButton *bttnAudioDel;
    QPushButton *bttnAudioPlay;
    QPushButton *bttnAudioRec;
    QLabel *recSign;
    QFrame *line;
    QFrame *line_3;
    QPushButton *bttnSave;
    QComboBox *sIDBox;
    QLabel *label_12;
    QLabel *label_14;
    QComboBox *sPriorityBox;
    QLabel *label_16;
    QLabel *sendMsgCount;
    QWidget *setTab;
    QSlider *recLenSlider;
    QComboBox *recBitrateBox;
    QComboBox *recSamRateBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *recLenLabel;
    QGroupBox *groupBox;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *serialPortDropbox;
    QComboBox *baudrateDropbox;
    QComboBox *timeoutDropbox;
    QLabel *label_11;
    QGroupBox *groupBox_2;
    QCheckBox *enEncrypt;
    QCheckBox *enCompress;
    QComboBox *IDBox;
    QLabel *label_13;
    QMenuBar *menuBar;
    QMenu *menuCMS;
    QMenu *menuMessage;
    QMenu *menuTesting;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1011, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionRecord_Audio = new QAction(MainWindow);
        actionRecord_Audio->setObjectName(QStringLiteral("actionRecord_Audio"));
        actionPlay_Audio = new QAction(MainWindow);
        actionPlay_Audio->setObjectName(QStringLiteral("actionPlay_Audio"));
        actionSend_Audio_Message = new QAction(MainWindow);
        actionSend_Audio_Message->setObjectName(QStringLiteral("actionSend_Audio_Message"));
        actionSend_Text_Message = new QAction(MainWindow);
        actionSend_Text_Message->setObjectName(QStringLiteral("actionSend_Text_Message"));
        actionView_Play_Message = new QAction(MainWindow);
        actionView_Play_Message->setObjectName(QStringLiteral("actionView_Play_Message"));
        actionMessage_Details = new QAction(MainWindow);
        actionMessage_Details->setObjectName(QStringLiteral("actionMessage_Details"));
        actionDelete_Message = new QAction(MainWindow);
        actionDelete_Message->setObjectName(QStringLiteral("actionDelete_Message"));
        actionHome_Station_Mode = new QAction(MainWindow);
        actionHome_Station_Mode->setObjectName(QStringLiteral("actionHome_Station_Mode"));
        actionReceiver_Mode = new QAction(MainWindow);
        actionReceiver_Mode->setObjectName(QStringLiteral("actionReceiver_Mode"));
        actionDelete_Audio = new QAction(MainWindow);
        actionDelete_Audio->setObjectName(QStringLiteral("actionDelete_Audio"));
        actionBER_Test = new QAction(MainWindow);
        actionBER_Test->setObjectName(QStringLiteral("actionBER_Test"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        recGroup = new QGroupBox(centralWidget);
        recGroup->setObjectName(QStringLiteral("recGroup"));
        recGroup->setEnabled(true);
        recGroup->setGeometry(QRect(460, 130, 541, 401));
        bttnRecDel = new QPushButton(recGroup);
        bttnRecDel->setObjectName(QStringLiteral("bttnRecDel"));
        bttnRecDel->setGeometry(QRect(450, 370, 75, 23));
        bttnRecDetails = new QPushButton(recGroup);
        bttnRecDetails->setObjectName(QStringLiteral("bttnRecDetails"));
        bttnRecDetails->setGeometry(QRect(90, 370, 72, 23));
        bttnRecView = new QPushButton(recGroup);
        bttnRecView->setObjectName(QStringLiteral("bttnRecView"));
        bttnRecView->setGeometry(QRect(10, 370, 72, 23));
        recMsgList = new QListWidget(recGroup);
        recMsgList->setObjectName(QStringLiteral("recMsgList"));
        recMsgList->setGeometry(QRect(10, 60, 521, 301));
        label_15 = new QLabel(recGroup);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(30, 25, 81, 16));
        treeCount = new QLabel(recGroup);
        treeCount->setObjectName(QStringLiteral("treeCount"));
        treeCount->setGeometry(QRect(120, 20, 51, 26));
        QFont font;
        font.setPointSize(14);
        treeCount->setFont(font);
        timeRadioButton = new QRadioButton(recGroup);
        timeRadioButton->setObjectName(QStringLiteral("timeRadioButton"));
        timeRadioButton->setGeometry(QRect(470, 25, 51, 17));
        priRadioButton = new QRadioButton(recGroup);
        priRadioButton->setObjectName(QStringLiteral("priRadioButton"));
        priRadioButton->setGeometry(QRect(400, 25, 61, 17));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(20, 110, 981, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 361, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setPointSize(20);
        label->setFont(font1);
        label->setTextFormat(Qt::RichText);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 40, 101, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(260, 40, 101, 16));
        modeGroup = new QGroupBox(centralWidget);
        modeGroup->setObjectName(QStringLiteral("modeGroup"));
        modeGroup->setGeometry(QRect(870, 20, 131, 80));
        radioHome = new QRadioButton(modeGroup);
        radioHome->setObjectName(QStringLiteral("radioHome"));
        radioHome->setGeometry(QRect(20, 25, 82, 17));
        radioRec = new QRadioButton(modeGroup);
        radioRec->setObjectName(QStringLiteral("radioRec"));
        radioRec->setGeometry(QRect(20, 50, 82, 17));
        radioRec->setChecked(true);
        sendTabWidget = new QTabWidget(centralWidget);
        sendTabWidget->setObjectName(QStringLiteral("sendTabWidget"));
        sendTabWidget->setGeometry(QRect(10, 130, 431, 401));
        sendTab = new QWidget();
        sendTab->setObjectName(QStringLiteral("sendTab"));
        bttnSaveText = new QPushButton(sendTab);
        bttnSaveText->setObjectName(QStringLiteral("bttnSaveText"));
        bttnSaveText->setGeometry(QRect(290, 280, 111, 32));
        textMsg = new QTextEdit(sendTab);
        textMsg->setObjectName(QStringLiteral("textMsg"));
        textMsg->setGeometry(QRect(20, 230, 251, 81));
        textMsg->setFrameShape(QFrame::StyledPanel);
        textMsg->setAcceptRichText(false);
        sendRecList = new QListWidget(sendTab);
        sendRecList->setObjectName(QStringLiteral("sendRecList"));
        sendRecList->setGeometry(QRect(10, 10, 301, 191));
        bttnSendMsg = new QPushButton(sendTab);
        bttnSendMsg->setObjectName(QStringLiteral("bttnSendMsg"));
        bttnSendMsg->setGeometry(QRect(290, 330, 121, 32));
        bttnAudioDel = new QPushButton(sendTab);
        bttnAudioDel->setObjectName(QStringLiteral("bttnAudioDel"));
        bttnAudioDel->setGeometry(QRect(331, 130, 81, 32));
        bttnAudioPlay = new QPushButton(sendTab);
        bttnAudioPlay->setObjectName(QStringLiteral("bttnAudioPlay"));
        bttnAudioPlay->setGeometry(QRect(331, 90, 81, 32));
        bttnAudioRec = new QPushButton(sendTab);
        bttnAudioRec->setObjectName(QStringLiteral("bttnAudioRec"));
        bttnAudioRec->setGeometry(QRect(331, 50, 81, 32));
        recSign = new QLabel(sendTab);
        recSign->setObjectName(QStringLiteral("recSign"));
        recSign->setGeometry(QRect(321, 10, 101, 31));
        QFont font2;
        font2.setPointSize(12);
        recSign->setFont(font2);
        recSign->setAlignment(Qt::AlignCenter);
        line = new QFrame(sendTab);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 310, 401, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(sendTab);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 210, 401, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        bttnSave = new QPushButton(sendTab);
        bttnSave->setObjectName(QStringLiteral("bttnSave"));
        bttnSave->setGeometry(QRect(330, 170, 81, 32));
        sIDBox = new QComboBox(sendTab);
        sIDBox->addItem(QString());
        sIDBox->addItem(QString());
        sIDBox->addItem(QString());
        sIDBox->setObjectName(QStringLiteral("sIDBox"));
        sIDBox->setGeometry(QRect(208, 335, 61, 22));
        label_12 = new QLabel(sendTab);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(150, 338, 51, 16));
        label_14 = new QLabel(sendTab);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 338, 51, 16));
        sPriorityBox = new QComboBox(sendTab);
        sPriorityBox->setObjectName(QStringLiteral("sPriorityBox"));
        sPriorityBox->setGeometry(QRect(80, 335, 61, 22));
        label_16 = new QLabel(sendTab);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(286, 240, 91, 20));
        sendMsgCount = new QLabel(sendTab);
        sendMsgCount->setObjectName(QStringLiteral("sendMsgCount"));
        sendMsgCount->setGeometry(QRect(373, 237, 31, 26));
        sendMsgCount->setFont(font);
        sendTabWidget->addTab(sendTab, QString());
        setTab = new QWidget();
        setTab->setObjectName(QStringLiteral("setTab"));
        recLenSlider = new QSlider(setTab);
        recLenSlider->setObjectName(QStringLiteral("recLenSlider"));
        recLenSlider->setGeometry(QRect(30, 70, 361, 31));
        recLenSlider->setMinimum(1);
        recLenSlider->setMaximum(10);
        recLenSlider->setPageStep(1);
        recLenSlider->setOrientation(Qt::Horizontal);
        recLenSlider->setTickPosition(QSlider::TicksBelow);
        recLenSlider->setTickInterval(1);
        recBitrateBox = new QComboBox(setTab);
        recBitrateBox->addItem(QString());
        recBitrateBox->addItem(QString());
        recBitrateBox->setObjectName(QStringLiteral("recBitrateBox"));
        recBitrateBox->setGeometry(QRect(170, 180, 221, 30));
        recBitrateBox->setFont(font2);
        recSamRateBox = new QComboBox(setTab);
        recSamRateBox->addItem(QString());
        recSamRateBox->addItem(QString());
        recSamRateBox->addItem(QString());
        recSamRateBox->setObjectName(QStringLiteral("recSamRateBox"));
        recSamRateBox->setGeometry(QRect(170, 240, 221, 30));
        recSamRateBox->setFont(font2);
        label_4 = new QLabel(setTab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 240, 111, 30));
        label_4->setFont(font2);
        label_5 = new QLabel(setTab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 180, 71, 30));
        label_5->setFont(font2);
        label_6 = new QLabel(setTab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 30, 211, 28));
        label_6->setFont(font2);
        label_7 = new QLabel(setTab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 110, 47, 21));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        label_7->setFont(font3);
        label_8 = new QLabel(setTab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(340, 110, 47, 21));
        label_8->setFont(font3);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        recLenLabel = new QLabel(setTab);
        recLenLabel->setObjectName(QStringLiteral("recLenLabel"));
        recLenLabel->setGeometry(QRect(250, 33, 47, 26));
        recLenLabel->setFont(font3);
        sendTabWidget->addTab(setTab, QString());
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(510, 20, 351, 80));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 25, 47, 13));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 53, 47, 13));
        serialPortDropbox = new QComboBox(groupBox);
        serialPortDropbox->setObjectName(QStringLiteral("serialPortDropbox"));
        serialPortDropbox->setGeometry(QRect(90, 20, 101, 22));
        baudrateDropbox = new QComboBox(groupBox);
        baudrateDropbox->addItem(QString());
        baudrateDropbox->addItem(QString());
        baudrateDropbox->addItem(QString());
        baudrateDropbox->addItem(QString());
        baudrateDropbox->addItem(QString());
        baudrateDropbox->addItem(QString());
        baudrateDropbox->setObjectName(QStringLiteral("baudrateDropbox"));
        baudrateDropbox->setGeometry(QRect(90, 50, 101, 22));
        timeoutDropbox = new QComboBox(groupBox);
        timeoutDropbox->addItem(QString());
        timeoutDropbox->addItem(QString());
        timeoutDropbox->addItem(QString());
        timeoutDropbox->addItem(QString());
        timeoutDropbox->addItem(QString());
        timeoutDropbox->addItem(QString());
        timeoutDropbox->setObjectName(QStringLiteral("timeoutDropbox"));
        timeoutDropbox->setGeometry(QRect(240, 50, 101, 22));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(240, 25, 71, 16));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 60, 351, 51));
        enEncrypt = new QCheckBox(groupBox_2);
        enEncrypt->setObjectName(QStringLiteral("enEncrypt"));
        enEncrypt->setGeometry(QRect(20, 20, 91, 21));
        enCompress = new QCheckBox(groupBox_2);
        enCompress->setObjectName(QStringLiteral("enCompress"));
        enCompress->setGeometry(QRect(110, 20, 91, 20));
        IDBox = new QComboBox(groupBox_2);
        IDBox->addItem(QString());
        IDBox->addItem(QString());
        IDBox->addItem(QString());
        IDBox->addItem(QString());
        IDBox->setObjectName(QStringLiteral("IDBox"));
        IDBox->setGeometry(QRect(260, 18, 81, 22));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(230, 20, 31, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1011, 21));
        menuCMS = new QMenu(menuBar);
        menuCMS->setObjectName(QStringLiteral("menuCMS"));
        menuMessage = new QMenu(menuBar);
        menuMessage->setObjectName(QStringLiteral("menuMessage"));
        menuTesting = new QMenu(menuBar);
        menuTesting->setObjectName(QStringLiteral("menuTesting"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCMS->menuAction());
        menuBar->addAction(menuMessage->menuAction());
        menuBar->addAction(menuTesting->menuAction());
        menuCMS->addAction(actionHome_Station_Mode);
        menuCMS->addAction(actionReceiver_Mode);
        menuCMS->addSeparator();
        menuCMS->addAction(actionExit);
        menuMessage->addAction(actionSend_Audio_Message);
        menuMessage->addSeparator();
        menuMessage->addAction(actionPlay_Audio);
        menuMessage->addAction(actionRecord_Audio);
        menuMessage->addAction(actionDelete_Audio);
        menuMessage->addSeparator();
        menuMessage->addAction(actionSend_Text_Message);
        menuMessage->addSeparator();
        menuMessage->addAction(actionView_Play_Message);
        menuMessage->addAction(actionMessage_Details);
        menuMessage->addAction(actionDelete_Message);
        menuTesting->addAction(actionBER_Test);

        retranslateUi(MainWindow);

        sendTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CMS", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionRecord_Audio->setText(QApplication::translate("MainWindow", "Record Audio", nullptr));
        actionPlay_Audio->setText(QApplication::translate("MainWindow", "Play Audio", nullptr));
        actionSend_Audio_Message->setText(QApplication::translate("MainWindow", "Send Audio Message", nullptr));
        actionSend_Text_Message->setText(QApplication::translate("MainWindow", "Send Text Message", nullptr));
        actionView_Play_Message->setText(QApplication::translate("MainWindow", "View/Play Message", nullptr));
        actionMessage_Details->setText(QApplication::translate("MainWindow", "Message Details", nullptr));
        actionDelete_Message->setText(QApplication::translate("MainWindow", "Delete Message", nullptr));
        actionHome_Station_Mode->setText(QApplication::translate("MainWindow", "Home Station Mode", nullptr));
        actionReceiver_Mode->setText(QApplication::translate("MainWindow", "Receiver Mode", nullptr));
        actionDelete_Audio->setText(QApplication::translate("MainWindow", "Delete Audio", nullptr));
        actionBER_Test->setText(QApplication::translate("MainWindow", "BER Test", nullptr));
        recGroup->setTitle(QApplication::translate("MainWindow", "Receive Messages", nullptr));
        bttnRecDel->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        bttnRecDetails->setText(QApplication::translate("MainWindow", "Details", nullptr));
        bttnRecView->setText(QApplication::translate("MainWindow", "View/Play", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Message count:", nullptr));
        treeCount->setText(QApplication::translate("MainWindow", "0", nullptr));
        timeRadioButton->setText(QApplication::translate("MainWindow", "Time", nullptr));
        priRadioButton->setText(QApplication::translate("MainWindow", "Priority", nullptr));
        label->setText(QApplication::translate("MainWindow", "Coded Message System", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Matthew Hengeveld", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Mark Whipple", nullptr));
        modeGroup->setTitle(QApplication::translate("MainWindow", "MODE", nullptr));
        radioHome->setText(QApplication::translate("MainWindow", "Home Station", nullptr));
        radioRec->setText(QApplication::translate("MainWindow", "Receiver", nullptr));
        bttnSaveText->setText(QApplication::translate("MainWindow", "Save Text Message", nullptr));
        textMsg->setPlaceholderText(QApplication::translate("MainWindow", "Message", nullptr));
        bttnSendMsg->setText(QApplication::translate("MainWindow", "Send Message", nullptr));
        bttnAudioDel->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        bttnAudioPlay->setText(QApplication::translate("MainWindow", "Play", nullptr));
        bttnAudioRec->setText(QApplication::translate("MainWindow", "Record", nullptr));
        recSign->setText(QApplication::translate("MainWindow", "IDLE", nullptr));
        bttnSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        sIDBox->setItemText(0, QApplication::translate("MainWindow", "0x69", nullptr));
        sIDBox->setItemText(1, QApplication::translate("MainWindow", "0x42", nullptr));
        sIDBox->setItemText(2, QApplication::translate("MainWindow", "Broadcast", nullptr));

        label_12->setText(QApplication::translate("MainWindow", "Send To:", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Priority:", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "Message length:", nullptr));
        sendMsgCount->setText(QApplication::translate("MainWindow", "0", nullptr));
        sendTabWidget->setTabText(sendTabWidget->indexOf(sendTab), QApplication::translate("MainWindow", "Send Messages", nullptr));
        recBitrateBox->setItemText(0, QApplication::translate("MainWindow", "8 bps", nullptr));
        recBitrateBox->setItemText(1, QApplication::translate("MainWindow", "16 bps", nullptr));

        recSamRateBox->setItemText(0, QApplication::translate("MainWindow", "4000 Hz", nullptr));
        recSamRateBox->setItemText(1, QApplication::translate("MainWindow", "8000 Hz", nullptr));
        recSamRateBox->setItemText(2, QApplication::translate("MainWindow", "16000 Hz", nullptr));

        label_4->setText(QApplication::translate("MainWindow", "Sample Rate", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Bitrate", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Recording Length (seconds):", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "10", nullptr));
        recLenLabel->setText(QApplication::translate("MainWindow", "1", nullptr));
        sendTabWidget->setTabText(sendTabWidget->indexOf(setTab), QApplication::translate("MainWindow", "Settings", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Serial", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Port", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Baudrate", nullptr));
        baudrateDropbox->setItemText(0, QApplication::translate("MainWindow", "4800", nullptr));
        baudrateDropbox->setItemText(1, QApplication::translate("MainWindow", "9600", nullptr));
        baudrateDropbox->setItemText(2, QApplication::translate("MainWindow", "19200", nullptr));
        baudrateDropbox->setItemText(3, QApplication::translate("MainWindow", "38400", nullptr));
        baudrateDropbox->setItemText(4, QApplication::translate("MainWindow", "57600", nullptr));
        baudrateDropbox->setItemText(5, QApplication::translate("MainWindow", "115200", nullptr));

        timeoutDropbox->setItemText(0, QApplication::translate("MainWindow", "500", nullptr));
        timeoutDropbox->setItemText(1, QApplication::translate("MainWindow", "1000", nullptr));
        timeoutDropbox->setItemText(2, QApplication::translate("MainWindow", "1500", nullptr));
        timeoutDropbox->setItemText(3, QApplication::translate("MainWindow", "2000", nullptr));
        timeoutDropbox->setItemText(4, QApplication::translate("MainWindow", "2500", nullptr));
        timeoutDropbox->setItemText(5, QApplication::translate("MainWindow", "3000", nullptr));

        label_11->setText(QApplication::translate("MainWindow", "Timeout (ms)", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
        enEncrypt->setText(QApplication::translate("MainWindow", "Encryption", nullptr));
        enCompress->setText(QApplication::translate("MainWindow", "Compression", nullptr));
        IDBox->setItemText(0, QApplication::translate("MainWindow", "0x69", nullptr));
        IDBox->setItemText(1, QApplication::translate("MainWindow", "0xAA", nullptr));
        IDBox->setItemText(2, QApplication::translate("MainWindow", "0x25", nullptr));
        IDBox->setItemText(3, QApplication::translate("MainWindow", "0x43", nullptr));

        label_13->setText(QApplication::translate("MainWindow", "ID:", nullptr));
        menuCMS->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuMessage->setTitle(QApplication::translate("MainWindow", "Message", nullptr));
        menuTesting->setTitle(QApplication::translate("MainWindow", "Testing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
