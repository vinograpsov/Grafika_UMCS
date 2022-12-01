#include "geometry.h"

inline void PRINT_GL_ERRORS(const char* mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR) { qDebug() << "ERROR in: " << mess << (const char*)gluErrorString(err); }
}

Geometry::Geometry()
{
    // inicjalizacja wskaznikow do funkcji OpenGLa
    initializeOpenGLFunctions();

    // wygenerowanie nazwy dla Vertex Array Object
    glGenVertexArrays(1, &vao);

    // wygenerowanie nazwy dla bufora wierzcholkow (w ogolnosci nie musi to byc jeden bufor dla danej siatki)
    //glGenBuffers(1, &vbo);

    primitiveMode = GL_TRIANGLES;
    n_verts = 0;
    n_indices = 0;
}

void Geometry::render()
{
    // narysowanie wszystkiego co jest wrzucone do tablicy obiektow wierzcholkow vao
    glBindVertexArray(vao);
        glDrawArrays(primitiveMode, 0, n_verts);
    glBindVertexArray(0);

//    PRINT_GL_ERRORS("Geometry::render(): ");
}

void Geometry::setVertices(uint index, glm::vec3* verts, int n)
{
    n_verts = n;
    setAttribute(index, verts, n);
//    PRINT_GL_ERRORS("Geometry::setVertices(): ");
}

void Geometry::setAttribute(uint index, glm::vec3 *data, int n)
{
    //wygenerowanie nazwy bufora dla atrybutu i dodanie do mapy pod konkretnym indexem
    if( !bufferObjects.contains(index) )
    {
        GLuint i;
        glGenBuffers(1, &i);
        bufferObjects.insert(index, i);
    }


    glBindVertexArray(vao);
    // setup bufora z danym atrybutem

        glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[index]);
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,3 , GL_FLOAT, GL_FALSE, 0,0);
        glBufferData(GL_ARRAY_BUFFER, n * sizeof(glm::vec3), data, GL_STATIC_DRAW);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0 );
//    PRINT_GL_ERRORS("Geometry::setAttribute(): ");
}

