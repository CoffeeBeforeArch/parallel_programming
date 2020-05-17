// This program shows off the basics of jthreads in C++
// By: Nick from CoffeeBeforeArch

#include <iostream>
#include <thread>

int main() {
  // Now we have jthreads!
  // jthreads are a new kind of thread that automatically re-join on destruction
  std::jthread t0([]() { std::cout << "Printing from the new thread!\n"; });

  // We dont need a join here now!
  // But this is just one thing we get with jthreads!

  return 0;
}
