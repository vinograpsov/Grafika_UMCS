#ifndef UTILS_H
#define UTILS_H

#include <QDebug>

#include <GL/gl.h>
#include <GL/glu.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

inline glm::mat4 identity() {return glm::mat4(1.0f);}

enum class Attributes{
    position = 0,
    color = 1,
    normal = 2,
    uv1 = 7,
};

inline void PRINT_GL_ERRORS(const char* mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR) { qDebug() << "ERROR in: " << mess << (const char*)gluErrorString(err); }
}

class Frame
{
public:
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;

    Frame() {
        pos = glm::vec3(0,0,0);
        forward = glm::vec3(0,0,1);
        up = glm::vec3(0,1,0);
    }
    virtual glm::vec3 s() {
        return glm::normalize(glm::cross(up, forward));
    }
    virtual glm::mat4 matrix();
};

class Camera : public Frame
{
public:
    Camera(){
        pos = glm::vec3(0,0, 1);
        forward = glm::vec3(0,0,-1);
        up = glm::vec3(0,1,0);
    }
    glm::vec3 s() {
        return glm::normalize(glm::cross(forward, up));
    }
    glm::mat4 matrix();
};


#endif // UTILS_H
