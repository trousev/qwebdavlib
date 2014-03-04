
QT += core xml
INCLUDEPATH+=$$PWD

SOURCES += $$PWD/qwebdav.cpp \
    $$PWD/qwebdavitem.cpp \
    $$PWD/qwebdavdirparser.cpp \
    $$PWD/qnaturalsort.cpp \
    $$PWD/qwebdavobject.cpp

HEADERS += $$PWD/qwebdav.h \
    $$PWD/qwebdavitem.h \
    $$PWD/qwebdavdirparser.h \
    $$PWD/qnaturalsort.h \
    $$PWD/qwebdav_global.h \
    $$PWD/qwebdavobject.h


# Enable DEBUG output with qDebug()
# DEFINES += DEBUG_WEBDAV

# Enable extended WebDAV properties (see QWebDavItem.h/cpp)
#DEFINES += QWEBDAVITEM_EXTENDED_PROPERTIES

# DO NOT REMOVE - REQUIRED BY qwebdav_global.h
DEFINES += QWEBDAV_LIBRARY

