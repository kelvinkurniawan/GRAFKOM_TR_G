#define _CRT_SECURE_NO_DEPRECATE // Force open unsafe file

#include <iostream>
#include <vector>
#include <GL/freeglut.h>

#include "_config.h";
#include "_vector.h";
#include "_loadModel.h"
#include "_loadTexture.h"

using namespace std;
Config conf;

void LoadTextures() {
	Tga info = Tga("./resources/Texture/Woman1.tga");

	glEnable(GL_TEXTURE_2D);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.GetWidth(), info.GetWidth(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, info.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void transform() {
	glRotatef(conf.xrotation, 1.0f, 0.0f, 0.0f); // Rotating horizontal
	glRotatef(conf.yrotation, 0.0f, 1.0f, 0.0f); // Rotating vertical
	glScalef(conf.scale, conf.scale, conf.scale); // Scalling
	glTranslatef(conf.xmovement, conf.ymovement, conf.zmovement); // Translate / Movement
}

void display() {

	Model model;
	model.process();

	int NTriangle = model.totalNrIndices / 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	LoadTextures();

	transform();


	for (int i = 0; i < NTriangle; i++) {
		//glColor3f(0, 0, 0);

		glBegin(GL_POLYGON);
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
	gluLookAt(0.0, 1, 8.0, 0.0, 1, 5.0, 0, 1, 0);

	//glTranslatef(0, 0, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit() {
	
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);

}

void keyboardControl(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		conf.yrotation += 5.0f;
		break;
	case 'd':
		conf.yrotation -= 5.0f;
		break;
	case 'w':
		conf.xrotation += 5.0f;
		break;
	case 's':
		conf.xrotation -= 5.0f;
		break;
	case 'q':
		if (conf.animated) {
			conf.animated = false;
			printf("Animated!");
		}
		else {
			printf("Animated!");
			conf.animated = true;
		}
		break;
	case '1':
		conf.scale += 0.2f;
		break;
	case '2':
		conf.scale -= 0.2f;
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
		conf.xmovement -= 0.025f;
		break;
	case 101:
		conf.ymovement += 0.025f;
		break;
	case 102:
		conf.xmovement += 0.025f;
		break;
	case 103:
		conf.ymovement -= 0.025f;
		break;
	}

	glutPostRedisplay();
}

void animate(int) {
	glutTimerFunc(1000 / 30, animate, 0);

	if (conf.animated)
		conf.yrotation -= 1.0f;
	else
		conf.yrotation = conf.yrotation;

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