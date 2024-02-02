#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std::chrono;
using namespace std;

void swap_ends(int arr[], int size) {
    for (int i = size/2 - 1, j = size - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_ends2(vector<int>& arr) { // overloading the same fn-name
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_ends3(int arr[], int dest1[]) {
    std::memcpy(dest1, arr, sizeof dest1);
}

void swap_ends4(int arr[], int dest2[]) {
    std::memcpy(dest2, arr, sizeof dest2);
}

void do_work(){
    constexpr int size2 = 10'000'000;    // use static memory instead of stack, since it cannot be contained
    static int arr[size2];                      // in stack (without static keyword usage)
    static vector<int> vec(size2);

    static int dest1[size2];
    int dest2[size2];

    //swap_ends(arr, size2); // running time: 140.469ms
    //swap_ends2(vec); // running time: 138.877ms
    //swap_ends3(arr, dest1); //
    swap_ends4(arr, dest2);

}

int main(){
    // do some warm up work here
    auto t0 = high_resolution_clock::now();
    do_work();
    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1-t0).count() << "ms\n";
}
