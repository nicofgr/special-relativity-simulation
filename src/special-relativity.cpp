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


sr::spacetime::spacetime() : current_Ref(sr::fwrd(0)) {}

void sr::spacetime::add_event(tsr::Vector4 event){
    events.push_back(event);
}
void sr::spacetime::add_event(double x0, double x1, double x2, double x3){
    tsr::Vector4 newevent(x0, x1, x2, x3);
    events.push_back(newevent);
}
int sr::spacetime::get_event_size(){
    return events.size();
}
void sr::spacetime::list_events(){
    for(int i = 0; i < events.size(); i++)
        std::cout << events.at(i) << std::endl;
}
void sr::spacetime::update_rFrame(double vel){
    current_Ref = fwrd(vel);
}
tsr::Matrix4 sr::spacetime::get_fwrd() const{
    return current_Ref; 
}
tsr::Vector4 sr::spacetime::operator[](int index){
    return current_Ref*(events.at(index));
}

void sr::entity::update_position(double dt){
    position[1] += velocity[1] * dt;
    position[2] += velocity[2] * dt;
    position[3] += velocity[3] * dt;
}

double sr::entity::operator[](int index) const{
    return position[index];
}
tsr::Matrix4 sr::fwrd(double velocity){
    double gm = sr::gamma(velocity);
    double bt = velocity;
    return tsr::Matrix4( gm    , -gm*bt, 0, 0,
                         -gm*bt,     gm, 0, 0,
                         0     ,      0, 1, 0,
                         0     ,      0, 0, 1);
}
tsr::Matrix4 sr::bkrd(double velocity);
