TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        actor.cpp \
        actorbroker.cpp \
        comic.cpp \
        director.cpp \
        directorbroker.cpp \
        drama.cpp \
        film.cpp \
        movieandtelevision.cpp \
        movieandtelevisionbroker.cpp \
        browseandwatchcontroller.cpp \
        controllerfactory.cpp \
        main.cpp \
        network.cpp \
        server.cpp \
        threadpool.cpp \
        variety.cpp

LIBS += -lboost_system -lpthread -lboost_thread -lmysqlclient

HEADERS += \
    actor.h \
    actorbroker.h \
    comic.h \
    director.h \
    directorbroker.h \
    drama.h \
    film.h \
    movieandtelevision.h \
    movieandtelevisionbroker.h \
    browseandwatchcontroller.h \
    controller.h \
    controllerfactory.h \
    network.h \
    region.h \
    relationalbroker.h \
    server.h \
    threadpool.h \
    variety.h
