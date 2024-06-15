#include "reaction.h"
#include "reactor.h"
#include "genericSymbolTable.h"
#include <map>
#include <random>
#include <sstream>
#include <utility>

namespace stochastic {
    template <typename T>
    inline reaction reaction::operator>>(T d) {
        if (!std::is_same<T, int>::value && !std::is_same<T, double>::value)
            throw std::invalid_argument("Delay must be either an int or a double.");
        delay = d;
        return *this;
    }

    inline reaction reaction::operator>>=(const reactor &r) {
        product.push_back(std::make_shared<reactor>(r));
        return *this;
    }

    inline reaction reaction::operator>>=(const reaction &reaction) {
        for (auto &r : reaction.input)
            product.push_back(std::make_shared<reactor>(*r));
        return *this;
    }

    inline reaction reaction::operator>>=(const std::vector<reactor> &reactors) {
        for (auto &r : reactors)
            product.push_back(std::make_shared<reactor>(r));
        return *this;
    }

    auto reaction::getReactorValues(GenericSymbolTable table) const {
        std::vector<double> values;
        for (auto &r : input) {
            double value = table.get(r->name);
            values.push_back(value);
        }
        return values;
    }

    auto reaction::update(GenericSymbolTable table) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::vector<double> v = getReactorValues(std::move(table));
        double prod = std::accumulate(v.begin(), v.end(), 1.0, std::multiplies<>());
        std::exponential_distribution<> d(delay*prod);
        delay = d(gen);
    }

    std::string reaction::show() {
        std::ostringstream oss;
        oss << " | ";
        for (auto it = input.begin(); it != input.end(); ++it) {
            oss << (*it)->name;
            if (std::next(it) != input.end())
                oss << " + ";
        }
        oss << " -->(" << delay << ") ";
        for (auto it = product.begin(); it != product.end(); ++it) {
            oss << (*it)->name;
            if (std::next(it) != product.end())
                oss << " + ";
        }
        return oss.str();
    }
}