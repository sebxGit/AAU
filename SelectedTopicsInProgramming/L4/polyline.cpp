#include "polyline.hpp"
#include <iostream>

Polyline0 &Polyline0::operator+=(const Point p){
    if (is_shared())
        points = clone();
    points->push_back(p);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Polyline0& p){
    os << "{";
    if (p.points !=nullptr) {
        os << (p.is_shared() ? "shared" : "owned");
        if (auto it = p.points->begin(), end = p.points->end(); it != end){
            os << ":" << *it;
            while (++it != end)
                os << "," << *it;
        }
    } else
        os << "nullptr";
    return os << "}";
}