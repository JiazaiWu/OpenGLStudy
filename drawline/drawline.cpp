#include<GL/glut.h>
#include<cmath>
#include<iostream>

using namespace std;

int x_1 = 0;
int y_1 = 0;
int x_2 = 200; //y1 is declared??
int y_2 = 300;

void Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void Reshape(int w, int h)
{
	/*show whole window*/
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	/*tell what you will do
	  GL_PROJECTION
	  GL_MODELVIEW
	  GL_TEXTURE*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void DDA()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glPointSize(1);

	/*to draw*/
	float stepLen = fabs(x_2-x_1) > fabs(y_2-y_1) ? fabs(x_2-x_1) : fabs(y_2-y_1);
	cout << "steplen " << stepLen << endl;

	float dx = (float) (x_2 - x_1) / stepLen;
	float dy = (float) (y_2 - y_1) / stepLen;
	cout << "dx " << dx << " dy " << dy << endl;

	/* count steplen, transfer to Int when draw*/
	float x = x_1;
	float y = y_1;

	glBegin(GL_POINTS);
	for (int i = 0; i < stepLen; i++) {
		
		glVertex2i((int)x, (int)y);

		x += dx;
		y += dy;
	}
	/*end draw*/
	glEnd();

	/*make show*/
	glFlush();
}


int main(int argc,  char *argv[])
{
	void (*myDisplay)();
	myDisplay = DDA;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("draw line");
	Init();
	glutDisplayFunc(myDisplay);
	
	/*Reshape function must exist,
	  otherwise no line show*/
	glutReshapeFunc(&Reshape);
	glutMainLoop();
	return 0;
}