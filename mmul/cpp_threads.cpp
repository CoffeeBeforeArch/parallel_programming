// This program computes matrix multiplication using C++11 threads
// By: Nick from CoffeeBeforeArch

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <thread>
#include <functional>

using std::ref;
using std::generate;
using std::vector;
using std::thread;
using std::min;

// Baseline matrix multiplication kernel
void matrixMul(vector<int> &a, vector<int> &b, vector<int> &c, int N, int tid) {
  // Calculate the starting row
  const int rows = N / 4;
  const int start = rows * tid;
  const int end = min(start + rows, N);
  
  // For each row...
  for(int row = start; row < end; row++) {
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
  thread t_a( [&](){ generate(begin(a), end(a), [](){ return rand() % 100; }); });
  thread t_b( [&](){ generate(begin(b), end(b), [](){ return rand() % 100; }); });
  t_a.join();
  t_b.join();

  // Set the number of threads to generate
  constexpr int n_threads = 4;

  // Launch threads
  thread t0(matrixMul, ref(a), ref(b), ref(c), ref(N), 0);
  thread t1(matrixMul, ref(a), ref(b), ref(c), ref(N), 1);
  thread t2(matrixMul, ref(a), ref(b), ref(c), ref(N), 2);
  thread t3(matrixMul, ref(a), ref(b), ref(c), ref(N), 3);

  // Join the threads
  t0.join();
  t1.join();
  t2.join();
  t3.join();

  return 0;
}
