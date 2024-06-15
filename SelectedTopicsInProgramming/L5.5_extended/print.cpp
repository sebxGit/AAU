/**
 * Printing implementation for the calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#include "print.hpp"
#include "visitor.hpp"
#include <iostream>

namespace calculator
{
    /**
     * Visitor implementation for printing terms into output stream.
     * In this particular case we are lucky to be able to inherit privately
     * just because we upcast to ConstVisitor ourselves in operator<<.
     * In general (especially if PrintVisitor is shared in header), inheritance should be public.
     * "final" means we do not allow further inheritance, thus allowing compiler to optimize
     * the virtual table calls into plain method calls when it deals with PrintVisitor directly
     * (unlikely here).
     */
    class PrintVisitor final : private ConstVisitor
    {
        std::ostream& os; ///< output stream to output to
        const symbol_table_t& symbols; ///< symbol table to lookup variable names

        void print(op_t op)
        {
            switch (op) {
            case op_t::plus: os << '+'; break;
            case op_t::minus: os << '-'; break;
            case op_t::mul: os << '*'; break;
            case op_t::div: os << '/'; break;
            case op_t::assign: break;
            default: throw std::logic_error{"unknown operator"};
            }
        }
        // Visitor implementation
        void visit(const var_t& v) override { os << symbols.get_name(v); }
        void visit(const const_t& c) override { os << c.get_value(); }
        void visit(const assign_t& a) override
        {
            visit(a.get_var());
            os << ' ';
            print(a.get_op());
            os << "= ";
            a.get_term().accept(*this);
        }
        void visit(const unary_t& u) override
        {
            print(u.get_op());
            //os << "(";
            u.get_term().accept(*this);
            //os << ")";
        }
        void visit(const binary_t& b) override
        {
            auto op = b.get_op();
            if (op == op_t::plus || op == op_t::minus)
                os << "(";
            b.get_term1().accept(*this);
            print(op);
            b.get_term2().accept(*this);
            if (op == op_t::plus || op == op_t::minus)
                os << ")";
        }
    public:
        PrintVisitor(std::ostream& os, const symbol_table_t& symbols): os{os}, symbols{symbols} {}
        std::ostream& operator<<(const expr_t& e)
        {
            e.term->accept(*this);
            return os;
        }
    };

    OExprStream& operator<<(OExprStream& os, const expr_t& expr)
    {
        PrintVisitor{os.os, os.symbols} << expr;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Printer& printer)
    {
        PrintVisitor{os, printer.symbols} << printer.expr;
        return os;
    }

}
