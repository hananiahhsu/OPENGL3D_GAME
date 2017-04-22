#pragma once
#include <QtOpenGL\qglwidget>
class DrawElementsInstance :public QGLWidget
{
public:
	DrawElementsInstance() {}
	~DrawElementsInstance() {}

	
protected:
	void initializeGL();
	void paintGL();
public:
	void sendDataToOpenGL();
	void sendAnotherTriToOpenGL();
	void installShaders();
private:

	GLuint program_object_id;
	GLuint num_indices;
};
