#include "polymorphism.h"

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

constexpr auto experiments = 1'000'000;


int main(){
    using clk = std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::milli;

    std::vector<std::unique_ptr<Base>> vec;
    vec.reserve(experiments);
    for (auto i = 0; i < experiments; i++)
        vec.push_back(std::make_unique<Derived>());

    auto inc_time = 0.;
    auto dec_time = 0.;

    for (auto i = 0; i < 100; ++i) {
        auto t0 = clk::now();
        for (auto& e : vec)
            e->increment();
        auto t1 = clk::now();
        inc_time += duration<double, milli>(t1-t0).count();

        for (auto& e : vec)
            e->decrement();
        auto t2 = clk::now();
        dec_time += duration<double, milli>(t2-t1).count();
    }

    std::cout << "Increment time: " << inc_time << '\n';
    std::cout << "Decrement time: " << dec_time << '\n';
    return 0;
}