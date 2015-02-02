class Barrier {
  private:
    //Add your private member variables
    int numThreads;
    int count;
    bool cycle;
    mutex state;
    cv notSerial;

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
  count = 0;
  cycle = false;
}

bool Barrier::wait() {
  lock_guard<Mutex> lk(state);
  bool ourCycle = cycle;
  if (++count != numThreads){
    while (cycle == ourCycle)
      notSerial.wait(state);
    return false;
  } else {
    count = 0;
    cycle = !cycle;
    notSerial.broadcast();
    return true;
  }
}
