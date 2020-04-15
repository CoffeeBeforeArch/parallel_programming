// This program shows off the basics of atomics in C++
// By: Nick from CoffeeBeforeArch

#include <atomic>
#include <iostream>
#include <thread>

// A simple work function at perform an atomic increment
void work(std::atomic<int> &data) {
  for (int i = 0; i < 100000; i++) data++;
}

int main() {
  // Create an atomic integer at set it equal to 0
  std::atomic<int> data;
  data = 0;

  // Launch 4 threads that all call the work function
  std::thread t0([&data]() { work(data); });
  std::thread t1([&data]() { work(data); });
  std::thread t2([&data]() { work(data); });
  std::thread t3([&data]() { work(data); });

  // Join the 4 threads at the end of the program
  t0.join();
  t1.join();
  t2.join();
  t3.join();

  // Print out the final result
  std::cout << "Final value for data is: " << data << '\n';

  return 0;
}
