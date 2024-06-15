/**
 * Implementation for the evaluation of DSEL calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include "evaluate.hpp"
#include "visitor.hpp"

namespace calculator
{
    class Evaluator final : private ConstVisitor
    {
        state_t& s;   ///< capture by ref. to preserve applied changes
        double res{}; ///< the result of visitor computation

        void visit(const var_t& v) override { res = s[v]; }
        void visit(const const_t& c) override { res = c.get_value(); }
        void visit(const unary_t& u) override {
            u.get_term().accept(*this);
            switch (u.get_op()) {
            case op_t::plus: break;
            case op_t::minus: res = -res; break;
            default:
                throw std::logic_error{"unknown unary operator"};
            }
        }
        void visit(const binary_t& b) override {
            b.get_term1().accept(*this);
            auto first = res;
            b.get_term2().accept(*this);
            auto second = res;
            switch (b.get_op()) {
            case op_t::plus: res = first + second; break;
            case op_t::minus: res = first - second; break;
            case op_t::mul: res = first * second; break;
            case op_t::div: {
                if (second == 0)
                    throw std::logic_error{"division by zero"};
                res = first / second;
                break;
            }
            default:
                throw std::logic_error{"unknown binary operator"};
            }
        }
        void visit(const assign_t& a) override {
            a.get_term().accept(*this);
            switch (a.get_op()) {
            case op_t::assign: s[a.get_var()] = res; break;
            case op_t::plus: res = s[a.get_var()] += res; break;
            case op_t::minus: res = s[a.get_var()] -= res; break;
            case op_t::mul: res = s[a.get_var()] *= res; break;
            case op_t::div: {
                if (res == 0)
                    throw std::logic_error{"division by zero"};
                res = s[a.get_var()] /= res;
                break;
            }
            default: throw std::logic_error{"unknown assignment operator"};
            }
        }
    public:
        explicit Evaluator(state_t& s): s{s} {}
        double evaluate(const term_t& term) {
            term.accept(*this);
            return res;
        }
    };

    double state_t::operator()(const term_t& term) {
        return Evaluator{*this}.evaluate(term);
    }

}
