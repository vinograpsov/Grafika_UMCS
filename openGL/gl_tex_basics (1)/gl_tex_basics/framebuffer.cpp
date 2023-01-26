#include "framebuffer.h"

#include<QOpenGLFunctions>
GLuint Framebuffer::DefaultFramebuffer = 0;
void Framebuffer::bindDefaultFramebuffer(){
    QOpenGLContext::currentContext()->functions()->glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer::DefaultFramebuffer);
}
Framebuffer::Framebuffer()
{
    initializeOpenGLFunctions();

    glGenFramebuffers(1,&handle);
}
void Framebuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER,handle);

    std::vector<GLenum> buffs(textures.size());
    for(int i = 0; i < textures.size();i++)
        buffs[i] = GL_COLOR_ATTACHMENT0 + textures.keys()[i];
//    int arr[1] = {0,textures.keys()[0]};

    glDrawBuffers(textures.size(), buffs.data());
}
void Framebuffer::setTexture2DAttachment(int attachment_number, Texture2D* tex){
    glBindFramebuffer(GL_FRAMEBUFFER,handle);
    textures[attachment_number] = tex;
    tex->bind();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_number,
                           GL_TEXTURE_2D,
                           tex->handle,
                           0);
    tex->unbind();
}
