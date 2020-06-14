#include "tbb/task_group.h"
#include "benchmark/benchmark.h"

int fib(int n) {
  if (n <= 1) return n;
  return fib(n - 1) + fib(n - 2);
}

int fib_tbb(int n) {
  if (n <= 1) return n;
  int x;
  int y;
  tbb::task_group g;
  g.run([&]() { x = fib_tbb(n - 1); });
  g.run([&]() { y = fib_tbb(n - 2); });
  g.wait();
  return x + y;
}

// Baseline Benchmark
static void base_fib(benchmark::State &s) {
  int *sink = new int;
  for(auto _ : s) {
    *sink = fib(s.range(0));
  }
  delete sink;
}
BENCHMARK(base_fib)->Arg(25);

// Baseline Benchmark
static void tbb_fib(benchmark::State &s) {
  int *sink = new int;
  for(auto _ : s) {
    *sink = fib_tbb(s.range(0));
  }
  delete sink;
}
BENCHMARK(tbb_fib)->Arg(25);

BENCHMARK_MAIN();

