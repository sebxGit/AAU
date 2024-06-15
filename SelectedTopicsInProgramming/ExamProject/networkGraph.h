#include <vector>
#include <iostream>
#include <algorithm>

#ifndef NETWORKGRAPH_H
#define NETWORKGRAPH_H

namespace stochastic {
    class node {
    public:
        std::string data;
        std::vector<std::shared_ptr<node>> next;
    };

    class networkGraph {
        std::map<std::string, std::shared_ptr<node>> nodeMap;

    public:
        std::string addNode(const std::string& name, const std::string& type="string");
        void addEdge(const std::string& name1, const std::string& name2);
        void show();
    };
}

#endif // NETWORKGRAPH_H
