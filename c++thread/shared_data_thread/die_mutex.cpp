//std::lock---可以一次性锁住多个互斥量
//交换操作中使用std::lock  std::lock_guard()

class some_big_object;

void swap(some_big_object& lhs,some_big_object& rhs);

class x
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	x(some_big_object const& sd) : some_detail(sd) {}

	friend void swap(x& lhs,x& rhs)
	{
		if (&lhs == &rhs)
			return ;
		//调用std::lock()①锁住两个互斥量，并且两个std:lock_guard实例已经创建好②③。提供std::adopt_lock参数除了表示std::lock_guard对象可获取锁之外，还将锁交由std::lock_guard对象管理，而不需要std::lock_guard对象再去构建新的锁。
		std::lock(ljs.m,rhs.m);
		//当std::lock成功的获取一个互斥量上的锁，并且当其尝试从另一个互斥量上再获取锁时，就会有异常抛出，第一个锁也会随着异常的产生而自动释放，所以std::lock要么将两个锁都锁住，要不一个都不锁。虽然std::lock可以在这情况下(获取两个以上的锁)避免死锁，但它没办法帮助你获取其中一个锁。
		std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock);
		std::lock_guard<std::mutex> lock_a(rhs.m,std::adopt_lock);
		swap(lhs.some_detail,rhs.some_detail);
	}
};
