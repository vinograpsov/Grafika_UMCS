QT += gui opengl widgets
CONFIG += debug c++11


equals(QT_MAJOR_VERSION, 6) {
    QT += openglwidgets
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    geometry.cpp \
    glslprogram.cpp \
    glwidget.cpp \
    main.cpp \
    primitives.cpp \
    texture2d.cpp \
    utils.cpp

HEADERS += \
    geometry.h \
    glslprogram.h \
    glwidget.h \
    primitives.h \
    texture2d.h \
    utils.h

unix {
    LIBS += -lGLU
}

win32 {
    LIBS += -lglu32 -lopengl32
}

FORMS +=

