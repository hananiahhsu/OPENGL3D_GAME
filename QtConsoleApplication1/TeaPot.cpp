#include "TeaPot.h"

#include "glut.h"  
#include "stdlib.h"  
#include "stdio.h"  
#include "math.h"  

static int big = 0;
static bool isLeftEye = false;

#define PI 3.1415926  
const GLfloat R = 8.0;

static GLfloat leftMatrix[16] = { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0,  0.0,
0.0, 0.0, 0.0, 1.0 };

static GLfloat rightMatrix[16] = { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

static GLfloat leftPersMatrix[16] = { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

static GLfloat rightPersMatrix[16] = { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };
void TeaPot::init(void)
{
	const GLfloat SD = 0.06;
	GLfloat n = SD*R / 2.0;
	//要是转秩  
	//n=0;  
	leftMatrix[12] = n;
	rightMatrix[12] = -n;

	//这里假设眼到屏幕为一米，以米为单位  
	GLfloat p = SD / (2 * 1 * tan(PI / 6) * 1);
	//p = 0.0;  
	leftPersMatrix[12] = -p;
	rightPersMatrix[12] = p;

	GLfloat mat_specular[] = { 0.8, 0.8, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat yellow_light[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.0, 0.7, 0.5, 1.0 };
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_light);//主体的颜色  
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);//高光的颜色  
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void TeaPot::display(void)
{
	glColorMask(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	// 画左眼  
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	float mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, mat);
	glLoadIdentity();

	glMultMatrixf(leftPersMatrix);
	glMultMatrixf(mat);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glLoadIdentity();

	glMultMatrixf(leftMatrix);
	glMultMatrixf(mat);

	glColorMask(1.0, 0.0, 0.0, 1.0);

	glRotatef((GLfloat)big, 0.0, 1.0, 0.0);
	glutSolidTeapot(2.0);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	//画右眼  
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glGetFloatv(GL_PROJECTION_MATRIX, mat);
	glLoadIdentity();

	glMultMatrixf(rightPersMatrix);
	glMultMatrixf(mat);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glLoadIdentity();

	glMultMatrixf(rightMatrix);
	glMultMatrixf(mat);
	glColorMask(0.0, 1.0, 1.0, 1.0);
	glRotatef((GLfloat)big, 0.0, 1.0, 0.0);
	glutSolidTeapot(2.0);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	//glPopMatrix();  
	//if(isLeftEye)  
	//{   
	//  glMatrixMode(GL_PROJECTION);  
	//  glMultMatrixf(leftPersMatrix);  

	//  glMatrixMode(GL_MODELVIEW);  
	//  glMultMatrixf(leftMatrix);  
	//  glColorMask(1.0, 0.0,0.0,1.0);  
	//    
	//    
	//    
	//  isLeftEye = false;  
	//}else  
	//{   
	//    
	//  glMatrixMode(GL_PROJECTION);  
	//  glMultMatrixf(rightPersMatrix);  

	//  glMatrixMode(GL_MODELVIEW);  
	//  glMultMatrixf(rightMatrix);  
	//  glColorMask(0.0, 1.0,1.0,1.0);    
	//  isLeftEye = true;  
	//}  

	//glRotatef((GLfloat) big, 0.0, 1.0, 0.0);  
	//glutSolidTeapot(1.0);  

	//glRotatef((GLfloat) big, 0.0, 1.0, 0.0);  
	//glTranslatef(3.0, 0.0, 0.0);  
	//glutSolidTeapot(0.5);  

	glutSwapBuffers();


}
void TeaPot::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.01, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, R, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void TeaPot::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'b':
		big = (big + 1) % 360;
		glutPostRedisplay();
		break;
	case 'B':
		big = (big - 1) % 360;
		glutPostRedisplay();
		break;
	case 0:                // 按ESC键时退出程序  
		exit(0);
		break;
	default:
		break;
	}
}
void TeaPot::spinDisplay(void)
{
	big = (big + 1) % 360;
	glutPostRedisplay();
}

int TeaPot::main(int argc, char** argv)
{
	TeaPot tp;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(tp.display);
	glutReshapeFunc(tp.reshape);
	glutKeyboardFunc(tp.keyboard);
	glutIdleFunc(tp.spinDisplay);
	glutMainLoop();

	return 0;
}