#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/threading.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <assert.h>

const int BATCH_SIZE = 3;
std::vector<emscripten_wasm_worker_t> workers;

// semaphores
emscripten_semaphore_t threadsWaiting = (emscripten_semaphore_t)12345315; // initialize with garbage
emscripten_semaphore_t threadsRunning = EMSCRIPTEN_SEMAPHORE_T_STATIC_INITIALIZER(0); // initialize with static initializer
emscripten_semaphore_t threadsCompleted = EMSCRIPTEN_SEMAPHORE_T_STATIC_INITIALIZER(0);

// for sync
volatile int32_t addr = 0;
volatile int32_t batch_complete = 0;

// resource locks
emscripten_lock_t console_log_lock = EMSCRIPTEN_LOCK_T_STATIC_INITIALIZER;

void console_log(std::string str)
{
	// lock and unlock shared resource
	emscripten_lock_waitinf_acquire(&console_log_lock);
	printf("%s\n", str.c_str());
	emscripten_lock_release(&console_log_lock);
}

void run_in_worker()
{
	// increment semaphore to mark that this thread is waiting for a signal from control thread to start
	emscripten_semaphore_release(&threadsWaiting, 1);
	
	// acquire thread run semaphore once main thread has given this thread a go signal
	emscripten_semaphore_waitinf_acquire(&threadsRunning, 1);
	
	console_log("Worker " + std::to_string(emscripten_wasm_worker_self_id()) + ": hello!");
  
	// computationally expensive task
	emscripten_wasm_worker_sleep(/*nsecs=*/1500*1000000);
	
	console_log("Worker " + std::to_string(emscripten_wasm_worker_self_id()) + ": byee!");
	
	// increment semaphore to signal that this thread has finished
    emscripten_semaphore_release(&threadsCompleted, 1);
}

void control_thread()
{
	// wait for BATCH_SIZE threads to be ready
	console_log("Control: waiting for " + std::to_string(BATCH_SIZE) + " threads to be available");
	emscripten_semaphore_waitinf_acquire(&threadsWaiting, BATCH_SIZE);
	
	// Set the BATCH_SIZE waiting threads to run simultaneously.
	console_log("Control: release " + std::to_string(BATCH_SIZE) + " threads to run");
	emscripten_semaphore_release(&threadsRunning, BATCH_SIZE);

	// Wait until we have BATCH_SIZE threads completed their run.
	emscripten_semaphore_waitinf_acquire(&threadsCompleted, BATCH_SIZE);
	console_log("Control: all " + std::to_string(BATCH_SIZE) + " threads have completed");
	
	// notify main thread
	emscripten_wasm_notify((int32_t*)&addr, 1);
}

void load_batch()
{
	// init control thread
	emscripten_semaphore_init(&threadsWaiting, 0);
	emscripten_wasm_worker_t control_worker = emscripten_malloc_wasm_worker(1024);
    emscripten_wasm_worker_post_function_v(control_worker, control_thread);
	
	// run workers
	for (int i = 0; i < workers.size(); ++i)
		emscripten_wasm_worker_post_function_v(workers[i], run_in_worker);
}

void asyncWaitFinishedShouldBeOk(int32_t *ptr, uint32_t val, ATOMICS_WAIT_RESULT_T waitResult, void *userData)
{
	console_log("Main: asyncWaitFinished");
	// do your game logic here
	
	// start new batch
	load_batch();
}

void game_loop()
{
	ATOMICS_WAIT_TOKEN_T ret = emscripten_atomic_wait_async((int32_t*)&addr, 1, asyncWaitFinishedShouldBeOk, (void*)42, EMSCRIPTEN_WAIT_ASYNC_INFINITY);
}

int main()
{
	// init some workers
	for (int i = 0; i < BATCH_SIZE; ++i)
		workers.push_back(emscripten_malloc_wasm_worker(1024));
	
	// init
	addr = 1;
	
	// start new batch
	load_batch();
	
	// game loop
	emscripten_set_main_loop(game_loop, 0, true);
}