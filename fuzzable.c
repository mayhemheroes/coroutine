#include "coroutine.h"
#include <stdio.h>
#include <stdlib.h>

struct args {
	int n;
};

static void
foo(struct schedule * S, void *ud) {
	struct args * arg = ud;
	int start = arg->n;
	int i;
	for (i=0;i<5;i++) {
		coroutine_yield(S);
	}
}

int LLVMFuzzerTestOneInput(char * data, size_t size)
{
	struct schedule * S = coroutine_open();
	struct args arg1 = { 0 };
	struct args arg2 = { 100 };
	if(size >= 2*sizeof(struct args))
	{
		arg1.n = *((int *) data);
		arg2.n = *((int *) data + 1);
	}
	int co1 = coroutine_new(S, foo, &arg1);
	int co2 = coroutine_new(S, foo, &arg2);
	while (coroutine_status(S,co1) && coroutine_status(S,co2)) {
		coroutine_resume(S,co1);
		coroutine_resume(S,co2);
	} 
	coroutine_close(S);
	return 0;
}
