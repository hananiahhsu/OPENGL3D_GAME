
//vec2 posion -->2 floats for the starting position of points
const char* vertexShaderCode =
"#version 580\r\n"
""
"in alyout(location=0) vec2 position;"
""
""
"void main()"
"{"
"gl_position = vec4(position,0.0,1.0);"
"}";


const char* fragmentShaderCode =
"#version 580\r\n"
""
"out vec4 daColor;"
""
"void main()"
"{"
"daColor = vec4(0.0,1.0,0.0,0.0);"
"}";