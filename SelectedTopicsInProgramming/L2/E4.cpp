#include <iostream>
#include "benchmark_util.h"

void benchmark_util::start(const std::string &name)
{
    time_point tp;
    tp.name = name;
    tp.start = std::chrono::high_resolution_clock::now();
    time_points.push_back(tp);
}

void benchmark_util::stop(const std::string &name)
{
    for(auto &tp : time_points)
    {
        if(tp.name == name)
        {
            tp.stop = std::chrono::high_resolution_clock::now();
            return;
        }
    }
}

void benchmark_util::report()
{
    for(const auto &tp : time_points)
    {
        std::chrono::duration<double, std::milli> duration = tp.stop - tp.start;
        std::cout << tp.name << " took " << duration.count() << " ms" << std::endl;
    }
}