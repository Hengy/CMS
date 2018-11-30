#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QSerialPortInfo>
#include <QtSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int openSerialPort();

    void handleError(QSerialPort::SerialPortError error);

    unsigned long getTime();

    short majority(short * data, int n);

    void refreshListHelper(struct Leaf* l, int* n);

    void refreshList();

    unsigned char checksum(unsigned char *, size_t);

    struct Header * createHeader(struct Msg *, unsigned char pri, unsigned char rID, unsigned char sID);

    void writeData(struct Msg *);

    const char * readData();

    void closeSerialPort();

    void on_radioRec_clicked();

    void on_radioHome_clicked();

    void on_recLenSlider_valueChanged(int value);

    void on_recBitrateBox_currentIndexChanged(int index);

    void on_recSamRateBox_currentIndexChanged(int index);

    void on_bttnAudioRec_released();

    void on_bttnAudioPlay_released();

    void on_actionExit_triggered();

    void on_actionRecord_Audio_triggered();

    void on_actionPlay_Audio_triggered();

    void on_baudrateDropbox_currentIndexChanged(int index);

    void on_bttnAudioDel_released();

    void on_serialPortDropbox_currentIndexChanged(int index);

    void on_bttnSaveText_released();

    void on_bttnSendMsg_released();

    void on_timeoutDropbox_currentIndexChanged(int index);

    void on_IDBox_currentIndexChanged(int index);

    void on_actionBER_Test_triggered();

    void on_priRadioButton_released();

    void on_timeRadioButton_released();

    void on_textMsg_textChanged();

    void on_RELcheck_released();

    void on_HuffCheck_released();

    Leaf* recViewHelper(Leaf* l, int* n, int j);

    void on_bttnRecView_released();

    void on_bttnRecDetails_released();

    Leaf* recreateHelper(Leaf* l, Leaf* newBST);

    Leaf* recreateBST(Leaf* l);

    void on_bttnRecDel_released();

private:
    Ui::MainWindow *ui;
    void disableCtrls();
    void enableCtrls();
    void startRecording();
    void startPlayback();

    QSerialPort *m_serial = nullptr;
};

#endif // MAINWINDOW_H
