#version 450

uniform mat4 MVMat;
uniform mat4 ProjMat;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
layout (location=7) in vec2 VertexUV;

out vec4 f_Color;
out vec2 f_UV;

void main()
{
    gl_Position = ProjMat * MVMat * vec4(VertexPosition, 1.0);
    f_Color = vec4(VertexColor, 1.0);
    f_UV = VertexUV;
}
