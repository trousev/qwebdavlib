QT       += core network xml
win32:{
    PRE_TARGETDEPS += $$PWD/lib/libqwebdav.a
    INCLUDEPATH += $$PWD/qwebdavlib/
    LIBS += -L$$PWD/lib/ -lqwebdav
} else {
    INCLUDEPATH += $$OUT_PWD/../qwebdavlib/
    LIBS += -L$$PWD/lib/ -lqwebdav
}
