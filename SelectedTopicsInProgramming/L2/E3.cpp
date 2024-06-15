#include <iostream>
double max(double a, double b)
{ return a < b ? b : a; }

// with c-style call by reference parameters
double max1(double *a, double *b)
{ return *a < *b ? *b : *a; }

// with call by C++ references
double max2(double a, double b)
{
    double& a1 = a;
    double& b1 = b;
    return a < b ? b1 : a1;
}

// with C++ const references
double max3(const double &a, const double &b){
    return a < b ? b : a;
}

// with C++ pointers to references do not exist
//double max4(const double &a, const double &b){
//    return *a < *b ? *b : *a;
//}

// with references to pointers
double* max5(double* &a, double* &b){
    return *a < *b ? b : a;
}

// with const references to pointers
const double* max6(const double* &a, const double* &b){
    return *a < *b ? b : a;
}

int main(){
    double a = 1.5;
    double b = 2.5;

    double *g = &a;
    double *h = &b;
    const double *i = &a;
    const double *j = &b;

    std::cout << max(a,b) << " max\n";
    std::cout << max1(&a,&b) << " max1\n";
    std::cout << max2(a,b) << " max2\n";
    std::cout << max3(a,b) << " max3\n";
    std::cout << max5(g,h) << " max5\n";
    std::cout << max6(i,j) << " max6\n";

}