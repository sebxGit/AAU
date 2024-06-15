/**
 * DSEL calculator expression implementation: just the evaluation.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

#include "expressions.hpp"
#include "evaluate.hpp"

namespace calculator
{
    double expr_t::operator()(state_t& s) const { return eval(s, *term); }
}
