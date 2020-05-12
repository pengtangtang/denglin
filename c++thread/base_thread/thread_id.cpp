//1:std::thread对象的成员函数get_id()
//2:在线程中调用std::this_thread::get_id()

std::thread::id master_thread;

//检查拥有的线程id是否与初始线程id相同
void some_core_part_of_algorithm()
{
	if (std::this_thread::get_id() == master_thread)
		do_master_thread_work();
	do_common_work();
	std::cout << std::this_thread::get_id();
}
