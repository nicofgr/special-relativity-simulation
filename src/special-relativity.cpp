#include "../include/tensor.h"
#include "../include/special-relativity.h"
#include <cmath>


double sr::gamma(double velocity){
    return 1/sqrt(1-pow(velocity,2));
}

double sr::own_time(double time, double velocity){
    return time/gamma(velocity);
}

double sr::own_distance(double distance, double velocity){
    return distance/gamma(velocity);
}

void sr::main_referential::add_event(Vector4 event){
    events.push_back(event);
}
void sr::main_referential::add_event(double x0, double x1, double x2, double x3){
    Vector4 newevent(x0, x1, x2, x3);
    events.push_back(newevent);
}
void sr::main_referential::list_events(){
    for(int i = 0; i < events.size(); i++)
        std::cout << events.at(i) << std::endl;
}

