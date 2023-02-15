QT += gui opengl widgets
CONFIG += debug c++11


equals(QT_MAJOR_VERSION, 6) {
    QT += openglwidgets
}

SOURCES += \
    geometry.cpp \
    main.cpp \
    glwidget.cpp \
    glslprogram.cpp \
    primitives.cpp \
    texture2d.cpp \
    utils.cpp

HEADERS += \
    geometry.h \
    glwidget.h \
    glslprogram.h \
    primitives.h \
    texture2d.h \
    utils.h

unix {
    LIBS += -lGLU
}

win32 {
    LIBS += -lglu32 -lopengl32
}

DISTFILES += \
    basic.frag \
    basic.vert \
    shaders/basic.frag \
    shaders/basic.vert \
    shaders/billboard.frag \
    shaders/billboard.vert \
    shaders/billboard_xyz.frag \
    shaders/billboard_xyz.vert \
    shaders/tex_basic.frag \
    shaders/tex_basic.vert \
    tex_basic.frag \
    tex_basic.vert
