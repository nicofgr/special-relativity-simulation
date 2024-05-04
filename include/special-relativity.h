#ifndef SPECIAL_RELATIVITY
#define SPECIAL_RELATIVITY

#include<vector>
#include "../include/tensor.h"
#define C 299792458

namespace sr{

    class main_referential{
        std::vector<Vector4> events;
      public:
        void add_event(Vector4 event);
        void add_event(double x0, double x1, double x2, double x3);
        void list_events();
    };

    double gamma(double velocity);
    double own_time(double time, double velocity);
    double own_distance(double distance, double velocity);

}
#endif
