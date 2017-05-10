#pragma once
#include <QtOpenGL\qgl.h>
#include<QtOpenGL/QGLshaderProgram>
class XuModel;
class LightSource :public QGLWidget
{
public:
	LightSource(XuModel * theModel);
	~LightSource();
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
	XuModel *theModel;

};



