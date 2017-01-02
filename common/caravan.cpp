#include "caravan.hpp"
#include <SOIL/SOIL.h>

Caravan::Caravan (int caravan_model) {

	// DESIGN VARIABLES
	length = 5.2;
	width = 2.2;
	axis_distance = 3.95;	// distance from axis to estreme of spear
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


// INHERITED METHODS
void Caravan::initBuffers () {
	glUseProgram (getProgram());
	// VERTEX ARRAY Y BUFFER
	GLuint vao, buffer;
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, &buffer);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);

	glBufferData (GL_ARRAY_BUFFER, sizeof (p), p, GL_STATIC_DRAW);


	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
			(const void*) 0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0,
			(const void*)( 8*sizeof(GLfloat)));
	glEnableVertexAttribArray (1);


	// PREPARE TEXTURE image
	glActiveTexture(GL_TEXTURE0);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int img_width, img_height;
	unsigned char *image;
	image = SOIL_load_image("caravan.png", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	SOIL_free_image_data(image);

	setVao (vao); setBuffer (buffer); setTexture (texture);

}
void Caravan::render (Camera cam) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());



	Mat trans = cam.getModel() * getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
