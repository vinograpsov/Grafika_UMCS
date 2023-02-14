#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <QOpenGLFunctions>

class Texture2D : protected QOpenGLFunctions
{
    GLuint handle;
public:
    Texture2D();

    void bind(int tex_unit=0);
    void unbind();

    bool loadFromFile(QString filename);
};

#endif // TEXTURE2D_H
