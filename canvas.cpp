#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include <object.hpp>
#include <math2d.hpp>


#include <math2d.hpp>
#include <loadShaders.h>


GLuint vao;	// vertex array object
GLuint buffer; // vertex buffer object
GLuint program;


void renderFunction () {

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	glBindVertexArray (vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);	// dibuja

	std::cout << "drawn" << std::endl;
	glFlush ();

}

void init () {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// vertex arrays and buffers
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, &buffer);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	program = loadShaders (shaders);
	glUseProgram (program);


	// mem buffers
	Point2f point [3];
	point[0] = Point2f (0.0, 0.0);
	point[1] = Point2f (1.0, 0.0);
	point[2] = Point2f (-1.0, 2.0);

	std::cout << "size of point = " << sizeof (point) << std::endl;

	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
	glBufferData (GL_ARRAY_BUFFER, sizeof (point), point, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
	glEnableVertexAttribArray (0);


	// ShaderInfo shaders[] = {
	// 	{GL_VERTEX_SHADER, "default.vs.glsl"},
	// 	{GL_FRAGMENT_SHADER, "default.fs.glsl"},
	// 	{GL_NONE, NULL}};

	// program = loadShaders (shaders);
	// glUseProgram (program);

}



int main(int argc, char *argv[]) {
	// init glut
	glutInit(&argc, argv);
	// init display con DEPTH Y RGBA
	glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);



	glutCreateWindow("Tutorial 03");

	// Must be done after glut is initialized!
	// glewExperimental = GL_TRUE;
	glewInit();


	init ();


	glutDisplayFunc(renderFunction);
	glutMainLoop();





	return 0;
}
