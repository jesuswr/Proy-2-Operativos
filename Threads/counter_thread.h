
#ifndef _COUNTER_THREAD_
#define _COUNTER_THREAD_

typedef struct {
	int n, MOD;
	char ** file;
} INPUT;

typedef struct {
	char * w;
	int c;
} pair_2;

typedef struct {
	pair_2 * cnt;
	int size;
} RET;

void counter_thread(void * input);

#endif