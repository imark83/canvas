#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <GL/glew.h>
#include <math2d.hpp>
#include <renderable.hpp>
#include <matrix.hpp>


class Object : public Renderable {
public:
	Vector2f scale;
	Vector2f position;
	float rotation;


	Object ()
		: scale (1.0, 1.0), position (0.0, 0.0), rotation (0.0), Renderable() {}
	Object (Vector2f _scale, Vector2f _position, Vector2f _rotation);
	// ~Object () {}

	void setScale (float sc) {scale.x = scale.y = sc;}

	void setScale (float scale_x, float scale_y) {
		scale.x = scale_x; scale.y = scale_y;
	}

	void setScale (Vector2f scale) {this->scale = scale;}

	void setPosition (float x, float y) {
		position.x = x; position.y = y;
	}

	void setPosition (Vector2f x) {position = x;}

	void setRot (float rotation) {this->rotation = rotation;}

	void move (Vector2f delta) {position += delta;}
	void move (float x, float y) {position += Vector2f(x,y);}

	void rotate (float delta) {rotation += delta;}

	Mat getModel () const {
		Mat rop(4);

		return transMatrix (position.x, position.y) *
					rotMatrix(rotation) *
					scaleMatrix (scale.x, scale.y) * rop;
	}

};


#endif
