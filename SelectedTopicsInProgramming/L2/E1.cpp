#include <iostream>
#include <cfloat>

int main(){
    std::cout <<
    sizeof(bool)    << " bool, max\n" <<
    sizeof(char)    << " char" << CHAR_MAX << "\n" <<
    sizeof(double)  << " double" << DBL_MAX << "\n"<<
    sizeof(float)   << " float"  << FLT_MAX << "\n"<<
    sizeof(long)    << " long" << LONG_MAX << "\n"
    ;
}