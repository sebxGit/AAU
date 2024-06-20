#ifndef NETWORKGRAPH_H
#define NETWORKGRAPH_H

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

namespace stochastic {
    class node {
    public:
        std::string data;
        std::vector<std::shared_ptr<node>> next;
        node(std::string data, const std::vector<std::shared_ptr<node>>& next) : data(std::move(data)), next(next) {}
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
