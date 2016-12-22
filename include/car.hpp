#ifndef __CAR_HPP__
#define __CAR_HPP__


#include <math2d.hpp>
#include <object.hpp>

class Car : public Object {
public:
	Vector2f p[8];

	Car () {
		p[0] = Vector2f (-0.5,-1.0);
		p[1] = Vector2f ( 0.5,-1.0);
		p[2] = Vector2f ( 0.5, 1.0);
		p[3] = Vector2f (-0.5, 1.0);
		p[4] = Vector2f ( 0.0, 1.0);
		p[5] = Vector2f ( 1.0, 1.0);
		p[6] = Vector2f ( 1.0, 0.0);
		p[7] = Vector2f ( 0.0, 0.0);
	}


	void initBuffers ();
	void render (Camera) const;
};
#endif
