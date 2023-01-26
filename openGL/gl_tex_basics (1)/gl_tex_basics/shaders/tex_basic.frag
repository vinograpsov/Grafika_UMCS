#version 450
uniform  sampler2D SamplerTex_1;
in vec4 f_Color;
in vec2 f_UV;
out vec4 FragColor;
layout (location = 0) out vec4 FragColor;
void main()
{
    FragColor = texture(SamplerTex_1, f_UV);
}
