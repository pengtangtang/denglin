/*量产线程，等待它们结束*/

void do_work(unsigned id);

void f()
{
	std::vector<std::thread> threads;
	for (unsigned i = 0;i < 20;i++)
		threads.push_back(std::thread(do_work,i));
	std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));//对每个线程调用join(), 然后使用mem_fun来取指针并绑定到thread的成员
}
