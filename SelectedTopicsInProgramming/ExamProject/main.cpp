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
        std::cout << "---Running simulation for " << func().getName() << "---\n";
        stochastic::Vessel vessel = func();
        stochastic::simulation sim(vessel);
        vessel.prettyPrintNetworkGraph();
//        vessel.prettyPrintHumanFormat();
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

void multiCore(const std::vector<std::function<stochastic::Vessel()>>& vesselFuncs, const bool useObserver, const int num_simulations, const int run_duration) {
    ThreadPool pool(std::thread::hardware_concurrency());
    std::vector<std::future<void>> futures;
    for (const auto& func : vesselFuncs) {
        for (int i = 0; i < num_simulations; ++i) {
            futures.emplace_back(pool.enqueueJob([func, useObserver, run_duration](){
                stochastic::Vessel vessel = func();
                stochastic::simulation sim(vessel);

                if (useObserver){
                    peakHospitalizationObserver<double> observer;
                    sim.run(run_duration, observer);
                }
                else
                    sim.run(run_duration);

                std::cout << "---End of simulation for " << vessel.getName() << "---\n";
            }));
        }
    }
    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) { ftr.get(); });
}

int main() {
    bool use_observer = true;
    const int num_simulations = 100;
    const int run_duration = 5;

    std::vector<std::function<stochastic::Vessel()>> vesselFuncs = {
            stochastic::figure_1,
//            stochastic::circadian_rhythm,
//            []() { return stochastic::seihr(10'000); },
    };
    std::vector<std::function<stochastic::Vessel()>> vesselFuncsHospitalizedPeak = {
            []() { return stochastic::seihr(589'755); }, // N_{NJ}
            []() { return stochastic::seihr(5'822'763); }, // N_{DK}
    };

    singleCore(vesselFuncs, use_observer, run_duration);
//    multiCore(vesselFuncsHospitalizedPeak, use_observer, num_simulations, run_duration);

//        stochastic::Vessel::table.showTrajectory(); // on use, remember to set useHistory = true

    return 0;
}