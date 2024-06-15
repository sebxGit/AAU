#include "reactor.h"
#include <typeinfo>

namespace stochastic {
    template <typename T>
    inline reaction reactor::operator>>(T delay) const {
        reaction result;
        if(!std::is_same_v<T, int> && !std::is_same_v<T, double>)
            throw std::invalid_argument("Delay must be either an int or a double.");

        result.input.push_back(std::make_shared<reactor>(*this));
        result.delay = static_cast<double>(delay);
        return result;
    }

    inline reaction reactor::operator+(const reactor &r) const {
        reaction result;
        result.input.push_back(std::make_shared<reactor>(*this));
        result.input.push_back(std::make_shared<reactor>(r));
        return result;
    }
}
