#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stdio.h>

typedef struct block {
    size_t size;
    char* pointer_to_start;
} block_t;

void heap_insert(block_t* new_chunk);
// * add a chunk back (on free)
// `create the chunk_on_heap; heap_insert()`

void* my_malloc(size_t size);

block_t* split(block_t* chunk, size_t size);
// try to find this size or bigger;
// if found a chunk: cut it into two (actual size, and leftover)
//      return the actual size
//      heap_insert(leftover)
// if no find:
//      get more memory from system (sbrk)
//      split that, add the rest to heap

void my_free(void* ptr);

// USE array for now

// * MINheap based on size of chunk -- sorted from smallest to largest
// * small chunks are more frequently requested
// * what do we do when the heap is empty?
// sbrk()
// * what do we do when the user requests a larger thing than is in the heap?
// sbrk()
// ## sbrk()
// * Ask linux for a HUGE chunk of memory




#endif // MY_MALLOC_H
