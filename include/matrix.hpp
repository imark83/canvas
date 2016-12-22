#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>

class Mat {
public:
	int row;
	int col;
	float *data;
	Mat (int = 1);
	Mat (int _row, int _col);
	Mat (const Mat &op);
	~Mat ();

	float & operator() (const int &i, const int &j) const;

};

Mat operator+ (const Mat &op1, const Mat &op2);
Mat operator- (const Mat &op1, const Mat &op2);
Mat operator* (const Mat &op1, const Mat &op2);
std::ostream & operator<< (std::ostream &output, const Mat &op);


#endif
