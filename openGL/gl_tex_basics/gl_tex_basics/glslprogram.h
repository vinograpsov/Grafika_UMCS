#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <QOpenGLFunctions_4_5_Core>
#include <string>
#include <QDebug>
#include <GL/glu.h>

#include "utils.h"
#include "mathgl.h"


//Klasa zarzadzajaca programem shadera
class GLSLProgram :  protected QOpenGLFunctions_4_5_Core
{
    GLuint handle;
    bool checkShaderStatus(GLuint);
    bool checkProgramStatus(GLuint);

public:
    GLSLProgram();
    //~GLSLProgram();
    bool compileShaderFromFile(const char* filename, GLenum type);
    bool compileShaderFromString(const std::string& source, GLenum type);
    bool link();

    void use();

    //void bindAttribLocation(GLuint location, const char* name);
    void setUniform(const char* name, int v);
    void setUniform(const char* name, glm::vec3 v);
    void setUniform(const char* name, glm::mat4 mat);
};

#endif // GLSLPROGRAM_H
