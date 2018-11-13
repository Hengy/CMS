#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QString>

#include "sound.h"
#include <stdio.h>
#include <windows.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
