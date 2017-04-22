#version 400 core
in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;

uniform mat4 mdlTrfMatrix ;
uniform mat4 projMatrix;

out vec3 theColor;

void main()
{
  vec4 v = vec4(position,1.0);
  vec4 new_pos = mdlTrfMatrix * v;
  vec4 proj_pos = projMatrix * new_pos;
  gl_Position = proj_pos;
  

  theColor = vertexColor;
}
