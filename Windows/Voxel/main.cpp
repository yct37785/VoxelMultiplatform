#include "OSEngine.h"

int main()
{

	OSEngine::instance()->Init();
	OSEngine::instance()->Run();

	// delete all instances
	delete OSEngine::instance();

	// display memory leak report (on program termination)
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
}