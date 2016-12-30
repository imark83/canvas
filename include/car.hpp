#ifndef __CAR_HPP__
#define __CAR_HPP__


#include <math2d.hpp>
#include <object.hpp>


enum model_t {DEFAULT, ROVER};

class Car : public Object {
public:

	// GEOMETRIA DEL COCHE
	float interaxis_length;

	Vector2f p[8];

	// VARIABLES DE ESTADO DE CONTROL DE COCHE
	float wheelPosition; // con respecto al eje del coche
	int pedal;	// -1 brake, +1 accelerate, 0 none
	int gear;		// -1 0 1 2
	int steeringOrientation; // +1-> Left, 0->None, -1-> Right


	// VARIABLES DE PRESTACIONES DEL COCHE
	float brk_acc;			// aceleracion del freno
	float max_acc;			// aceleracion maxima (drive and rear)
	float def_acc;			// aceleracion/deceleracion a ralenti
	float max_speed;		// velocidad maxima hacia adelante
	float min_speed;		// velocidad maxima hacia atras
	float def_speed;		// velocidad de ralenti (drive and rear)


	// VARIABLE FISICAS (JUNTAR CON LAS DE OBJECT)
	// JUNTAR CON POSITION, ROTATION
	float speed;

	Car (int = 0);
	Car (const Car &op);
	void setScale (float sc);

	// CAMBIAR CONTROL DE COCHE
	void wheelStep (float angle);
	void throttle ();
	void brake ();
	void releasePedal ();
	void gearUp ();
	void gearDown ();
	void turnLeft ();
	void turnRight ();
	void releaseHandle ();

	// ACTUALIZAR POSICION DE COCHE DE ACUERDO CON EL CONTROL
	void motionStep (int millis);

	void initBuffers ();
	void render (Camera) const;
};
#endif
