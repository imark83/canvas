#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <GL/glew.h>
#include <math2d.hpp>
#include <matrix.hpp>
#include <renderable.hpp>


class Object : public Renderable {
public:
	Vector2f scale;
	Vector2f position;
	float rotation;
	Vector2f p[8];



	Object ()
		: scale (1.0, 1.0), position (0.0, 0.0), rotation (0.0) {}
	// Object (Vector2f _scale, Vector2f _position, float _rotation);
	// ~Object () {}

	virtual void setScale (float sc) {scale.x = scale.y = sc;}

	void setScale (float scale_x, float scale_y) {
		scale.x = scale_x; scale.y = scale_y;
	}

	void setScale (const Vector2f &scale) {this->scale = scale;}

	void setPosition (float x, float y) {
		position.x = x; position.y = y;
	}

	void setPosition (const Vector2f &x) {position = x;}

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


	void render (Camera) const {}
	virtual void render (Camera cam, float depth) const;

};


#endif
