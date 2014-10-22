#ifndef safeMalloc_H
#define safeMalloc_H

void _safeMalloc(unsigned int size,int lineNumber, char *filename);
void *safeMalloc(unsigned int size,int lineNumber, char *filename);

#endif // safeMalloc_H
