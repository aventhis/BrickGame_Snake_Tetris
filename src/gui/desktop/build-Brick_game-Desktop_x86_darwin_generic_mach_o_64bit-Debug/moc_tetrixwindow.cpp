/****************************************************************************
** Meta object code from reading C++ file 'tetrixwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qmetatype.h>
#include <QtGui/qscreen.h>
#include <QtGui/qtextcursor.h>

#include "../Brick_game/tetrixwindow.h"

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif

#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tetrixwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS =
    QtMocHelpers::stringData("s21::TetrixWindow");
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS_t {
  uint offsetsAndSizes[2];
  char stringdata0[18];
};
#define QT_MOC_LITERAL(ofs, len)                                       \
  uint(sizeof(qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS_t:: \
                  offsetsAndSizes) +                                   \
       ofs),                                                           \
      len
Q_CONSTINIT static const qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS_t
    qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS = {
        {
            QT_MOC_LITERAL(0, 17)  // "s21::TetrixWindow"
        },
        "s21::TetrixWindow"};
#undef QT_MOC_LITERAL
#endif  // !QT_MOC_HAS_STRING_DATA
}  // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSs21SCOPETetrixWindowENDCLASS[] =
    {

        // content:
        12,     // revision
        0,      // classname
        0,  0,  // classinfo
        0,  0,  // methods
        0,  0,  // properties
        0,  0,  // enums/sets
        0,  0,  // constructors
        0,      // flags
        0,      // signalCount

        0  // eod
};

Q_CONSTINIT const QMetaObject s21::TetrixWindow::staticMetaObject = {
    {QMetaObject::SuperData::link<GameWindow::staticMetaObject>(),
     qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS.offsetsAndSizes,
     qt_meta_data_CLASSs21SCOPETetrixWindowENDCLASS, qt_static_metacall,
     nullptr,
     qt_incomplete_metaTypeArray<
         qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS_t,
         // Q_OBJECT / Q_GADGET
         QtPrivate::TypeAndForceComplete<TetrixWindow, std::true_type> >,
     nullptr}};

void s21::TetrixWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c,
                                           int _id, void **_a) {
  (void)_o;
  (void)_id;
  (void)_c;
  (void)_a;
}

const QMetaObject *s21::TetrixWindow::metaObject() const {
  return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                    : &staticMetaObject;
}

void *s21::TetrixWindow::qt_metacast(const char *_clname) {
  if (!_clname) return nullptr;
  if (!strcmp(_clname,
              qt_meta_stringdata_CLASSs21SCOPETetrixWindowENDCLASS.stringdata0))
    return static_cast<void *>(this);
  return GameWindow::qt_metacast(_clname);
}

int s21::TetrixWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a) {
  _id = GameWindow::qt_metacall(_c, _id, _a);
  return _id;
}
QT_WARNING_POP
