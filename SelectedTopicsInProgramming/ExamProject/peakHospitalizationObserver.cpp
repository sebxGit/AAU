#include "peakHospitalizationObserver.h"

template<typename T>
void peakHospitalizationObserver<T>::operator()(const stochastic::Vessel &v) {
    T current = v.table.get("H");
    if (current > peak)
        peak = current;
}