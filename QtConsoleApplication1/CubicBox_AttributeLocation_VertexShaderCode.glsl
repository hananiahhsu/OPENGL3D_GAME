#version 400 core
in  vec3 position;
in  vec3 vertexColor;
in  mat4 fullTransformMatrix ;

out vec3 theColor;

void main()
{
  vec4 v = vec4(position,1.0);
  gl_Position = fullTransformMatrix * v;
 
  theColor = vertexColor;
}