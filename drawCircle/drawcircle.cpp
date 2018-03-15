#include <iostream>
#include <GL/glut.h>

int x = 400;
int y = 400;
int r = 200;

void Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
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

inline void drawCircle(int x, int y, int x0, int y0) {
	glVertex2i(x+x0, y+y0);
	glVertex2i(x+y0, y+x0);
	glVertex2i(x-x0, y-y0);
	glVertex2i(x-y0, y-x0);
	glVertex2i(x+x0, y-y0);
	glVertex2i(x+y0, y-x0);
	glVertex2i(x-x0, y+y0);
	glVertex2i(x-y0, y+x0);
}

void bresenhamCircle() {
	int x0 = 0;
	int y0 = r;
	int d = 3-2*r;
	glBegin(GL_POINTS);
	while (y0 > x0) {
		//for all 8 part
		{
			drawCircle(x, y, x0, y0);
		}
		if (d < 0) {
			d += 4*x0 + 6;
			x0++;
		} else {
			d += 4*(x0-y0) + 10;
			x0++; y0--;
		}

		/*trade off*/
		if (x0 == y0) {
			drawCircle(x, y, x0, y0);
		}
	}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("draw circle");
	Init();
	glutDisplayFunc(&bresenhamCircle);
	glutReshapeFunc(&Reshape);
	glutMainLoop();

	return 0;
}