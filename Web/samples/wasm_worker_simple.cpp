#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/threading.h>
#include <stdio.h>

emscripten_wasm_worker_t worker_1 = 0;
emscripten_wasm_worker_t worker_2 = 0;
char stack_1[1024];
char stack_2[1024];
emscripten_lock_t lock = EMSCRIPTEN_LOCK_T_STATIC_INITIALIZER;

void run_in_worker()
{
  emscripten_lock_waitinf_acquire(&lock);
  printf("Hello from wasm worker %d!\n", emscripten_wasm_worker_self_id());
  emscripten_lock_release(&lock);
  emscripten_wasm_worker_sleep(/*nsecs=*/1500*1000000);
  emscripten_lock_waitinf_acquire(&lock);
  printf("Bye from wasm worker %d!\n", emscripten_wasm_worker_self_id());
  emscripten_lock_release(&lock);
}

int main()
{
	worker_1 = emscripten_create_wasm_worker(stack_1, sizeof(stack_1));
	worker_2 = emscripten_create_wasm_worker(stack_2, sizeof(stack_2));
	emscripten_wasm_worker_post_function_v(worker_1, run_in_worker);
	emscripten_wasm_worker_post_function_v(worker_2, run_in_worker);
}