#include <iostream>

#ifndef PEAKHOSPITALIZATIONOBSERVER_H
#define PEAKHOSPITALIZATIONOBSERVER_H

template <typename T>
class peakHospitalizationObserver {
    T peak = 0;

public:
    void operator()(const stochastic::Vessel& v) {
        T current = v.table.get("H");
        if (current > peak){
            peak = current;
        }
    }
    T getPeak() { return peak; }

    peakHospitalizationObserver() { std::cout << "Peak hospitalization observer created and running..." << std::endl; }
    ~peakHospitalizationObserver() { std::cout << "Peak hospitalization: " << peak << std::endl; }
};


#endif //PEAKHOSPITALIZATIONOBSERVER_H
