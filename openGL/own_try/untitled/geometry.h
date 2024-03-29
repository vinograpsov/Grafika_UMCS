#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "glslprogram.h"
#include <QOpenGLFunctions_4_5_Core>

#include <QMap>

class Geometry : protected QOpenGLFunctions_4_5_Core
{
protected:
    GLuint vao;    // Vertex Array Object
    int n_verts;   //ilosc wierzcholkow

    GLuint ibo;     //bufor indeksow
    int n_indices;  //ilosc indeksow

    //! Mapa buforow atrybutow
    //! klucz mapy to index danego atrybutu, wartosc mapy to uchwyt do bufora
    QMap<uint, GLuint> bufferObjects;
    GLenum primitiveMode;  // tryb rysowania geometrii: punkty, linie, trojkaty

public:
    Geometry();
    virtual ~Geometry() {}

    void setPrimitiveMode(GLenum);
    virtual void render();

    void setIndices(uint* data, int n);

    void setVertices(uint index, glm::vec3* verts, int n);
    void setAttribute(uint index, glm::vec2* data, int n);
    void setAttribute(uint index, glm::vec3* data, int n);

    int n_vetrices() { return n_verts; }
};



#endif // GEOMETRY_H
