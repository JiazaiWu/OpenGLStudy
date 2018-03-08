/*gcc add.c -o add -lGL -lglut*/

#include <GL/glut.h>

void myDisplay(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // white Rect

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.8f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.8f, -0.5f);
    glEnd();

    glPointSize(3);
    glBegin(GL_POINT);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.4f, 0.4f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.4f, 0.4f);
    glEnd();

    glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.4f, 0.25f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.4f, 0.25f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, -0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("hello world!");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}