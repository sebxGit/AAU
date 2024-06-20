#include <iomanip>
#include <fstream>

namespace stochastic {
    void GenericSymbolTable::add(const std::string& name, double value) {
        if (table.find(name) != table.end())
            std::cout << "Symbol " << name << " is already in the table" << std::endl;
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
        auto res = std::max_element(table.begin(), table.end(), [] (const auto& a, const auto& b) { return a.first.length() < b.first.length(); });
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
    }

    auto GenericSymbolTable::showTrajectory() const {
        if(!recordHistory)
            std::cout << "Trajectory is not enabled" << std::endl;

        std::cout << "--- Showing Trajectory ---" << std::endl;
        for (const auto& state : history) {
            for (const auto& pair : state.second)
                std::cout << pair.first << ": " << pair.second << " ";
            std::cout << "| time: " << state.first << std::endl;
        }
        std::cout << "--- End of Trajectory ---" << std::endl;
    }

    void GenericSymbolTable::exportTrajectory(const std::string& path) const {
        if(!recordHistory) {
            std::cout << "Trajectory is not enabled" << std::endl;
            return;
        }

        auto filename = "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming"
                        "/ExamProject/figures/" + path;

        std::fstream fout;

        fout.open(filename, std::ios::out | std::ios::trunc);
        if (!fout.is_open()) {
            std::cerr << "Could not open file for writing" << std::endl;
            return;
        }

        for (const auto& pair : history[0].second)
            fout << pair.first << ",";
        fout << "Time\n";

        for (const auto& pair : history) {
            for (const auto& pair2 : pair.second)
                fout << pair2.second << ",";
            fout << pair.first << "\n";
        }

        fout.close();
    }

}