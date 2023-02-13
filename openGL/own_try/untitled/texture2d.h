#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <QOpenGLFunctions_4_5_Core>

class Texture2D : protected QOpenGLFunctions_4_5_Core
{
    GLuint handle;
public:
    Texture2D();

    void bind(int tex_unit=0);
    void unbind();

    bool loadFromFile(QString filename);


    void bindOnSphere();
};

#endif // TEXTURE2D_H
