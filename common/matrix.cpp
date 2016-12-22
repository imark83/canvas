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
  for (int i=0; i<op.row; ++i) {
    for (int j=0; j<op.col; ++j) output << "  " << op(i,j);
    output << std::endl;
  }
  return output;
}
