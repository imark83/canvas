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
	pedal = gear = 0;

	brk_acc = -10.0;
	max_acc = 2.5;
	def_acc = 1.0;
	max_speed = 10.0;
	min_speed = -8.0;
	def_speed = 3.0;

	interaxis_length = 2.0;
}

void Car::setScale (float sc) {
	Object::setScale(sc);
	interaxis_length *= sc;
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
void Car::wheelStep (float angle) {
	wheelPosition += angle;
	if (wheelPosition > 40) wheelPosition = 40;
	if (wheelPosition < -40) wheelPosition = -40;
}


void Car::turnLeft () {
	steeringOrientation = 1;
}
void Car::turnRight () {
	steeringOrientation = -1;
}
void Car::releaseHandle () {
	steeringOrientation = 0;
}

void Car::throttle () {
	pedal = 1;
}
void Car::brake () {
	pedal = -1;
}
void Car::releasePedal () {
	pedal = 0;
}
void Car::gearUp () {
	++gear;
	if (gear > 1) gear = 1;
}
void Car::gearDown () {
	--gear;
	if (gear < -1) gear = -1;
}

// ACTUALIZAR POSICION DE COCHE DE ACUERDO CON EL CONTROL
void Car::motionStep (int millis) {
	// update speed
	float deltaV;
	float deltaT = (millis/1000.0);
	switch (pedal) {
		case -1:
			deltaV = brk_acc * sgn<float>(speed) * deltaT;
			if (fabs(deltaV) > fabs(speed)) speed = 0;
			else speed += deltaV;
			break;
		case 1:
			if (gear == 0) break;
			deltaV = max_acc * gear * deltaT;
			speed += deltaV;
			if (speed > max_speed) speed = max_speed;
			if (speed < min_speed) speed = min_speed;
			break;
		case 0:
			if (gear == 0) break;
			deltaV = sgn<float> (def_speed*gear - speed) * def_acc * deltaT;
			float vf = speed + deltaV;
			if ((vf - def_speed*gear)*(speed - def_speed*gear) < 0.0)
				speed = def_speed*gear;
			else speed = vf;
			break;
	}

	// UPDATE STEERING WHEEL
	switch (steeringOrientation) {
		case 1: wheelStep(2.0);
			break;
		case -1: wheelStep(-2.0);
			break;
	}

	// MOVE THE CAR

	if (wheelPosition != 0.0) {
		Vector2f deltaX;
		float deltaTheta =
		 		sin(2.0*M_PI*wheelPosition/360.0)*
				speed*millis/(1000.0*interaxis_length);

		float beta = atan (tan(2.0*M_PI*wheelPosition/360.0)/2.0);

		float Rc = interaxis_length / (2.0 * sin(beta));

		float aux = 2.0*M_PI*rotation/360.0 + beta;

		deltaX.x = Rc * ((cos(deltaTheta)-1.0)*cos(aux) - sin(deltaTheta)*sin(aux));
		deltaX.y = Rc * ((cos(deltaTheta)-1.0)*sin(aux) + sin(deltaTheta)*cos(aux));
		move (deltaX);
		rotate (360.0*deltaTheta/(2.0*M_PI));
	} else {
		float deltaX = speed * deltaT;
		move (-sin(2.0*M_PI*rotation/360.0)*deltaX,
		 		cos(2.0*M_PI*rotation/360.0)*deltaX);
	}

}
