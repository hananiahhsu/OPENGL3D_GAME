#pragma once
#ifndef Cubic_Box_Location
#define Cubic_Box_Location

//#include <QtOpenGL\qtopenglglobal.h>
//#include <QtWidgets/qwidget.h>
#include <QtOpenGL\qgl.h>//INCLUDE IN QtOpenGL 
//#include <QtWidgets/qopenglwidget.h>
#include<QtOpenGL/QGLshaderProgram>
//#include<QtWidgets/QOpenGLWidget>
//#include "Primitives\ShapeData.h"

class CubicBox_AttributeLocation :public QGLWidget
{
public:
	CubicBox_AttributeLocation();
	~CubicBox_AttributeLocation();
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

private:

	GLuint program_object_id;


};



#endif