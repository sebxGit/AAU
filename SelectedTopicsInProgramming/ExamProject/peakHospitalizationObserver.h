
#ifndef PEAKHOSPITALIZATIONOBSERVER_H
#define PEAKHOSPITALIZATIONOBSERVER_H

#include <iostream>

template <typename T>
class peakHospitalizationObserver {
    T peak = 0;
    bool disablePrint = false;

public:
    void operator()(stochastic::Vessel v) {
        T current = v.getTableValue("H");
        if (current > peak){
            peak = current;
        }
    }
    T getPeak() const { return peak; }

    peakHospitalizationObserver() { if (!disablePrint) std::cout << "Peak hospitalization observer created and running..." << std::endl; }
    ~peakHospitalizationObserver() { if (!disablePrint) std::cout << "Peak hospitalization: " << peak << std::endl; }
};


#endif //PEAKHOSPITALIZATIONOBSERVER_H
