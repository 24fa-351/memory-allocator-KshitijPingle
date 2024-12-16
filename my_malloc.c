// Add a header later

#define _GNU_SOURCE    // needed for 'RTLD_NEXT'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

#include "my_malloc.h"

// Insert chunks the user does not need back into our heap
void heap_insert(block_t* new_chunk) {
    if (heap_count < MAX_CHUNKS) {
        my_heap[heap_count++] = *new_chunk;
    }
}

void* malloc(size_t size) {

    // Override malloc to use our malloc
    void* (*libc_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");

    printf("You just used my implementation of malloc\n");

    // try to find a chunk that is the right size
    for (size_t i = 0; i < heap_count; i++) {
        if (my_heap[i].size >= size) {
            block_t* chunk = &my_heap[i];
            block_t* leftover = split(chunk, size);
            if (leftover) {
                heap_insert(leftover);
            }
            return chunk->pointer_to_start;
        }
    }

    // if we don't have enough, get more memory from the system
    block_t* new_chunk = sbrk(size + sizeof(block_t));
    if (new_chunk == (void*)-1) {
        return NULL;
    }
    new_chunk->size = size;
    new_chunk->pointer_to_start = (char*)(new_chunk + 1);

    return new_chunk->pointer_to_start;
}

block_t* split(block_t* chunk, size_t size) {
    if (chunk->size <= size) {
        return NULL;
    }

    block_t* leftover = (block_t*)(chunk->pointer_to_start + size);
    leftover->size = chunk->size - size - sizeof(block_t);
    leftover->pointer_to_start = (char*)(leftover + 1);

    chunk->size = size;
    return leftover;
}

void free(void* ptr) {

    // Override free to use our free
    void (*libc_free)(void*) = dlsym(RTLD_NEXT, "free");

    printf("You just used my implementation of free\n");

    if (!ptr) {
        return;
    }

    block_t* chunk = (block_t*)ptr - 1;
    heap_insert(chunk);
}






