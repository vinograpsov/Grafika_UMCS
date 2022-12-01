#include "glwidget.h"
#include <QFile>
#include <QTextStream>
#include<QTimer>
inline void PRINT_GL_ERRORS(const char* mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR) { qDebug() << "ERROR in: " << mess << (const char*)gluErrorString(err); }
}

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
    glm::vec3 verts[] = { {0,0,0}, {0.5,0,0}, {0,0,0}, {0,0.5,0}, {0,0,0}, {0,0,0.5},  {0.5,0,0}, {0.5,0.5,0}, {0,0.5,0}, {0.5,0.5,0}};
    glm::vec3 colors[] = { {1,0,0}, {1,0,0},   {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1},   {1,0,0}, {1,0,0},   {0,1,0}, {0,1,0} };
    axes->setVertices(0, verts, 10);
    axes->setAttribute(1, colors, 10);

    rectangle = new Geometry();
    rectangle->primitiveMode = GL_TRIANGLES;
    glm::vec3 verts_2[] ={{-0.2,-0.2,0.0},{0.2,-0.2,0.0},{0.2,0.2,0.0},
                    {-0.2,-0.2,0.0},{0.2,0.2,0.0},{-0.2,0.2,0.0}};
    glm::vec3 colors_2[] ={{1,0,0},{1,1,0},{1,0,1},
                    {1,0,1},{1,1,0},{1,1,0}};
    rectangle->setVertices(0,verts_2,6);
    rectangle->setAttribute(1,colors_2,6);


//    MVMat = identity();
    MVMat = glm::mat4(1.0);

//    PRINT_GL_ERRORS("Widget::initializeGL(): ");


    timer.setInterval(16);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
//    PRINT_GL_ERRORS("Widget::paintGL(): ");

    prog->use();
    MVMat = glm::rotate<float>(MVMat,0.01,glm::vec3(0,1,0));
    prog->setUniform("MVMat", MVMat);
    axes->render();
    rectangle->render();
}




