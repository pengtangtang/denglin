#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int sum = 0;
mutex m;

void* countgold() {
	int i;
	for (i = 0;i < 10;i++) {
		m.lock();
		sum += i;
		m.unlock();
	}
	return NULL;
}

int main()
{
	thread t1(countgold);
	thread t2(countgold);

	t1.join();
	t1.join();

	cout << "sum = " << sum << endl;
	return 0;
}
