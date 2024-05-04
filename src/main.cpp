#include <iostream>
#include <cmath>
#include <vector>
#include "../include/tensor.h"
#include "../include/special-relativity.h"

using namespace std;

int main(){

    sr::main_referential mainref;
    
    double velocity = 0.8;  // USAR % DE c
    double gam = sr::gamma(velocity);
    double beta = velocity;
    Matrix4 matrix( gam      , -gam*beta, 0, 0,
                    -gam*beta,       gam, 0, 0,
                    0        ,         0, 1, 0,
                    0        ,         0, 0, 1);
    Matrix4 g(1,  0, 0, 0,
              0, -1, 0, 0,
              0,  0,-1, 0,
              0,  0, 0,-1);
    
    cout << matrix << endl;
    cout << "gamma: " << gam << endl;
    cout << "beta: " << beta << endl;
    Vector4 A(0, 0, 0, 0);
    Vector4 B(0, 1800, 0, 0);
    Vector4 D(0, 0, 0, 0);
    cout << "Size = " << B[1] - A[1] << endl;
    cout << "Size = " << (matrix*B)[1] - (matrix*A)[1] << endl;
    cout << matrix*A << endl;
    cout << B << endl;
    cout << matrix*B << endl;
    cout << D << endl;
    cout << matrix*D << endl;

    cout << "My time: 30 s" << endl;
    cout << "Particle time: "<< sr::own_time(30, velocity) << " s" << endl;
    cout << "My distance: 3000 m" << endl;
    cout << "Particle distance: "<< sr::own_distance(3000, velocity) << " m" << endl;
    
}
