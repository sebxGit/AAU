#include <set>
#include "networkGraph.h"

namespace stochastic {
    std::string networkGraph::addNode(const std::string &name, const std::string &type) {
        if (nodeMap.find(name) != nodeMap.end() && type != "number") return name;
        std::string temp;
        while (type == "number" && nodeMap.find(name+temp) != nodeMap.end())
            temp += "_";
        nodeMap[name+temp] = std::make_shared<node>(name+temp, std::vector<std::shared_ptr<node>>{});
        return name+temp;
    }

    void networkGraph::show() {
        for (const auto &node : nodeMap) {
            std::cout << node.second->data << " -> ";
            for (const auto nextNode : node.second->next) {
                if (nextNode != nullptr)
                    std::cout << nextNode->data << " ";
            }
            std::cout << std::endl;
        }
    }

    void networkGraph::addEdge(const std::string& name1, const std::string& name2) {
        nodeMap[name1]->next.push_back(nodeMap[name2]);
    }
}

