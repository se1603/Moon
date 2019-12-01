TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        actor.cpp \
        actorbroker.cpp \
        audience.cpp \
        audiencebroker.cpp \
        audiencecontroller.cpp \
        collection.cpp \
        comic.cpp \
        comment.cpp \
        commentbroker.cpp \
        commentcontroller.cpp \
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
        record.cpp \
        server.cpp \
        threadpool.cpp \
        variety.cpp

LIBS += -lboost_system -lpthread -lboost_thread -lmysqlclient

HEADERS += \
    actor.h \
    actorbroker.h \
    audience.h \
    audiencebroker.h \
    audiencecontroller.h \
    collection.h \
    comic.h \
    comment.h \
    commentbroker.h \
    commentcontroller.h \
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
    record.h \
    region.h \
    relationalbroker.h \
    server.h \
    threadpool.h \
    variety.h
