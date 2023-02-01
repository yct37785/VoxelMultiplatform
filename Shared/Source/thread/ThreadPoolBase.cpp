#include "ThreadPoolBase.h"
std::unique_ptr<ThreadPoolBase> ThreadPoolBase::instance;

std::unique_ptr<ThreadPoolBase>& ThreadPoolBase::getInstance()
{
	if (instance == nullptr)
	{
		instance = std::make_unique<ThreadPoolBase>();
	}
	return instance;
}

void ThreadPoolBase::Init()
{
#ifdef PLATFORM_WINDOWS
	int win_total_threads = std::thread::hardware_concurrency();
	p = std::make_unique<ctpl::thread_pool>(win_total_threads);
#endif
}

void ThreadPoolBase::WaitAll()
{
#ifdef PLATFORM_WINDOWS
	for (int i = 0; i < futures.size(); ++i) {
		futures[i].get();
	}
	futures.clear();
	std::cout << "All jobs completed --" << std::endl;
#endif
}