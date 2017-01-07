#ifndef __SPOT_HPP__
#define __SPOT_HPP__

#include <object.hpp>
#include <camera.hpp>
#include <math2d.hpp>

class Spot : public Object {
public:
	float width;
	float length;

	Spot (float = 4.0, float = 6.5);



};
#endif
