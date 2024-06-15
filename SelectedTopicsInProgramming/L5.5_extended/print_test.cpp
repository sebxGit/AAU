/**
 * Unit test for the printing of expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#include "print.hpp"

#include <doctest/doctest.h>
#include <sstream>

using namespace calculator;

TEST_CASE("Printing expressions using OExprStream")
{
    auto os = std::ostringstream{};
    auto st = symbol_table_t{};
    const auto a = st.var("a", 2);
    const auto b = st.var("b", 3);
    const auto c = st.var("c", 5);
    auto oes = OExprStream{os, st};
    SUBCASE("Print expressions 1")
    {
        oes << -(a + b * c);
        CHECK(os.str() == "-(a+b*c)");
    }
    SUBCASE("Print expressions 2")
    {
        oes << (c <<= -(a + b) * c);
        CHECK(os.str() == "c = -(a+b)*c");
    }
}

TEST_CASE("Printing expressions using Printer")
{
    auto os = std::ostringstream{};
    auto st = symbol_table_t{};
    const auto a = st.var("a", 2);
    const auto b = st.var("b", 3);
    const auto c = st.var("c", 5);
    SUBCASE("Print expressions 1")
    {
        os << Printer{st, -(a + b * c)};
        CHECK(os.str() == "-(a+b*c)");
    }
    SUBCASE("Print expressions 2")
    {
        os << Printer{st, (c <<= -(a + b) * c)};
        CHECK(os.str() == "c = -(a+b)*c");
    }
}
