mutex bathroom_lock;
cv men, women;
int active_men = 0;
int active_women = 0;

//1st try: unfair, starvation
void woman_wants_to_enter() {
  std::lock_guard<mutex> lk(bathroom_lock);
  while (active_men) {
    women.wait(bathroom_lock);
  }
  active_women++;
}

woman_leaves() {
  std::lock_guard<mutex> lk(bathroom_lock);
  active_women--;
  if (active_women == 0) {
    men.broadcast();
  }
}

//man_wants_to_enter(), man_leaves() are same with men/women reversed

