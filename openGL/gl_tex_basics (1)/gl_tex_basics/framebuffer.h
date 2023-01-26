#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <QOpenGLFunctions_4_5_Core>
#include "texture2d.h"

class Framebuffer : public QOpenGLFunctions_4_5_Core
{
    GLuint handle;
    QMap<int, Texture2D*> textures;
public:
    static GLuint DefaultFramebuffer;
    static void bindDefaultFramebuffer();
    Framebuffer();
    void bind();
    void setTexture2DAttachment(int attachment_number, Texture2D* tex);
};

#endif // FRAMEBUFFER_H
