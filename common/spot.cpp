#include <spot.hpp>
#include <SOIL/SOIL.h>

Spot::Spot (float w, float l) {
	p[0] = Vector2f (-1.0,-1.0);
	p[1] = Vector2f ( 1.0,-1.0);
	p[2] = Vector2f ( 1.0, 1.0);
	p[3] = Vector2f (-1.0, 1.0);
	p[4] = Vector2f ( 0.0, 1.0);
	p[5] = Vector2f ( 1.0, 1.0);
	p[6] = Vector2f ( 1.0, 0.0);
	p[7] = Vector2f ( 0.0, 0.0);

	width = w;
	length = l;

	setScale (width/2.0, length/2.0);

}
