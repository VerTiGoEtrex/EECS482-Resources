#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>
#include <tuple>

#include <signal.h>

using std::thread; using std::vector;
using std::tuple; using std::make_tuple; using std::tie;


static unsigned int NUM_THREADS = 2;
static const int n = 20;
static unsigned int tally = 0;

static void total()
{
    int count;
    for (count = 0; count < n; count++) {
        tally = tally + 1;
    }
}

static bool running = true;

static void handler(int signum)
{
    running = false;
}

static tuple<unsigned int, unsigned int>
run_threads_until_failure()
{
    int num_successes = 0, num_failures = 0;
    do {
        tally = 0;

        vector<thread *> threads;
        for (size_t i = 0; i < NUM_THREADS; i++) {
            threads.push_back(new thread(total));
        }
        for (thread *t : threads) {
            t->join();
            delete t;
        }
        if (tally != n * NUM_THREADS) {
            printf("\ntally = %d", tally);
            ++num_failures;
        } else {
            printf("tally = %d (%d times)\r", tally, ++num_successes);
            fflush(stdout);
        }
    } while (running && tally == n * NUM_THREADS);
    printf("\n");
    return make_tuple(num_successes, num_failures);
}

int main(int argc, char *argv[])
{
    if (argc >= 2) NUM_THREADS = atoi(argv[1]);
    if (NUM_THREADS < 0) {
        printf("%d threads?  what does that even mean?\n", NUM_THREADS);
        exit(1);
    }
    printf("%d threads at a time\n", NUM_THREADS);
    if (NUM_THREADS <= 1) {
        printf("Well this is going to be boring.\n");
    }

    signal(SIGINT, handler);
    unsigned int total_failures = 0, total_successes = 0;
    while (running) {
        unsigned int successes, failures;
        tie(successes, failures) = run_threads_until_failure();
        total_successes += successes;
        total_failures += failures;
    }

    unsigned int total = total_successes + total_failures;
    printf("Failure rate: %u out of %u (%f %%)\n",
           total_failures, total, ((double) total_failures) / total * 100.0);

    return 0;
}
