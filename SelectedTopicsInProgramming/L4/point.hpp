#ifndef SELECTEDTOPICSINPROGRAMMING_POINT_HPP
#define SELECTEDTOPICSINPROGRAMMING_POINT_HPP

#include <iostream>

/// Represents 2D point
struct Point
{
    // public: by default in struct
    int x; ///< x coordinate
    int y; ///< y coordinate
};

/// forward declaration of output operator for printing:
std::ostream& operator<<(std::ostream&, const Point&);


#endif //SELECTEDTOPICSINPROGRAMMING_POINT_HPP
