#include "Vessel.h"
#include "networkGraph.cpp"
#include "genericSymbolTable.h"

namespace stochastic {

    template<typename T>
    auto Vessel::add(const std::string &&name, T value) {
        auto reactor_ = reactor{name};
        table.add(name, static_cast<double>(value));
        return reactor_;
    };

    auto Vessel::prettyPrintHumanFormat() {
        std::string result;
        result += "Reactions: \n";

        for (auto &reaction : reactions_) {
            std::string offset = "  ";
            result += offset + "Reaction: ";
            result += getNames(reaction.input);
            result += " -->(" + std::to_string(reaction.delay) + ") ";
            result += getNames(reaction.product);
            result += '\n';
        }
        std::cout << result;
        return result;
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

    std::string Vessel::getNames(const std::vector<std::shared_ptr<reactor>> &reactors) {
        std::string result;
        for (auto it = reactors.begin(); it != reactors.end(); ++it) {
            result += (*it)->name;
//            result += "[" + std::to_string(getTableValue((*it)->name)) + "]";
            if (std::next(it) != reactors.end())
                result += " + ";
        }
        return result;
    }
}