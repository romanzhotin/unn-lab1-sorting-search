#include <time.h>
#include "sorts.h"

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void bubble_sort(int *arr, size_t n, sort_stats_t *stats) {
    clock_t start = clock();
    if (n < 2) {
        stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
        return;
    }

    for (size_t i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (size_t j = 0; j < n - i - 1; j++) {
            stats->comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                stats->swaps++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
}

// cocktail_sor | bubble_sort_bidirectional
static void cocktail_sort(int *arr, size_t n, sort_stats_t *stats) {
    clock_t start = clock();
    if (n < 2) {
        stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
        return;
    }

    size_t l = 0, r = n - 1;

    while (l < r) {
        size_t new_r = l;
        for (size_t i = l; i < r; i++) {
            stats->comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                stats->swaps++;
                new_r = i;
            }
        }
        r = new_r;

        size_t new_l = r;
        for (size_t i = r; i > l; i--) {
            stats->comparisons++;
            if (arr[i - 1] > arr[i]) {
                swap(&arr[i - 1], &arr[i]);
                stats->swaps++;
                new_l = i;
            }
        }
        l = new_l;
    }
    stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
}

const sort_algo_t SORT_ALGOS[] = {
    {"Пузырьковая", bubble_sort},
    {"Шейкерная",   cocktail_sort}
};

const size_t SORT_ALGOS_COUNT = sizeof(SORT_ALGOS) / sizeof(SORT_ALGOS[0]);