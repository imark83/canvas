#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>


#include <object.hpp>
#include <loadShaders.h>
#include <car.hpp>

Car car;
Camera cam(2.0, 2.0);

void renderFunction () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	car.render (cam);
	glFlush ();
	car.move(0.00011, 0.0);
}


void init () {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	car.initBuffers ();
	car.setScale (0.5);
	car.move(2.0, 1.0);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	car.setProgram (loadShaders (shaders));
	glUseProgram (car.getProgram ());
}

void reshapeFunction(int w, int h) {
	std::cout << "reshape! w = " << w << std::endl;
	cam.setWidth((2.0*w)/512.0);
	cam.setHeight((2.0*h)/512.0);
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
	glutIdleFunc (renderFunction);
	glutReshapeFunc(reshapeFunction);
	glutDisplayFunc(renderFunction);


	init ();


	glutMainLoop();





	return 0;
}
