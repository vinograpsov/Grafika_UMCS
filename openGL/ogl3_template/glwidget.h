#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "glslprogram.h"
#include "geometry.h"

#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif

#include <QOpenGLFunctions_4_5_Core>
#include <QMap>
#include<QTimer>

//#include "mathgl.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    GLSLProgram* prog;
    Geometry* axes;
    Geometry* rectangle;

    QTimer timer;

    glm::mat4 MVMat;
    glm::mat4 ProjMat;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public:
    GLWidget();
};


#endif // GLWIDGET_H
