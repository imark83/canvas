#include <GL/glew.h>
#include <GL/freeglut.h>
#include <scene.hpp>

void Scene::init () {
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glAlphaFunc(GL_GREATER, 0.5);
	// glEnable(GL_ALPHA_TEST);

	glEnable(GL_DEPTH_TEST);

	// glClearColor (26.0/256.0, 102.0/256.0, 46.0/256.0, 0.0f);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "default.vs.glsl"},
		{GL_FRAGMENT_SHADER, "default.fs.glsl"},
		{GL_NONE, NULL}};

	car.setProgram (loadShaders (shaders));




	glUseProgram (car.getProgram ());


	car.initBuffers (car.p, "car2.png");
	car.move(15, 7.5);
	car.setRot (-90);

	car.attachCaravan();
	car.caravan->setProgram(car.getProgram());
	car.caravan->initBuffers (car.caravan->p, "caravan.png");

	spot.setProgram (car.getProgram());
	spot.initBuffers (spot.p, "parking.jpg");
	spot.setPosition (20,10);


	ShaderInfo shaders2[] = {
		{GL_VERTEX_SHADER, "ground.vs.glsl"},
		{GL_FRAGMENT_SHADER, "ground.fs.glsl"},
		{GL_NONE, NULL}};

	ground.setProgram (loadShaders (shaders2));

	ground.initBuffers (ground.p, "grass.jpg");
}

void Scene::render () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram (car.getProgram());
	car.render (cam, 0.0);

	glUseProgram (spot.getProgram());
	spot.render(cam, 0.99);
	glUseProgram (ground.getProgram());
	ground.render(cam, 0.99999);

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
