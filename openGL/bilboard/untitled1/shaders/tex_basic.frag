#version 450

uniform sampler2D SamplerTex_1;
uniform sampler2D SamplerTex_2;
in vec4 f_Color;
in vec2 f_UV;

out vec4 FragColor;

void main()
{
    //rozne kombinacje mieszania tekstur:
    //FragColor = f_Color * mix(texture(SamplerTex_1, f_UV), texture(SamplerTex_2, f_UV), 0.2);
    FragColor = f_Color * texture(SamplerTex_1, f_UV) + 0.25f*texture(SamplerTex_2, f_UV) - 0.125f;
}
