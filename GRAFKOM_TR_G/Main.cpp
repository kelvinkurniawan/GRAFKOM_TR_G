#include <iostream>
#include <GL/freeglut.h>

using namespace std;

float xrotation = 0.0f;
float yrotation = 0.0f;

float scale = 1.0f;
float xmovement = 0.0f;
float ymovement = 0.0f;
float zmovement = 0.0f;

void drawObject() {
	glColor3f(1.0, 0.0, 0.0);

	// Depan
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);

	// Belakang
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, 0.5);	//A
	glVertex3f(0.5, 0.5, 0.5);	//B 
	glVertex3f(0.5, -0.5, 0.5);	//C
	glVertex3f(-0.5, -0.5, 0.5);//D
	glEnd();

	glColor3f(1.0, 0.0, 1.0);

	// Kanan
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);

	// Kiri
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);

	// Bawah
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);

	// Atas
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	glRotatef(xrotation, 1.0f, 0.0f, 0.0f); // Rotating horizontal
	glRotatef(yrotation, 0.0f, 1.0f, 0.0f); // Rotating vertical
	glScalef(scale, scale, scale); // Scalling
	glTranslatef(xmovement, ymovement, zmovement); // Translate / Movement

	drawObject();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void keyboardControl(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		yrotation += 5.0f;
		break;
	case 'd':
		yrotation -= 5.0f;
		break;
	case 'w':
		xrotation += 5.0f;
		break;
	case 's':
		xrotation -= 5.0f;
		break;
	case '1':
		scale += 0.05f;
		break;
	case '2':
		scale -= 0.05f;
		break;
	case 27:
		exit(1);
		break;
	}

	glutPostRedisplay();
}

void keyboardSpecialControl(int key, int x, int y) {

	switch (key) {
	case 100:
		xmovement -= 0.025f;
		break;
	case 101:
		ymovement += 0.025f;
		break;
	case 102:
		xmovement += 0.025f;
		break;
	case 103:
		ymovement -= 0.025f;
		break;
	}

	glutPostRedisplay();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("TR GRAFIKA KOMPUTER DOSEN");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardControl);
	glutSpecialFunc(keyboardSpecialControl);

	myinit();
	glutMainLoop();

	return 0;

}