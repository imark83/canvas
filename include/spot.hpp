#ifndef __SPOT_HPP__
#define __SPOT_HPP__

#include <object.hpp>
#include <camera.hpp>
#include <math2d.hpp>

class Spot : public Object {
public:
	Vector2f p[8];
	float width;
	float length;

	Spot (float = 4.0, float = 6.5);
	
	void render (Camera) const;


};
#endif
