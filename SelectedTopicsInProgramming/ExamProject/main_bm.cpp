#include <string>
#include <vector>
#include <functional>
#include <future>
#include "reaction.cpp"
#include "reactor.cpp"
#include "genericSymbolTable.cpp"
#include "Vessel.cpp"
#include "simulation.cpp"
#include "peakHospitalizationObserver.h"
#include "ThreadPool.h"
#include "definitions.cpp"

void singleCore(const std::vector<std::function<stochastic::Vessel()>>& vesselFuncs, const bool useObserver, const int run_duration){
    for (const auto& func : vesselFuncs) {
        stochastic::Vessel vessel = func();
        stochastic::simulation sim(vessel);
        bool isCovid = func().getName().find("COVID19 SEIHR:") != std::string::npos;
        if (isCovid && useObserver){
            peakHospitalizationObserver<double> observer;
            sim.runNoPrint(run_duration, observer);
        }
        else
            sim.runNoPrint(run_duration);
    }
}

int main() {
    bool use_observer = true;
    const int num_simulations = 100;
    const int run_duration = 5;
    std::vector<std::function<stochastic::Vessel()>> vesselFuncs = {
            stochastic::figure_1,
            stochastic::circadian_rhythm,
            []() { return stochastic::seihr(10'000); },
    };
    // Get the time before the function call
    auto start = std::chrono::high_resolution_clock::now();

    // Call the function
    singleCore(vesselFuncs, use_observer, run_duration);

    // Get the time after the function call
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration of the function call
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "singleCore function took " << duration << " milliseconds to run.\n";

    return 0;
}