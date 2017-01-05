#ifndef __SCENE__HPP
#define __SCENE__HPP

#include <loadShaders.h>

#include <object.hpp>
#include <car.hpp>
#include <camera.hpp>
#include <list>


extern Vector2f windowSize;
extern Vector2f canvasSize;

class Scene {
public:
	Car car;
	Camera cam;
	std::list<Object> objects;

	Scene () : car(), cam(canvasSize.x, canvasSize.y) {}

	void init ();

	void setWidth (float w) {cam.setWidth(w);}
	void setHeight (float h) {cam.setHeight(h);}

	void initBuffers ();
	void render ();

	void step (int millis);

	void specKeyboardFunction (int key, int x, int y);
	void specKeyboardUpFunction (int key, int x, int y);
	void keyboardFunction(unsigned char key, int x, int y);
	void keyboardUpFunction(unsigned char key, int x, int y);

};

#endif
