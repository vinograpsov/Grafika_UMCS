#include "glslprogram.h"
#include <QDebug>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <QFile>
#include<QTextStream>
#include <QString>


GLSLProgram::GLSLProgram()
{
    initializeOpenGLFunctions();
    handle = glCreateProgram();
}


bool GLSLProgram::compileShaderFromFile(const char *filename, GLenum type)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        std::cout << file.errorString().toStdString() << std::endl;
    }

    QTextStream in(&file);

    QString shader_code;

    while(!in.atEnd()) {
        QString line = in.readLine();
        shader_code += line + "\n";
    }

    file.close();

    std::cout << shader_code.toStdString() << std::endl;

    return compileShaderFromString(shader_code.toStdString(), type);
}

bool GLSLProgram::compileShaderFromString(const std::string &source, GLenum type)
{
    GLuint sh = glCreateShader(type);
    GLchar* srcs[] = {(GLchar*)source.c_str()};
    glShaderSource(sh, 1, srcs, NULL);
    glCompileShader(sh);
    if( checkShaderStatus(sh) )
    {
        glAttachShader(handle, sh);
        glDeleteShader(sh);
        return true;
    }
    return false;
}

bool GLSLProgram::link()
{
    glLinkProgram(handle);
    return checkProgramStatus(handle);
}

void GLSLProgram::use()
{
    glUseProgram(handle);
    PRINT_GL_ERRORS("GLSLProgram::use(): ");
}

void GLSLProgram::setUniform(const char* name, vec3 v)
{
    GLint loc = glGetUniformLocation(handle, name);
    if(loc != -1)
//        glUniform3f(loc, x,y,z)
        glUniform3fv(loc, 1, &v.x);

    // else PRINT SOME ERROR
}

void GLSLProgram::setUniform(const char *name, mat4 mat)
{
    GLint loc = glGetUniformLocation(handle, name);
    if(loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat.m);
    // else PRINT SOME ERROR
}

bool GLSLProgram::checkShaderStatus(GLuint shader)
{
  GLint stat;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
  if(stat == GL_FALSE)
  {
    GLchar infoLog[10240];
    glGetShaderInfoLog(shader, 10240, NULL, infoLog);
//    qDebug() << "Shader ERROR: " << infoLog << endl;
    return false;
  }
  return true;
}

bool GLSLProgram::checkProgramStatus(GLuint program)
{
  GLint stat;
  glGetProgramiv(program, GL_LINK_STATUS, &stat);
  if(stat == GL_FALSE)
  {
    GLchar infoLog[10240];
    glGetProgramInfoLog(program, 10240, NULL, infoLog);
//    qDebug() << "Program ERROR: " << infoLog << endl;
    return false;
  }
  else
  {
//    qDebug() << "Program LINKED"<< endl;
  }
  return true;
}
