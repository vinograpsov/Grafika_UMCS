#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#include <QOpenGLFunctions_4_5_Core>

class Texture3D : protected QOpenGLFunctions_4_5_Core
{
    GLuint handle;
public:
    Texture3D();

    void bindSphere(int tex_unit=0);
    void unbind();

    bool loadFromFile(QString filename);
};

#endif // TEXTURE2D_H
