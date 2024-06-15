# Calculator
The project demonstrates a solution to a simple DSEL calculator with:
1. Arithmetic operations over variables and constants.
2. Lazy evaluation using visitor pattern.
3. Printing using visitor pattern.

## Overview

The project contains two independent implementations:

1. [calculator.hpp](calculator.hpp) contains a complete but naive implementation in one header, without visitor pattern.
2. Complete and clean, separated across multiple files:
   - [terms.hpp](terms.hpp) class hierarchy for capturing AST structure without operator overloads.
   - [terms.cpp](terms.cpp) visitor support implementation.
   - [expressions.hpp](expressions.hpp) arithmetic operator overloads building a corresponding AST.
   - [visitor.hpp](visitor.hpp) contains visitor pattern interface for double-dispatching over the AST terms.
   - [evaluate.hpp](evaluate.hpp) contains evaluation interface.
   - [evaluate.cpp](evaluate.cpp) contains evaluation implementation using visitor pattern.
   - [print.hpp](print.hpp) contains printing interface.
   - [print.cpp](print.cpp) contains printing implementation using visitor pattern.

The library usage is demonstrated in the [expressions_test.cpp](expressions_test.cpp) unit tests.

## Unit tests:
- Run all tests: `All CTest`
- `calculator_test` in [calculator_test.cpp](calculator_test.cpp) tests for [calculator.hpp](calculator.hpp).
- `terms_test` in [terms_test.cpp](terms_test.cpp) tests for [terms.hpp](terms.hpp).
- `expressions_test` in [expressions_test.cpp](expressions_test.cpp) tests for [expressions.hpp](expressions.hpp), [evaluate.hpp](evaluate.hpp) and [print.hpp](print.hpp).