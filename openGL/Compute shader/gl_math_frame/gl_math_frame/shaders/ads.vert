#version 450

uniform mat4 MVMat;
uniform mat4 ProjMat;
uniform vec3 LightPosition;
uniform vec4 LightColor;
uniform vec4 MaterialColor;


layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
layout (location=2) in vec3 VertexNormal;

out vec4 fColor;

void main()
{
    vec3 vertex_in_eye = (MVMat * vec4(VertexPosition, 1.0)).xyz;

//    fColor = vec4(VertexColor, 1.0);
    vec3 light = normalize(LightPosition - vertex_in_eye);
    vec3 normal = mat3(MVMat) * VertexNormal;


    vec3 r = normalize(reflect(light,normal));
    vec3 e = normalize(vertex_in_eye);
    float specular = pow(max(0.0,dot(r,e)),10);
    float diffuse = max(0.0, dot(normal, light));
    fColor = diffuse * MaterialColor + specular * vec4(1,1,1,1) ;


    gl_Position = ProjMat * vec4(vertex_in_eye,1.0);
}
