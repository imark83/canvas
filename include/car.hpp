#ifndef __CAR_HPP__
#define __CAR_HPP__


#include <math2d.hpp>
#include <object.hpp>

class Car : public Object {
public:
	Vector2f p[8];

	// VARIABLES DE ESTADO DE CONTROL DE COCHE
	float wheelPosition; // con respecto al eje del coche
	int pedal;	// 
	int gear;

	// VARIABLE FISICAS (JUNTAR CON LAS DE OBJECT)
	// JUNTAR CON POSITION, ROTATION
	float speed;

	Car ();

	// CAMBIAR CONTROL DE COCHE
	void wheelStep (float angle;);
	void accelerate ();
	void stop ();
	void none ();

	// ACTUALIZAR POSICION DE COCHE DE ACUERDO CON EL CONTROL
	void motionStep (int millis);

	void initBuffers ();
	void render (Camera) const;
};
#endif
