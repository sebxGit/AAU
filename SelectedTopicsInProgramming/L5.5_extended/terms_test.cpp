/**
 * Unit tests for the term hierarchy.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#include "evaluate.hpp"
#include "print.hpp"

#include <doctest/doctest.h>

#include <sstream>
#include <memory>

using namespace calculator;

TEST_CASE("Terms")
{
    // create a symbol table to manage the variables and the state structure:
    auto sys = symbol_table_t{};

    // create variables:
    auto a = std::make_shared<var_t>(sys.var("a", 2));
    auto b = std::make_shared<var_t>(sys.var("b", 3));
    auto c = std::make_shared<var_t>(sys.var("c"));

    // build a simple AST:
    std::shared_ptr<term_t> add = std::make_shared<binary_t>(a, b, op_t::plus); // a+b
    std::shared_ptr<term_t> mul = std::make_shared<binary_t>(c, add, op_t::mul); // c*(a+b)
    std::shared_ptr<term_t> ass = std::make_shared<assign_t>(c, add, op_t::assign); // c=a+b

    // create a state to evaluate the AST on:
    auto state = sys.state();

    SUBCASE("evaluate")
    {
        auto v = eval(state, *add); // function which constructs evaluator and calls it
        CHECK(v == 2+3);
        v = eval(state, *mul);
        CHECK(v == 0*(2+3));
        v = eval(state, *ass);
        CHECK(v == 2+3);
        v = eval(state, *mul);
        CHECK(v == 5*(2+3));
        v = eval(state, *add);
        CHECK(v == 2+3);
    }

    // create a stream to print to:
    auto os = std::ostringstream();
    auto oes = OExprStream{os, sys};

    SUBCASE("print add")
    {
        oes << add; // function which constructs a printable object which calls printer visitor
        CHECK(os.str() == "(a+b)");
    }
    SUBCASE("print mul")
    {
        oes << mul; // function which constructs a printable object which calls printer visitor
        CHECK(os.str() == "c*(a+b)");
    }
    SUBCASE("print assign")
    {
        oes << ass; // function which constructs a printable object which calls printer visitor
        CHECK(os.str() == "c = (a+b)");
    }
}
