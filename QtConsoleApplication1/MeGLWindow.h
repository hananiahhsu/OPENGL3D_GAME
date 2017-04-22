#pragma once
#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
//#include <QtOpenGL/qtopenglglobal.h>
//#include <QtWidgets/qwidget.h>
//#include <QtOpenGL\QGL>//INCLUDE IN QtOpenGL
//#include <QtWidgets/qopenglwidget.h>
//#include<QtOpenGL/QGLshaderProgram>
//#include<QtWidgets/QOpenGLWidget>

#include <QtOpenGL\qglwidget>
class MeGLWindow:public QGLWidget
{
public:
	MeGLWindow() {}
	~MeGLWindow() {}

protected:
	void initializeGL();
	void paintGL();
public:
	void sendDataToOpenGL();
	void sendAnotherTriToOpenGL();
	void installShaders();
private:
	GLuint program_object_id;
};



#endif