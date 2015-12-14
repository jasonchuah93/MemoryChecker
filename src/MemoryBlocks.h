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
	//Block 1
	char header[HEADER_SIZE];
	char memory[200];
    char footer[FOOTER_SIZE];
};	

    /*
	//Block 2
	char header2[HEADER_SIZE];
	char memory2[200];
	char footer2[FOOTER_SIZE];
	//Block 3
	char header3[HEADER_SIZE];
	char memory3[300];
	char footer3[FOOTER_SIZE];
	//Block 4
	char header4[HEADER_SIZE];
	char memory4[400];
	char footer4[FOOTER_SIZE];
	//Block 5
	char header5[HEADER_SIZE];
	char memory5[500];
	char footer5[FOOTER_SIZE];
	//Block 6
	char header6[HEADER_SIZE];
	char memory6[600];
	char footer6[FOOTER_SIZE];
	//Block 7
	char header7[HEADER_SIZE];
	char memory7[700];
	char footer7[FOOTER_SIZE];
	//Block 8
	char header8[HEADER_SIZE];
	char memory8[800];
	char footer8[FOOTER_SIZE];
	//Block 9
	char header9[HEADER_SIZE];
	char memory9[900];
	char footer9[FOOTER_SIZE];
	//Block 10
	char header10[HEADER_SIZE];
	char memory10[1000];
	char footer10[FOOTER_SIZE];
    */


#endif // MemoryBlocks_H