#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include <object.hpp>
#include <math2d.hpp>
#include <camera.hpp>

class Ground : public Object {
public:
	float width;
	float height;

	Ground (float = 1.0, float = 1.0);

	float getWidth () {return width;}
	float getHeight () {return height;}

	void setWidth (float w) {
		setScale (w/width, 1.0);
		width = w;
	}
	void setHeight (float h) {
		setScale (1.0, h/height);
		height = h;
	}

	void render (Camera cam, float depth) const;

};
#endif
