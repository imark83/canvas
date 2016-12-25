#include <matrix.hpp>

Mat::Mat (int _rowcol) {
  row = col = _rowcol;
  data = new float[row * col];
  for (int i=0; i<row; ++i) for (int j=0; j<col; ++j)
    data[row*j+i] = (i==j)? 1.0 : 0.0;
}
Mat::Mat (int _row, int _col) {
  row = _row; col = _col;
  data = new float[row * col];
  for (int i=0; i<row; ++i) for (int j=0; j<col; ++j)
    data[row*j+i] = (i==j)? 1.0 : 0.0;
}
Mat::Mat (const Mat &op) {
  row = op.row; col = op.col;
	data = new float[row * col];
  for (int i=0; i<row*col; ++i) data[i] = op.data[i];
}
Mat::~Mat () {
  delete [] data;
}

float & Mat::operator() (const int &i, const int &j) const {
  return data[row*j+i];
}

Mat operator+ (const Mat &op1, const Mat &op2) {
  Mat rop (op1);
  for (int i=0; i<op1.row*op1.col; ++i) rop.data[i] += op2.data[i];
  return rop;
}
Mat operator- (const Mat &op1, const Mat &op2) {
  Mat rop (op1);
  for (int i=0; i<op1.row*op1.col; ++i) rop.data[i] -= op2.data[i];
  return rop;
}
Mat operator* (const Mat &op1, const Mat &op2) {
  Mat rop (op1.row, op2.col);
  for (int i=0; i<rop.row; ++i) for (int j=0; j<rop.col; ++j) {
    rop(i,j) = 0.0;
    for (int k=0; k<op1.col; ++k) rop(i,j) += op1(i,k)*op2(k,j);
  }
  return rop;
}
std::ostream & operator<< (std::ostream &output, const Mat &op) {
	output << std::endl;
  for (int i=0; i<op.row; ++i) {
    for (int j=0; j<op.col; ++j) output << "  " << op(i,j);
    output << std::endl;
  }
  return output;
}

Mat rotMatrix (float angle) {
	Mat rop(4);

	float rad = M_PI/180.0*angle;
	rop(0,0) =  cosf(rad);
	rop(0,1) = -sinf(rad);
	rop(1,0) =  sinf(rad);
	rop(1,1) =  cosf(rad);

	return rop;
}

Mat transMatrix (float x, float y) {
	Mat rop(4);
	rop(0,3) = x;
	rop(1,3) = y;
	return rop;
}

Mat scaleMatrix (float scalex, float scaley) {
	Mat rop(4);
	rop(0,0) = scalex;
	rop(1,1) = scaley;

	return rop;
}
