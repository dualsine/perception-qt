include(configs/config.pri)

TEMPLATE = subdirs
CONFIG += ordered c++14
SUBDIRS = signals \
          signals/client_stdlibcpp \
          signals/client_stdlibcpp/zmq_stdlibcpp \
          main
app.depends = signals signals_client_stdlibcpp
