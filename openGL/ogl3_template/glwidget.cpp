#include "glwidget.h"
#include <QFile>
#include <QTextStream>


GLWidget::GLWidget() { }


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // program shadera
    prog = new GLSLProgram();
//    prog->compileShaderFromString("stirng_vertex sh",GL_VERTEX_SHADER);
//    prog->compileShaderFromString("stirng_fragment sh",GL_FRAGMENT_SHADER);
    prog->compileShaderFromFile("C:\\Users\\KirVin\\Downloads\\ogl3_template\\ogl3_template\\vshader.glsl",GL_VERTEX_SHADER);
    prog->compileShaderFromFile("C:\\Users\\KirVin\\Downloads\\ogl3_template\\ogl3_template\\fshader.glsl",GL_FRAGMENT_SHADER);
    prog->link();

    // jakas geometria
    axes = new Geometry();
    axes->primitiveMode = GL_LINES;
    vec3 verts[] = { {0,0,0}, {0.5,0,0}, {0,0,0}, {0,0.5,0}, {0,0,0}, {0,0,0.5} };
    vec3 colors[] = { {1,0,0}, {1,0,0},   {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1} };
    axes->setVertices(0, verts, 6);
    axes->setAttribute(1, colors, 6);


    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    PRINT_GL_ERRORS("Widget::paintGL(): ");

    prog->use();
    prog->setUniform("MVMat", MVMat);
    axes->render();
}




