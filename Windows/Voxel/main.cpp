#include "OSEngine.h"

int main()
{
	OSEngine::instance()->Init();
	OSEngine::instance()->Run();

	// delete all instances
	delete OSEngine::instance();

	// display memory leak report
	_CrtDumpMemoryLeaks();
}