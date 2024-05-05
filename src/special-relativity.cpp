#include "../include/tensor.h"
#include "../include/special-relativity.h"
#include <cmath>

static int c = 299792458;

int sr::get_c() { return c; }
void sr::set_c(int new_value) { c = new_value; }

double sr::gamma(double velocity){
    return 1/sqrt(1-pow(velocity,2));
}
double sr::gamma(double v1, double v2, double v3){
    return gamma(v1+v2+v3);
}

double sr::own_time(double time, double velocity){
    return time/gamma(velocity);
}

double sr::own_distance(double distance, double velocity){
    return distance/gamma(velocity);
}

void sr::spacetime::add_event(tsr::Vector4 event){
    events.push_back(event);
}
void sr::spacetime::add_event(double x0, double x1, double x2, double x3){
    tsr::Vector4 newevent(x0, x1, x2, x3);
    events.push_back(newevent);
}
void sr::spacetime::list_events(){
    for(int i = 0; i < events.size(); i++)
        std::cout << events.at(i) << std::endl;
}
void sr::spacetime::add_rFrame(double v1, double v2, double v3){
}

