#version 450

uniform vec3 Color;
uniform mat4 MVMat;
uniform mat4 ProjMat;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;

out vec4 fColor;

void main()
{
    gl_Position = ProjMat * MVMat * vec4(VertexPosition, 1.0);
    fColor = vec4(VertexColor, 1.0);
}
