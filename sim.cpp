#include <iostream>
#include <cmath>
#include <vector>
#define C 299792458

using namespace std;

float gamma(float velocity){
    return 1/(sqrt(1-pow(velocity/float(C),2)));
}

float own_time(float time, float velocity){
    return time/gamma(velocity);
}

float own_distance(float distance, float velocity){
    return distance/gamma(velocity);
}

class Vector4{
    vector<double> vector;
  public:
    Vector4(double x0, double x1, double x2, double x3) : vector{x0, x1, x2, x3}{}
    double at(int pos){
        return vector.at(pos);
    }
    double operator*(Vector4 other_vector){
        float three_vector;
        for(int i = 1; i <= 3; i++)
            three_vector += vector.at(i)*other_vector.at(i);
        return vector.at(0)*other_vector.at(0) - three_vector;
    }
    double operator[](int pos){
        return vector.at(pos);
    }
};

ostream& operator<<(ostream& stream, Vector4 vector){
    stream << "( ";
    stream << vector[0]/(float)C << "c,";
    for(int i = 1; i <= 2; i++)
        stream << vector[i] << ",";
    stream << vector[3];
    stream << " )";
    return stream;
}

class Matrix4{
    vector<vector<double>> matrix;
  public:
    Matrix4(double x00,double x01,double x02,double x03,
            double x10,double x11,double x12,double x13,
            double x20,double x21,double x22,double x23,
            double x30,double  x31,double  x32,double  x33) : matrix{{x00, x01, x02, x03},
                                         {x10, x11, x12, x13},
                                         {x20, x21, x22, x23},
                                         {x30, x31, x32, x33}}{};
};

class referential{};

class main_referential{
    vector<Vector4> events;
  public:
    void add_event(Vector4 event){
        events.push_back(event);
    }
    void add_event(float x0, float x1, float x2, float x3){
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
    mainref.add_event(30.0*C, 0, 0, 0);
    mainref.list_events();

    cout << "My time: 30 s" << endl;
    cout << "Particle time: "<< own_time(30, 0.8*C) << " s" << endl;
    cout << "My distance: 3000 m" << endl;
    cout << "Particle distance: "<< own_distance(3000, 0.8*C) << " m" << endl;
    
}
