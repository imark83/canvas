#include <object.hpp>

void Object::render (Camera cam, float depth) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());



	Mat trans = cam.getModel() * getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);
	glUniform1f (glGetUniformLocation(program, "depth"), depth);


	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
