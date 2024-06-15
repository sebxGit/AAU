#include <utility>

#include "Vessel.h"

#ifndef SIMULATION_H
#define SIMULATION_H

namespace stochastic {
    class simulation {
        double t{0};
        Vessel vessel;
    public:
        explicit simulation(Vessel vessel) : vessel(std::move(vessel)) {};
        void run(int endTime);

        template <typename Observer>
        void run(double T, Observer& observer);
    };
}



#endif //SIMULATION_H
