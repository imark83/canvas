#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>


#include <object.hpp>
#include <loadShaders.h>
#include <triangle.hpp>

Triangle tr;


void renderFunction () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	tr.render ();
	glFlush ();
}

void init () {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// vertex arrays and buffers
	// glGenVertexArrays (1, &vao);
	// glGenBuffers (1, &buffer);

	tr.initBuffers ();

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	tr.setProgram (loadShaders (shaders));
	glUseProgram (tr.getProgram ());
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


	init ();


	glutDisplayFunc(renderFunction);
	glutMainLoop();





	return 0;
}
