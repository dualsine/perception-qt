include(../configs/config.pri)

TEMPLATE = lib

CONFIG += staticlib

QMAKE_CXX = ccache g++

HEADERS = base.h \
          deserializator.h \
          events.h \
          observer.h \
          serializator.h \
          server.h \
          server_api.h \
          utils.h

SOURCES = base.cc \
          observer.cc \
          server.cc \
          server_api.cc

INCLUDEPATH += ../external/zmq/include

QMAKE_LIBDIR += ../external/zmq/lib

LIBS += -lzmq
