QT += widgets svg
qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

HEADERS += \
    src/icon.h \
    src/vectah.h \
    src/view.h

SOURCES += \
    src/icon.cpp \
    src/main.cpp \
    src/vectah.cpp \
    src/view.cpp

