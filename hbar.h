#ifndef HBAR_H
#define HBAR_H
#include <stddef.h>

// is_time = 1 (для времени), is_time = 0 (для штук: сравнений/перестановок)
void hbar_chart(const char *title, const char *const *labels,
                const double *values, size_t n, int max_width, int is_time);

#endif // HBAR_H