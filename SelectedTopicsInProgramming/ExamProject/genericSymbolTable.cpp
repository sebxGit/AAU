#include <algorithm>
#include "genericSymbolTable.h"
#include <iomanip>

namespace stochastic {
    void GenericSymbolTable::add(auto name, auto value) {
        if (table.contains(name)){
            std::cout << "Symbol " << name << " is already in the table" << std::endl;
        }
        else {
            table[name] = value;
            initial.push_back(reactor{name});
        }
    }

    double GenericSymbolTable::get(const std::string &name) {
        if (table.find(name) == table.end())
            throw std::runtime_error("Symbol not found");
        return table[name];
    }

    void GenericSymbolTable::show() {
        auto res = std::ranges::max_element(table,[] (const auto& a, const auto& b) { return a.first.length() < b.first.length(); });
        int maxKeyLength = static_cast<int>(res->first.length())+2;

        for (const auto &pair : table)
            std::cout << std::left << std::setw(maxKeyLength) << pair.first;
        std::cout << std::endl;

        for (const auto &pair : table)
            std::cout << std::left << std::setw(maxKeyLength) << pair.second;
        std::cout << std::endl;
    }

    void GenericSymbolTable::setIncrease(const std::string &name, double value) {
        if (table.find(name) == table.end())
            throw std::runtime_error("Symbol not found");
        table[name] += value;
        if (useHistory) history.push_back(table);
    }

    auto GenericSymbolTable::showTrajectory() const {
        if(!useHistory)
            std::cout << "Trajectory is not enabled" << std::endl;

        std::cout << "--- Showing Trajectory ---" << std::endl;
        for (const auto& state : history) {
            for (const auto& [name, value] : state) {
                std::cout << name << ": " << value << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "--- End of Trajectory ---" << std::endl;
    }

//    double &GenericSymbolTable::operator[](const std::string &key) {
//        std::lock_guard<std::mutex> lock(mtx); // Lock the table when accessing or modifying it
//        return table[key];
//    }
}