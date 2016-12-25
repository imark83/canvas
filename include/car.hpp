#ifndef __CAR_HPP__
#define __CAR_HPP__


#include <math2d.hpp>
#include <object.hpp>

class Car : public Object {
public:
	Vector2f p[8];

	// VARIABLES DE ESTADO DE CONTROL DE COCHE
	float wheelPosition; // con respecto al eje del coche
	int pedal;	// -1 brake, +1 accelerate, 0 none
	int gear;		// -1 0 1 2

	// VARIABLE FISICAS (JUNTAR CON LAS DE OBJECT)
	// JUNTAR CON POSITION, ROTATION
	float speed;

	Car ();

	// CAMBIAR CONTROL DE COCHE
	void wheelStep (float angle);
	void throttle ();
	void brake ();
	void gearUp ();
	void gearDown ();

	// ACTUALIZAR POSICION DE COCHE DE ACUERDO CON EL CONTROL
	void motionStep (int millis);

	void initBuffers ();
	void render (Camera) const;
};
#endif
