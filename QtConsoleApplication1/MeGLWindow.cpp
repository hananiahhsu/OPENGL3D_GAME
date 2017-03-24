#include<glew.h>//put before MeGLWindow.h,or the error taking place
#include<MeGLWindow.h>


void MeGLWindow::initializeGL()
{
	glewInit();


}

void MeGLWindow::paintGL()
{
	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
}