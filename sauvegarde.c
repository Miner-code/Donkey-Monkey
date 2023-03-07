#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 10

int compare_ints(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int replace(int num) {


    int nums[MAX_NUMS + 1];  // Add an extra slot for the new number
    int num_count = 0;

    FILE *fp = fopen("integers.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file integers.txt\n");
        return 1;
    }

    // Read in the existing numbers from the file
    while (fscanf(fp, "%d", &nums[num_count]) == 1) {
        num_count++;
        if (num_count > MAX_NUMS) {
            break;
        }
    }

    fclose(fp);

    // Add the new number to the list
    nums[num_count] = num;
    num_count++;

    // Sort the list in descending order
    qsort(nums, num_count, sizeof(int), compare_ints);

    // Truncate the list to only the 10 largest numbers
    if (num_count > MAX_NUMS) {
        num_count = MAX_NUMS;
    }

    // Write the new list back out to the file
    fp = fopen("integers.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file integers.txt for writing\n");
        return 1;
    }

    for (int i = 0; i < num_count; i++) {
        fprintf(fp, "%d\n", nums[i]);
    }

    fclose(fp);

    return 0;
}
