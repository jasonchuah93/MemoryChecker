#ifndef safeMalloc_H
#define safeMalloc_H

typedef struct Record Record;

struct Record{
    unsigned int size;
    int lineNumber;
    char *filename;
};
    

void _safeMalloc(unsigned int size,int lineNumber, char *filename);
void *safeMalloc(unsigned int size,int lineNumber, char *filename);

#endif // safeMalloc_H
