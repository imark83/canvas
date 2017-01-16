#include <ground.hpp>
// #include <SOIL/SOIL.h>

Ground::Ground (float w, float h) {
	width = w; height = h;
	p[0] = Vector2f (-1.0, -1.0);
	p[1] = Vector2f ( 1.0, -1.0);
	p[2] = Vector2f ( 1.0,  1.0);
	p[3] = Vector2f (-1.0,  1.0);
	p[4] = Vector2f (0.0, 0.0);
	p[5] = Vector2f (1.0, 0.0);
	p[6] = Vector2f (1.0, 1.0);
	p[7] = Vector2f (0.0, 1.0);
}

void Ground::render (Camera cam, float depth) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());



	Mat trans = getModel();
	glUniform2f (glGetUniformLocation(program, "size"), 10.0, 20.0);
	glUniform1f (glGetUniformLocation(program, "depth"), depth);


	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
