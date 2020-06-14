// This program shows are the basics of using the parallel STL in C++
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

int main() {
  // Size of our vector
  const int N = 1 << 20;

  // Create our vector
  std::vector<int> v(N);

  // Set up our random number generator
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0, 255);

  // Generate our random inputs
  std::generate(begin(v), end(v), [&]() { return dist(rng); });

  // Reduce the vector in parallel and vectorized
  int result = std::reduce(std::execution::par, begin(v), end(v));

  // Print out the result
  std::cout << result << '\n';

  return 0;
}
