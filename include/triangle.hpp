#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include <math2d.hpp>
#include <object.hpp>

class Triangle : public Object {
public:
	Vector2f p[3];

	Triangle () {
		p[0].x = 0.0; p[0].y = 1.0;
		p[1].x = 0.86603; p[1].y = -0.5;
		p[2].x = -0.86603; p[2].y = -0.5;
	}

	void initBuffers ();
	void render (Camera) const;
};
#endif
