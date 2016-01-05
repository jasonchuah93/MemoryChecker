#ifndef MemoryBlocks_H
#define MemoryBlocks_H

//Define the Memory Size for the allocator use.
#define HEADER_SIZE 	50
#define FOOTER_SIZE 	HEADER_SIZE

//The memory blocks below act as the memory addr to 
//use for testing purpose
typedef struct MemoryBlock1 MemoryBlock1;
struct MemoryBlock1{
	//Block 1
	char header[HEADER_SIZE];
	char memory[100];
    char footer[FOOTER_SIZE];
};	

typedef struct MemoryBlock2 MemoryBlock2;
struct MemoryBlock2{
	//Block 2
	char header[HEADER_SIZE];
	char memory[200];
    char footer[FOOTER_SIZE];
};	

typedef struct MemoryBlock3 MemoryBlock3;
struct MemoryBlock3{
	//Block 3
	char header[HEADER_SIZE];
	char memory[300];
    char footer[FOOTER_SIZE];
};	

typedef struct MemoryBlock4 MemoryBlock4;
struct MemoryBlock4{
	//Block 4
	char header[HEADER_SIZE];
	char memory[400];
    char footer[FOOTER_SIZE];
};

typedef struct MemoryBlock5 MemoryBlock5;
struct MemoryBlock5{
	//Block 5
	char header[HEADER_SIZE];
	char memory[500];
    char footer[FOOTER_SIZE];
};		

typedef struct MemoryBlock6 MemoryBlock6;
struct MemoryBlock6{
	//Block 6
	char header[HEADER_SIZE];
	char memory[600];
    char footer[FOOTER_SIZE];
};		   

typedef struct MemoryBlock7 MemoryBlock7;
struct MemoryBlock7{
	//Block 7
	char header[HEADER_SIZE];
	char memory[700];
    char footer[FOOTER_SIZE];
};

typedef struct MemoryBlock8 MemoryBlock8;
struct MemoryBlock8{
	//Block 8
	char header[HEADER_SIZE];
	char memory[800];
    char footer[FOOTER_SIZE];
};

#endif // MemoryBlocks_H