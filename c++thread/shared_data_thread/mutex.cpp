#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>
using namespace std;

list<int> some_list;
mutex some_mutex;

void add_to_list(int new_value)
{
	//C++标准库为互斥量提供了一个RAII语法的模板类std::lock_guard，其会在构造的时候提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁的互斥量总是会被正确的解锁。
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}

bool list_contauns(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(some_list.begin().some_list.end(),value_to_find) != some_list.end();
	
}

/*无意中传递了保护数据的引用*/
class some_data
{
	int a;
	std::string b;
public:
	void do_something();
};

class data_wrapper
{
	private:
		some_data data;
		std::mutex mutex m;
	public:
		template<typename Function>
		void process_data(Function func)
		{
			std::lock_guard<std::mutex> l(m);
			func(data);
		}
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}

data_wrapper x;
void foo()
{
	x.process_data(malicious_function);
	unprotected->do_somthing();
}


















