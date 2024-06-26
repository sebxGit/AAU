#include <string>
#include <vector>
#include <memory>

#ifndef REACTION_H
#define REACTION_H

namespace stochastic {
    class reactor;
    class GenericSymbolTable;

    class reaction {
    public:
        std::vector<std::shared_ptr<reactor>> input;
        std::vector<std::shared_ptr<reactor>> product;
        double delay{};

        [[nodiscard]] auto getReactorValues(GenericSymbolTable& table) const;
        [[nodiscard]] auto update(GenericSymbolTable table);
        std::string show();

        template <typename T>
        inline reaction operator>>(T d);
        inline reaction operator>>=(const reactor& r);
        inline reaction operator>>=(const reaction& reaction);
        inline reaction operator>>=(const std::vector<reactor> &reactors);
    };
}

#endif // REACTION_H
