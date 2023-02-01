#pragma once
#include <cstdarg>
#include <iostream>
#ifdef PLATFORM_WINDOWS
#include "../../../Windows/Voxel/ctpl_stl.h"
#endif

/******************************************************************************
* Platform unified API for multi-threading
******************************************************************************/
#define p_ThreadPool ThreadPoolBase::getInstance()
class ThreadPoolBase
{
	static std::unique_ptr<ThreadPoolBase> instance;

	// platform specific multi-thread helpers
#ifdef PLATFORM_WINDOWS
	std::unique_ptr<ctpl::thread_pool> p;
	std::vector<std::future<void>> futures;
#endif

public:
	static std::unique_ptr<ThreadPoolBase>& getInstance();

	void Init();
	void WaitAll();

	// template functions
	template<typename F, typename... Rest>
	void RunJob(F&& f, Rest&&... rest)
	{
#ifdef PLATFORM_WINDOWS
		futures.push_back(p->push(f, rest...));
#endif
	}
};
