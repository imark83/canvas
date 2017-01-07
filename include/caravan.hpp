#ifndef __CARAVAN_HPP__
#define __CARAVAN_HPP__

#include <object.hpp>
#include <camera.hpp>
#include <math2d.hpp>

class Caravan : public Object {
public:


	// DESIGN VARIABLES
	float length;
	float width;
	float axis;	// distance from axis to estreme of spear
							// not including spear

	// STATUS VARIABLES
	float angle;			// angle respect to car axis

	Caravan (int = 0);


};

#endif
