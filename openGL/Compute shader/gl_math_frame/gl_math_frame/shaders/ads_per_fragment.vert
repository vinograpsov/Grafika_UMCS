#version 450

uniform mat4 MVMat;
uniform mat4 ProjMat;
uniform vec3 LightPosition;
uniform vec4 LightColor;
uniform vec4 MaterialColor;


layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
layout (location=2) in vec3 VertexNormal;

out vec3 normal;
out vec3 vertex_in_eye;




void main()
{
    vec3 vertex_in_eye = (MVMat * vec4(VertexPosition, 1.0)).xyz;
    vec3 normal = mat3(MVMat) * VertexNormal;
    gl_Position = ProjMat * vec4(vertex_in_eye,1.0);
}
