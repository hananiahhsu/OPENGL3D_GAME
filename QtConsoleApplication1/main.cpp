#include <QtCore/QCoreApplication>
#include "MeGLWindow.h"
#include <QtWidgets/qapplication>
#include <GL/glut.h>
int main(int argc, char *argv[])
{
	//The following 2 lines were created by the Qt automatically
	//QCoreApplication a(argc, argv);
	//return a.exec();

	//显示模式初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
	QApplication app(argc, argv);
	MeGLWindow megl;
	megl.show();
	return app.exec();


}
