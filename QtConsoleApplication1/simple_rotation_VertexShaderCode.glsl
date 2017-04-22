#version 400 core
in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;

uniform mat4 fullTrfMatrix ;

out vec3 theColor;

void main()
{
  vec4 v = vec4(position,1.0);
  gl_Position = fullTrfMatrix * v;
  
  theColor = vertexColor;
}








