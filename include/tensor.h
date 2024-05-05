#ifndef TENSOR
#define TENSOR
#include<iostream>
#include<vector>

namespace tsr{

class Vector4{
    std::vector<double> vector;
  public:
    Vector4(double x0 = 0, double x1 = 0, double x2 = 0, double x3 = 0);
    double at(int pos);
    double operator*(Vector4 other_vector);
    double operator[](int pos) const;
    double& operator[](int pos);
    Vector4 operator-(Vector4 other_vector);
};

class Matrix4{
    std::vector<std::vector<double>> matrix;
  public:
    Matrix4(double x00 = 0,double x01 = 0,double x02 = 0,double x03 = 0,
            double x10 = 0,double x11 = 0,double x12 = 0,double x13 = 0,
            double x20 = 0,double x21 = 0,double x22 = 0,double x23 = 0,
            double x30 = 0,double x31 = 0,double x32 = 0,double  x33 = 0);
    void set_value(int row, int column, double value);
    std::vector<double> operator[](int i); 
    Vector4 get_row(int i);
    Vector4 get_column(int i);
    Matrix4 operator*(Matrix4 other_matrix);
    Vector4 operator*(Vector4 vector);
    Matrix4 inverse();
};
}
std::ostream& operator<<(std::ostream& stream, tsr::Vector4 vector);
std::ostream& operator<<(std::ostream& stream, tsr::Matrix4 matrix);


#endif
