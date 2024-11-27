// Add a header later

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "my_malloc.h"

static void* free_array[1024 * 1024] = {0};  // 1MB for now


void heap_insert(block_t* new_chunk) {
    // Add a chunk back to our free_array
    for (int i = 0; i < 1024 * 1024; i++) {
        // Find where our free space is (indicated by where we have zeroes)
        if (free_array[i] == 0) {
            free_array[i] = new_chunk->pointer_to_start;

            for (int j = i; j < new_chunk->size; j++) {
                // reinitialize free space as zeroes
                free_array[j] = 0;
            }

            break;
        }
    }

    // Free everything needed
    my_free(new_chunk->pointer_to_start);
    my_free(new_chunk);
}




