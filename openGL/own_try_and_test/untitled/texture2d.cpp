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
//    glBindTexture(GL_TEXTURE_2D, handle);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture( GL_TEXTURE_2D, handle );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
}

void bindOnSphere(){

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
