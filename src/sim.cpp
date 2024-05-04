#include <iostream>
#include <cmath>
#include <vector>
#include "tensor.h"
#define C 299792458

using namespace std;

double gamma(double velocity){
    return 1/sqrt(1-pow(velocity,2));
}

double own_time(double time, double velocity){
    return time/gamma(velocity);
}

double own_distance(double distance, double velocity){
    return distance/gamma(velocity);
}

class referential{};

class main_referential{
    vector<Vector4> events;
  public:
    void add_event(Vector4 event){
        events.push_back(event);
    }
    void add_event(double x0, double x1, double x2, double x3){
        Vector4 newevent(x0, x1, x2, x3);
        events.push_back(newevent);
    }
    void list_events(){
        for(int i = 0; i < events.size(); i++)
            cout << events.at(i) << endl;
    }
};

int main(){

    main_referential mainref;
    
    double velocity = 0.8;  // USAR % DE c
    double gam = gamma(velocity);
    double beta = velocity;
    Matrix4 matrix( gam      , -gam*beta, 0, 0,
                    -gam*beta,       gam, 0, 0,
                    0        ,         0, 1, 0,
                    0        ,         0, 0, 1);
    Matrix4 g(1,  0, 0, 0,
              0, -1, 0, 0,
              0,  0,-1, 0,
              0,  0, 0,-1);
    
    cout<< "gamma: " << gam << endl;
    cout << beta << endl;
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
    cout << "Particle time: "<< own_time(30, velocity) << " s" << endl;
    cout << "My distance: 3000 m" << endl;
    cout << "Particle distance: "<< own_distance(3000, velocity) << " m" << endl;
    
}
