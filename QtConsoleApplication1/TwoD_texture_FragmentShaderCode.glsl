#version 400 core

out vec4 daColor;
in vec3 theColor;
in vec2 TexCoord;


uniform sampler2D ourTexture1;

void main()
{
  daColor = texture(ourTexture1, TexCoord);
}