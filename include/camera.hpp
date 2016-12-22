#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

class Camera {
public:

  float x0;
  float x1;
  float y0;
  float y1;

  Camera () {x0=y0=0.0; x1=y1=1.0;}
  Camera (float _x0, float _x1, float _y0, float _y1) {
    x0 = _x0; x1 = _x1; y0 = _y0; y1 = _y1;
  }

  float getWidth () {return x1-x0;}
  float getHeight () {return y1-y0;}
};

#endif
