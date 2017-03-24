#include <QtCore/QCoreApplication>
#include "MeGLWindow.h"
#include <QtWidgets/qapplication>
int main(int argc, char *argv[])
{
	//The following 2 lines were created by the Qt automatically
	//QCoreApplication a(argc, argv);
	//return a.exec();


	QApplication app(argc, argv);
	MeGLWindow megl;
	megl.show();
	return app.exec();


}
