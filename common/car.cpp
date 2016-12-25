#include <car.hpp>
#include <SOIL/SOIL.h>


Car::Car () {
	p[0] = Vector2f (-0.5,-1.0);
	p[1] = Vector2f ( 0.5,-1.0);
	p[2] = Vector2f ( 0.5, 1.0);
	p[3] = Vector2f (-0.5, 1.0);
	p[4] = Vector2f ( 0.0, 1.0);
	p[5] = Vector2f ( 1.0, 1.0);
	p[6] = Vector2f ( 1.0, 0.0);
	p[7] = Vector2f ( 0.0, 0.0);

	wheelPosition = speed = 0.0;
	throttle = gear = 0;
}

void Car::initBuffers () {
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
	image = SOIL_load_image("car.png", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	SOIL_free_image_data(image);



	setVao (vao); setBuffer (buffer); setTexture (texture);

}
void Car::render (Camera cam) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());


	Mat trans = cam.getModel() * getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}



// CAMBIAR CONTROL DE COCHE
void wheelStep (float angle) {
	wheelPosition += angle;
	if (wheelPosition > 40) angle = 40;
	if (wheelPosition < -40) angle = -40;
}
void throttle () {
	pedal = 1;
}
void brake () {
	pedal = -1;
}
void gearUp () {
	++gear;
	if (gear > 2) gear = 2;
}
void gearDown () {
	--gear;
	if (gear < -1) gear = -1;
}

// ACTUALIZAR POSICION DE COCHE DE ACUERDO CON EL CONTROL
void motionStep (int millis) {
	// update speed
	float acceleration;
	switch (pedal) {
		case -1:
			if (speed > 0) acceleration = -30;
			else if (speed == 0) acceleration = 0.0;
			else acceleration = +30;
			break;
		case 0:
			if (speed > 1) acceleration = -2;
			else if (speed == )
	}
	switch (gear) {
		case -1:
			switch (pedal) {
				case 0:
			}
			break;
		case 0:
		case 1:
		case 2:
	}
	if (speed >= 20 * geal)
	// primer prototipo.

}
