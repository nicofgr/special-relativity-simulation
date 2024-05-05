#ifndef SPECIAL_RELATIVITY
#define SPECIAL_RELATIVITY

#include<vector>
#include "../include/tensor.h"
#define C 299792458

namespace sr{

    const tsr::Matrix4 g(1,  0, 0, 0,
                         0, -1, 0, 0,
                         0,  0,-1, 0,
                         0,  0, 0,-1);

    int get_c();
    void set_c(int new_value);

    class entity{
        tsr::Vector4 position;
        tsr::Vector4 velocity;
      public:
        entity(double x1 = 0, double x2 = 0, double x3 = 0, 
               double v1 = 0, double v2 = 0, double v3 = 0) : position(1,x1,x2,x3), 
                                                              velocity(1,v1,v2,v3) {}
        entity(tsr::Vector4 position, tsr::Vector4 velocity);
        tsr::Vector4 get_position() const;
        void update_position(double dt);
        double operator[](int index) const;

        tsr::Vector4 get_velocity() const;
        void update_velocity(double vel);

        tsr::Matrix4 get_fwrd() const;
    };


    class spacetime{
        std::vector<tsr::Vector4> events;
        std::vector<sr::entity> entity;
        tsr::Matrix4 current_Ref;
        double ref_vel;
      public:
        spacetime();
        void add_event(tsr::Vector4 event);
        void add_event(double x0, double x1, double x2, double x3);
        int get_event_size();
        void list_events();
        tsr::Vector4 operator[](int index);

        void add_entity(double v1=0, double v2=0, double v3=0);
        sr::entity get_entity(int index) const;
        int get_entity_size() const;

        void update_rFrame(double vel);
        tsr::Matrix4 get_fwrd() const;
    };

    double gamma(double velocity);
    double gamma(double v1, double v2, double v3);
    double own_time(double time, double velocity);
    double own_distance(double distance, double velocity);
    tsr::Matrix4 fwrd(double velocity);
tsr::Matrix4 bkrd(double velocity);
}
#endif
