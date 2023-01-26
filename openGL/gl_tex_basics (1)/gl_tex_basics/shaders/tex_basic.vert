#version 450
layout (location=0) in vec3 VertexPosition;
layout (location=7) in vec2 VertexUV;

out vec4 f_Color;
out vec2 f_UV;

void main()
{
    gl_Position = vec4(VertexPosition, 1.0);
    f_UV = VertexUV;
}
