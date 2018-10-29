#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>

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
    void on_radioRec_clicked();

    void on_radioHome_clicked();

    void on_bttnAudioRec_clicked();

    void on_recLenSlider_sliderReleased();

    void on_recLenSlider_valueChanged(int value);

    void on_recBitrateBox_currentIndexChanged(int index);

    void on_recSamRateBox_currentIndexChanged(int index);

    void on_bttnAudioRec_released();

    void on_bttnAudioPlay_released();

    void on_actionExit_triggered();

    void on_actionRecord_Audio_triggered();

    void on_actionPlay_Audio_triggered();

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void disableCtrls();
    void enableCtrls();
    void startRecording();
    void startPlayback();
};

#endif // MAINWINDOW_H
