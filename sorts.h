#ifndef SORTS_H
#define SORTS_H
#include <stddef.h>
#include "stats.h"

typedef void (*sort_fn)(int *arr, size_t n, sort_stats_t *stats);

typedef struct {
    const char *name;
    sort_fn fn;
} sort_algo_t;

extern const sort_algo_t SORT_ALGOS[];
extern const size_t SORT_ALGOS_COUNT;

#endif // SORTS_H