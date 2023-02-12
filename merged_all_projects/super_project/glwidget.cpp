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

    Identity = glm::mat4(1.0);
    earth_obrit_angle = 0.0f;
    moon_rotate_angle = 0.0f;

    mainCamera.pos = glm::vec3(0,0,2);
    mouse_move_pos = QPoint(0,0);
}

void GLWidget::createShaders()
{
    bool stat;

    shaders["basic"] = new GLSLProgram;
    stat = shaders["basic"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/Compute shader/gl_math_frame/gl_math_frame/shaders/basic.vert", GL_VERTEX_SHADER);
    stat &= shaders["basic"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/Compute shader/gl_math_frame/gl_math_frame/shaders/basic.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["basic"]->link();
    if (!stat) qFatal("Some problem with shader!");


    shaders["ads"] = new GLSLProgram;
    stat = shaders["ads"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/Compute shader/gl_math_frame/gl_math_frame/shaders/ads.vert", GL_VERTEX_SHADER);
    stat &= shaders["ads"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/Compute shader/gl_math_frame/gl_math_frame/shaders/ads.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["ads"]->link();
    if (!stat) qFatal("Some problem with shader!");



    shaders["ads_per_fragment"] = new GLSLProgram;
    stat = shaders["ads_per_fragment"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/Compute shader/gl_math_frame/gl_math_frame/shaders/ads_per_fragment.vert", GL_VERTEX_SHADER);
    stat &= shaders["ads_per_fragment"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/Compute shader/gl_math_frame/gl_math_frame/shaders/ads_per_fragment.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["ads_per_fragment"]->link();
    if (!stat) qFatal("Some problem with shader!");
}

void GLWidget::createGeometry()
{
    geometry["main_axes"] = createAxesGeometry();
    geometryMat["main_axes"] = Identity;

    geometry["earth"] = createPlaneGeometry({1.1,1.1}, {0.1,0.5,1});

    glm::vec3 normals[] = {{0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1}};
    geometry["earth"]->setAttribute((int)Attributes::normal, normals, 4);


    geometryMat["earth"] = Identity;
    frames["earth"] = Frame();

    geometry["earth_axes"] = createAxesGeometry();
    geometryMat["earth_axes"] = Identity;

    geometry["moon"] = createPlaneGeometry({0.1,0.1}, {0.5,0.5,0.5});
    geometry["moon"]->setAttribute((int)Attributes::normal, normals, 4);

    geometryMat["moon"] = glm::scale(Identity, glm::vec3(0.25f,0.25f,0.25f));;

    geometry["moon_axes"] = createAxesGeometry();
    geometryMat["moon_axes"] = Identity;
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    createShaders();
    createGeometry();

    connect(&frame_timer, SIGNAL(timeout()), this, SLOT(update()));
    frame_timer.setInterval(10);
    frame_timer.start();
    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    float aspect = w/(float)h;
    //projMat = glm::ortho(-1*aspect, 1*aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    projMat = glm::perspective(30.0f, aspect, 0.1f, 10.0f);
}

void GLWidget::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
        mouse_press_pos = e->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        mouse_move_pos += mouse_press_pos - e->pos();
        mouse_press_pos = e->pos();
    }
}

void GLWidget::wheelEvent(QWheelEvent *e)
{
    zoom += e->angleDelta().y()/10000.0f;
}

void GLWidget::keyPressEvent(QKeyEvent* e)
{
    keys.insert(e->key());
}

void GLWidget::keyReleaseEvent(QKeyEvent* e)
{
    keys.remove(e->key());
}

void GLWidget::processCamera()
{
    float dv = 0.02;
    if(keys.contains(Qt::Key_W))
    {
        mainCamera.pos = mainCamera.pos + dv*mainCamera.forward;
    }
    if(keys.contains(Qt::Key_S))
    {
        mainCamera.pos = mainCamera.pos - dv*mainCamera.forward;
    }
    if(keys.contains(Qt::Key_A))
    {
        mainCamera.pos = mainCamera.pos + dv*mainCamera.s();
    }
    if(keys.contains(Qt::Key_D))
    {
        mainCamera.pos = mainCamera.pos - dv*mainCamera.s();
    }
    if(keys.contains(Qt::Key_C))
    {
        mainCamera.pos = mainCamera.pos + dv*mainCamera.up;
    }
    if(keys.contains(Qt::Key_Space))
    {
        mainCamera.pos = mainCamera.pos - dv*mainCamera.up;
    }

    glm::vec4 camera_init_forward = glm::normalize(glm::vec4(0,0,-1,1));
    mainCamera.forward = glm::rotate(Identity, mouse_move_pos.x()/100.0f, glm::vec3(0.0f,1.0f,0.0f)) * camera_init_forward;
    glm::vec3 sx = glm::normalize(mainCamera.s());
    mainCamera.forward = glm::rotate(Identity, mouse_move_pos.y()/100.0f, sx) * glm::vec4(mainCamera.forward,1.0f);
}

void GLWidget::paintGL()
{
    glClearColor(1,1,1,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 light_position(0,0,0);
    glm::vec4 light_color(1,1,1,1);

    glm::vec4 earth_color(0.1,0.6,1.0,1.0);
    glm::vec4 moon_color(0.5,0.5,0.5,1.0);



    processCamera();
    viewMat = mainCamera.matrix();

    glm::mat4 MVMat;


    //axes
    shaders["basic"]->use();
    shaders["basic"]->setUniform("MVMat", viewMat);
    shaders["basic"]->setUniform("ProjMat", projMat);
    geometry["main_axes"]->render();

    //earth
    shaders["ads_per_fragment"]->use();

    shaders["ads_per_fragment"]->setUniform("LightPosition",light_position);
    shaders["ads_per_fragment"]->setUniform("LightColor",light_color);
    shaders["ads_per_fragment"]->setUniform("MaterialColor",earth_color);




    glm::mat4 R_orb     = glm::rotate(Identity, earth_obrit_angle, glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4 R_rot     = glm::rotate(Identity, earth_rotate_angle, glm::vec3(0.0f,0.0f,1.0f));
    frames["earth"].pos = R_orb * glm::vec4(0.75,0.0,0.0,1.0);
    frames["earth"].up = R_rot * glm::vec4(0.0,1.0,0.0,1.0);
    MVMat = viewMat * frames["earth"].matrix() * geometryMat["earth"];
    shaders["ads_per_fragment"]->setUniform("MVMat", MVMat);
    shaders["ads_per_fragment"]->setUniform("ProjMat", projMat);

    geometry["earth"]->render();
    geometry["earth_axes"]->render();

//    //moon
//    glm::mat4 R_moon_rot = glm::rotate(Identity, moon_rotate_angle, glm::vec3(0.0f,0.0f,1.0f));
//    frames["moon"].pos = frames["earth"].pos + glm::vec3(R_moon_rot * glm::vec4(0.25,0.0,0.0,1.0));
//    frames["moon"].up = R_moon_rot * glm::vec4(0.0,1.0,0.0,1.0);
//    MVMat = viewMat * frames["moon"].matrix() * geometryMat["moon"];
//    shaders["ads"]->setUniform("MVMat", MVMat);

//    geometry["moon"]->render();
//    geometry["moon_axes"]->render();

    earth_obrit_angle  += glm::radians(0.01f);
    earth_rotate_angle += glm::radians(1.0f);
    moon_rotate_angle  += glm::radians(1.0f);

    frame++;
    PRINT_GL_ERRORS("Widget::paintGL(): ");
}




