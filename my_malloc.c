// Add a header later

#define _GNU_SOURCE // needed for 'RTLD_NEXT'
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

#include "my_malloc.h"

#define MAX_CHUNKS 128

block_t heap[MAX_CHUNKS];
size_t heap_count = 0;

// Insert chunks the user does not need back into our heap
void heap_insert(block_t *new_chunk)
{
    if (heap_count < MAX_CHUNKS)
    {
        heap[heap_count++] = *new_chunk;
    }
}

void *malloc(size_t size)
{

    // Override malloc to use our malloc
    void *(*libc_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");

    printf("You just used my implementation of malloc\n");

    // try to find a chunk that is the right size
    for (size_t i = 0; i < heap_count; i++)
    {
        if (heap[i].size >= size)
        {
            block_t *chunk = &heap[i];
            block_t *leftover = split(chunk, size);
            if (leftover)
            {
                heap_insert(leftover);
            }
            return chunk->pointer_to_start;
        }
    }

    // if we don't have enough, get more memory from the system
    block_t *new_chunk = sbrk(size + sizeof(block_t));
    if (new_chunk == (void *)-1)
    {
        return NULL;
    }
    new_chunk->size = size;
    new_chunk->pointer_to_start = (char *)(new_chunk + 1);

    return new_chunk->pointer_to_start;
}

block_t *split(block_t *chunk, size_t size)
{
    if (chunk->size <= size)
    {
        return NULL;
    }

    block_t *leftover = (block_t *)(chunk->pointer_to_start + size);
    leftover->size = chunk->size - size - sizeof(block_t);
    leftover->pointer_to_start = (char *)(leftover + 1);

    chunk->size = size;
    return leftover;
}

void free(void *ptr)
{

    // Override free to use our free
    void (*libc_free)(void *) = dlsym(RTLD_NEXT, "free");

    printf("You just used my implementation of free\n");

    if (!ptr)
    {
        return;
    }

    block_t *chunk = (block_t *)ptr - 1;
    heap_insert(chunk);
}

void *realloc(void *ptr, size_t size)
{

    // Override free to use our realloc
    void *(*libc_realloc)(void *, size_t) = dlsym(RTLD_NEXT, "realloc");

    printf("You just used my implementation of realloc\n");

    if (ptr == NULL)
    {
        return malloc(size);
    }
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    // Check if we can still use the old block
    block_t *old_block = (block_t *)((char *)ptr - sizeof(block_t));
    if (old_block->size >= size)
    {
        return ptr;
    }

    // Allocate a new block and copy the old data
    void *new_ptr = malloc(size);
    if (new_ptr == NULL)
    {
        return NULL;
    }

    memcpy(new_ptr, ptr, old_block->size);
    free(ptr);
    return new_ptr;
}

void *calloc(size_t num, size_t size)
{
    // Override calloc to use our calloc
    void *(*libc_calloc)(size_t, size_t) = dlsym(RTLD_NEXT, "calloc");

    printf("You just used my implementation of calloc\n");

    size_t total_size = num * size;
    void *ptr = malloc(total_size);
    if (ptr == NULL)
    {
        return NULL;
    }

    memset(ptr, 0, total_size);
    return ptr;
}
