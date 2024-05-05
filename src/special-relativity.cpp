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


sr::spacetime::spacetime() : current_Ref(sr::fwrd(0)), ref_vel(0) {}

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
tsr::Vector4 sr::spacetime::operator[](int index){
    return get_fwrd()*(events.at(index));
}


void sr::spacetime::add_entity(double v1, double v2, double v3){
    entity.push_back(sr::entity(0,0,0,v1,v2,v3));
}
sr::entity sr::spacetime::get_entity(int index) const{
    sr::entity original_ent = entity.at(index);
    tsr::Vector4 o_vel = original_ent.get_velocity();
    double new_vel = (o_vel[1]+ref_vel)/(1+(o_vel[1]*ref_vel));
    tsr::Vector4 n_vel(0, new_vel, 0, 0);

    tsr::Vector4 original_pos = original_ent.get_position();
    tsr::Vector4 transform_pos = get_fwrd()*original_pos;

    sr::entity transform_ent(transform_pos, n_vel);

    return transform_ent;
}
int sr::spacetime::get_entity_size() const{
    return entity.size();
}


void sr::spacetime::update_rFrame(double vel){
    ref_vel=vel;
    current_Ref = fwrd(vel);
}
tsr::Matrix4 sr::spacetime::get_fwrd() const{
    return current_Ref; 
}



// ENTITY

sr::entity::entity(tsr::Vector4 position, tsr::Vector4 velocity) : position(position),
                                                                   velocity(velocity){}
tsr::Vector4 sr::entity::get_position() const{
    return position;
}
void sr::entity::update_position(double dt){
    position[1] += velocity[1] * dt;
    position[2] += velocity[2] * dt;
    position[3] += velocity[3] * dt;
}
double sr::entity::operator[](int index) const{
    return position[index];
}

tsr::Vector4 sr::entity::get_velocity() const{
    return velocity;
}
void sr::entity::update_velocity(double vel){
    velocity[1] = vel;
}

tsr::Matrix4 sr::entity::get_fwrd() const{
    return sr::fwrd(velocity[1]);
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
