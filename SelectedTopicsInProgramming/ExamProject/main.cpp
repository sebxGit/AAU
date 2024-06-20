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
        bool useTrajectory = vessel.getTableRecordHistory();

        bool isSeihr = func().getName().find("COVID19 SEIHR:") != std::string::npos;
        if (isSeihr && useObserver && !useTrajectory){
            peakHospitalizationObserver<double> observer;
            sim.run(run_duration, observer);
        }
        else
            sim.run(run_duration);

        if (useTrajectory){ // change recordHistory value in GenericSymbolTable.h to enable/disable
            std::string path = std::string{vessel.getName() + "Trajectory.csv"};
            std::replace(path.begin(), path.end(), ' ', '_');
            std::replace(path.begin(), path.end(), ':', '_');
            vessel.tableShowTrajectory();
            vessel.tableExportTrajectory(path);
        }
        std::cout << "---End of simulation for " << vessel.getName() << "---\n";
    }
}

void multiCore(const std::vector<std::function<stochastic::Vessel()>>& vesselFuncs, const bool useObserver, const int run_duration, const int num_simulations) {
    ThreadPool pool(std::thread::hardware_concurrency());
    std::vector<std::future<double>> futures;

    for (const auto& func : vesselFuncs) {
        for (int i = 0; i < num_simulations; ++i) {
            std::cout << "---Running simulation for " << func().getName() << " iteration " << i << "---\n";
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

                std::cout << "---End of simulation for " << vessel.getName() << " iteration " << i << "---\n";
                return observer.getPeak();
            }));
        }
    }

    if (useObserver){
        double totalPeak = 0;
        for(auto &future : futures)
            totalPeak += future.get();
        double averagePeak = totalPeak / static_cast<double>(futures.size());

        std::cout << "Average peak hospitalization over " << num_simulations << " simulations: " << averagePeak << "\n";
    }
}

void prettyPrint(const std::vector<std::function<stochastic::Vessel()>>& vesselFuncs){
    for (const auto& func : vesselFuncs) {
        stochastic::Vessel vessel = func();
        std::cout << "---Pretty printing for " << vessel.getName() << "---\n";
        vessel.prettyPrintHumanFormat();
        std::cout << "--- Middle of pretty printing for " << vessel.getName() << "---\n";
        vessel.prettyPrintNetworkGraph();
        std::cout << "---End of pretty printing for " << vessel.getName() << "---\n";
    }
}

int main() {
    bool use_observer = true;
    const int num_simulations = 100;
    const int run_duration = 5;

    std::vector<std::function<stochastic::Vessel()>> vesselFuncs = {
            stochastic::figure_1b,
            stochastic::circadian_rhythm,
            []() { return stochastic::seihr(10'000); },
    };

    std::vector<std::function<stochastic::Vessel()>> vesselFuncsHospitalizedPeak = {
            []() { return stochastic::seihr(589'755); }, // N_{NJ}
            []() { return stochastic::seihr(5'822'763); }, // N_{DK}
    };

    std::vector<std::function<stochastic::Vessel()>> vesselFuncsParallel = {
            []() { return stochastic::seihr(5'822'763); }, // N_{DK}
    };

    // note: remember to
    //      enable/disable trajectory recording in GenericSymbolTable.h (useHistory)
    //      and to enable/disable observer prints in peakHospitalizationObserver.h (disablePrint)

    singleCore(vesselFuncs, use_observer, run_duration);
    multiCore(vesselFuncsHospitalizedPeak, use_observer, run_duration, num_simulations);
    prettyPrint(vesselFuncs);

    return 0;
}