#pragma once
#ifndef Cubic_Box_DynamicDraw
#define Cubic_Box_DynamicDraw

#include <QtOpenGL\qgl.h>
#include<QtOpenGL/QGLshaderProgram>


class CubicBox_DynamicDraw :public QGLWidget
{
public:
	CubicBox_DynamicDraw();
	~CubicBox_DynamicDraw();
protected:
	void initializeGL();
	void paintGL();
	void mouseMoveEvent(QMouseEvent *);
	void keyPressEvent(QKeyEvent *);
public://Method of pipeline
	void sendDataToOpenGL();
	void sendAnotherTriToOpenGL();
	void installShaders();
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