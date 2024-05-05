#include <vector>
#include <iostream>
#include "../include/tensor.h"


tsr::Vector4::Vector4(double x0, double x1, double x2, double x3) : vector{x0, x1, x2, x3}{}
double tsr::Vector4::at(int pos){
    return vector.at(pos);
}
double tsr::Vector4::operator*(Vector4 other_vector){
    double three_vector;
    for(int i = 1; i <= 3; i++)
        three_vector += vector.at(i)*other_vector.at(i);
    return vector.at(0)*other_vector.at(0) - three_vector;
}
double tsr::Vector4::operator[](int pos) const{
    return vector.at(pos);
}
double& tsr::Vector4::operator[](int pos){
    return vector[pos];
}
tsr::Vector4 tsr::Vector4::operator-(Vector4 other_vector){
    return Vector4(vector[0] - other_vector[0], vector[1]-other_vector[1],
                   vector[2] - other_vector[2], vector[3]-other_vector[3]);
}

std::ostream& operator<<(std::ostream& stream, tsr::Vector4 vector){
    stream << "( ";
    for(int i = 0; i <= 2; i++)
        stream << vector[i] << ", ";
    stream << vector[3];
    stream << " )";
    return stream;
}

tsr::Matrix4::Matrix4(double x00,double x01,double x02,double x03,
                 double x10,double x11,double x12,double x13,
                 double x20,double x21,double x22,double x23,
                 double x30,double x31,double x32,double x33) : matrix{{x00, x01, x02, x03},
                                                                       {x10, x11, x12, x13},
                                                                       {x20, x21, x22, x23},
                                                                       {x30, x31, x32, x33}}{};

std::vector<double> tsr::Matrix4::operator[](int i) { return this->matrix[i];}
void tsr::Matrix4::set_value(int row, int column, double value) { 
    this->matrix[row][column] = value;
}
tsr::Vector4 tsr::Matrix4::get_column(int i){
    Vector4 row(matrix[0][i], matrix[1][i], matrix[2][i], matrix[3][i]);
    return row;
}
tsr::Vector4 tsr::Matrix4::get_row(int i){
    Vector4 column(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
    return column;
}
tsr::Matrix4 tsr::Matrix4::operator*(Matrix4 other_matrix){
    Matrix4 result;
    for(int i = 0; i <= 3; i++){
        for(int j = 0; j <= 3; j++){
            double sum = 0;
            for(int k = 0; k <= 3; k++){
                sum+= matrix[i][k]*other_matrix[k][j];
            }
            result.set_value(i, j, sum);
        }
    }
    return result;
}
tsr::Vector4 tsr::Matrix4::operator*(Vector4 vector){
    Vector4 result;
    for(int i = 0; i <= 3; i++){
        for(int j = 0; j <= 3; j++){
            result[i] += matrix[i][j]*vector[j];
        }
    }
    return result;
}
std::ostream& operator<<(std::ostream& stream, tsr::Matrix4 matrix){
    for(int i = 0; i <= 3; i++){
        stream << "| ";
        for(int j = 0; j <= 3; j++){
            stream << matrix[i][j] << " ";
        }
        stream << "|" << std::endl;
    }
    return stream;
}


