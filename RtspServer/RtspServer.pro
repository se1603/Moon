TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        datasource.cpp \
        main.cpp \
        rtspserver.cpp \
        rtspsession.cpp \
        socket.cpp \
        tcpsocket.cpp \
        threadpool.cpp \
        tsfilereader.cpp \
        tsparse.cpp \
        udpsocket.cpp

HEADERS += \
    datasource.h \
    rtspserver.h \
    rtspsession.h \
    socket.h \
    tcpsocket.h \
    threadpool.h \
    tsfilereader.h \
    tsparse.h \
    udpsocket.h

LIBS += -lpthread
