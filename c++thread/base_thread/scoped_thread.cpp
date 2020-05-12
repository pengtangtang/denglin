class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :
		t(std::move(t_)
	{
		if (!t.joinable())
			throw std::logic_error("no thread");
	}
	~scoped_thread()
	{
		t.join();
	}
};

struct func();

void f()
{
	int some_local_state = 0;
	scoped_thread t(std::thread(func(some_local_state)));
	do_something_in_current_thread();
}
