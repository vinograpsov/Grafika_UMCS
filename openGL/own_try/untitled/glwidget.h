#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>

#include <QOpenGLFunctions>
#include <QMap>
#include <QTimer>

#include "utils.h"
#include "glslprogram.h"
#include "geometry.h"
#include "texture2d.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    QMap<QString, GLSLProgram*> shaders;
    QMap<QString, Geometry*> geometry;
    QMap<QString, Texture2D*> textures;
    QMap<QString, glm::mat4> geometryMat;
    QMap<QString, Frame> frames;

    glm::mat4 viewMat;
    glm::mat4 projMat;

    Camera mainCamera;
    QSet<int> keys;

    QTimer frame_timer;
    int frame;

    float earth_obrit_angle, earth_rotate_angle;

    void createShaders();
    void createGeometry();
    void createTextures();

    void processCamera();

    QPoint mouse_press_pos;
    QPoint mouse_move_pos;
    int pos_x, pos_y;
    float zoom;

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
