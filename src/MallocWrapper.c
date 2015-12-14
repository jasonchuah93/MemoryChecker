#include <malloc.h>
#include "MallocWrapper.h"

char *_malloc(int size){
	return malloc(size);
}

void _free(void *ptr){
	free(ptr);
}
