#version 450

uniform sampler2D SamplerTex;
in vec4 fColor;
in vec2 fUV;

out vec4 FragColor;

void main()
{
    FragColor = fColor * texture(SamplerTex, fUV);
}
