/*创建两个执行线程，并在thread实例之间转移所有权*/

void some_function();
void some_other_function();
std::thread t1(some_function);
std::thread t2 = std::move(t1);
t1 = std::thread(some_other_funtion);//临时对象移动操作会隐式调用
std::thread t3;
t3 = std::move(t2);
t1 = std::move(t3);//复制操作将使程序崩溃，t1已经与一个线程相关联

/*函数返回thread对象*/
std::thread f()
{
	void some_function();
	return std::thread(some_function);
}

std::thread g()
{
	void some_other_function();
	std::thread t(some_other_function);
	return t;
}

/*所有权在函数内部传递*/
void f(std::thread t);
void g()
{
	void some_function();
	f(std::thread(some_function));
	std::thread t(some_function);
	f(std::move(t));
}












