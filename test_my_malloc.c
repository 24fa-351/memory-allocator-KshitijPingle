// Kshitij Pingle
// kpingle@csu.fullerton.edu
// Date: November 25, 2024
// Description: Program to test my implementation of malloc and free

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "my_malloc.h"  // Includes my overridden malloc and free

#define NUM_OF_TESTS 5

int rand_between(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool small_test() {

    int num_of_tests = 5;

    // 64 chars long currently
    char *test_string = "This is a test string for Kshitij to test his mallocs and frees.";

    printf("Number of tests: %d\n", num_of_tests);

    char *ptrs[num_of_tests];

    // malloc here
    for (int i = 0; i < num_of_tests; i++) {
        int rand_size = rand_between(1, 63);
        fprintf(stderr, "[%d] size: %d\n", i, rand_size);

        ptrs[i] = malloc(rand_size);
        if (ptrs[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for ptrs[%d]\n", i);
            return false;
        }

        int len_to_copy = (rand_size > strlen(test_string)) ? strlen(test_string) : rand_size;  // Give the min of the two

        fprintf(stderr, "[%d] len_to_copy: %d\n", i, len_to_copy);
        strncpy(ptrs[i], test_string, len_to_copy);
        ptrs[i][len_to_copy] = '\0';

        fprintf(stderr, "ptrs[%d]: %s\n", i, ptrs[i]);

    }

    // free here
    for (int i = 0; i < num_of_tests; i++) {
        fprintf(stderr, "Freeing ptrs[%d]\n", i);
        free(ptrs[i]);
        fprintf(stderr, "Freed ptrs[%d]\n", i);
    }

    // If we reached here, all tests passed
    return true;
}

int main(int argc, char *argv[]) {
    printf("Testing my_malloc\n");

    srand(time(NULL));

    bool result = false;

    if (argc > 1) {
        if ((strcmp(argv[1], "-t") == 0) && (strcmp(argv[2], "num") == 0)) {
            // Execute only one random test
            int test_num = atoi(argv[3]);

            switch (test_num) {
                case 1:
                    printf("Executing small_test()\n");
                    result = small_test();
                    printf("RESULT: %s\n", result ? "PASSED" : "FAILED");
                    break;
                default:
                    printf("Executing small_test()\n");
                    result = small_test();
                    printf("RESULT: %s\n", result ? "PASSED" : "FAILED");
                    break;
            }

            return 0;
        }
        else {
            printf("Error: Invalid arguments\n");
            printf("Usage: %s -t num\n", argv[0]);
            return 1;
        }
    }

    // Otherwise execute all tests

    printf("Executing small_test()\n");
    result = small_test();
    printf("RESULT: %s\n", result ? "PASSED" : "FAILED");


    return 0;
}