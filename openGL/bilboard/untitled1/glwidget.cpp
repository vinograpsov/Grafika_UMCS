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

    shaders["basic"] = new GLSLProgram;
    stat = shaders["basic"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/basic.vert", GL_VERTEX_SHADER);
    stat &= shaders["basic"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/basic.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["basic"]->link();
    if (!stat) qFatal("Some problem with shader!");

    shaders["tex"] = new GLSLProgram;
    stat = shaders["tex"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/billboard.vert", GL_VERTEX_SHADER);
    stat &= shaders["tex"]->compileShaderFromFile("F:/uniwesitet/5 сем/grafika/openGL/bilboard/untitled1/shaders/tex_basic.frag", GL_FRAGMENT_SHADER);
    stat &= shaders["tex"]->link();
    if (!stat) qFatal("Some problem with shader!");
}

void GLWidget::createGeometry()
{
    geometry["main_axes"] = newAxesGeometry();
    geometryMat["main_axes"] = identity();

    geometry["earth"] = newPlaneGeometry({1,1}, {1,1,1});
    glm::vec2 plane_uv[] = { {0,0}, {0,1}, {1,1}, {1,0}};
    geometry["earth"]->setAttribute((int)Attributes::uv1, plane_uv, 4);
    geometryMat["earth"] = identity();

}

void GLWidget::createTextures()
{
    bool stat;
    textures["wood"] = new Texture2D();
    stat = textures["wood"]->loadFromFile("C:/Users/KirVin/Downloads/pngimg.com - simpsons_PNG95.png");
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

    glm::vec4 camera_init_forward = glm::normalize(glm::vec4(0,0,-1,1));
    mainCamera.forward = glm::rotate(identity(), mouse_move_pos.x()/400.0f, glm::vec3(0.0f,1.0f,0.0f)) * camera_init_forward;
    glm::vec3 sx = glm::normalize(mainCamera.s());
    mainCamera.forward = glm::rotate(identity(), mouse_move_pos.y()/400.0f, sx) * glm::vec4(mainCamera.forward,1.0f);
}

void GLWidget::paintGL()
{
    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    processCamera();
    viewMat = mainCamera.matrix();

    glm::mat4 MVMat;

    //narysowanie osi globalnych shaderem 'basic'
    shaders["basic"]->use();
    shaders["basic"]->setUniform("MVMat", viewMat);
    shaders["basic"]->setUniform("ProjMat", projMat);
    geometry["main_axes"]->render();

    // wlaczenie tekstury 'wood' w pierwszej jednostce teksturujacej
    int tex_unit_wood = 1;
    textures["wood"]->bind(tex_unit_wood);


    MVMat = viewMat * geometryMat["earth"];

    //render earth shaderem 'tex'
    shaders["tex"]->use();
    shaders["tex"]->setUniform("MVMat", MVMat);
    shaders["tex"]->setUniform("ProjMat", projMat);
    shaders["tex"]->setUniform("SamplerTex_1", tex_unit_wood);
    geometry["earth"]->render();


    frame++;
    PRINT_GL_ERRORS("Widget::paintGL(): ");
}




