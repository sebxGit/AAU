/**
 * Arithmetic operators over the DSEL calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#ifndef CALCULATOR_EXPRESSIONS_HPP
#define CALCULATOR_EXPRESSIONS_HPP

#include "terms.hpp"
#include <memory>

namespace calculator
{
    struct state_t;

    /** Lightweight adapter for operator overloading, which wraps AST term and participate in operator overloads */
    struct expr_t
    {
        std::shared_ptr<term_t> term;
        /// *implicit* constructors for conversion during operator applications:
        expr_t(std::shared_ptr<term_t> term): term{std::move(term)} {}
        expr_t(const var_t& var): term{std::make_shared<var_t>(var)} {}
        expr_t(double value): term{std::make_shared<const_t>(value)} {}

        // Rule of Five:
        expr_t(const expr_t&) = default;
        expr_t& operator=(const expr_t&) = default;
        expr_t(expr_t&&) = default;
        expr_t& operator=(expr_t&&) = default;
        ~expr_t() noexcept = default;
        /** Evaluates the expression on a given state: */
        double operator()(state_t&) const; // external implementation
    };

    // Operator overload definitions can be moved into CPP file, but they are short, thus INLINE:
    /** unary plus */
    inline expr_t operator+(const expr_t& expr) { return {std::make_unique<unary_t>(expr.term, op_t::plus)}; }
    /** unary minus */
    inline expr_t operator-(const expr_t& expr) { return {std::make_unique<unary_t>(expr.term, op_t::minus)}; }

    /** binary plus */
    inline expr_t operator+(const expr_t& expr1, const expr_t& expr2)
    {
        return {std::make_unique<binary_t>(expr1.term, expr2.term, op_t::plus)};
    }
    /** binary minus */
    inline expr_t operator-(const expr_t& expr1, const expr_t& expr2)
    {
        return {std::make_unique<binary_t>(expr1.term, expr2.term, op_t::minus)};
    }
    /** multiply */
    inline expr_t operator*(const expr_t& expr1, const expr_t& expr2)
    {
        return {std::make_unique<binary_t>(expr1.term, expr2.term, op_t::mul)};
    }
    /** divide */
    inline expr_t operator/(const expr_t& expr1, const expr_t& expr2)
    {
        return {std::make_unique<binary_t>(expr1.term, expr2.term, op_t::div)};
    }

    /** assignment: */
    inline expr_t operator<<=(const expr_t& var, const expr_t& expr)
    {
        return {std::make_unique<assign_t>(var.term, expr.term, op_t::assign)};
    }

    /** summation */
    inline expr_t operator+=(const expr_t& var, const expr_t& expr)
    {
        return {std::make_unique<assign_t>(var.term, expr.term, op_t::plus)};
    }
    /** subtraction */
    inline expr_t operator-=(const expr_t& var, const expr_t& expr)
    {
        return {std::make_unique<assign_t>(var.term, expr.term, op_t::minus)};
    }
    /** multiplication */
    inline expr_t operator*=(const expr_t& var, const expr_t& expr)
    {
        return {std::make_unique<assign_t>(var.term, expr.term, op_t::mul)};
    }
    /** division */
    inline expr_t operator/=(const expr_t& var, const expr_t& expr)
    {
        return {std::make_unique<assign_t>(var.term, expr.term, op_t::div)};
    }
}

#endif  // CALCULATOR_EXPRESSIONS_HPP
