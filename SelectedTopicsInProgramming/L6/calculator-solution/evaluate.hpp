/**
 * Declarations for the evaluation of DSEL calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#ifndef CALCULATOR_EVALUATE_HPP
#define CALCULATOR_EVALUATE_HPP

#include "expressions.hpp"

namespace calculator {

    /** Distinct class for managing the state with restricted interface */
    class state_t
    {
        std::vector<double> values; ///< only symbol_table_t can change

    public:
        /** Evaluates the term (nicer syntax): */
        double operator()(const term_t&);
        /** Evaluates the expression (nicer syntax): */
        double operator()(const expr_t& e) { return (*this)(*e.term); }
        /** Evaluates the variable (nicer syntax): */
        double& operator[](const var_t& var) { return values[var.get_id()]; }
        friend class symbol_table_t;
    };

    class symbol_table_t
    {
        std::vector<std::string> names; ///< variable identifier names
        state_t initial;                ///< initial value for each variable
        /** Helper function to create new variable identifiers: */
        size_t create_id(std::string name, double init = 0) {
            auto id = names.size();
            names.push_back(std::move(name));
            initial.values.push_back(init);
            return id;
        }
    public:
        /** Create a variable expression (cleaner interface): */
        [[nodiscard]] expr_t vare(std::string name, double init = 0) {
            return {std::shared_ptr<var_t>(new var_t{var(name, init)})};
        }
        /** Create a variable (internal, just for term tests): */
        [[nodiscard]] var_t var(std::string name, double init = 0)
        {
            return var_t{create_id(std::move(name), init)};
        }
        const std::string& get_name(const var_t& var) const { return names[var.id]; }
        [[nodiscard]] state_t state() const { return initial; }
    };

    /** Evaluates the term over a given state: */
    inline double eval(state_t& state, const term_t& term) { return state(term); }

    /** Evaluates the expression over a given state: */
    inline double eval(state_t& state, const expr_t& expr) {
        return eval(state, *expr.term);
    }
}

#endif  // CALCULATOR_EVALUATE_HPP
