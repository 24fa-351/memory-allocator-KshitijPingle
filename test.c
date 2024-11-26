// Add header later

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_OF_TESTS 10

int rand_between(int min, int max) {
    return min + rand() % (max - min + 1);
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    int num_of_tests = NUM_OF_TESTS;

    // Accept arguments
    if (argc > 1) {
        if ((strcmp(argv[1], "-t") == 0) && (strcmp(argv[2], "num") == 0)) {
            num_of_tests = atoi(argv[3]);
        }
        else {
            printf("Error: Invalid arguments\n");
            printf("Usage: %s -t num <num_of_tests>\n", argv[0]);
            return 1;
        }
    }

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
            return 1;
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

    return 0;
}