#define _CRT_SECURE_NO_DEPRECATE // Force open unsafe file

#include <iostream>
#include <vector>
#include <GL/freeglut.h>

#include "_config.h";
#include "_vector.h";
#include "_loadModel.h"
#include "_loadTexture.h"

using namespace std;

bool animated = false;
float xrotation = 0.0f;
float yrotation = 0.0f;

float scale = 1.0f;
float xmovement = 0.0f;
float ymovement = 0.0f;
float zmovement = 0.0f;

bool WIREFRAME = false;

void LoadTextures() {
	Tga info = Tga("./resources/Texture/Woman1.tga");

	glEnable(GL_TEXTURE_2D);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, info.HasAlphaChannel() ? GL_RGBA : GL_RGB, info.GetWidth(), info.GetWidth(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, info.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void transform() {
	glRotatef(xrotation, 1.0f, 0.0f, 0.0f); // Rotating horizontal
	glRotatef(yrotation, 0.0f, 1.0f, 0.0f); // Rotating vertical
	glScalef(scale, scale, scale); // Scalling
	glTranslatef(xmovement, ymovement, zmovement); // Translate / Movement
}

void display() {

	Model model;
	model.process();

	int NTriangle = model.totalNrIndices / 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	LoadTextures();

	gluLookAt(0.0, 2.0, 8.0, 0.0, 1.5, 5.0, 0, 1, 0);

	transform();


	for (int i = 0; i < NTriangle; i++) {

		if (WIREFRAME)
		{
			glColor4f(0, 0, 0, 1.0);
			glBegin(GL_LINE_LOOP);
		}
		else {
			glColor4f(1, 1, 1, 0.0);
			glBegin(GL_POLYGON);
		}

		glTexCoord2f(model.myVertex[model.myPattern[i].pos.x].uv.x, model.myVertex[model.myPattern[i].pos.x].uv.y);
		glVertex3f(model.myVertex[model.myPattern[i].pos.x].pos.x, model.myVertex[model.myPattern[i].pos.x].pos.y, model.myVertex[model.myPattern[i].pos.x].pos.z);
		glTexCoord2f(model.myVertex[model.myPattern[i].pos.y].uv.x, model.myVertex[model.myPattern[i].pos.y].uv.y);
		glVertex3f(model.myVertex[model.myPattern[i].pos.y].pos.x, model.myVertex[model.myPattern[i].pos.y].pos.y, model.myVertex[model.myPattern[i].pos.y].pos.z);
		glTexCoord2f(model.myVertex[model.myPattern[i].pos.z].uv.x, model.myVertex[model.myPattern[i].pos.z].uv.y);
		glVertex3f(model.myVertex[model.myPattern[i].pos.z].pos.x, model.myVertex[model.myPattern[i].pos.z].pos.y, model.myVertex[model.myPattern[i].pos.z].pos.z);
		glEnd();

		//printf("%f", model.myVertex[model.myPattern[i].pos.x].uv.x);
		//printf("%d. %d, %d, %d\n", i, model.myPattern[i].pos.x, model.myPattern[i].pos.y, model.myPattern[i].pos.z);

	}

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w > h) {
		glViewport(0, 0, w, w);
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glScalef(-0.5, 0.5, -0.5);
	}
	else {
		glViewport(0, 0, w, h);
	}

	gluPerspective(20.0, w / h, 0.1f, 100.0f);

	//glTranslatef(0, 0, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
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
	case 'q':
		if (animated) {
			animated = false;
			printf("Animated!");
		}
		else {
			printf("Animated!");
			animated = true;
		}
		break;
	case '1':
		scale += 0.2f;
		break;
	case '2':
		scale -= 0.2f;
		break;
	case 27:
		exit(1);
		break;
	case 'l':
		if (WIREFRAME) WIREFRAME = false;
		else WIREFRAME = true;
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

void animate(int) {
	glutTimerFunc(1000 / 30, animate, 0);

	if (animated)
		yrotation -= 1.0f;
	else
		yrotation = yrotation;

	glutPostRedisplay();
}

int main(int argc, char** argv) {

	Config conf;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(conf.windowWidth, conf.windowHeight);
	glutInitWindowPosition(conf.windowPositionX, conf.windowPositionY);
	glutCreateWindow("TR GRAFIKA KOMPUTER DOSEN");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardControl);
	glutSpecialFunc(keyboardSpecialControl);
	glutTimerFunc(0, animate, 0);

	cout << " << Help" << endl << endl;
	cout << " >> W, A, S, D to rotate" << endl;
	cout << " >> 1, 2 to scaling" << endl;
	cout << " >> Arrow to move camera" << endl;

	myinit();
	glutMainLoop();

	return 0;

}