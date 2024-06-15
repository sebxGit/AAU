/**
 * Printing interface for the calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#ifndef CALCULATOR_PRINT_HPP
#define CALCULATOR_PRINT_HPP

#include "expressions.hpp"
#include "evaluate.hpp" // symbol table

namespace calculator
{
    /** Lightweight wrapper to capture entire context needed for printing expressions. */
    struct OExprStream
    {
        std::ostream& os; ///< output stream to print to
        const symbol_table_t& symbols; ///< symbol table to look up variable names
    };
    /** Forward declaration of output operator. */
    OExprStream& operator<<(OExprStream& os, const expr_t& expr);

    /** Lightweight wrapper to capture things to be printed (alternative implementation) */
    struct Printer
    {
        const symbol_table_t& symbols; ///< symbol table to look up variable names
        const expr_t& expr; ///< expression to be printed (elevated risk for reference to dangle)
    };
    std::ostream& operator<<(std::ostream& os, const Printer& printer);
}

#endif // CALCULATOR_PRINT_HPP
