// This program prints from multiple threads using C++11
// By: Nick from CoffeeBeforeArch

#include <iostream>
#include <thread>
#include <mutex>

// Our lock at global scope
std::mutex my_mutex;

// This function is the entrypoint for our threads
void print_func(int id) {
  // Lock guard that follows the RAII design pattern
  std::lock_guard<std::mutex> g(my_mutex);
  std::cout << "Printing from threads: " << id << '\n';
}

int main() {
  // Create 4 threads that all call the print function
  std::thread t0(print_func, 0);
  std::thread t1(print_func, 1);
  std::thread t2(print_func, 2);
  std::thread t3(print_func, 3);

  // Wait for the threads to finish
  t0.join();
  t1.join();
  t2.join();
  t3.join();

  return 0;
}
