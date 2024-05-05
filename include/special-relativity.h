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

    class spacetime{
        std::vector<tsr::Vector4> events;
        std::vector<tsr::Matrix4> reference_frame;
      public:
        void add_event(tsr::Vector4 event);
        void add_event(double x0, double x1, double x2, double x3);
        void list_events();
        void add_rFrame(double v1, double v2, double v3);
    };

    double gamma(double velocity);
    double gamma(double v1, double v2, double v3);
    double own_time(double time, double velocity);
    double own_distance(double distance, double velocity);
}
#endif
