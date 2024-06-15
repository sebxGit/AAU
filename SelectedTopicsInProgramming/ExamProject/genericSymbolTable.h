#include <map>
#include <vector>
#include <string>
#include <any>
#include <iostream>
#include <mutex>
#include "reactor.h"

#ifndef GENERICSYMBOLTABLE_H
#define GENERICSYMBOLTABLE_H

namespace stochastic {
    class GenericSymbolTable {
        std::map<std::string, double> table;
        std::vector<reactor> initial;
        std::vector<std::map<std::string, double>> history;
        bool useHistory = false;

    public:
        void add(auto name, auto value);
        double get(const std::string &name);
        void show();
        [[nodiscard]] std::vector<reactor> state() const { return initial; }
        void setIncrease(const std::string &name, double value);
        [[nodiscard]] auto showTrajectory() const;
    };
}

#endif //GENERICSYMBOLTABLE_H
