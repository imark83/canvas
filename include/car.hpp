#ifndef __CAR_HPP__
#define __CAR_HPP__


#include <math2d.hpp>
#include <object.hpp>

class Car : public Object {
public:
	Vector2f p[8];

	float wheelPosition;
	float speed;
	int throttle;
	int gear;

	Car ();

	void motionStep (int millis);
	void wheelStep ();

	void initBuffers ();
	void render (Camera) const;
};
#endif
