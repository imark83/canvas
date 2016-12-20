#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <GL/glew.h>
#include <math2d.hpp>


class Object {
public:
	Vector2f scale;
	Vector2f position;
	float rotation;


	Object ()
		: scale (1.0, 1.0), position (0.0, 0.0), rotation (0.0) {}
	Object (Vector2f _scale, Vector2f _position, Vector2f _rotation);
	~Object () {}

	void setScale (float sc) {scale.x = scale.y = sc;}

	void setScale (float scale_x, float scale_y) {
		scale.x = scale_x; scale.y = scale_y;
	}

	void setScale (Vector2f scale) {this->scale = scale;}

	void setPosition (float x, float y) {
		position.x = x; position.y = y;
	}

	void setRot (float rotation) {this->rotation = rotation;}

	// void rotate ()

	// virtual Matrix4f getModel () const;
};


#endif
