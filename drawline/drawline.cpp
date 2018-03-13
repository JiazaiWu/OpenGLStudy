#include<GL/glut.h>
#include<cmath>
#include<functional>
#include<iostream>

using namespace std;

template<typename T>
void swap_value(T& a, T& b) {
	auto x = a;
	a = b;
	b = x;
}

int x_1 = 50;
int y_1 = 300;
int x_2 = 400; //y1 is declared??
int y_2 = 50;

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

void DDA()
{
	/*to draw*/
	float stepLen = fabs(x_2-x_1) > fabs(y_2-y_1) ? fabs(x_2-x_1) : fabs(y_2-y_1);

	float dx = (float) (x_2 - x_1) / stepLen;
	float dy = (float) (y_2 - y_1) / stepLen;

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

void compare()
{
	int nx, ny, offx, offy;
	int F = 0;
	int x = 0, y = 0;

	if (y_2 > y_1) {
		nx = x_2 - x_1;
		ny = y_2 - y_1;
		offx = x_1;
		offy = y_1;
	} else {
		nx = x_1 - x_2;
		ny = y_1 - y_2;
		offx = x_2;
		offy = y_2;
	}

	cout << nx << " " << ny << endl;
	int stepLen = abs(nx) + abs(ny);

	glBegin(GL_POINTS);
	for (int i = 0; i < stepLen; i++) {
		glVertex2i(x+offx, y+offy);
		if (nx > 0) {
			/*line in 1st region*/
			if (F >= 0) {
				x++; F -= ny;
			} else {
				y++; F += nx;
			}
		} else {
			/*line in 2nd region*/
			if (F >= 0) {
				y++; F += nx;
			} else {
				/*notice in 2nd region
				  x will decrease when step move on*/
				x--; F += ny;
			}
		}
	}

	/*end draw*/
	glEnd();

	/*make show*/
	glFlush();
}


void bresenham()
{
	int dx = abs(x_2-x_1);
	int dy = abs(y_2-y_1);
	int flag = 0;

	if (dy > dx) { //make k (-1, 1)
		flag = 1;
		swap_value(x_1, y_1);
		swap_value(x_2, y_2);
		swap_value(dx, dy);
	}

	int tx = (x_2 > x_1) ? 1:-1;
	int ty = (y_2 > y_1) ? 1:-1;
	int x = x_1;
	int y = y_1;
	int dS = 2*dy;
	int dT = 2*(dy-dx);
	int d = dS-dx; // first node's d

	glBegin(GL_POINTS);
	for (int i = 0; i < dx; i++) {
		if(flag){
			glVertex2i(y, x);
		} else {
			glVertex2i(x, y);
		}

		if(d < 0) {
			d += dS;
			x += tx;
		}
		else {
			d +=dT;
			y += ty;
			x += tx;
		}

	}
	glEnd();
	glFlush();
}


int main(int argc,  char *argv[])
{
	void (*myDisplay)();

	//myDisplay = DDA;
	myDisplay = bresenham;

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