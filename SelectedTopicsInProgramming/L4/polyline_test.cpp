#include "polyline.hpp"
#include <cassert>
#include <sstream>

int main(){
    auto pl1 = Polyline{};
    assert(pl1 == false);
    {
        auto os = std::ostringstream{};
        os << pl1;
        assert(os.str() == "[owned]");
    }
    pl1 += {1,2}; // "write"
    assert(pl1 == true);
    {
        auto os = std::ostringstream{};
        os << pl1;
        assert(os.str() == "[owned:{1,2}]");
    }
    auto pl2 = pl1; // copy construction
    assert(pl1 == true);
    assert(pl2 == true);
    {
        auto os1 = std::ostringstream{};
        os1 << pl1;
        assert(os1.str() == "[owned:{1,2}]");
        auto os2 = std::ostringstream{};
        os2 << pl2;
        assert(os2.str() == "[shared:{1,2}]");
    }
    pl2 += {3,4}; // "write"
    assert(pl1 == true);
    assert(pl2 == true);
    {
        auto os1 = std::ostringstream{};
        os1 << pl1;
        assert(os1.str() == "[owned:{1,2}]");
        auto os2 = std::ostringstream{};
        os2 << pl2;
        assert(os2.str() == "[owned:{1,2},{3,4}]");
    }
    pl1 = pl2; // copy assignment
    assert(pl1 == true);
    assert(pl2 == true);
    {
        auto os1 = std::ostringstream{};
        os1 << pl1;
        assert(os1.str() == "[shared:{1,2},{3,4}]");
        auto os2 = std::ostringstream{};
        os2 << pl2;
        assert(os2.str() == "[owned:{1,2},{3,4}]");
    }
    pl1 += {5,6}; // "write"
    assert(pl1 == true);
    assert(pl2 == true);
    {
        auto os1 = std::ostringstream{};
        os1 << pl1;
        assert(os1.str() == "[owned:{1,2},{3,4},{5,6}]");
        auto os2 = std::ostringstream{};
        os2 << pl2;
        assert(os2.str() == "[owned:{1,2},{3,4}]");
    }
    pl2 = std::move(pl1); // move assignment
    assert(pl1 == true); // ambiguous: depends on the implementation
    assert(pl2 == true);
    {
        auto os1 = std::ostringstream{};
        os1 << pl1;
        assert(os1.str() == "[owned:{1,2},{3,4}]"); // ambiguous
        auto os2 = std::ostringstream{};
        os2 << pl2;
        assert(os2.str() == "[owned:{1,2},{3,4},{5,6}]");
    }
}