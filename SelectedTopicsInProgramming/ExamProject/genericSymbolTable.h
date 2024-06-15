#ifndef GENERICSYMBOLTABLE_H
#define GENERICSYMBOLTABLE_H
#include <map>
#include <vector>
#include <string>
#include <any>
#include <iostream>
#include <mutex>
#include "reactor.h"


namespace stochastic {
    class GenericSymbolTable {
        std::map<std::string, double> table;
        std::vector<reactor> initial;
        std::vector<std::pair<double, std::map<std::string, double>>> history;
        bool useHistory = false;

    public:
        void add(const std::string& name, double value);
        double get(const std::string &name);
        void show();
        [[nodiscard]] std::vector<reactor> state() const { return initial; }
        bool getHistory() const { return useHistory; }
        void addHistory(double time) { history.emplace_back(time,table); }
        void setIncrease(const std::string &name, double value);
        [[nodiscard]] auto showTrajectory() const;
        void exportTrajectory() const;
    };
}

#endif //GENERICSYMBOLTABLE_H
