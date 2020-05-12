template<typename Iterator,typename T>
struct accumulate_block
{
	void operator()(Iterator first,Iterator last,T& result)
	{
		result = std::accumulate(first,last,result);
	}
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{
	unsigned long const length = std::distance(first,last);
	if (!length)
		return init;

	unsigned long const min_per_thread = 25;

	//确定启动线程的最大数量    22
	unsigned long const max_threads = 
		(length+min_per_thread-1)/min_per_thread;

	//硬件支持线程数
	unsigned long const hardware_threads = 
		std::thread::haredware_concurrency();

	//33
	unsigned long const num_threads = 
		std::min(hardware_threads != 0 ? hardware_threads : 2,max_thread);
	
	//44每个线程中处理的元素数量
	unsigned long const block_size = length / num_threads;

	std::vetor<T> results(num_threads);
	//55
	std::vector<std::thread> threads(num_threads-1);

	Iterator block_start = first;
	for (unsigned long i = 0;i < (num_threads-1);i++)
	{
		Iterator block_end = block_start;
		//66
		std::advance(block_end,block_size);
		//77启动新线程为当前块的累加结果
		threads[i] = std::thread(
				accumulate_block<Iterator,T>(),
				block_start,block_end,std::ref(results[i]));
		//88启动下一个快
		block_start = block_end;
	}

	//99启动所有线程后，处理最终快的结果
	accumulate_block<Iterator,T>() (
		block_start,last,results[num_threads-1]);

	//10等待所有线程创建完成
	std::for_each(threads.begin(),threads.end(),
			std::mem_fn(&std::thread::join));
	//111将所有结果进行累加
	return std::accumulate(results.begin(),results.end(),init);
	}
	




