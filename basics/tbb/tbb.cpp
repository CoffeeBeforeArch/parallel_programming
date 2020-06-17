// This program shows the basics of using TBB in C++
// By: Nick from CoffeeBeforeArch

#include "tbb/parallel_invoke.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// Helper function for getting the current time for profiling
auto get_time() { return std::chrono::high_resolution_clock::now(); }

int main() {
  // Size of the vector
  constexpr int N = 1 << 20;

  // Create our two vectors
  std::vector<int> v1(N);
  std::vector<int> v2(N);

  // Create our random number generators
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0, 255);

  // Generate our random inputs
  std::generate(begin(v1), end(v1), [&]() { return dist(rng); });
  std::generate(begin(v2), end(v2), [&]() { return dist(rng); });

  // Profile parallel invoke
  auto start = get_time();
  tbb::parallel_invoke([&] { std::sort(begin(v1), end(v1)); },
                       [&] { std::sort(begin(v2), end(v2)); });
  auto finish = get_time();

  // Print out the execution time
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  std::cout << "Elapsed time = " << duration.count() << " ms\n";

  return 0;
}
