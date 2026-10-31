#ifndef STATS_H
#define STATS_H

typedef struct {
    unsigned long long comparisons; // количество сравнений
    unsigned long long swaps;       // количество перестановок
    double time;                    // время в секундах
} sort_stats_t;

#endif // STATS_H