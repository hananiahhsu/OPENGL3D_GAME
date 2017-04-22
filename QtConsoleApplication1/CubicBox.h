#pragma once
#ifndef Cubic_Box
#define Cubic_Box

//#include <QtOpenGL\qtopenglglobal.h>
//#include <QtWidgets/qwidget.h>
#include <QtOpenGL\qgl.h>//INCLUDE IN QtOpenGL 
//#include <QtWidgets/qopenglwidget.h>
#include<QtOpenGL/QGLshaderProgram>
//#include<QtWidgets/QOpenGLWidget>
//#include "Primitives\ShapeData.h"

class CubicBox :public QGLWidget
{
public:
	CubicBox();
	~CubicBox();
protected:
	 void initializeGL();
	 void paintGL();
	
public://Method of pipeline
	 void sendDataToOpenGL();
	 void sendAnotherTriToOpenGL();
	 void installShaders();
	 void main(int argc, char** argv);
	 bool checkStatus(
		 GLuint objectID,
		 PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		 PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
		 GLenum statusType);
	 bool checkProgramStatus(GLuint programID);


public:	//Traditional way of rendering
	static void init(void);
	static void display(void);
	static void reshape(int w, int h);
	static void keyboard(unsigned char key, int x, int y);
	static void spinDisplay(void);
private:

	 GLuint program_object_id;


};



#endif