#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std::chrono;
using namespace std;

constexpr int ARR_SIZE = 10'000'000;


void swap_ends(int arr[], int size) {
    for (int i = size/2 - 1, j = size - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_ends2(vector<int>& arr) { // overloading the same fn-name
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void memcpy_int_swap(int* arr, int* buff, int size)
{
    auto bytes_copied = size/2 * sizeof(int);

    std::memcpy(buff, arr, bytes_copied);
    std::memcpy(arr, arr + (size+1)/2, bytes_copied);     // (size+1)/2 leaves alone the middle element if size is odd
    std::memcpy(arr + (size+1)/2, buff, bytes_copied);
}

void swap_ends_mem_static(int arr[], int size)
{
    static int buff[ARR_SIZE/2];
    if (size > ARR_SIZE)
        throw std::range_error("swap_ends_mem_static: Size is too large for the static buffer");
    memcpy_int_swap(arr, buff, size);
}

void swap_ends_mem_dynamic(int arr[], int size)
{
    auto buff = new int[size/2];
    memcpy_int_swap(arr, buff, size);
    delete [] buff;
}

int main(){
    constexpr int size2 = 10'000'000;    // use static memory instead of stack, since it cannot be contained
    static int arr[size2];                      // in stack (without static keyword usage)
    static vector<int> vec(size2);

    std::cout << "running!\n";

    auto t0 = high_resolution_clock::now();
    swap_ends(arr, size2);
    auto t1 = high_resolution_clock::now();
    swap_ends2(vec);
    auto t2 = high_resolution_clock::now();
    swap_ends_mem_static(arr, size2);
    auto t3 = high_resolution_clock::now();
    swap_ends_mem_dynamic(arr, size2);
    auto t4 = high_resolution_clock::now();

    std::cout << "swap_ends: " << duration<double, std::milli>(t1-t0).count() << "ms\n";
    std::cout << "swap_ends2: " << duration<double, std::milli>(t2-t1).count() << "ms\n";
    std::cout << "swap_ends_mem_static: " << duration<double, std::milli>(t3-t2).count() << "ms\n";
    std::cout << "swap_ends_mem_dynamic: " << duration<double, std::milli>(t4-t3).count() << "ms\n";
}
