#include "glwidget.h"
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>

#include "primitives.h"

GLWidget::GLWidget()
{
    frame = 0;
    pos_x = pos_y = 0;
    zoom = 1.0f;
    earth_orbit_angle = 0.0f;
    earth_mid_rotate = 0.0f;

    float moon_orbit_angle = 0.0f;
    float moon_mid_rotate = 0.0f;
}

void GLWidget::createShaders()
{
    bool stat;

    shaders["basic"] = new GLSLProgram;
    stat = shaders["basic"]->compileShaderFromFile("F://uniwesitet//5 сем//grafika//openGL//gl_tex_basics//gl_tex_basics//shaders//basic.vert", GL_VERTEX_SHADER);
    stat &= shaders["basic"]->compileShaderFromFile("F://uniwesitet//5 сем//grafika//openGL//gl_tex_basics//gl_tex_basics//shaders//basic.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["basic"]->link();
    if (!stat) qFatal("Some problem with shader!");

    shaders["tex"] = new GLSLProgram;
    stat = shaders["tex"]->compileShaderFromFile("F://uniwesitet//5 сем//grafika//openGL//gl_tex_basics//gl_tex_basics//shaders//tex_basic.vert", GL_VERTEX_SHADER);
    stat &= shaders["tex"]->compileShaderFromFile("F://uniwesitet//5 сем//grafika//openGL//gl_tex_basics//gl_tex_basics//shaders//tex_basic.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["tex"]->link();
    if (!stat) qFatal("Some problem with shader!");
}

void GLWidget::createGeometry()
{
    geometry["main_axes"] = createAxesGeometry();
    geometryMat["main_axes"] = glm::mat4(1.0);

    geometry["earth"] = createPlaneGeometry({1,1}, {1,1,1});
    glm::vec2 plane_uv[] = { {0,0}, {0,1}, {1,1}, {1,0}};
    geometry["earth"]->setAttribute((int)Attributes::uv1, plane_uv, 4);
    geometryMat["earth"] = glm::mat4(1.0);


}

void GLWidget::createTextures()
{
    bool stat;
    textures["wood"] = new Texture2D();
    stat = textures["wood"]->loadFromFile("C://Users//KirVin//Downloads//473e6d822792f08471715322110d5570.jpg");
    if (!stat) qFatal("Some problem with texture!");
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    createShaders();
    createGeometry();
    createTextures();

    connect(&frame_timer, SIGNAL(timeout()), this, SLOT(update()));
    frame_timer.setInterval(10);
    frame_timer.start();
    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    pos_x = e->x();
    pos_y = e->y();
}

void GLWidget::wheelEvent(QWheelEvent *e)
{
    zoom += e->angleDelta().y()/10000.0f;
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    glm::mat4 identity = glm::mat4(1.0);
    viewMat = glm::mat4(1.0);

    viewMat = viewMat * glm::scale(identity, glm::vec3(zoom,zoom,zoom));
    viewMat = viewMat * glm::rotate(identity,pos_y/100.0f, glm::vec3(1.0f ,0.0f , 0.0f));
    viewMat = viewMat * glm::rotate(identity,pos_x/100.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    shaders["basic"]->use();
    shaders["basic"]->setUniform("MVMat", viewMat);
    geometry["main_axes"]->render();

    int tex_unit = 2;
    textures["wood"]->bind(tex_unit);
    shaders["tex"]->use();

    geometryMat["earth"] = glm::rotate(identity, earth_orbit_angle,glm::vec3(0.0f,0.0f,1.0f));

    glm::mat4 R_orb = glm::rotate(identity, earth_orbit_angle,glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4 T = glm::translate(identity,glm::vec3(1.0f,0.0f,0.0f));
    glm::mat4 R_orb_rev = glm::rotate(identity, -earth_orbit_angle,glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4 R_rot = glm::rotate(identity, earth_mid_rotate,glm::vec3(0.0f,0.0f,1.0f));


    geometryMat["earth"] = R_orb * T * R_orb_rev * R_rot;

    glm::mat4 mvMat = viewMat * geometryMat["earth"];
    shaders["tex"]->setUniform("MVMat", mvMat);
    shaders["tex"]->setUniform("SamplerTex", tex_unit);
    geometry["earth"]->render();

// ------------------------------------------------------ mooon
    geometryMat["moon"] = identity;
    shaders["tex"]->setUniform("MVMat",glm::mat4(1.0));


    viewMat_moon = glm::mat4(1.0);

    viewMat_moon = viewMat_moon * glm::scale(identity, glm::vec3(zoom,zoom,zoom));
    viewMat_moon = viewMat_moon * glm::rotate(identity,pos_y/100.0f, glm::vec3(1.0f ,0.0f , 0.0f));
    viewMat_moon = viewMat_moon * glm::rotate(identity,pos_x/100.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    shaders["basic"]->use();
    shaders["basic"]->setUniform("MVMat", viewMat_moon);
    geometry["main_axes"]->render();

    textures["wood"]->bind(2);
    shaders["tex"]->use();




//    geometryMat["moon"] = glm::rotate(identity, earth_orbit_angle,glm::vec3(0.0f,0.0f,1.0f));

//    glm::mat4 R_orb_moon = glm::rotate(identity, earth_orbit_angle,glm::vec3(0.0f,0.0f,1.0f));
//    glm::mat4 T_moon = glm::translate(identity,glm::vec3(1.0f,0.0f,0.0f));
//    glm::mat4 R_orb_rev_moon = glm::rotate(identity, -earth_orbit_angle,glm::vec3(0.0f,0.0f,1.0f));


//    glm::mat4 R_rot_moon = glm::rotate(identity, moon_mid_rotate,glm::vec3(0.0f,0.0f,1.0f));
//    glm::mat4 T_rot_moon = glm::translate(identity,glm::vec3(1.0f,0.0f,0.0f));


//    geometryMat["moon"] = R_orb_moon * T_moon * R_orb_rev_moon * R_rot_moon * T_rot_moon;

//    glm::mat4 mvMat_moon = viewMat * geometryMat["earth"];
//    shaders["tex"]->setUniform("MVMat", mvMat);
//    shaders["tex"]->setUniform("SamplerTex", tex_unit);


    geometry["earth"]->render();


    frame++;
    PRINT_GL_ERRORS("Widget::paintGL(): ");

    earth_orbit_angle += 0.01;
    earth_mid_rotate += 0.1;

    float moon_orbit_angle = 0.1f;
    float moon_mid_rotate = 0.1f;

}


