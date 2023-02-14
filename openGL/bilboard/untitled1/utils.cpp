#include "utils.h"

glm::mat4 Frame::matrix(){
    glm::mat4 mat = glm::mat4(1.0);
    glm::vec3 xx = s();
    glm::vec3 f_norm = glm::normalize(forward);
    glm::vec3 u_norm = glm::normalize(up);
    mat[0] = glm::vec4(xx, 0.0);
    mat[1] = glm::vec4(u_norm, 0.0);
    mat[2] = glm::vec4(f_norm, 0.0);
    mat[3] = glm::vec4(pos, 1.0);

    return mat;
}

glm::mat4 Camera::matrix()
{
    glm::mat4 mat = glm::mat4(1.0);
    glm::vec3 xx = s();
    glm::vec3 f_norm = glm::normalize(forward);
    glm::vec3 u_norm = glm::normalize(glm::cross(xx, forward));

    mat[0][0] = xx.x;
    mat[1][0] = xx.y;
    mat[2][0] = xx.z;

    mat[0][1] = u_norm.x;
    mat[1][1] = u_norm.y;
    mat[2][1] = u_norm.z;

    mat[0][2] = -f_norm.x;
    mat[1][2] = -f_norm.y;
    mat[2][2] = -f_norm.z;

    mat = mat * glm::translate(glm::mat4(1.0), glm::vec3(-pos.x, -pos.y, -pos.z));
    return mat;
}
