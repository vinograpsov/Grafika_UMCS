#include "texture3d.h"
#include <QImage>
#include "utils.h"

Texture3D::Texture3D()
{
    initializeOpenGLFunctions();
    glGenTextures(1, &handle);
}

void Texture3D::bind(int tex_unit)
{
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture3D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture3D::loadFromFile(QString filename)
{
    QImage image(filename);
    if( !image.isNull() )
    {
        bind(0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     image.width(), image.height(),
                     0,
                     GL_BGRA, GL_UNSIGNED_BYTE,
                     image.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
        unbind();
        return true;
    }
    return false;
}
