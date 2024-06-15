/**
 * Simple (all in one header) implementation of DSEL calculator (limited design).
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#ifndef INCLUDE_CALCULATOR_HPP
#define INCLUDE_CALCULATOR_HPP

#include <vector>
#include <list>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace calculator
{
    using state_t = std::vector<double>;

    /** Operations: */
    enum class op_t { plus, minus, mul, div, assign };

    /** Interface to various terms */
    struct term_t //: std::enable_shared_from_this<term_t>
    {
        term_t() = default;
        term_t(const term_t&) = delete;
        term_t& operator=(const term_t&) = delete;
        term_t(term_t&&) = delete;
        term_t& operator=(term_t&&) = delete;
        virtual ~term_t() noexcept = default;
        virtual double operator()(state_t&) const = 0;
    };

    /** Special term for a variable: */
    class var_t: public term_t
    {
        size_t id{};
    protected:
        // Only symbol_table_t is allowed to create variables:
        explicit var_t(size_t id): id{id} {}
    public:
        var_t(const var_t& other) { *this = other; }
        var_t& operator=(const var_t& other) { id = other.id; return *this; }
        size_t get_id() const { return id; }
        /** returns the value of the variable stored in a state */
        double operator()(state_t& s) const override { return s[id]; }
        friend class symbol_table_t;
    };

    /** Symbol table manages variables and the structure of the state. */
    class symbol_table_t
    {
        std::vector<std::string> names;
        state_t initial;
    public:
        [[nodiscard]] var_t var(std::string name, double init = 0) {
            auto id = names.size();
            names.push_back(std::move(name));
            initial.push_back(init);
            return var_t{id};
        }
        const std::string& get_name(size_t id) const { return names[id]; }
        [[nodiscard]] state_t state() const { return initial; }
    };

    class const_t : public term_t
    {
        double value;
    public:
        explicit const_t(double value): value{value} {}
        double get_value() const { return value; }
        double operator()(state_t&) const override { return value; }
    };

    /** Specialization for unary operations: */
    class unary_t : public term_t
    {
        std::shared_ptr<term_t> term;
        op_t op;

    public:
        explicit unary_t(std::shared_ptr<term_t> term, op_t op = op_t::plus): term{std::move(term)}, op{op} {}
        const term_t& get_term() const { return *term; }
        op_t get_op() const { return op; }
        double operator()(state_t& s) const override
        {
            switch (op) {
            case op_t::plus: return (*term)(s);
            case op_t::minus: return -(*term)(s);
            default: throw std::logic_error{"unsupported unary operator"};
            }
        }
    };

    class binary_t : public term_t
    {
        std::shared_ptr<term_t> t1;
        std::shared_ptr<term_t> t2;
        op_t op;

    public:
        binary_t(std::shared_ptr<term_t> t1, std::shared_ptr<term_t> t2, op_t op):
            t1{std::move(t1)}, t2{std::move(t2)}, op{op} {}
        const term_t& get_term1() const { return *t1; }
        const term_t& get_term2() const { return *t2; }
        op_t get_op() const { return op; }
        double operator()(state_t& s) const override
        {
            switch (op) {
            case op_t::plus: return (*t1)(s) + (*t2)(s);
            case op_t::minus: return (*t1)(s) - (*t2)(s);
            case op_t::mul: return (*t1)(s) * (*t2)(s);
            case op_t::div: {
                auto denom = (*t2)(s);
                if (denom == 0)
                    throw std::logic_error{"division by zero"};
                return (*t1)(s) / denom;
            }
            default: throw std::logic_error{"unsupported binary operator"};
            }
        }
    };

    class assign_t: public term_t
    {
        std::shared_ptr<var_t> var;
        std::shared_ptr<term_t> term;
        op_t op;

    public:
        assign_t(std::shared_ptr<term_t> var, std::shared_ptr<term_t> term, op_t op = op_t::assign):
            var{std::dynamic_pointer_cast<var_t>(std::move(var))}, term{std::move(term)}, op{op}
        {
            if (this->var == nullptr)
                throw std::logic_error{"assignment destination must be a variable expression"};
        }
        const var_t& get_var() const { return *var; }
        const term_t& get_term() const { return *term; }
        op_t get_op() const { return op; }
        double operator()(state_t& s) const override
        {
            switch (op) {
            case op_t::assign: return s[var->get_id()] = (*term)(s);
            case op_t::plus: return s[var->get_id()] += (*term)(s);
            case op_t::minus: return s[var->get_id()] -= (*term)(s);
            case op_t::mul: return s[var->get_id()] *= (*term)(s);
            case op_t::div: {
                auto denom = (*term)(s);
                if (denom == 0)
                    throw std::logic_error{"division by zero"};
                return s[var->get_id()] /= denom;
            }
            default: throw std::logic_error{"unsupported assignment operator"};
            }
        }
    };

    /** Lightweight adapter for arithmetic operator overloading and building AST: */
    struct expr_t
    {
        // Wrap the term:
        std::shared_ptr<term_t> term;
        // Conversion operators: *implicit* constructors:
        expr_t(std::shared_ptr<term_t> term) : term{std::move(term)} {}
        expr_t(const var_t& var) : term{std::make_shared<var_t>(var)} {}
        expr_t(double value) : term{std::make_shared<const_t>(value)} {}

        // Rule of Five:
        expr_t(const expr_t&) = default;
        expr_t& operator=(const expr_t&) = default;
        expr_t(expr_t&&) = default;
        expr_t& operator=(expr_t&&) = default;
        ~expr_t() noexcept = default;

        // Evaluates the term over the given state:
        double operator()(state_t& s) const { return (*term)(s); }
    };

    inline expr_t operator+(const expr_t& expr) { return {std::make_shared<unary_t>(expr.term, op_t::plus)}; }
    inline expr_t operator-(const expr_t& expr) { return {std::make_shared<unary_t>(expr.term, op_t::minus)}; }

    inline expr_t operator+(const expr_t& expr1, const expr_t& expr2) {
        return {std::make_shared<binary_t>(expr1.term, expr2.term, op_t::plus)};
    }
    inline expr_t operator-(const expr_t& expr1, const expr_t& expr2) {
        return {std::make_shared<binary_t>(expr1.term, expr2.term, op_t::minus)};
    }
    inline expr_t operator*(const expr_t& expr1, const expr_t& expr2) {
        return {std::make_shared<binary_t>(expr1.term, expr2.term, op_t::mul)};
    }
    inline expr_t operator/(const expr_t& expr1, const expr_t& expr2) {
        return {std::make_shared<binary_t>(expr1.term, expr2.term, op_t::div)};
    }

    inline expr_t operator+=(const expr_t& var, const expr_t& expr) {
        return {std::make_shared<assign_t>(var.term, expr.term, op_t::plus)};
    }
    inline expr_t operator-=(const expr_t& var, const expr_t& expr) {
        return {std::make_shared<assign_t>(var.term, expr.term, op_t::minus)};
    }
    inline expr_t operator*=(const expr_t& var, const expr_t& expr) {
        return {std::make_shared<assign_t>(var.term, expr.term, op_t::mul)};
    }
    inline expr_t operator/=(const expr_t& var, const expr_t& expr) {
        return {std::make_shared<assign_t>(var.term, expr.term, op_t::div)};
    }
    inline expr_t operator<<=(const expr_t& var, const expr_t& expr) {
        return {std::make_shared<assign_t>(var.term, expr.term, op_t::assign)};
    }
}

#endif // INCLUDE_CALCULATOR_HPP
