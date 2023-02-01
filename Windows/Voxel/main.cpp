#include "OSEngine.h"
#include "ctpl_stl.h"

void first(int id, int jobid, const int delayms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
	std::cout << "Job #" << jobid << " completed" << std::endl;
}

int main()
{
	int TOTAL_JOBS = 4;
	p_ThreadPool->Init();
	for (int i = 0; i < 8; ++i) {
		// add jobs
		for (int j = 0; j < TOTAL_JOBS; ++j) {
			p_ThreadPool->RunJob(first, j + 1, (j + 1) * 1000);
		}
		// wait
		p_ThreadPool->WaitAll();
	}

	//OSEngine::instance()->Init();
	//OSEngine::instance()->Run();

	//// delete all instances
	//delete OSEngine::instance();

	// display memory leak report (on program termination)
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
}