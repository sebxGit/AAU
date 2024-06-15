#include <iostream>
#include <string>
#include "reaction.h"

#ifndef REACTOR_H
#define REACTOR_H

namespace stochastic {
    class reactor {
    public:
        std::string name{};

        template <typename T>
        inline reaction operator>>(T delay) const;
        inline reaction operator+(const reactor &r) const;
    };
};
#endif //REACTOR_H