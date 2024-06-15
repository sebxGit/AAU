#include <iostream>
#include <random>
#include "E4.cpp"

void lehman_rand_number_generator() {
    std::vector<int> histogram(100, 0);
    unsigned int seed = 1729;
    for(int i = 0; i < 1000000; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;
        histogram[seed % 100]++;
    }
    for(int i = 0; i < 100; i++) {
        std::cout << i * 10 << " - " << (i + 1) * 10 << ": " << std::string(histogram[i] / 1000, '*') << std::endl;
    }
}

int main() {
    benchmark_util b;
    b.start("Using std::mt19937 and std::uniform_real_distribution");
    std::mt19937 mt(1729);
    std::uniform_real_distribution<double> dist(0, 1000);
    for(int i = 0; i < 10'000'000; i++) {
        dist(mt);
    }
    b.stop("Using std::mt19937 and std::uniform_real_distribution");
    b.start("lehman_rand_number_generator");
    lehman_rand_number_generator();
    b.stop("lehman_rand_number_generator");
    b.report();
    std::vector<int> histogram(100, 0);
    for(int i = 0; i < 1000000; i++) {
        double number = dist(mt);
        histogram[static_cast<int>(number / 10)]++;
    }
    for(int i = 0; i < 100; i++) {
        std::cout << i * 10 << " - " << (i + 1) * 10 << ": " << std::string(histogram[i] / 1000, '*') << std::endl;
    }

    return 0;
}