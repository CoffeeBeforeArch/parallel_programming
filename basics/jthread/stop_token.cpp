// This program shows off the basics of stop tokens in C++20
// By: Nick from CoffeeBeforeArch

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono;

int main() {
  // Let's create a jthread an pass it a stop token
  std::jthread jt0([](std::stop_token tk) {
    // Print in a loop
    for (int i = 0; i < 10; i++) {
      std::cout << "Printing value: " << i << '\n';

      // Stop, if that has been requested
      if (tk.stop_requested()) {
        std::cout << "Stopping the jthread!\n";
        return;
      }

      // Sleep so this doesn't go too quickly
      std::this_thread::sleep_for(seconds(1));
    }
  });

  // Pause the main thread before cancelling the jthread
  std::this_thread::sleep_for(seconds(5));

  // Request for our jthread to stop
  jt0.request_stop();

  return 0;
}
