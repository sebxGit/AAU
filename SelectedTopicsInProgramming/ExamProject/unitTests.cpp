#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>
#include <vector>
#include <functional>
#include <future>
#include "reaction.cpp"
#include "reactor.cpp"
#include "genericSymbolTable.cpp"
#include "Vessel.cpp"
#include "simulation.cpp"
#include "peakHospitalizationObserver.h"
#include "ThreadPool.h"
#include "definitions.cpp"

void printAsciiValues(const std::string& str) {
    for (char c : str) {
        std::cout << static_cast<int>(c) << " ";
    }
    std::cout << "\n";
}

// Pretty print tests
TEST_CASE("testing prettyPrintHumanFormat for figure_1b") {
    stochastic::Vessel vessel = stochastic::figure_1b();
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout to a stringstream

    vessel.prettyPrintHumanFormat();

    std::cout.rdbuf(prevcoutbuf); // Redirect std::cout back to the console

    std::string expectedOutput = "Vessel: Figure 1\n"
                                 "Reactions: \n"
                                 "  Reaction: A + C -->(0.001000) B + C\n"
                                 "    Input: A : 100.000000, C : 2.000000\n"
                                 "    Output: B : 0.000000, C : 2.000000\n"
                                 "    Delay: 0.001000\n";
//    printAsciiValues(buffer.str());
//    printAsciiValues(expectedOutput);
    CHECK(buffer.str() == expectedOutput);
}

TEST_CASE("testing prettyPrintNetworkGraph for figure_1b") {
    stochastic::Vessel vessel = stochastic::figure_1b();
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout to a stringstream

    vessel.prettyPrintNetworkGraph();

    std::cout.rdbuf(prevcoutbuf); // Redirect std::cout back to the console

    std::string expectedOutput = "0.001000 -> B C \n"
                                 "A -> 0.001000 \n"
                                 "B -> \n"
                                 "C -> 0.001000 \n";
//    printAsciiValues(buffer.str());
//    printAsciiValues(expectedOutput);
    CHECK(buffer.str() == expectedOutput);
}

// GenericSymbolTable tests
TEST_CASE("testing add and get two values, assign two values, but expect no value change") {
    stochastic::GenericSymbolTable table;
    table.add("test", 1.0);
    CHECK(table.get("test") == 1.0);
    table.add("test", 2.0);
    CHECK(table.get("test") == 1.0);
}

TEST_CASE("testing add but symbol already in table") {
    stochastic::GenericSymbolTable table;
    table.add("test", 1.0);

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout to a stringstream

    table.add("test", 2.0); // Expect message printed: "Symbol test is already in the table"

    std::cout.rdbuf(prevcoutbuf); // Redirect std::cout back to the console

    std::string expectedOutput = "Symbol test is already in the table\n";
    CHECK(buffer.str() == expectedOutput);
}

TEST_CASE("testing get and expect Symbol not found") {
    stochastic::GenericSymbolTable table;
    CHECK_THROWS_WITH(table.get("nonExistingSymbol"), "Symbol not found");
}

TEST_CASE("testing setIncrease increase and decrease"){
    stochastic::GenericSymbolTable table;
    table.add("test", 1.0);
    table.setIncrease("test", 1.0);
    CHECK(table.get("test") == 2.0);
    table.setIncrease("test", -1.0);
    CHECK(table.get("test") == 1.0);
}

TEST_CASE("testing setIncrease but symbol not in table"){
    stochastic::GenericSymbolTable table;
    CHECK_THROWS_WITH(table.setIncrease("nonExistingSymbol", 1.0), "Symbol not found");
}


