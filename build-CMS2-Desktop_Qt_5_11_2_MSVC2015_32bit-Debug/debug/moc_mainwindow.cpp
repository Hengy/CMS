/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CMS2/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[45];
    char stringdata0[869];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "openSerialPort"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "handleError"
QT_MOC_LITERAL(4, 39, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(5, 68, 5), // "error"
QT_MOC_LITERAL(6, 74, 11), // "refreshList"
QT_MOC_LITERAL(7, 86, 8), // "checksum"
QT_MOC_LITERAL(8, 95, 14), // "unsigned char*"
QT_MOC_LITERAL(9, 110, 6), // "size_t"
QT_MOC_LITERAL(10, 117, 12), // "createHeader"
QT_MOC_LITERAL(11, 130, 7), // "Header*"
QT_MOC_LITERAL(12, 138, 4), // "Msg*"
QT_MOC_LITERAL(13, 143, 3), // "pri"
QT_MOC_LITERAL(14, 147, 3), // "rID"
QT_MOC_LITERAL(15, 151, 3), // "sID"
QT_MOC_LITERAL(16, 155, 9), // "writeData"
QT_MOC_LITERAL(17, 165, 8), // "readData"
QT_MOC_LITERAL(18, 174, 11), // "const char*"
QT_MOC_LITERAL(19, 186, 15), // "closeSerialPort"
QT_MOC_LITERAL(20, 202, 19), // "on_radioRec_clicked"
QT_MOC_LITERAL(21, 222, 20), // "on_radioHome_clicked"
QT_MOC_LITERAL(22, 243, 28), // "on_recLenSlider_valueChanged"
QT_MOC_LITERAL(23, 272, 5), // "value"
QT_MOC_LITERAL(24, 278, 36), // "on_recBitrateBox_currentIndex..."
QT_MOC_LITERAL(25, 315, 5), // "index"
QT_MOC_LITERAL(26, 321, 36), // "on_recSamRateBox_currentIndex..."
QT_MOC_LITERAL(27, 358, 24), // "on_bttnAudioRec_released"
QT_MOC_LITERAL(28, 383, 25), // "on_bttnAudioPlay_released"
QT_MOC_LITERAL(29, 409, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(30, 433, 31), // "on_actionRecord_Audio_triggered"
QT_MOC_LITERAL(31, 465, 29), // "on_actionPlay_Audio_triggered"
QT_MOC_LITERAL(32, 495, 38), // "on_baudrateDropbox_currentInd..."
QT_MOC_LITERAL(33, 534, 24), // "on_bttnAudioDel_released"
QT_MOC_LITERAL(34, 559, 40), // "on_serialPortDropbox_currentI..."
QT_MOC_LITERAL(35, 600, 24), // "on_bttnSaveText_released"
QT_MOC_LITERAL(36, 625, 23), // "on_bttnSendMsg_released"
QT_MOC_LITERAL(37, 649, 32), // "on_sendRecList_currentRowChanged"
QT_MOC_LITERAL(38, 682, 10), // "currentRow"
QT_MOC_LITERAL(39, 693, 25), // "on_actionTest_1_triggered"
QT_MOC_LITERAL(40, 719, 37), // "on_timeoutDropbox_currentInde..."
QT_MOC_LITERAL(41, 757, 28), // "on_IDBox_currentIndexChanged"
QT_MOC_LITERAL(42, 786, 27), // "on_actionBER_Test_triggered"
QT_MOC_LITERAL(43, 814, 26), // "on_priRadioButton_released"
QT_MOC_LITERAL(44, 841, 27) // "on_timeRadioButton_released"

    },
    "MainWindow\0openSerialPort\0\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "refreshList\0checksum\0unsigned char*\0"
    "size_t\0createHeader\0Header*\0Msg*\0pri\0"
    "rID\0sID\0writeData\0readData\0const char*\0"
    "closeSerialPort\0on_radioRec_clicked\0"
    "on_radioHome_clicked\0on_recLenSlider_valueChanged\0"
    "value\0on_recBitrateBox_currentIndexChanged\0"
    "index\0on_recSamRateBox_currentIndexChanged\0"
    "on_bttnAudioRec_released\0"
    "on_bttnAudioPlay_released\0"
    "on_actionExit_triggered\0"
    "on_actionRecord_Audio_triggered\0"
    "on_actionPlay_Audio_triggered\0"
    "on_baudrateDropbox_currentIndexChanged\0"
    "on_bttnAudioDel_released\0"
    "on_serialPortDropbox_currentIndexChanged\0"
    "on_bttnSaveText_released\0"
    "on_bttnSendMsg_released\0"
    "on_sendRecList_currentRowChanged\0"
    "currentRow\0on_actionTest_1_triggered\0"
    "on_timeoutDropbox_currentIndexChanged\0"
    "on_IDBox_currentIndexChanged\0"
    "on_actionBER_Test_triggered\0"
    "on_priRadioButton_released\0"
    "on_timeRadioButton_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  164,    2, 0x08 /* Private */,
       3,    1,  165,    2, 0x08 /* Private */,
       6,    0,  168,    2, 0x08 /* Private */,
       7,    2,  169,    2, 0x08 /* Private */,
      10,    4,  174,    2, 0x08 /* Private */,
      16,    1,  183,    2, 0x08 /* Private */,
      17,    0,  186,    2, 0x08 /* Private */,
      19,    0,  187,    2, 0x08 /* Private */,
      20,    0,  188,    2, 0x08 /* Private */,
      21,    0,  189,    2, 0x08 /* Private */,
      22,    1,  190,    2, 0x08 /* Private */,
      24,    1,  193,    2, 0x08 /* Private */,
      26,    1,  196,    2, 0x08 /* Private */,
      27,    0,  199,    2, 0x08 /* Private */,
      28,    0,  200,    2, 0x08 /* Private */,
      29,    0,  201,    2, 0x08 /* Private */,
      30,    0,  202,    2, 0x08 /* Private */,
      31,    0,  203,    2, 0x08 /* Private */,
      32,    1,  204,    2, 0x08 /* Private */,
      33,    0,  207,    2, 0x08 /* Private */,
      34,    1,  208,    2, 0x08 /* Private */,
      35,    0,  211,    2, 0x08 /* Private */,
      36,    0,  212,    2, 0x08 /* Private */,
      37,    1,  213,    2, 0x08 /* Private */,
      39,    0,  216,    2, 0x08 /* Private */,
      40,    1,  217,    2, 0x08 /* Private */,
      41,    1,  220,    2, 0x08 /* Private */,
      42,    0,  223,    2, 0x08 /* Private */,
      43,    0,  224,    2, 0x08 /* Private */,
      44,    0,  225,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::UChar, 0x80000000 | 8, 0x80000000 | 9,    2,    2,
    0x80000000 | 11, 0x80000000 | 12, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,    2,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 12,    2,
    0x80000000 | 18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->openSerialPort();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 2: _t->refreshList(); break;
        case 3: { unsigned char _r = _t->checksum((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< unsigned char*>(_a[0]) = std::move(_r); }  break;
        case 4: { Header* _r = _t->createHeader((*reinterpret_cast< Msg*(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3])),(*reinterpret_cast< unsigned char(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< Header**>(_a[0]) = std::move(_r); }  break;
        case 5: _t->writeData((*reinterpret_cast< Msg*(*)>(_a[1]))); break;
        case 6: { const char* _r = _t->readData();
            if (_a[0]) *reinterpret_cast< const char**>(_a[0]) = std::move(_r); }  break;
        case 7: _t->closeSerialPort(); break;
        case 8: _t->on_radioRec_clicked(); break;
        case 9: _t->on_radioHome_clicked(); break;
        case 10: _t->on_recLenSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_recBitrateBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_recSamRateBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_bttnAudioRec_released(); break;
        case 14: _t->on_bttnAudioPlay_released(); break;
        case 15: _t->on_actionExit_triggered(); break;
        case 16: _t->on_actionRecord_Audio_triggered(); break;
        case 17: _t->on_actionPlay_Audio_triggered(); break;
        case 18: _t->on_baudrateDropbox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_bttnAudioDel_released(); break;
        case 20: _t->on_serialPortDropbox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_bttnSaveText_released(); break;
        case 22: _t->on_bttnSendMsg_released(); break;
        case 23: _t->on_sendRecList_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_actionTest_1_triggered(); break;
        case 25: _t->on_timeoutDropbox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_IDBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_actionBER_Test_triggered(); break;
        case 28: _t->on_priRadioButton_released(); break;
        case 29: _t->on_timeRadioButton_released(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
