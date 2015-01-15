#include <iostream>
using namespace std;

void bestFunction(int *awesomeptr) {
	*awesomeptr = 1337;
}

int main() {
	int hello = 1903;
	cout << hello << endl;
	int *ptr = 0xdeadbeef;
	bestFunction(ptr);
	cout << "[*ptr] => " << *ptr << endl;
	cout << "[hello] => " << hello << endl;
	return 0;
}