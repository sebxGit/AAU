#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memcpy
#include <array>

auto func(std::array<int, 10> arr){
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    return arr;
}

int main(){
    std::array<int, 10> arr1 {1,2,3,5,7,2,3,1,2,3};
    arr1 = func(arr1);
    for (int i = arr1.size() - 1; i >= 0; i--)
        std::cout << arr1[i];
}
