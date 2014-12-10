#ifndef ErrorCode_H
#define ErrorCode_H

typedef enum{
	ERR_NO_ERROR,
	ERR_EXCEED_ALLOCATED_MEMORY,
    ERR_BUFFER_SIZE,
	ERR_EQUIVALENT_NODE,
    ERR_EQUIVALENT_MEMORY,
    ERR_RECORD_EXISTED,
    ERR_EMPTY_RECORD
}ErrorCode;

#endif // ErrorCode_H
