
//vec2 posion -->2 floats for the starting position of points
const char* vertexShaderCode =
"#version 400 core\r\n"
"\n"
"in layout(location=0) vec2 position;\n"
"in layout(location=1) vec3 vertexColor;\n"
"\n"
"out vec3 theColor;\n"
"\n"
"void main()\n"
"{\n"
"\n"
"   gl_Position = vec4(position,0.0,1.0);\n"
"   theColor = vertexColor;\n"
"\n"
"}";
 

const char* fragmentShaderCode =
"#version 400 core\r\n"
""
"out vec4 daColor;"
"in vec3 theColor;"
""
"void main()"
"{"
"   daColor = vec4(theColor,1.0);"
"}";