#include <GL/glew.h>
#include <GL/freeglut.h>
#include <scene.hpp>

void Scene::init () {
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearColor (26.0/256.0, 102.0/256.0, 46.0/256.0, 0.0f);
	// glClearColor(0.12500f, 0.57812f, 0.11719f, 1.0f);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	car.setProgram (loadShaders (shaders));
	glUseProgram (car.getProgram ());


	car.initBuffers ();
	car.move(10, 10);
	car.setRot (-90);

	car.attachCaravan();
	car.caravan->setProgram(car.getProgram());
	car.caravan->initBuffers ();

	spot.setProgram (car.getProgram());
	spot.initBuffers ();
	spot.setPosition (20,10);
}

void Scene::render () {
	glUseProgram (car.getProgram());
	car.render (cam);
	spot.render(cam);

}

void Scene::step (int millis) {
	car.motionStep(millis);
	std::cout << "speed = " << car.speed << std::endl;
	std::cout << "steering angle = " << car.wheelPosition << '\n' << std::endl;
}


void Scene::specKeyboardFunction (int key, int x, int y) {
	// std::cout << "special key pressed" << '\n';
	switch (key) {
		case GLUT_KEY_UP:
			car.throttle ();
			// std::cout << "pedal = " << car.pedal << '\n';
			break;
		case GLUT_KEY_DOWN:
			car.brake();
			// std::cout << "pedal = " << car.pedal << '\n';
			break;
		case GLUT_KEY_LEFT:
			car.turnLeft();
			break;
		case GLUT_KEY_RIGHT:
			car.turnRight();
			break;
	}
}
void Scene::specKeyboardUpFunction (int key, int x, int y) {
	// std::cout << "special key released" << '\n';
	switch (key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			car.releasePedal ();
			// std::cout << "pedal = " << car.pedal << '\n';
			break;
		case GLUT_KEY_LEFT:
			car.releaseHandle();
			break;
		case GLUT_KEY_RIGHT:
			car.releaseHandle();
			break;
	}
}


void Scene::keyboardFunction(unsigned char key, int x, int y) {
	// std::cout << "key pressed" << '\n';
	switch (key) {
		case 'a':
		case 'A':
			car.gearUp();
			// std::cout << "gear = " << car.gear << '\n';
			break;
		case 'z':
		case 'Z':
			car.gearDown();
			// std::cout << "gear = " << car.gear << '\n';
			break;
	}
}

void Scene::keyboardUpFunction(unsigned char key, int x, int y) {
}
