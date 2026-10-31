#ifndef SEARCHES_H
#define SEARCHES_H
#include <stddef.h>
#include "stats.h"

typedef void (*search_fn)(const int *arr, size_t n, int target, search_stats_t *stats);

typedef struct {
    const char *name;
    search_fn fn;
    int requires_sorted; // 1 - требует сортировки, 0 - нет
} search_algo_t;

extern const search_algo_t SEARCH_ALGOS[];
extern const size_t SEARCH_ALGOS_COUNT;

#endif // SEARCHES_H