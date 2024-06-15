#include "Vessel.h"
#include "networkGraph.cpp"
#include "genericSymbolTable.h"

namespace stochastic {
    GenericSymbolTable Vessel::table;

    template<typename T>
    auto Vessel::add(const std::string &&name, T value) {
        auto reactor_ = reactor{name};
        table.add(name, static_cast<double>(value));
        return reactor_;
    };

    auto Vessel::prettyPrintHumanFormat() {
        std::cout << "Vessel: " << name_ << '\n';
        std::cout << "Reactions: " << '\n';
        for (auto &reaction : reactions_) {
            std::string offset = "  ";
            std::cout << offset << "Reaction: ";
            printNames(reaction.input);
            std::cout << " -->(" << reaction.delay << ") ";
            printNames(reaction.product);
            std::cout << '\n';

            offset += "  ";
            printReactors(reaction.input, "Input", offset);
            printReactors(reaction.product, "Output", offset);
            std::cout << offset << "Delay: " << reaction.delay << std::endl;
        }
    }

    auto Vessel::prettyPrintNetworkGraph() {
        networkGraph graph;
        for (auto &reaction : reactions_) {

            std::string delay = graph.addNode(std::to_string(reaction.delay), "number");

            for (auto &input : reaction.input){
                graph.addNode(input->name);
                graph.addEdge(input->name, delay);
            }

            for (auto &output : reaction.product){
                graph.addNode(output->name);
                graph.addEdge(delay, output->name);
            }

        }
        graph.show();
    }

    void Vessel::printReactors(const std::vector<std::shared_ptr<reactor>> &reactors, const std::string &label,
                               const std::string &offset) {
        std::cout << offset << label << ": ";
        for (auto it = reactors.begin(); it != reactors.end(); ++it) {
            std::cout << (*it)->name << " : " << table.get((*it)->name);
            if (std::next(it) != reactors.end())
                std::cout << ", ";
        }
        std::cout << std::endl;
    }

    void Vessel::printNames(const std::vector<std::shared_ptr<reactor>> &reactors) {
        for (auto it = reactors.begin(); it != reactors.end(); ++it) {
            std::cout << (*it)->name;
            if (std::next(it) != reactors.end())
                std::cout << " + ";
        }
    }
}