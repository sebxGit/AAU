#include <iostream>
#include <vector>
#include <functional>
#include "Vessel.cpp"
#include "simulation.cpp"
#include "peakHospitalizationObserver.h"

void singleCore(const std::vector<std::function<stochastic::Vessel()>>& vesselFuncs, const bool useObserver, const int run_duration){
    for (const auto& func : vesselFuncs) {
        std::cout << "---Running simulation for " << func().getName() << "---\n";
        stochastic::Vessel vessel = func();
        stochastic::simulation sim(vessel);

        bool isCovid = func().getName().find("COVID19 SEIHR:") != std::string::npos;

        if (isCovid && useObserver){
            peakHospitalizationObserver<double> observer;
            sim.run(run_duration, observer);
        }
        else
            sim.run(run_duration);

        std::cout << "---End of simulation for " << vessel.getName() << "---\n";
    }
}