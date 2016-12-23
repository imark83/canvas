#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>


#include <object.hpp>
#include <loadShaders.h>
#include <car.hpp>


Vector2f windowSize (512, 512);
Vector2f canvasSize (5, 5);
Car car;
Camera cam(canvasSize.x, canvasSize.y);

void renderFunction () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	car.render (cam);
	glFlush ();
}

void timerFunction (int value) {
	std::cout << value << std::endl;
	car.setPosition(2.5+2.0*cos(2.0*M_PI*value/360.0), 2.5+2.0*sin(2.0*M_PI*value/360.0));
	car.setRot (-value);
	// car.move ((float) sin(value/3600), cos(value/3600));
	glutPostRedisplay();
	glutTimerFunc (33, timerFunction, value+1);

}


void init () {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	car.setProgram (loadShaders (shaders));
	glUseProgram (car.getProgram ());


	car.initBuffers ();
	car.setScale (0.5);
	car.move(1.0, 1.0);
}

void reshapeFunction(int w, int h) {
	cam.setWidth((canvasSize.x*w)/windowSize.x);
	cam.setHeight((canvasSize.y*h)/windowSize.y);
	glViewport(0,0,w,h);
}



int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);



	glutCreateWindow("Canvas");

	// Must be done after glut is initialized!
	// glewExperimental = GL_TRUE;
	glewInit();
	// glutIdleFunc (renderFunction);
	glutReshapeFunc(reshapeFunction);
	glutDisplayFunc(renderFunction);

	glutTimerFunc(33, timerFunction, 0);


	init ();


	glutMainLoop();





	return 0;
}
