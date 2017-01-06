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

	Spot (float = 3.0, float = 6.0);

	virtual void initBuffers ();
	virtual void render (Camera) const;


};
#endif
