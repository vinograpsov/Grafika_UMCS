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
  mat4 modelView = MVMat;
  // First colunm.
  modelView[0][0] = 1.0;
  modelView[0][1] = 0.0;
  modelView[0][2] = 0.0;


//  //second for super transformation
//  modelView[1][0] = 0.0;
//  modelView[1][1] = 1.0;
//  modelView[1][2] = 0.0;



  // Thrid colunm.
  modelView[2][0] = 0.0;
  modelView[2][1] = 0.0;
  modelView[2][2] = 1.0;

  gl_Position = ProjMat * modelView * vec4(VertexPosition,1);
  f_Color = vec4(VertexColor, 1.0);
  f_UV = VertexUV;
}
