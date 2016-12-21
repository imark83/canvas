#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>

class Mat {
public:
	float data[16];
	Mat (float op = 1);
	Mat (const Mat &op);

	float & operator() (const int i, const int j) {
		return data[4*i+j];
	}
};

Mat operator+ (const Mat &op1, const Mat &op2);
Mat operator- (const Mat &op1, const Mat &op2);
Mat operator* (const Mat &op1, const Mat &op2);
std::ostream & operator<< (std::ostream &output, const Matrix4f &op);


#endif
