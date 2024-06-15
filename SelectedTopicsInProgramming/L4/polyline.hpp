#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include "point.hpp"
#include <vector>

using namespace std;

using Points = std::vector<Point>;

class Polyline {
    std::shared_ptr<Points> points = std::make_shared<Points>();
    std::unique_ptr<Points> clone() { return std::make_unique<Points>(*points); }

// Rule of Zero: uses compiler-generated default/copy/move ctors/assignments
// default ctor: uses default member initializers (see above)
// default copy: copy member by member, points are shared by shared_ptr
// default move: move member by member, points are moved by shared_ptr
public:
    Polyline&operator+=(const Point p);
    [[nodiscard]] bool is_shared() const { return points.use_count() > 1; }
    const Points* data() const { return points.get(); }
    operator bool() const { return points != nullptr && !points->empty(); }
    friend std::ostream& operator<<(std::ostream& os, const Polyline& p);
};

