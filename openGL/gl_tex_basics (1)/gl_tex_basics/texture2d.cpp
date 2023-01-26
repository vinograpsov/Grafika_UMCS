#include "texture2d.h"
#include <QImage>
#include "utils.h"

Texture2D::Texture2D()
{
    initializeOpenGLFunctions();
    glGenTextures(1, &handle);
}

void Texture2D::bind(int tex_unit)
{
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture2D::loadFromFile(QString filename)
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


void Texture2D::create(int w, int h){
    bind(0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h,0,
                 GL_RGBA, GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    unbind();
}


