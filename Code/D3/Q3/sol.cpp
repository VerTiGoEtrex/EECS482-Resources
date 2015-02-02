#define LIMIT 100; /* n = 100; */
int count = 0;
mutex m;
cv waitingForFile;

getAccess(int uniqueNumber) {
  std::lock_guard<mutex> lk(m);
  while(uniqueNumber + count >= LIMIT)
    waitingForFile.wait(m);
  count += uniqueNumber;
}

releaseAccess(int uniqueNumber) {
  std::lock_guard<mutex> lk(m);
  count -= uniqueNumber;
  waitingForFile.broadcast();
}
