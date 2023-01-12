#ifndef MATHGL_H
#define MATHGL_H
#include <QDebug>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//struct vec2 { float x,y; };
//struct vec3 { float x,y,z; };
//struct vec4 { float x,y,z,w; };

//struct mat4 { float m[16]; };

//inline float deg2rad(float deg)
//{
//    return deg*M_PI/180.0f;
//}

//inline float len(const vec3& a)
//{

//}

//inline vec3 normal(const vec3& a)
//{

//}

//inline float dot(const vec3& a, const vec3& b)
//{

//}

//inline vec3 cross(const vec3& a, const vec3& b)
//{

//}

//inline vec3 operator*(const vec3& a, float f)
//{
//    return vec3{a.x*f, a.y*f, a.z*f};
//}

//inline vec3 operator+(const vec3& a, const vec3& b)
//{
//    return {a.x+b.x, a.y+b.y, a.z+b.z};
//}

//inline mat4 identity()
//{
//    mat4 m;
//    memset(m.m, 0, 16*4);
//    m.m[0]=m.m[5]=m.m[10]=m.m[15]=1.0f;
//    return m;
//}

//inline mat4 translation_mat(float x, float y, float z)
//{
//    mat4 mret = identity();
//    mret.m[12] = x;
//    mret.m[13] = y;
//    mret.m[14] = z;
//    return mret;
//}

//inline mat4 rotation_mat(float angle, float x, float y, float z)
//{
//    mat4 mret = identity();
//    float s = sin(angle);
//    float c = cos(angle);

//    mret.m[0] = x*x*(1-c)+c;
//    mret.m[1] = y*x*(1-c)+z*s;
//    mret.m[2] = x*z*(1-c)-y*s;

//    mret.m[4] = x*y*(1-c)-z*s;
//    mret.m[5] = y*y*(1-c)+c;
//    mret.m[6] = y*z*(1-c)+x*s;

//    mret.m[8] = x*z*(1-c)+y*s;
//    mret.m[9] = y*z*(1-c)-x*s;
//    mret.m[10] = z*z*(1-c)+c;

//    return mret;
//}

//inline mat4 scale_mat(float x, float y, float z)
//{
//    mat4 mret = identity();
//    mret.m[0] = x;
//    mret.m[5] = y;
//    mret.m[10] = z;
//    return mret;
//}

//inline mat4 inversed(const mat4& mat)
//{
//    mat4 mret = identity();
//    //...

//    return mret;
//}

//inline mat4 transposed(const mat4& mat)
//{
//    mat4 mret = identity();
//    //...

//    return mret;
//}

//inline mat4 mul(const mat4& m1, const mat4& m2)
//{
//    mat4 mret;
//    mret.m[0] = m1.m[0]*m2.m[0] + m1.m[4]*m2.m[1] + m1.m[8]*m2.m[2]  + m1.m[12]*m2.m[3];
//    mret.m[1] = m1.m[1]*m2.m[0] + m1.m[5]*m2.m[1] + m1.m[9]*m2.m[2]  + m1.m[13]*m2.m[3];
//    mret.m[2] = m1.m[2]*m2.m[0] + m1.m[6]*m2.m[1] + m1.m[10]*m2.m[2] + m1.m[14]*m2.m[3];
//    mret.m[3] = m1.m[3]*m2.m[0] + m1.m[7]*m2.m[1] + m1.m[11]*m2.m[2] + m1.m[15]*m2.m[3];

//    mret.m[4] = m1.m[0]*m2.m[4] + m1.m[4]*m2.m[5] + m1.m[8]*m2.m[6]  + m1.m[12]*m2.m[7];
//    mret.m[5] = m1.m[1]*m2.m[4] + m1.m[5]*m2.m[5] + m1.m[9]*m2.m[6]  + m1.m[13]*m2.m[7];
//    mret.m[6] = m1.m[2]*m2.m[4] + m1.m[6]*m2.m[5] + m1.m[10]*m2.m[6] + m1.m[14]*m2.m[7];
//    mret.m[7] = m1.m[3]*m2.m[4] + m1.m[7]*m2.m[5] + m1.m[11]*m2.m[6] + m1.m[15]*m2.m[7];

//    mret.m[8]  = m1.m[0]*m2.m[8] + m1.m[4]*m2.m[9] + m1.m[8]*m2.m[10]  + m1.m[12]*m2.m[11];
//    mret.m[9]  = m1.m[1]*m2.m[8] + m1.m[5]*m2.m[9] + m1.m[9]*m2.m[10]  + m1.m[13]*m2.m[11];
//    mret.m[10] = m1.m[2]*m2.m[8] + m1.m[6]*m2.m[9] + m1.m[10]*m2.m[10] + m1.m[14]*m2.m[11];
//    mret.m[11] = m1.m[3]*m2.m[8] + m1.m[7]*m2.m[9] + m1.m[11]*m2.m[10] + m1.m[15]*m2.m[11];

//    mret.m[12] = m1.m[0]*m2.m[12] + m1.m[4]*m2.m[13] + m1.m[8]*m2.m[14]  + m1.m[12]*m2.m[15];
//    mret.m[13] = m1.m[1]*m2.m[12] + m1.m[5]*m2.m[13] + m1.m[9]*m2.m[14]  + m1.m[13]*m2.m[15];
//    mret.m[14] = m1.m[2]*m2.m[12] + m1.m[6]*m2.m[13] + m1.m[10]*m2.m[14] + m1.m[14]*m2.m[15];
//    mret.m[15] = m1.m[3]*m2.m[12] + m1.m[7]*m2.m[13] + m1.m[11]*m2.m[14] + m1.m[15]*m2.m[15];
//    return mret;
//}

//inline mat4 operator*(const mat4& m1, const mat4& m2)
//{
//    return mul(m1, m2);
//}

//inline vec3 mul(const mat4& m1, const vec3& v)
//{
//    vec3 vret;
//    //...
//    return vret;
//}

//inline vec4 mul(const mat4& m1, const vec4& v)
//{
//    vec4 vret;
//    //...
//    return vret;
//}

//inline mat4 perspective(float fovy, float aspect, float znear, float zfar)
//{
//    mat4 M;
//    //...

//    return M;
//}

#endif // MATHGL_H
