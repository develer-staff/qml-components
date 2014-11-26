TEMPLATE = lib
TARGET = libcharts
QT += qml quick
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.develer.libcharts

# Input
SOURCES += \
    libcharts_plugin.cpp \
    libcharts.cpp

HEADERS += \
    libcharts_plugin.h \
    libcharts.h

OTHER_FILES = qmldir

QMAKE_CXXFLAGS += -fwrapv

TARGET_DIR = $$OUT_PWD/com/develer/libcharts
TARGET_LIBRARY = $$OUT_PWD/liblibcharts.so
QMLDIR_TARGET = $$_PRO_FILE_PWD_/qmldir
QMAKE_PRE_LINK += $(DEL_FILE) \"$$replace(TARGET_LIBRARY, /, $$QMAKE_DIR_SEP)\" \"$$replace(TARGET_DIR, /, $$QMAKE_DIR_SEP)\";
QMAKE_PRE_LINK += \"$$replace(QMLDIR_TARGET, /, $$QMAKE_DIR_SEP)\" \"$$replace(TARGET_DIR, /, $$QMAKE_DIR_SEP)\";
QMAKE_POST_LINK += $(MKDIR) $${TARGET_DIR};
QMAKE_POST_LINK += $(COPY_FILE) \"$$replace(TARGET_LIBRARY, /, $$QMAKE_DIR_SEP)\" \"$$replace(TARGET_DIR, /, $$QMAKE_DIR_SEP)\";
QMAKE_POST_LINK += $(COPY_FILE) \"$$replace(QMLDIR_TARGET, /, $$QMAKE_DIR_SEP)\" \"$$replace(TARGET_DIR, /, $$QMAKE_DIR_SEP)\";

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

