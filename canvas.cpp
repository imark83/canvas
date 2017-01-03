#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>


#include <object.hpp>
#include <loadShaders.h>
#include <car.hpp>


Vector2f windowSize (1024, 512);
Vector2f canvasSize (40, 20);
Car car;
Camera cam(canvasSize.x, canvasSize.y);

void renderFunction () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	car.render (cam);
	glFlush ();
}

void timerFunction (int value) {
	// car.setRot (-value);
	// car.move ((float) sin(value/3600), cos(value/3600));
	car.motionStep(33);
	std::cout << "speed = " << car.speed << std::endl;
	std::cout << "steering angle = " << car.wheelPosition << '\n' << std::endl;



	glutPostRedisplay();
	glutTimerFunc (33, timerFunction, value+1);
}


void init () {
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearColor (26.0/256.0, 102.0/256.0, 46.0/256.0, 1.0f);
	// glClearColor(0.12500f, 0.57812f, 0.11719f, 1.0f);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	car.setProgram (loadShaders (shaders));
	glUseProgram (car.getProgram ());


	car.initBuffers ();
	car.move(10, 10);
	car.setRot (-90);

	car.attachCaravan();
	car.caravan->setProgram(car.getProgram());
	car.caravan->initBuffers ();
	car.caravan->angle = 90;
	car.wheelPosition = 00;


	// car.speed=1;
	// car.wheelPosition = -89.99;
}

void reshapeFunction(int w, int h) {
	cam.setWidth((canvasSize.x*w)/windowSize.x);
	cam.setHeight((canvasSize.y*h)/windowSize.y);
	glViewport(0,0,w,h);
}


void keyboardFunction(unsigned char key, int x, int y) {
	// std::cout << "key pressed" << '\n';
	switch (key) {
		case 'a':
		case 'A':
			car.gearUp();
			// std::cout << "gear = " << car.gear << '\n';
			break;
		case 'z':
		case 'Z':
			car.gearDown();
			// std::cout << "gear = " << car.gear << '\n';
			break;
	}
}
void specKeyboardFunction (int key, int x, int y) {
	// std::cout << "special key pressed" << '\n';
	switch (key) {
		case GLUT_KEY_UP:
			car.throttle ();
			// std::cout << "pedal = " << car.pedal << '\n';
			break;
		case GLUT_KEY_DOWN:
			car.brake();
			// std::cout << "pedal = " << car.pedal << '\n';
			break;
		case GLUT_KEY_LEFT:
			car.turnLeft();
			break;
		case GLUT_KEY_RIGHT:
			car.turnRight();
			break;
	}
}

void keyboardUpFunction(unsigned char key, int x, int y) {
	// std::cout << "key released" << '\n';
	// switch (key) {
	// 	case 'a':
	// 	case 'A':
	// 		break;
	// 	case 'z':
	// 	case 'Z':
	// 		break;
	// }
}

void specKeyboardUpFunction (int key, int x, int y) {
	// std::cout << "special key released" << '\n';
	switch (key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			car.releasePedal ();
			// std::cout << "pedal = " << car.pedal << '\n';
			break;
		case GLUT_KEY_LEFT:
			car.releaseHandle();
			break;
		case GLUT_KEY_RIGHT:
			car.releaseHandle();
			break;
	}
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


	init ();


	glutMainLoop();





	return 0;
}
