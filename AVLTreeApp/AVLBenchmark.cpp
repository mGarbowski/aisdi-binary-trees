#include <chrono>
#include <random>
#include <map>
#include "../benchmark/benchmark.h"
#include "../AVLTreeLib/AVLTree.h"

int main() {
    std::vector<int> sampleSizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

    std::map<int, size_t> creationTimeNanos;
    std::map<int, size_t> searchTimeNanos;

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator((unsigned long) seed);
    std::vector<unsigned long> randomNumbers;
    for (size_t i = 0; i < sampleSizes[sampleSizes.size() - 1]; i++) {
        randomNumbers.push_back(generator());
    }

    // Tree creation (multiple insertion) benchmark
    for (auto sampleSize : sampleSizes) {
        Benchmark<std::chrono::nanoseconds> timer;

        auto tree = AVLTree<unsigned long, unsigned long>();
        for (size_t idx = 0; idx < sampleSize; idx++) {
            auto number = randomNumbers[idx];
            tree.insert(number, number);
        }
        auto timeNanos = timer.elapsed();
        creationTimeNanos[sampleSize] = timeNanos;
    }

    // Tree search benchmark
    auto tree = AVLTree<unsigned long, unsigned long>();
    for (auto number : randomNumbers) {
        tree.insert(number, number);
    }

    for (auto sampleSize : sampleSizes) {
        Benchmark<std::chrono::nanoseconds> timer;

        for (size_t idx = 0; idx < sampleSize; idx++) {
            tree.find(randomNumbers[idx]);
        }

        auto timeNanos = timer.elapsed();
        searchTimeNanos[sampleSize] = timeNanos;
    }

    std::cout << "Creation time benchmark\nSize\ttime (ns)\n";
    std::map<int, size_t>::iterator it;
    for (it = creationTimeNanos.begin(); it != creationTimeNanos.end(); it++) {
        auto pair = *it;
        std::cout << pair.first << "\t" << pair.second << std::endl;

    }

    std::cout << "Search time benchmark\nSize\ttime (ns)\n";
    for (it = searchTimeNanos.begin(); it != searchTimeNanos.end(); it++) {
        auto pair = *it;
        std::cout << pair.first << "\t" << pair.second << std::endl;

    }
    return 0;
}