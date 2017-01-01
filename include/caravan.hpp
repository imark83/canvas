#ifndef __CARAVAN_HPP__
#define __CARAVAN_HPP__

#include <object.hpp>
#include <camera.hpp>
#include <math2d.hpp>

class Caravan : public Object {
public:
	// DRAWING VARIABLES
	Vector2f p[8];			// puntos


	// DESIGN VARIABLES
	float length;
	float width;
	float axis_distance;	// distance from axis to estreme of spear
							// not including spear
	float spear_length;		// from front part

	// STATUS VARIABLES
	float angle;			// angle respect to car axis

	Caravan (int = 0);


	// INHERITED METHODS
	void initBuffers ();
	void render (Camera) const;

};

#endif
