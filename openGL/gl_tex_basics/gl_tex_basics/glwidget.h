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

#include "utils.h"
#include "mathgl.h"
#include "glslprogram.h"
#include "geometry.h"
#include "texture2d.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    QMap<QString, GLSLProgram*> shaders;
    QMap<QString, Geometry*> geometry;
    QMap<QString, Texture2D*> textures;
    QMap<QString, glm::mat4> geometryMat;

    glm::mat4 viewMat;
//    glm::mat4 ProjMat;

    float earth_orbit_angle;
    float earth_mid_rotate;

    QTimer frame_timer;
    int frame;

    void createShaders();
    void createGeometry();
    void createTextures();

    int pos_x, pos_y;
    float zoom;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public:
    GLWidget();
};


#endif // GLWIDGET_H
