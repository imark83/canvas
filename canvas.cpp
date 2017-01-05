#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>


#include <scene.hpp>


Vector2f windowSize (1024, 512);
Vector2f canvasSize (30, 15);

Scene scene;

void renderFunction () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	scene.render ();
	glFlush ();
}

void timerFunction (int value) {
	glutTimerFunc (33, timerFunction, value+1);

	scene.step(33);
	glutPostRedisplay();
}



void reshapeFunction(int w, int h) {
	scene.setWidth((canvasSize.x*w)/windowSize.x);
	scene.setHeight((canvasSize.y*h)/windowSize.y);
	glViewport(0,0,w,h);
}


void keyboardFunction(unsigned char key, int x, int y) {
	scene.keyboardFunction(key, x, y);
}
void specKeyboardFunction (int key, int x, int y) {
	scene.specKeyboardFunction (key, x, y);
}

void keyboardUpFunction(unsigned char key, int x, int y) {
	scene.keyboardUpFunction(key, x, y);
}

void specKeyboardUpFunction (int key, int x, int y) {
	scene.specKeyboardUpFunction (key, x, y);
}

int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutInitWindowPosition(500, 100);



	glutCreateWindow("Canvas");

	// Must be done after glut is initialized!
	// glewExperimental = GL_TRUE;
	glewInit();
	// glutIdleFunc (renderFunction);
	glutReshapeFunc(reshapeFunction);
	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(keyboardFunction);
	glutKeyboardUpFunc(keyboardUpFunction);
	glutSpecialFunc(specKeyboardFunction);
	glutSpecialUpFunc(specKeyboardUpFunction);
	glutIgnoreKeyRepeat(1);
	glutTimerFunc(33, timerFunction, 0);


	scene.init ();


	glutMainLoop();





	return 0;
}
