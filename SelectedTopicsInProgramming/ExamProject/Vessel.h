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

        static void printReactors(const std::vector<std::shared_ptr<reactor>>& reactors, const std::string& label, const std::string& offset);
        static void printNames(const std::vector<std::shared_ptr<reactor>>& reactors);
    public:
        static GenericSymbolTable table;

        explicit Vessel(std::string name) : name_(std::move(name)) { table = GenericSymbolTable(); };

        auto environment(){ return table.state(); }
        auto getName() { return name_; };

        template<typename T>
        auto add(const std::string &&name, T value);
        auto add(const reaction& r){ reactions_.push_back(r); }

        auto prettyPrintHumanFormat();
        auto prettyPrintNetworkGraph();
        auto getReactions() { return reactions_; }
    };
}
#endif //VESSEL_H
