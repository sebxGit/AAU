#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <future>
#include <numeric>
#include "reaction.cpp"
#include "reactor.cpp"
#include "genericSymbolTable.cpp"
#include "Vessel.cpp"
#include "simulation.cpp"
#include "peakHospitalizationObserver.h"
#include "ThreadPool.h"

namespace stochastic {
    Vessel circadian_rhythm() {
#pragma region constants
        const auto alphaA = 50;
        const auto alpha_A = 500;
        const auto alphaR = 0.01;
        const auto alpha_R = 50;
        const auto betaA = 50;
        const auto betaR = 5;
        const auto gammaA = 1;
        const auto gammaR = 1;
        const auto gammaC = 2;
        const auto deltaA = 1;
        const auto deltaR = 0.2;
        const auto deltaMA = 10;
        const auto deltaMR = 0.5;
        const auto thetaA = 50;
        const auto thetaR = 100;
        auto v = stochastic::Vessel{"Circadian Rhythm"};
        const auto env = v.environment();
        const auto DA = v.add("DA", 1);
        const auto D_A = v.add("D_A", 0);
        const auto DR = v.add("DR", 1);
        const auto D_R = v.add("D_R", 0);
        const auto MA = v.add("MA", 0);
        const auto MR = v.add("MR", 0);
        const auto A = v.add("A", 0);
        const auto R = v.add("R", 0);
        const auto C = v.add("C", 0);
#pragma endregion constants
        v.add((A + DA) >> gammaA >>= D_A);
        v.add(D_A >> thetaA >>= DA + A);
        v.add((A + DR) >> gammaR >>= D_R);
        v.add(D_R >> thetaR >>= DR + A);
        v.add(D_A >> alpha_A >>= MA + D_A);
        v.add(DA >> alphaA >>= MA + DA);
        v.add(D_R >> alpha_R >>= MR + D_R);
        v.add(DR >> alphaR >>= MR + DR);
        v.add(MA >> betaA >>= MA + A);
        v.add(MR >> betaR >>= MR + R);
        v.add((A + R) >> gammaC >>= C);
        v.add(C >> deltaA >>= R);
        v.add(A >> deltaA >>= env);
        v.add(R >> deltaR >>= env);
        v.add(MA >> deltaMA >>= env);
        v.add(MR >> deltaMR >>= env);
        return v;
    };

    Vessel seihr(uint32_t N) {
        auto v = Vessel{"COVID19 SEIHR: " + std::to_string(N)};
        const auto eps = 0.0009; // initial fraction of infectious
        const auto I0 = size_t(std::round(eps * N)); // initial infectious
        const auto E0 = size_t(std::round(eps * N * 15)); // initial exposed
        const auto S0 = N - I0 - E0; // initial susceptible
        const auto R0 = 2.4; // initial basic reproductive number
        const auto alpha = 1.0 / 5.1; // incubation rate (E -> I) ~5.1 days
        const auto gamma = 1.0 / 3.1; // recovery rate (I -> R) ~3.1 days
        const auto beta = R0 * gamma; // infection/generation rate (S+I -> E+I)
        const auto P_H = 0.9e-3; // probability of hospitalization
        const auto kappa = gamma * P_H * (1.0 - P_H); // hospitalization rate (I -> H)
        const auto tau = 1.0 / 10.12; // removal rate in hospital (H -> R) ~10.12 days
        const auto S = v.add("S", S0); // susceptible
        const auto E = v.add("E", E0); // exposed
        const auto I = v.add("I", I0); // infectious
        const auto H = v.add("H", 0); // hospitalized
        const auto R = v.add("R", 0); // removed/immune (recovered + dead)
        v.add((S + I) >> beta / N >>= E + I); // susceptible becomes exposed by infectious
        v.add(E >> alpha >>= I); // exposed becomes infectious
        v.add(I >> gamma >>= R); // infectious becomes removed
        v.add(I >> kappa >>= H); // infectious becomes hospitalized
        v.add(H >> tau >>= R); // hospitalized becomes removed
        return v;
    };
}

void singleCore(const auto vesselFuncs, const bool useObserver, const int run_duration){
    for (const auto& func : vesselFuncs) {
        std::cout << "---Running simulation for " << func().getName() << "---\n";
        stochastic::Vessel vessel = func();
        stochastic::simulation sim(vessel);

        if (useObserver){
            peakHospitalizationObserver<double> observer;
            sim.run(run_duration, observer);
        }
        else
            sim.run(run_duration);

        std::cout << "---End of simulation for " << vessel.getName() << "---\n";
    }
}

void multiCore(const auto vesselFuncs, const bool useObserver, const int num_simulations, const int run_duration) {
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
            stochastic::circadian_rhythm,
            []() { return stochastic::seihr(10'000); },
    };
    std::vector<std::function<stochastic::Vessel()>> vesselFuncsHospitalizedPeak = {
            []() { return stochastic::seihr(589'755); }, // N_{NJ}
            []() { return stochastic::seihr(5'822'763); }, // N_{DK}
    };

    singleCore(vesselFuncsHospitalizedPeak, use_observer, run_duration);
//    multiCore(vesselFuncsHospitalizedPeak, use_observer, num_simulations, run_duration);

//        stochastic::Vessel::table.showTrajectory(); // on use, remember to set useHistory = true

    // TODO: 2. need fix for pretty print for network graph
    // TODO: 5. demonstrate Fig 1
    return 0;
}
