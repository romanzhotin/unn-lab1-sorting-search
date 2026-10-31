#include "searches.h"

static void linear_search(const int *arr, size_t n, int target, search_stats_t *stats) {
    stats->index = -1;
    for (size_t i = 0; i < n; i++) {
        stats->comparisons++;
        if (arr[i] == target) {
            stats->index = (long)i;
            return;
        }
    }
}

static void binary_search(const int *arr, size_t n, int target, search_stats_t *stats) {
    stats->index = -1;
    if (n == 0) return;

    long left = 0, right = (long)n - 1;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        stats->comparisons++;
        if (arr[mid] == target) {
            stats->index = mid;
            return;
        }
        stats->comparisons++;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
}

const search_algo_t SEARCH_ALGOS[] = {
    {"Линейный", linear_search, 0},
    {"Бинарный", binary_search, 1}
};

const size_t SEARCH_ALGOS_COUNT = sizeof(SEARCH_ALGOS) / sizeof(SEARCH_ALGOS[0]);