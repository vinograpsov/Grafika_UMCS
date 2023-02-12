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
    utils.cpp

HEADERS += \
    geometry.h \
    glwidget.h \
    glslprogram.h \
    primitives.h \
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
    shaders/ads.frag \
    shaders/ads.vert \
    shaders/ads_per_fragment.frag \
    shaders/ads_per_fragment.vert \
    shaders/basic.frag \
    shaders/basic.vert \
    tex_basic.frag \
    tex_basic.vert
