#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stddef.h>

// Заполняет массив случайными числами от min_val до max_val
void generate_random_array(int *arr, size_t n, int min_val, int max_val);

// Выводит массив на экран (если элементов > 20, выводит первые 10 и последние 5)
void print_array(const int *arr, size_t n);

// Чтение массива вручную с клавиатуры (возвращает 1 при успехе, 0 при ошибке)
int read_array_manual(int *arr, size_t *n, size_t max_n);

#endif // ARRAY_UTILS_H