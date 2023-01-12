#version 450

uniform mat4 MVMat;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
layout (location=7) in vec2 VertexUV;

out vec4 fColor;
out vec2 fUV;

void main()
{
    gl_Position = MVMat * vec4(VertexPosition, 1.0);
    fColor = vec4(VertexColor, 1.0);
    fUV = VertexUV;
}
