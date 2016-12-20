#ifndef __MATH2D_HPP__
#define __MATH2D_HPP__

struct Vector2f {
public:
	float x;
	float y;
	Vector2f () {x = 0.0; y=0.0;}
	Vector2f (float _x, float _y) {x = _x; y = _y;}
	~Vector2f () {}

	Vector2f & operator= (const Vector2f &op) {
		x = op.x; y = op.y;
		return *this;
	}
};
typedef Vector2f Point2f;

#endif
