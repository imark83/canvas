#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <matrix.hpp>
class Camera {
public:

	float x0;
	float x1;
	float y0;
	float y1;

	Camera () {x0=y0=0.0; x1=y1=1.0;}
	Camera (float w, float h) {x0=y0=0.0; x1=w; y1=h;}
	Camera (float _x0, float _x1, float _y0, float _y1) {
		x0 = _x0; x1 = _x1; y0 = _y0; y1 = _y1;
	}

	float getWidth () {return x1-x0;}
	float getHeight () {return y1-y0;}

	void setWidth (float w) {
		x1 = x0+w;
		std::cout << "x = [" << x0 << " " << x1 << "]" << std::endl;
		std::cout << "width = " << getWidth() << std::endl;
	}
	void setHeight (float h) {
		y1 = y0+h;
		std::cout << "y = [" << y0 << " " << y1 << "]" << std::endl;
		std::cout << "height = " << getHeight() << std::endl;
	}
	Mat getModel () {
		return scaleMatrix (2.0/getWidth(), 2.0/getHeight()) *
				transMatrix (-x0 - getWidth()/2.0, -y0 - getHeight()/2.0);
	}

};

#endif
