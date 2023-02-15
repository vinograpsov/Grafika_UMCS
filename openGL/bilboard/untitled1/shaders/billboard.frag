#version 450

uniform sampler2D SamplerTex_1;
in vec4 f_Color;
in vec2 f_UV;

out vec4 FragColor;

void main()
{

    vec4 texColor = texture(SamplerTex_1, f_UV);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
//    FragColor = texture(SamplerTex_1, f_UV);
//    FragColor = f_Color;
}
