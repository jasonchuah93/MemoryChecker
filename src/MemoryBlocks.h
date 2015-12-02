#ifndef MemoryBlocks_H
#define MemoryBlocks_H

//The memory blocks below act as the memory addr to 
//use for testing purpose
typedef struct MemoryBlocks MemoryBlocks;
struct MemoryBlocks{
	//Block 1
	char header1[50];
	char memory1[100];
	char footer1[50];
	//Block 2
	char header2[50];
	char memory2[200];
	char footer2[50];
	//Block 3
	char header3[50];
	char memory3[300];
	char footer3[50];
	//Block 4
	char header4[50];
	char memory4[400];
	char footer4[50];
	//Block 5
	char header5[50];
	char memory5[500];
	char footer5[50];
	//Block 6
	char header6[50];
	char memory6[600];
	char footer6[50];
	//Block 7
	char header7[50];
	char memory7[700];
	char footer7[50];
	//Block 8
	char header8[50];
	char memory8[800];
	char footer8[50];
	//Block 9
	char header9[50];
	char memory9[900];
	char footer9[50];
	//Block 10
	char header10[50];
	char memory10[1000];
	char footer10[50];
};
#endif // MemoryBlocks_H