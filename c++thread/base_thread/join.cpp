#include <thread>
#include <iostream>

/*特殊情况下的等待：
 * 在异常；处理中调用join()
  */
struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator() ()
	{
		for (unsigned j = 0;j < 100;j++)
			do_somthing(i);//悬空引用
	}
};

struct func;

void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		do_somthing_in_current_thread();
	}catch(...){
		t.join();
		throw;
	}
	t.join();
}

/*资源获取初始化方式RALL确保线程在函数结束前结束
 * 提供一个类，在析构函数中使用join()*/

class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) : t(t_) {}
	~thread_guard()
	{
		if (t.joinable())
			t.join();
	}
	thread_guard(thread_guard const&)=delete;
	thread_guard& operator= (thread_guard const&)=delete;
};

struct func;

void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
}//thread_guard对象g是第一个被销毁的，这时线程在析构函数中被加入②到原始线程中。即使do_something_in_current_thread抛出一个异常，这个销毁依旧会发生。

















