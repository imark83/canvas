#include <car.hpp>
#include <SOIL/SOIL.h>


Car::Car (int model) {
	p[0] = Vector2f (-1.0,-1.0);
	p[1] = Vector2f ( 1.0,-1.0);
	p[2] = Vector2f ( 1.0, 1.0);
	p[3] = Vector2f (-1.0, 1.0);
	p[4] = Vector2f ( 0.0, 1.0);
	p[5] = Vector2f ( 1.0, 1.0);
	p[6] = Vector2f ( 1.0, 0.0);
	p[7] = Vector2f ( 0.0, 0.0);

	wheelPosition = speed = 0.0;
	pedal = gear = 0;

	switch (model) {
		case DEFAULT:
			length = 4.36;
			// length = 4.0;
			width = 2.0;
			brk_acc = -15.0;
			max_acc = 2.5;
			def_acc = 1.0;
			max_speed = 30.0;
			min_speed = -8.0;
			def_speed = 1.0;
			interaxis_length = 2.62;
			// interaxis_length = 4.0;
			setScale (width/2.0, length/2.0);
			break;
	}
	caravan = NULL;
}

Car::Car (const Car &op) {
	Object::setScale (op.scale);
	Object::setPosition (op.position);
	Object::setRot (op.rotation);
	p[0] =op.p[0];
	p[1] =op.p[1];
	p[2] =op.p[2];
	p[3] =op.p[3];
	p[4] =op.p[4];
	p[5] =op.p[5];
	p[6] =op.p[6];
	p[7] =op.p[7];

	width = op.width;
	length = op.length;
	wheelPosition = op.wheelPosition;
	speed = op.speed;
	pedal = op.pedal;
	gear = op.gear;
	brk_acc = op.brk_acc;
	max_acc = op.max_acc;
	def_acc = op.def_acc;
	max_speed = op.max_speed;
	min_speed = op.min_speed;
	def_speed = op.def_speed;
	interaxis_length = op.interaxis_length;
	caravan = NULL;
}

Car::~Car () {
	if (caravan != NULL) {
		delete caravan;
	}
}

void Car::attachCaravan (int caravan_model) {
	caravan = new Caravan (caravan_model);
	// caravan->setProgram (program);
}

// void Car::setScale (float sc) {
// 	Object::setScale(sc);
// 	interaxis_length *= sc;
// }

// void Car::initBuffers () {
//
// }
void Car::render (Camera cam) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());

	Car clone(*this);
	while (clone.position.x > cam.x1)
		clone.position.x -= cam.getWidth();
	while (clone.position.x < cam.x0)
		clone.position.x += cam.getWidth();

	while (clone.position.y > cam.y1)
		clone.position.y -= cam.getHeight();
	while (clone.position.y < cam.y0)
		clone.position.y += cam.getHeight();


	Mat trans = cam.getModel() * clone.getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);
	glUniform1f (glGetUniformLocation(program, "depth"), 0.0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// RENDERIZAR CARAVANA
	if (caravan != NULL) {
		caravan->setRot (clone.rotation + caravan->angle);

		Vector2f caravanDirection (sin(M_PI*rotation/180.0), -cos(M_PI*rotation/180.0));

		// std::cout << "caravanDirection = " << caravanDirection.x << ", " << caravanDirection.y << '\n';

		Vector2f caravanPosition(clone.position);
		caravanPosition += caravanDirection * (length/2.0f);
		caravanDirection = Vector2f (sin(M_PI*caravan->rotation/180.0),
						-cos(M_PI*caravan->rotation/180.0));
		caravanPosition += caravanDirection * (caravan->length/2);


		caravan->setPosition(caravanPosition);
		caravan->render(cam);
	}

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


		float beta = atan (tan(M_PI*wheelPosition/180.0)/2.0);
		// std::cout << "beta = " << beta << '\n';

		float Rf = interaxis_length / sin(M_PI*wheelPosition/180.0);
		// std::cout << "Rf = " << Rf << '\n';
		float Rc = interaxis_length / (2.0 * sin(beta));
		// std::cout << "Rc = " << Rc << '\n';

		float omega_car = speed / Rf;
		float deltaTheta = (omega_car*millis)/1000.0;



		float aux = M_PI*rotation/180.0 + beta;

		deltaX.x = Rc * ((cos(deltaTheta)-1.0)*cos(aux) -
		 			sin(deltaTheta)*sin(aux));
		deltaX.y = Rc * ((cos(deltaTheta)-1.0)*sin(aux) +
		 			sin(deltaTheta)*cos(aux));

		move (deltaX);
		rotate (180.0*deltaTheta/M_PI);

		// IF CARAVAN, UPDATE ANGLE
		if (caravan != NULL) {
			// RADIO DE LA RUEDA TRASERA
			// std::cout << "beta ahora = " << 180.0*beta/M_PI << '\n';
			float Rr = interaxis_length / tan (M_PI*wheelPosition/180.0);
			// std::cout << "Rr = " << Rr << '\n';

			// ANGULO DE DESVIACIÓN POR VOLANDA
			float delta = atan ((length-interaxis_length)/(2.0*Rr));
			// std::cout << "delta = " << delta << '\n';

			// RADIO DE GIRO DE LA PARTE TRASERA DEL COCHE
			float Rb = Rr / cos (delta);
			// std::cout << "Rb = " << Rb << '\n';
			// VELOCIDAD EFECTIVA DE LA BOLA
			float v_b = omega_car * Rb;


			// ANGULO EFECTIVO DE LA VELOCIDAD DEL COCHE SOBRE CARAVANA
			float lambda = (M_PI*(caravan->angle)/180.0) + delta;

			float omega_caravan = v_b * sin (lambda) / caravan->axis;


			float deltaTheta_caravan = omega_caravan*millis/1000.0;

			caravan->angle += -180*(deltaTheta_caravan + deltaTheta)/M_PI;
		}

	} else {
		float deltaX = speed * deltaT;
		move (-sin(2.0*M_PI*rotation/360.0)*deltaX,
		 		cos(2.0*M_PI*rotation/360.0)*deltaX);

		// IF CARAVAN, UPDATE ANGLE
		if (caravan != NULL) {
			float deltaX = speed * millis / 1000.0;
			float deltaTheta = 180.0*sin(M_PI*wheelPosition/180.0)*
					deltaX/(M_PI*interaxis_length);
			std::cout << "angle = " << caravan->angle << '\n';
			caravan->angle += -180.0*deltaX*
					sin(M_PI*caravan->angle/180.0)/(M_PI*caravan->axis)
					- deltaTheta;
		}
	}


}
