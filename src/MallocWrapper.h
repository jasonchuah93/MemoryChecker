#ifndef TEST
#include <malloc.h>

#define _malloc(x) malloc(x)
#define _free(x) free(x)

#else 
	char *_malloc(int size);
	void _free(void* ptr);
	
#endif //TEST