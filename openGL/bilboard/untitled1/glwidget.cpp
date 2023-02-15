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

    mainCamera.pos = glm::vec3(0,0,2);
    mouse_move_pos = QPoint(0,0);
    mouse_press_pos = QPoint(0,0);
}

void GLWidget::createShaders()
{
    bool stat;

    // --------------shader to drowing ax --------------
    shaders["basic"] = new GLSLProgram;
    stat = shaders["basic"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/basic.vert", GL_VERTEX_SHADER);
    stat &= shaders["basic"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/basic.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["basic"]->link();
    if (!stat) qFatal("Some problem with shader!");
    // --------------shader to drowing ax --------------

    // ------------- shader to billboard on xz rotation ------
    shaders["bilboard_xz"] = new GLSLProgram;
    stat = shaders["bilboard_xz"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/billboard.vert", GL_VERTEX_SHADER);
    stat &= shaders["bilboard_xz"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/billboard.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["bilboard_xz"]->link();
    if (!stat) qFatal("Some problem with shader!");
    // ------------- shader to billboard on xz rotation ------

    // ------------- shader to billboard on xyz rotation ------
    shaders["bilboard_xyz"] = new GLSLProgram;
    stat = shaders["bilboard_xyz"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/billboard_xyz.vert", GL_VERTEX_SHADER);
    stat &= shaders["bilboard_xyz"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/billboard_xyz.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["bilboard_xyz"]->link();
    if (!stat) qFatal("Some problem with shader!");
    // ------------- shader to billboard on xyz rotation ------

}

void GLWidget::createGeometry()
{

    // --- axis geometry ----
    geometry["main_axes"] = newAxesGeometry();
    geometryMat["main_axes"] = identity();
    // --- axis geometry ----


    // --- first_billboard geometry ----
    geometry["first_billboard"] = newPlaneGeometry({1,1}, {1,1,1});
    glm::vec2 plane_uv1[] = { {0,0}, {0,1}, {1,1}, {1,0}};
    geometry["first_billboard"]->setAttribute((int)Attributes::uv1, plane_uv1, 4);
    geometryMat["first_billboard"] = identity();
    // --- first_billboard geometry ----


    // --- second_billboard geometry ----
    geometry["second_billboard"] = newPlaneGeometry({1,1}, {1,1,1});
    glm::vec2 plane_uv2[] = { {0,0}, {0,1}, {1,1}, {1,0}};
    geometry["second_billboard"]->setAttribute((int)Attributes::uv1, plane_uv2, 4);
    geometryMat["second_billboard"] = identity();
    frames["second_billboard"] = Frame();
    // --- second_billboard geometry ----


}

void GLWidget::createTextures()
{

    bool stat;

    // ------------loading bart simpson texture--------------
    textures["bart"] = new Texture2D();
    stat = textures["bart"]->loadFromFile("C:/Users/KirVin/Downloads/pngimg.com - simpsons_PNG95.png");
    if (!stat) qFatal("Some problem with texture!");
    // ------------loading bart simpson texture---------------

    // ------------loading grass texture--------------
    textures["grass"] = new Texture2D();
    stat = textures["grass"]->loadFromFile("C:/Users/KirVin/Downloads/grass.png");
    if (!stat) qFatal("Some problem with texture!");
    // ------------loading grass texture---------------

    // ------------loading openglcaca texture--------------
    textures["openglcaca"] = new Texture2D();
    stat = textures["openglcaca"]->loadFromFile("C:/Users/KirVin/Downloads/openglcaca.png");
    if (!stat) qFatal("Some problem with texture!");
    // ------------loading openglcaca texture---------------

    // ------------loading openglpinky texture--------------
    textures["openglpinky"] = new Texture2D();
    stat = textures["openglpinky"]->loadFromFile("C:/Users/KirVin/Downloads/openglpinky.png");
    if (!stat) qFatal("Some problem with texture!");
    // ------------loading openglpinky texture---------------

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
    float aspect = w/(float)h;
    //projMat = glm::ortho(-1*aspect, 1*aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
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
    float dv = (keys.contains(Qt::Key_Shift) ? 0.2 : 0.02);

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
        mainCamera.pos = mainCamera.pos - dv*mainCamera.s();
    }
    if(keys.contains(Qt::Key_D))
    {
        mainCamera.pos = mainCamera.pos + dv*mainCamera.s();
    }
    if(keys.contains(Qt::Key_C))
    {
        mainCamera.pos = mainCamera.pos - dv*mainCamera.up;
    }
    if(keys.contains(Qt::Key_Space))
    {
        mainCamera.pos = mainCamera.pos + dv*mainCamera.up;
    }

    // made camera go down
    if(keys.contains(Qt::Key_Control))
    {
        mainCamera.pos = mainCamera.pos + dv*(-mainCamera.up);
    }

    glm::vec4 camera_init_forward = glm::normalize(glm::vec4(0,0,-1,1));
    mainCamera.forward = glm::rotate(identity(), mouse_move_pos.x()/400.0f, glm::vec3(0.0f,1.0f,0.0f)) * camera_init_forward;
    glm::vec3 sx = glm::normalize(mainCamera.s());
    mainCamera.forward = glm::rotate(identity(), mouse_move_pos.y()/400.0f, sx) * glm::vec4(mainCamera.forward,1.0f);
}

void GLWidget::paintGL()
{
    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    processCamera();
    viewMat = mainCamera.matrix();

    glm::mat4 MVMat;


    // ----- texture binding -------
    int pinky_tex = 1;
    int caca_tex = 2;
    int bart_tex = 3;
    int grass_tex = 4;

    textures["openglpinky"]->bind(pinky_tex);
    textures["openglcaca"]->bind(caca_tex);
    textures["grass"]->bind(bart_tex);
    textures["bart"]->bind(grass_tex);
    // ----- texture binding -------



    // ----- rendering axis with basic shader -----------
    shaders["basic"]->use();
    shaders["basic"]->setUniform("MVMat", viewMat);
    shaders["basic"]->setUniform("ProjMat", projMat);
    geometry["main_axes"]->render();
    // ----- rendering axis with basic shader -----------


    // ---- rendering first_billboard on xz rotation ------
    MVMat = viewMat * geometryMat["first_billboard"];
    shaders["bilboard_xz"]->use();
    shaders["bilboard_xz"]->setUniform("MVMat", MVMat);
    shaders["bilboard_xz"]->setUniform("ProjMat", projMat);
    shaders["bilboard_xz"]->setUniform("SamplerTex_1", pinky_tex);
    geometry["first_billboard"]->render();
    // ---- rendering first_billboard on xz rotation ------


    // ---- rendering second_billboard on xz rotation -----
    shaders["bilboard_xz"]->use();

    // making position of object
    frames["second_billboard"].pos = glm::vec4(1.0,0.0,1.0,1.0);
    MVMat = viewMat * geometryMat["second_billboard"] * frames["second_billboard"].matrix();

    shaders["bilboard_xz"]->setUniform("MVMat", MVMat);
    shaders["bilboard_xz"]->setUniform("ProjMat", projMat);
    shaders["bilboard_xz"]->setUniform("SamplerTex_1", caca_tex);
    geometry["second_billboard"]->render();
    // ---- rendering second_billboard on xz rotation ------



    frame++;
    PRINT_GL_ERRORS("Widget::paintGL(): ");
}




