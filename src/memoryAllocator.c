#include <stdio.h>
#include <stdlib.h>
#include "memoryAllocator.h"

/**
  The functions below act as the mocking purpose
  for malloc and free function
**/
  
void *allocateMemory(unsigned int size){
    void *memory = malloc(size);
}

void freeMemory(void *memory){
    free(memory);
}
