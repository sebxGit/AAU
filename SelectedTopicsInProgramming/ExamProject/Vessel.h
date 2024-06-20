#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "reaction.h"
#include "reactor.h"

#ifndef VESSEL_H
#define VESSEL_H

namespace stochastic {
    class Vessel {
        std::string name_;
        std::vector<reaction> reactions_;
        GenericSymbolTable table;

        std::string getNames(const std::vector<std::shared_ptr<reactor>>& reactors);
    public:
        explicit Vessel(std::string name) : name_(std::move(name)) { table = GenericSymbolTable(); };

        auto environment(){ return table.state(); }
        auto getName() { return name_; };
        GenericSymbolTable getTable() { return table; }

        template<typename T>
        auto add(const std::string &&name, T value);
        auto add(const reaction& r){ reactions_.push_back(r); }

        auto addTableHistory(const double time) { table.addHistory(time); }
        auto setTableIncrease(const std::string &name, const double value) { table.setIncrease(name, value); }
        bool getTableRecordHistory() { return table.getRecordHistory(); }
        auto showTable() { table.show(); }
        double getTableValue(const std::string& name) { return table.get(name);}
        void tableExportTrajectory(const std::string& path) { table.exportTrajectory(path); }
        auto tableShowTrajectory() { return table.showTrajectory(); }

        auto prettyPrintHumanFormat();
        auto prettyPrintNetworkGraph();
        auto getReactions() { return reactions_; }
    };
}
#endif //VESSEL_H
