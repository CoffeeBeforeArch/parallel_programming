// This program shows the basics of using Pthreads in C++
// By: Nick from CoffeeBeforeArch

#include <pthread.h>
#include <array>
#include <cassert>
#include <iostream>

// Our mutex for each thread
// We can statically or dynamically initialize it
// Use pthread_mutex_init(...) for dynamic initialization
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Our function that serves as the entry point for the threads
// Return values and parameters are passed through void pointers
void *print_func(void *args) {
  // Cast our argument back to it's original type
  int *ID = static_cast<int *>(args);

  // Lock the mutex before printing
  pthread_mutex_lock(&lock);
  std::cout << "Printing from thread: " << *ID << '\n';
  pthread_mutex_unlock(&lock);

  // We can call pthread_exit to kill the thread
  // Pass NULL if we don't care about the status code
  pthread_exit(NULL);
}

int main() {
  // Create an array of four thread IDs and four threads
  std::array<int, 4> ids = {0, 1, 2, 3};
  std::array<pthread_t, 4> threads;

  // Create four threads with the print function as an entrypoint
  // Arguments:
  //  1.) Address of thread object
  //  2.) Thread attributes (NULL means default)
  //  3.) Entrypoint (function pointer)
  //  4.) Void pointer to arguments
  for (auto &id : ids) {
    pthread_create(&threads[id], NULL, print_func, static_cast<void *>(&id));
  }

  // Called from the main thread, this will block until the other 4 threads
  // complete
  pthread_exit(NULL);
}
