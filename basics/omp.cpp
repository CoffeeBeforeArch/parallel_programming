// This program is a basic OpenMP example with C++
// By: Nick from CoffeeBeforeArch

#include <iostream>
#include <omp.h>

int main() {
// We can let the compiler do the work for us using OpenMP
#pragma omp parallel
  // All code in this region executes with the default number of threads
  {
#pragma omp critical
    // All code in this region executes for 1 thread at a time
    {
      std::cout << "Printing from thread: " << omp_get_thread_num() << '\n';
    }
  }

  return 0;
}
