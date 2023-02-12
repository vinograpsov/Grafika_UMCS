#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"

Geometry *newAxesGeometry();

Geometry *newPlaneGeometry(glm::vec2 size, glm::vec3 color);

Geometry* newBoxGeometry(glm::vec3 size, glm::vec3 color);

#endif // PRIMITIVES_H
