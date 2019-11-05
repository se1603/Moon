TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        network.cpp \
        server.cpp \
        threadpool.cpp

LIBS += -lboost_system -lpthread -lboost_thread -lmysqlclient

HEADERS += \
    network.h \
    server.h \
    threadpool.h
