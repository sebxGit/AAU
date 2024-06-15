/**
 * Visitor interface declaration.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#ifndef CALCULATOR_VISITOR_HPP
#define CALCULATOR_VISITOR_HPP

#include "terms.hpp"

namespace calculator {

    /** Visitor interface declaration (no implementation details!): */
    struct Visitor
    {
        virtual ~Visitor() noexcept = default;
        virtual void visit(var_t&) = 0;
        virtual void visit(const_t&) = 0;
        virtual void visit(unary_t&) = 0;
        virtual void visit(binary_t&) = 0;
        virtual void visit(assign_t&) = 0;
    };

    /**
     * Visitor interface which preserves data const-ness
     * (the visitor can still change its state).
     */
    struct ConstVisitor
    {
        virtual ~ConstVisitor() noexcept = default;
        virtual void visit(const var_t&) = 0;
        virtual void visit(const const_t&) = 0;
        virtual void visit(const unary_t&) = 0;
        virtual void visit(const binary_t&) = 0;
        virtual void visit(const assign_t&) = 0;
    };
}

#endif  // CALCULATOR_VISITOR_HPP
