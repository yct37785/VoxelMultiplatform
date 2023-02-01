#include "OSEngine.h"
#include "ctpl_stl.h"

void first(int id, int jobid, const int delayms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
	std::cout << "Job #" << jobid << " completed" << std::endl;
}

int main()
{
	const int TOTAL_THREADS = std::thread::hardware_concurrency();
	std::cout << "TOTAL_THREADS: " << TOTAL_THREADS << std::endl;
	const int TOTAL_JOBS = 4;
	ctpl::thread_pool p(TOTAL_THREADS);
	std::vector<std::future<void>> results(4);
	for (int i = 0; i < 8; ++i) {
		// add jobs
		for (int j = 0; j < TOTAL_JOBS; ++j) {
			results[j] = p.push(first, j + 1, (j + 1) * 1000);
		}
		for (int j = 0; j < TOTAL_JOBS; ++j) {
			results[j].get();
		}
		std::cout << "All jobs completed --" << std::endl;
	}

	//OSEngine::instance()->Init();
	//OSEngine::instance()->Run();

	//// delete all instances
	//delete OSEngine::instance();

	// display memory leak report (on program termination)
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
}