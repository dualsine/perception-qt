include(../configs/config.pri)

system(cd $$_PRO_FILE_PWD_ && bash build_frontend.sh)

QT += core gui widgets
TARGET = perception
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += static

QMAKE_CXX = ccache g++

QMAKE_LFLAGS += -Wl,-rpath,"'\$$ORIGIN'"

QMAKE_CXXFLAGS += -Wno-padded -Wno-unused-parameter

RESOURCES = main.qrc

SOURCES += \
    src/main.cc \
    src/cef_code/bindings_qt/widget.cc \
    src/cef_code/bindings_qt/widget_linux.cc \
    src/cef_code/core.cc \
    src/cef_code/dev_tools_handler.cc \
    src/cef_code/client_handler.cc \
    src/qt_code/main_window.cc \
    src/qt_code/keyboard.cc \
    src/global_actions.cc \
    src/cef_code/internal_scheme.cc \
    src/qt_code/elements.cc \
    src/qt_code/qui/url_bar.cc \
    src/cef_code/blink_signals.cc \
    src/cef_code/app_class/app_renderer.cc \
    src/cef_code/app_class/app_browser.cc \
    src/cef_code/app_class/app_other.cc \
    src/cef_code/app_class/base_app.cc \
    src/perception/signals_server.cc \
    src/perception/config.cc

HEADERS  += \
    src/cef_code/bindings_qt/widget.h \
    src/cef_code/core.h \
    src/cef_code/dev_tools_handler.h \
    src/cef_code/client_handler.h \
    src/qt_code/main_window.h \
    src/qt_code/keyboard.h \
    src/global_actions.h \
    src/cef_code/internal_scheme.h \
    src/qt_code/elements.h \
    src/qt_code/qui/url_bar.h \
    src/keys_enum.h \
    src/cef_code/blink_signals.h \
    src/cef_code/app_class/app_renderer.h \
    src/cef_code/app_class/app_browser.h \
    src/cef_code/app_class/app_other.h \
    src/cef_code/app_class/base_app.h \
    src/perception/signals_server.h \
    src/perception/config.h

FORMS += src/qt_code/mainwindow.ui

INCLUDEPATH += . \
               $$LIBCEF_BUILD_PATH/include \
               $$LIBCEF_BUILD_PATH/include/cef

QMAKE_LIBDIR += $$LIBCEF_BUILD_PATH/libcef_dll_wrapper \
                $$LIBCEF_BUILD_PATH/Release

LIBS += $$quote(-L$$LIBCEF_BUILD_PATH) \
    -lcef\
    -lEGL\
    -lGLESv2\
    -lX11\
    -pthread\
    -L../signals -lsignals\
    $$LIBCEF_BUILD_PATH/libcef_dll_wrapper/libcef_dll_wrapper.a

PRE_TARGETDEPS += $$LIBCEF_BUILD_PATH/libcef_dll_wrapper/libcef_dll_wrapper.a

DEPENDPATH  += $$LIBCEF_BUILD_PATH/libcef_dll_wrapper
DEPENDPATH  += $$LIBCEF_BUILD_PATH/Release

#copy CEF dependencies to build directory
copy_cef_release.commands = $(COPY_DIR) $$LIBCEF_BUILD_PATH/Release/* $$OUT_PWD
copy_cef_resources.commands = $(COPY_DIR) $$LIBCEF_BUILD_PATH/Resources/* $$OUT_PWD
first.depends = $(first) copy_cef_release copy_cef_resources
export(first.depends)
export(copy_cef_release.commands)
export(copy_cef_resources.commands)
QMAKE_EXTRA_TARGETS += first copy_cef_release copy_cef_resources
