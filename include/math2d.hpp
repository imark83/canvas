#ifndef __MATH2D_HPP__
#define __MATH2D_HPP__

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

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

	Vector2f operator+ (const Vector2f &op) const {
		return Vector2f (this->x+op.x, this->y+op.y);
	}

	Vector2f & operator+= (const Vector2f &op) {
		this->x+=op.x; this->y+=op.y; return *this;
	}
};
typedef Vector2f Point2f;

#endif
