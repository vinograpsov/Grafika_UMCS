#version 450


uniform vec3 LightPosition;
uniform vec4 LightColor;
uniform vec4 MaterialColor;

in vec3 normal;
in vec3 vertex_in_eye;

out vec4 FragColor;

void main()
{
    vec3 light = normalize(LightPosition - vertex_in_eye);
    float diffuse = max(0.0, dot(normal, light));

    vec3 r = normalize(reflect(-light,normal));
    vec3 e = normalize(-vertex_in_eye);
    float specular = pow(max(0.0,dot(r,e)),10);
    FragColor = diffuse * MaterialColor + specular * vec4(1,1,1,1);
}
