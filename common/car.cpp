#include <car.hpp>


void Car::initBuffers () {
	GLuint vao, buffer[2];
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, buffer);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, buffer[0]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (p), p, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
	glEnableVertexAttribArray (0);

	setVao (vao); setBuffer (buffer[0]);

}
void Car::render (Camera cam) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());


	Mat trans = cam.getModel() * getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}
