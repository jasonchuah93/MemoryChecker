#ifndef ErrorCode_H
#define ErrorCode_H

typedef enum{
	ERR_NO_ERROR,
	ERR_EXCEED_ALLOCATED_MEMORY,
    ERR_EXCEED_BUFFER_SIZE,
	ERR_EQUIVALENT_NODE,
    ERR_NODE_UNAVAILABLE,
    ERR_EQUIVALENT_RECORD,
    ERR_MEMORY_WRONG
    
}ErrorCode;

#endif // ErrorCode_H
