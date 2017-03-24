#pragma once
#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <QtOpenGL\qtopenglglobal.h>
#include <QtWidgets\qwidget.h>
#include <QGL>//INCLUDE IN QtOpenGL
class MeGLWindow:public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();

public:




};



#endif