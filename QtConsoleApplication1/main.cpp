#include <QtCore/QCoreApplication>
#include "MeGLWindow.h"
#include "UniformColor.h"
#include "CubicBox.h"
#include <QtWidgets/qapplication>
#include <glut.h>
#include "TeaPot.h"
#include "DrawElementsInstance.h"
#include "CubicBox_AttributeLocation.h"
#include "CubicBox_DynamicDraw.h"
int main(int argc, char *argv[])
{
	//The following 2 lines were created by the Qt automatically
	//QCoreApplication a(argc, argv);
	//return a.exec();
	//QApplication::addLibraryPath("E:/X_HSU/201703/GraphicsApplication/QtConsoleApplication1/x64/Debug/platforms");
	//显示模式初始化(GLUT_SINGLE,GLUT_DOUBLE)
#if 1
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	QApplication app(argc, argv);


#endif 


#if 0
	MeGLWindow megl;
	megl.show();
#endif

#if 0 
	UniformColor uni_color;
	uni_color.show();
#endif


#if 0
	TeaPot tea_pot;
	tea_pot.main(argc, argv);
#endif


#if 0
	CubicBox c_box;
    c_box.show();
#endif

#if 0
	DrawElementsInstance df;
	df.show();
#endif

#if 0
	CubicBox_AttributeLocation ca;
	ca.show();
#endif

#if 1
	CubicBox_DynamicDraw cd;
	cd.show();
#endif
	return app.exec();
}
