#include <iostream>
#include <cmath>
#include <GL/glut.h>

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = -100.0, xwcMax = 500.0;
GLfloat ywcMin = -100.0, ywcMax = 500.0;

class wcPt3D
{
public:
	GLfloat x, y, z;
};

void Init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void rotate3D(wcPt3D p1, wcPt3D p2, GLfloat thetaDegrees)
{
	/* vector of rotate*/
	float vx = (p2.x - p1.x);
	float vy = (p2.y - p1.y);
	float vz = (p2.z - p1.z);

	glTranslatef(p1.x, p1.y, p1.z);
	glRotatef(thetaDegrees, vx, vy, vz);
	glTranslatef(-p1.x, -p1.y, -p1.z);
}

void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
	glTranslatef(fixedPt.x, fixedPt.y, fixedPt.z);
	glScalef(sx, sy, sz);
	glTranslatef(-fixedPt.x, -fixedPt.y, -fixedPt.z);
}

void displayFunc()
{
	wcPt3D centroidPt, R_p1, R_p2;

	centroidPt.x = 50;
	centroidPt.y = 100;
	centroidPt.z = 0;

	R_p1 = centroidPt;

	R_p2.x = 50;
	R_p2.y = 100;
	R_p2.z = 1;

	wcPt3D p1, p2, fixedPt;
	p1 = R_p1;
	p2 = R_p2;
	fixedPt=centroidPt;

	GLfloat tx = 0.0, ty = 100.0, tz = 0.0;
	GLfloat sx = 0.5, sy = 0.5, sz = 1.0;
	GLdouble thetaDegrees = 90.0;

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.0, 0.0, 1.0);
	glRecti(50, 100, 200, 150);

	glTranslatef(tx, ty, tz);
	glColor3f(0.0, 1.0, 0.0);
	glRecti(50, 100, 200, 150);

	scale3D(sx, sy, sz, fixedPt);
	glColor3f(1.0, 0.0, 0.0);
	glRecti(50, 100, 200, 150);

	rotate3D(p1, p2, thetaDegrees);
	glColor3f(0.0, 0.0, 0.0);
	glRecti(50, 100, 200, 150);

	glFlush();

}

void Reshape(int w, int h)
{
	/*show whole window*/
	//glViewport(0, 0, (GLsizei)winWidth, (GLsizei)winHeight);

	/*tell what you will do
	  GL_PROJECTION
	  GL_MODELVIEW
	  GL_TEXTURE*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("transform");
	Init();
	glutDisplayFunc(&displayFunc);
	glutReshapeFunc(&Reshape);
	glutMainLoop();

	return 0;
}