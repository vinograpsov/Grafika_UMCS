#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"

Geometry *createAxesGeometry();

Geometry *createPlaneGeometry(glm::vec2 size, glm::vec3 color);

Geometry* createBoxGeometry(glm::vec3 size, glm::vec3 color);

#endif // PRIMITIVES_H
