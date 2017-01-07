#include "caravan.hpp"
#include <SOIL/SOIL.h>

Caravan::Caravan (int caravan_model) {

	// DESIGN VARIABLES
	length = 5.9;
	width = 2.5;
	axis = 3.55;	// distance from axis to estreme of spear
							// not including spear

	// STATUS VARIABLES
	angle = 0.0;			// angle respect to car axis

	// points
	p[0] = Vector2f (-1.0,-1.0);
	p[1] = Vector2f ( 1.0,-1.0);
	p[2] = Vector2f ( 1.0, 1.0);
	p[3] = Vector2f (-1.0, 1.0);
	p[4] = Vector2f ( 1.0, 1.0);
	p[5] = Vector2f ( 1.0, 0.0);
	p[6] = Vector2f ( 0.0, 0.0);
	p[7] = Vector2f ( 0.0, 1.0);

	setScale (width/2.0, length/2.0);

}


void Caravan::render (Camera cam) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());



	Mat trans = cam.getModel() * getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);
	glUniform1f (glGetUniformLocation(program, "depth"), 0.5);


	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
