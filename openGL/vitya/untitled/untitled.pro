QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    builder.cpp\
    camera.cpp\
    frame.cpp\
    geometry.cpp\
    glslprogram.cpp\
    glwidget.cpp\
    stb_image.cpp\
    texture2d.cpp\

HEADERS += \
builder.h\
camera.h\
frame.h\
geometry.h\
glslprogram.h\
glwidget.h\
stb_image.h\
texture2d.h\
mathgl.h

DISTFILES += \
    textures/clouds.png  \
    textures/earth.jpg \
    textures/grass.jpg \
    textures/lenna.png \
    textures/metal_1.jpg \
    textures/metal_2.jpg \
    textures/moon.jpg \
    textures/wood.jpg \
    shaders/ads.shader \
    shaders/ads_per_fragment.shader \
    shaders/base.shader \
    shaders/one_texture.shader


FORMS +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
