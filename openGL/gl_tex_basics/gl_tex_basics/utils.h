#ifndef UTILS_H
#define UTILS_H

#include <GL/gl.h>
#include <GL/glu.h>

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


#endif // UTILS_H
