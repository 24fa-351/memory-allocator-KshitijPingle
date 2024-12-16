#ifndef MY_MALLOC_H
#define MY_MALLOC_H

typedef struct block {
    size_t size;
    char* pointer_to_start;
} block_t;

void heap_insert(block_t* new_chunk);

void* malloc(size_t size);

block_t* split(block_t* chunk, size_t size);

void free(void* ptr);

#endif // MY_MALLOC_H
