class Barrier {
  private:
    //Add your private member variables
    int numThreads;
    int in;
    int out;
    mutex state;
    cv in_cv;
    cv out_cv;

  public:
    /* Constructs a new barrier that will allow number_of_threads
       threads to check in. */
    Barrier(int number_of_threads);

    /* Called by a thread checking in to the barrier. Should return
       true if the thread was the last thread to check in (in POSIX threads
       lingo, the "serial thread") and false otherwise. This function should
       block until all threads have checked in. */
    bool wait();

    /* Delete copy constructor and copy assignment operators */
    Barrier(const Barrier&) = delete;
    Barrier& operator=(const Barrier&) = delete;
    Barrier(Barrier&&) = delete;
    Barrier& operator=(Barrier&&) = delete;
};

Barrier::Barrier(int nt) {
  numThreads = nt;
  in = 0;
  out = 0;
}

bool Barrier::wait() {
  lock_guard<Mutex> lk(state);
  // Wait for all threads to exit
  while (out || in == numThreads)
    in_cv.wait(state);

  // Check if we're last
  bool isSerial = (++in == numThreads);
  if (!isSerial){
    // We're not last, so wait
    while(in != numThreads)
      out_cv.wait(state);
  } else {
    // We're last to enter, so broadcast
    out_cv.broadcast();
  }

  // We're last to exit, so tell everyone else to enter
  if (++out == numThreads) {
    in_cv.broadcast();
    in = 0;
    out = 0;
  }

  return isSerial;
}
