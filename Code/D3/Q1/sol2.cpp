mutex bathroom_lock;
cv men, women;
int active_men = 0, waiting_men = 0;
int active_women = 0, waiting_women = 0;
bool turn = WOMEN; /* init to either MEN or WOMEN */

//better try: no starvation, fair
woman_wants_to_enter() {
  std::lock_guard<mutex> lk(bathroom_lock);
  while (active_men || (waiting_men && (turn == MEN))) {
    waiting_women++;
    women.wait(bathroom_lock);
    waiting_women--;
  }
  active_women++;
}

woman_leaves() {
  std::lock_guard<mutex> lk(bathroom_lock);
  active_women--;
  if (active_women == 0) {
    men.broadcast();
  }
  turn = MEN;
}
