include(../../configs/config.pri)
include(../../configs/stdlibcpp.pri)

TEMPLATE = lib

CONFIG += staticlib

HEADERS = api.h \
          client.h

SOURCES = api.cc \
          client.cc \
          ../base.cc

INCLUDEPATH += ../../external/zmq/include

LIBS += -L./zmq_stdlibcpp -lzmq_stdlibcpp

lib.depends = zmq_stdlibcpp
