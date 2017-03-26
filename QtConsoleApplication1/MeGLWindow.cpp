#include<glew.h>//put before MeGLWindow.h,or the error taking place
#include<MeGLWindow.h>

#if 0
//GL type
C Type	Bitdepth	Description	Common Enum
GLboolean	        1 + A boolean value, either GL_TRUE or GL_FALSE
GLbyte	8	        Signed, 2's complement binary integer	GL_BYTE
GLubyte	8	        Unsigned binary integer	GL_UNSIGNED_BYTE
GLshort	16	        Signed, 2's complement binary integer	GL_SHORT
GLushort	16	    Unsigned binary integer	GL_UNSIGNED_SHORT
GLint	32	        Signed, 2's complement binary integer	GL_INT
GLuint	32	        Unsigned binary integer	GL_UNSIGNED_INT
GLfixed	32	        Signed, 2's complement 16.16 integer	GL_FIXED
GLint64	64	        Signed, 2's complement binary integer	
GLuint64 64	        Unsigned binary integer
GLsizei	32	        A non - negative binary integer, for sizes.
GLenum	32	        An OpenGL enumerator value
GLintptr	  ptrbits ? 1	Signed, 2's complement binary integer	
GLsizeiptr	ptrbits ? 1	Non - negative binary integer size, for pointer offsets and ranges
GLsync	ptrbits ? 1	Sync Object handle
GLbitfield	32	A bitfield value
GLhalf	16	An IEEE - 754 floating - point value	GL_HALF_FLOAT
GLfloat	32	An IEEE - 754 floating - point value	GL_FLOAT
GLclampf	32	An IEEE - 754 floating - point value, clamped to the range[0, 1]
GLdouble	64	An IEEE - 754 floating - point value	GL_DOUBLE
GLclampd	64	An IEEE - 754 floating - point value, clamped to the range[0, 1]


#endif


extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;


void sendDataToOpenGL()
{
	//a triangle vertextes-1-dimensional array
#if 0
	GLfloat vertexes[]
	{
		0.0f,+1.0f,
		-1.0f,-1.0f,
		+1.0f,-1.0f,
	};
#endif


#if 0
	//Drawing 4 triangles on the dialog
	//counter-clockwise direction of pnts location
	GLfloat vertexes[]
	{
		0.0f,+0.0f,
		1.0f,-1.0f,
		1.0f,1.0f,

		0.0f,+0.0f,//redundant point
		-1.0f,1.0f,
		-1.0f,-1.0f,
	};
#endif


#if 1
	//counter-clockwise direction of pnts location
	//This structure contains 5 points of two triangles for we remove the redundant point(0.0,0.0,0.0.) 
	//which is the common point of the 2 triangles
	GLfloat vertexes[]
	{
		0.0f,+0.0f,//-0(position)
		1.0f,0.0f,0.0f,//-0(color-red)
		1.0f,-1.0f,//-1(position)
		1.0f,0.0f,0.0f,//-0(color-green)
		1.0f,1.0f,//-2(position)
		1.0f,0.0f,1.0f,//-0(color-blue)

		-1.0f,1.0f,//-3(position)
		1.0f,0.0f,0.0f,//-0(color)
		-1.0f,-1.0f,//-4(position)
		1.0f,0.0f,0.0f,//-0(color)
	};

#endif


	//Buffer object-BINDING gl_object to GL_ARRAY_BUFFER
	//gl_element_array_buffer :
	//gl_array_buffer:
	//Stride:the gap space between postion address or color address
	//Color mode:RGBA
	//glVertexAttribPointer()-the 4th parameter is for the starting address of color 
	//vertex attribute--> vertex shader:(position,custom data-->fragment shader-->RGB)
	//Segment shader:
	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);//
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
	glEnableVertexAttribArray(1);//
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));//from vertexed[],you can see that the stride of color is also sizeof(float)*5

	GLushort indices[] = { 0,1,2,0,3,4 };//why use the GLushort?
	GLuint index_vertex_id;
	glGenBuffers(1, &index_vertex_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vertex_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void installShaders()
{

}


void MeGLWindow::initializeGL()
{
	glewInit();
	//Send datas to OpenGL
	sendDataToOpenGL();
	//install the shaders(vertex shaders and fragment shaders)
	installShaders();

}

void MeGLWindow::paintGL()
{
#if 0
	//Set the background color--to red
	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
#endif
	glViewport(0,0,width(),height());//Get the width and height of the dialog(window)
	//Notes:The folloeling commented lines are several steps of trying to realize different functions
	//glDrawArrays(GL_TRIANGLES,0,3);//Draw 1 triangle on the drialog by the vertex
	//glDrawArrays(GL_TRIANGLES,0,6);//Draw 2 triangle on the dialog by the vertex

	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
}  