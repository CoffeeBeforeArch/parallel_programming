// This program implements a baseline version of MMul in C++
// By: Nick from CoffeeBeforeArch

#include <vector>
#include <algorithm>
#include <cstdlib>

using std::generate;
using std::vector;

// Baseline matrix multiplication kernel
void matrixMul(vector<int> &a, vector<int> &b, vector<int> &c, int N) {
  // For each row...
  for(int row = 0; row < N; row++) {
    // For each col...
    for(int col = 0; col < N; col++) {
      // For each element in the row-col pair..
      int tmp = 0;
      for(int i = 0; i < N; i++) {
        // Accumulate partial results
        tmp += a[row * N + i] * b[i * N + col];
      }
      
      // Store the result
      c[row * N + col] = tmp;
    }
  }
}

int main() {
  // Set up the size of our matrix
  constexpr int N = 1 << 10;
  
  // Allocate space for our results
  vector<int> a(N * N);
  vector<int> b(N * N);
  vector<int> c(N * N);

  // Generate input data
  generate(begin(a), end(a), [](){ return rand() % 100; });
  generate(begin(b), end(b), [](){ return rand() % 100; });

  // Calculate MMul
  matrixMul(a, b, c, N);

  return 0;
}
