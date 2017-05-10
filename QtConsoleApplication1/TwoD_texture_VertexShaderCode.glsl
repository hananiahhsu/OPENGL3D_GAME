#version 400 core
in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec2 texCoord;


out vec3 theColor;
out vec2 TexCoordinate;


void main()
{
  gl_Position = vec4(position,1.0);

  theColor = vertexColor;

  TexCoordinate = texCoord;
}