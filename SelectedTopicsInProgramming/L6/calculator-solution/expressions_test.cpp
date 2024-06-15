/**
 * Demo and unit tests for DSEL calculator expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#include "expressions.hpp"
#include "evaluate.hpp"
#include "print.hpp"

#include <doctest/doctest.h>

#include <sstream>

using namespace calculator;

TEST_CASE("Calculate expressions")
{
    auto sys = symbol_table_t{};
    auto a = sys.vare("a", 2);
    auto b = sys.vare("b", 3);
    auto c = sys.vare("c");
    auto state = sys.state();
    auto os = std::ostringstream();
    auto oes = OExprStream{os, sys};

    SUBCASE("Reading the value of a variable from state")
    {
        // check initial values:
        CHECK(a(state) == 2);
        CHECK(b(state) == 3);
        CHECK(c(state) == 0);
    }
    SUBCASE("Unary operations")
    {
        // check initial values:
        CHECK((+a)(state) == 2);
        CHECK((-b)(state) == -3);
        CHECK((-c)(state) == 0);
    }
    SUBCASE("Addition and subtraction")
    {
        CHECK((a + b)(state) == 2+3);
        CHECK((a - b)(state) == 2-3);
        // the state should not have changed:
        CHECK(a(state) == 2);
        CHECK(b(state) == 3);
        CHECK(c(state) == 0);
    }
    SUBCASE("Assignment expression evaluation")
    {
        CHECK(c(state) == 0);
        CHECK((c <<= b - a)(state) == 3-2); // 1
        CHECK(c(state) == 1);
        CHECK((c += b - a * c)(state) == 1 + 3-2*1); // 2
        CHECK(c(state) == 2);
        CHECK((c += b - a * c)(state) == 2 + 3-2*2); // 1
        CHECK(c(state) == 1);
        CHECK_THROWS_MESSAGE((c - a += b - c), "assignment destination must be a variable expression");
    }
    SUBCASE("Parenthesis")
    {
        CHECK((a - (b - c))(state) == 2-(3-0));
        CHECK((a - (b - a))(state) == 2-(3-2));
    }
    SUBCASE("Evaluation of multiplication and division")
    {
        CHECK((a * b)(state) == 2*3);
        CHECK((a / b)(state) == 2./3);
        CHECK_THROWS_MESSAGE((a / c)(state), "division by zero");
    }
    SUBCASE("Mixed addition and multiplication")
    {
        CHECK((a + a * b)(state) == 2+2*3);
        CHECK((a - b / a)(state) == 0.5);
    }
    SUBCASE("Constant expressions")
    {
        CHECK((7+a)(state) == 9);
        CHECK((a-7)(state) == -5);
    }
    SUBCASE("Store expression and evaluate lazily")
    {
        auto expr = (a+b)*c;
        auto c_4 = c <<= 4;
        CHECK(expr(state) == 0);
        CHECK(c_4(state) == 4);
        CHECK(expr(state) == 20);
    }
    SUBCASE("Print expressions 1")
    {
        oes << -(a+b*c);
        CHECK(os.str() == "-(a+b*c)");
    }
    SUBCASE("Print expressions 2")
    {
        oes << (c <<= -(a+b)*c);
        CHECK(os.str() == "c = -(a+b)*c");
    }
    // Library usage demonstration:
    SUBCASE("Fancy syntax for expression evaluation on a state")
    {
        CHECK(state(a) == 2);
        CHECK(state(b) == 3);
        CHECK(state(c) == 0);
        CHECK(state(-a) == -2);
        CHECK(state(+b) == 3);
        CHECK(state(a+b) == 2+3);
        CHECK(state(a+b*c) == 2+3*0);
        CHECK(state((a+b)*c) == (2+3)*0);
        CHECK(state(c += a+b) == 0+2+3);
        CHECK(state(a+b*c) == 2+3*5);
        CHECK(state((a+b)*c) == (2+3)*5);
    }
}
