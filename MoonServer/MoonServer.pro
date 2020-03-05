TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        actor.cpp \
        actorbroker.cpp \
    advert.cpp \
    advertbroker.cpp \
        audience.cpp \
        collection.cpp \
        comic.cpp \
        comment.cpp \
        director.cpp \
        directorbroker.cpp \
        drama.cpp \
        film.cpp \
    manager.cpp \
    managerbroker.cpp \
        movieandtelevision.cpp \
        movieandtelevisionbroker.cpp \
        browseandwatchcontroller.cpp \
        controllerfactory.cpp \
managercontroller.cpp \
        main.cpp \
        network.cpp \
        record.cpp \
        server.cpp \
        threadpool.cpp \
        variety.cpp\
        audiencebroker.cpp \
        audiencecontroller.cpp \
        commentbroker.cpp \
        commentcontroller.cpp \

LIBS += -lboost_system -lpthread -lboost_thread -lmysqlclient

HEADERS += \
    actor.h \
    actorbroker.h \
    advert.h \
    advertbroker.h \
    audience.h \
    collection.h \
    comic.h \
    comment.h \
    director.h \
    directorbroker.h \
    drama.h \
    film.h \
    manager.h \
    managerbroker.h \
    managercontroller.h \
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
    audiencebroker.h \
    audiencecontroller.h \
    commentbroker.h \
    commentcontroller.h \
    variety.h
