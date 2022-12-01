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


#include "mathgl.h"


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    GLSLProgram* prog;
    Geometry* axes;

    mat4 MVMat;
    mat4 ProjMat;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public:
    GLWidget();
};


#endif // GLWIDGET_H
