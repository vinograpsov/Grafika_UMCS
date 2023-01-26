#version 450
uniform sampler2D SamplerTex_1;
in vec4 f_Color;
in vec2 f_UV;
layout (location =0) out vec4 FragColor;

void main(void)
{
    ivec2 size = textureSize(SamplerTex_1,0);
    vec4 color = texture(SamplerTex_1, f_UV) +
            texture(SamplerTex_1, f_UV+ vec2(-1.0/size.x,0)) +
            texture(SamplerTex_1, f_UV+ vec2(1.0/size.x,0)) +
            texture(SamplerTex_1, f_UV+ vec2(0,-1.0/size.y)) +
            texture(SamplerTex_1, f_UV+ vec2(0,1.0/size.y)) +
            texture(SamplerTex_1, f_UV+ vec2(1.0/size.x,-1.0/size.y)) +
            texture(SamplerTex_1, f_UV+ vec2(1.0/size.x,1.0/size.y)) +
            texture(SamplerTex_1, f_UV+ vec2(-1.0/size.x,-1.0/size.y)) +
            texture(SamplerTex_1, f_UV+ vec2(-1.0/size.x,1.0/size.y));
    color = color / 9.0;
    FragColor = color;
}
