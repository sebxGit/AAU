/// Created by Marius Mikučionis <marius@cs.aau.dk>

#include "terms.hpp"
#include "visitor.hpp"

/** Visitor support implementation moved to CPP file in order to break the circular dependency. */

namespace calculator
{
    void const_t::accept(Visitor& v) { v.visit(*this); };
    void const_t::accept(ConstVisitor& v) const { v.visit(*this); };
    void var_t::accept(Visitor& v) { v.visit(*this); };
    void var_t::accept(ConstVisitor& v) const { v.visit(*this); };
    void unary_t::accept(Visitor& v) { v.visit(*this); };
    void unary_t::accept(ConstVisitor& v) const { v.visit(*this); };
    void binary_t::accept(Visitor& v) { v.visit(*this); };
    void binary_t::accept(ConstVisitor& v) const { v.visit(*this); };
    void assign_t::accept(Visitor& v) { v.visit(*this); };
    void assign_t::accept(ConstVisitor& v) const { v.visit(*this); };
}
