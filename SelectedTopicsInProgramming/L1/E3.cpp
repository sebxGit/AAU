#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string_view>

int func(std::array<int, 10> arr){
    return std::sort(arr.begin(), arr.end());
}

int main(){
    std::array<int, 10> arr {1,2,3,4,5,6,7,8,9};
    std::cout << func(arr);
}
