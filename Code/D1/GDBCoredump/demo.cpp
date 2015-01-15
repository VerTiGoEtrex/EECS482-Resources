#include <iostream>
using namespace std;

void doStuffs() {
	for (size_t i = 0; i < 15000; ++i) {
		int x = 0;
		int y = 1;
		int z = 2;
	}
}

void loopForever() {
	while (true) {
		doStuffs();
	}
}

int main() {
	loopForever();
	return 0;
}