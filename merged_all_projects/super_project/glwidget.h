#ifndef GLWIDGET_H
#define GLWIDGET_H

#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif

#include <QOpenGLFunctions_4_5_Core>
#include <QMap>
#include <QTimer>
#include <QSet>

#include "utils.h"
#include "glslprogram.h"
#include "geometry.h"
#include "texture2d.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    QMap<QString, GLSLProgram*> shaders;
    QMap<QString, Geometry*> geometry;
    QMap<QString, glm::mat4> geometryMat;
    QMap<QString, Frame> frames;

    glm::mat4 viewMat;
    glm::mat4 projMat;
    glm::mat4 Identity;

    Camera mainCamera;
    QSet<int> keys;

    float earth_obrit_angle, earth_rotate_angle, moon_rotate_angle;

    QTimer frame_timer;
    int frame;

    void createShaders();
    void createGeometry();
    void createTextures();

    int pos_x, pos_y;
    QPoint mouse_press_pos;
    QPoint mouse_move_pos;
    float zoom;

    void processCamera();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

public:
    GLWidget();
};


#endif // GLWIDGET_H
