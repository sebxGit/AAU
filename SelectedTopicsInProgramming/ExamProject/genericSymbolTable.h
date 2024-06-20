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
        std::vector<reactor> initial; // initial state of the simulation
        std::vector<std::pair<double, std::map<std::string, double>>> history;
        bool recordHistory = true;

    public:
        void add(const std::string& name, double value);
        double get(const std::string &name);
        void show();
        [[nodiscard]] std::vector<reactor> state() const { return initial; }
        void addHistory(double time) { history.emplace_back(time,table); }
        void setRecordHistory(bool setting) { recordHistory = setting; }
        [[nodiscard]] bool getRecordHistory() const { return recordHistory; }
        void setIncrease(const std::string &name, double value);
        [[nodiscard]] auto showTrajectory() const;
        void exportTrajectory(const std::string& path) const;
    };
}

#endif //GENERICSYMBOLTABLE_H
