/**
 * Declarations for the term hierarchy capturing the AST of calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#ifndef CALCULATOR_TERMS_HPP
#define CALCULATOR_TERMS_HPP

#include <vector>
#include <memory>

namespace calculator
{
    class Visitor;
    class ConstVisitor;

    /** Interface to various terms: */
    struct term_t // : std::enable_shared_from_this<term_t>
    {
        term_t() = default;
        term_t(const term_t&) = delete;
        term_t& operator=(const term_t&) = delete;
        /** Abstract class should always supply a virtual destructor: */
        virtual ~term_t() noexcept = default;
        /** Visitor interface with mutable access: */
        virtual void accept(Visitor&) = 0;
        /** Visitor interface with read-only access: */
        virtual void accept(ConstVisitor&) const = 0;
    };

    /** Special term for a variable expression: */
    class var_t final: public term_t
    {
        size_t id{}; ///< variable identifier (index into state)

    protected:
        /// Only symbol_table_t is allowed to construct variables:
        explicit var_t(size_t id): id{id} {}

    public:
        var_t(const var_t& other) { *this = other; } ///< allow copying
        var_t& operator=(const var_t& other) { id = other.id; return *this; }
        size_t get_id() const { return id; }
        void accept(Visitor& v) override;
        void accept(ConstVisitor& v) const override;
        friend class symbol_table_t; // to create instances
    };

    /** Special term for capturing number literals/constants */
    class const_t final : public term_t
    {
        double value;

    public:
        explicit const_t(double value): value{value} {}
        double get_value() const { return value; }
        void accept(Visitor& v) override;
        void accept(ConstVisitor& v) const override;
    };

    /** Possible operations: */
    enum class op_t { plus, minus, mul, div, assign };

    /** Specialization for two unary operations: */
    class unary_t final : public term_t
    {
        std::shared_ptr<term_t> term;
        op_t op;

    public:
        explicit unary_t(std::shared_ptr<term_t> term, op_t op = op_t::plus): term{std::move(term)}, op{op} {}
        const term_t& get_term() const { return *term; }
        op_t get_op() const { return op; }
        void accept(Visitor& v) override;
        void accept(ConstVisitor& v) const override;
    };

    /** Specialization for four binary operations: */
    class binary_t final : public term_t
    {
        std::shared_ptr<term_t> t1;
        std::shared_ptr<term_t> t2;
        op_t op;

    public:
        binary_t(std::shared_ptr<term_t> t1, std::shared_ptr<term_t> t2, op_t op):
            t1{std::move(t1)}, t2{std::move(t2)}, op{op}
        {}
        const term_t& get_term1() const { return *t1; }
        const term_t& get_term2() const { return *t2; }
        op_t get_op() const { return op; }

        void accept(Visitor& v) override;
        void accept(ConstVisitor& v) const override;
    };

    /** Specialization for five assignment operations: */
    class assign_t final : public term_t
    {
        std::shared_ptr<var_t> var;
        std::shared_ptr<term_t> term;
        op_t op;

    public:
        assign_t(std::shared_ptr<term_t> var, std::shared_ptr<term_t> term, op_t op = op_t::assign):
            var{std::dynamic_pointer_cast<var_t>(std::move(var))}, term{std::move(term)}, op{op}
        {
            if (this->var == nullptr)
                throw std::logic_error{"assignment destination must be a valid variable expression"};
        }
        const var_t& get_var() const { return *var; }
        const term_t& get_term() const { return *term; }
        op_t get_op() const { return op; }
        void accept(Visitor& v) override;
        void accept(ConstVisitor& v) const override;
    };
}

#endif  // CALCULATOR_TERMS_HPP
