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

void multiCore(const std::vector<std::function<stochastic::Vessel()>>& vesselFuncs, const bool useObserver, const int run_duration, const int num_simulations) {
    ThreadPool pool(std::thread::hardware_concurrency());
    std::vector<std::future<double>> futures;
    for (const auto& func : vesselFuncs) {
        for (int i = 0; i < num_simulations; ++i) {
            futures.emplace_back(pool.enqueueJob([func, useObserver, run_duration, i](){
                stochastic::Vessel vessel = func();
                stochastic::simulation sim(vessel);
                peakHospitalizationObserver<double> observer;
                bool useTrajectory = vessel.getTableRecordHistory();

                bool isSeihr = func().getName().find("COVID19 SEIHR:") != std::string::npos;
                if (isSeihr && useObserver && !useTrajectory)
                    sim.runNoPrint(run_duration, observer);
                else
                    sim.runNoPrint(run_duration);
                return observer.getPeak();
            }));
        }
    }

    if (useObserver){
        double totalPeak = 0;
        for(auto &future : futures)
            totalPeak += future.get();
        double averagePeak = totalPeak / static_cast<double>(futures.size());
    }
}

int main() {
    bool use_observer = true;
    const int num_simulations = 100; // each vessel
    const int run_duration = 5;
    std::vector<std::function<stochastic::Vessel()>> vesselFuncs = {
            stochastic::figure_1b,
            stochastic::circadian_rhythm,
            []() { return stochastic::seihr(10'000); },
    };

    std::vector<std::pair<std::string, std::function<void()>>> cores = {
            {"Single Core", [&](){ singleCore(vesselFuncs, use_observer, run_duration); }},
            {"Multi Core", [&](){ multiCore(vesselFuncs, use_observer, run_duration, num_simulations); }},
    };

    for (const auto& core : cores) {
        std::cout << "Starting chrono for " << core.first << '\n';
        auto start = std::chrono::high_resolution_clock::now();
        core.second();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << core.first << " took " << duration << " milliseconds to run.\n";
    }
    return 0;
}