#include <time.h>
#include <stdlib.h>
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

static void merge(int a[], int t[], int l, int m, int r, sort_stats_t *stats) {
    int i = l, j = m + 1, k = l;
    
    while (i <= m && j <= r) {
        stats->comparisons++;
        if (a[i] <= a[j]) t[k++] = a[i++];
        else t[k++] = a[j++];
    }
    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];
    
    for (i = l; i <= r; i++) {
        a[i] = t[i];
        stats->swaps++;
    }
}

static void merge_sort_rec(int a[], int t[], int l, int r, sort_stats_t *stats) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort_rec(a, t, l, m, stats);
    merge_sort_rec(a, t, m + 1, r, stats);
    merge(a, t, l, m, r, stats);
}

static void merge_sort(int *arr, size_t n, sort_stats_t *stats) {
    clock_t start = clock();
    if (n > 1) {
        int *temp = malloc(n * sizeof(int));
        if (temp) {
            merge_sort_rec(arr, temp, 0, n - 1, stats);
            free(temp);
        }
    }
    stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
}

static void quick_sort_rec(int a[], int l, int r, sort_stats_t *stats) {
    if (l >= r) return;
    int i = l, j = r;
    int p = a[l + (r - l) / 2];
    
    while (i <= j) {
        while (a[i] < p) { i++; stats->comparisons++; }
        while (a[j] > p) { j--; stats->comparisons++; }
        
        stats->comparisons++;
        if (i <= j) {
            swap(&a[i], &a[j]);
            stats->swaps++;
            i++; j--;
        }
    }
    quick_sort_rec(a, l, j, stats);
    quick_sort_rec(a, i, r, stats);
}

static void quick_sort(int *arr, size_t n, sort_stats_t *stats) {
    clock_t start = clock();
    if (n > 1) {
        quick_sort_rec(arr, 0, n - 1, stats);
    }
    stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
}

static void insertion_sort(int *arr, size_t n, sort_stats_t *stats)
{
    clock_t start = clock();
    if (n < 2) {
        stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
        return;
    }

    for (size_t i = 1; i < n; i++) {
        int key = arr[i];
        size_t j = i;

        while (j > 0) {
            stats->comparisons++;
            if (arr[j - 1] <= key)
                break;

            arr[j] = arr[j - 1];
            stats->swaps++;
            j--;
        }
        arr[j] = key;
    }

    stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
}

static void radix_sort(int *arr, size_t n, sort_stats_t *stats) {
    clock_t start = clock();
    if (n < 2) {
        stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
        return;
    }

    // Находим минимум и максимум для обработки отрицательных чисел
    int min_val = arr[0];
    int max_val = arr[0];
    for (size_t i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    long long range = (long long)max_val - min_val;
    if (range == 0) {
        stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
        return; // Все элементы одинаковые
    }

    // Выделяем буфер
    int *temp = malloc(n * sizeof(int));
    if (!temp) {
        stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
        return;
    }

    long long exp = 1;
    
    while (range / exp > 0) {
        int count[10] = {0}; // Массив для подсчета цифр от 0 до 9

        // Считаем количество чисел с каждой цифрой в текущем разряде
        for (size_t i = 0; i < n; i++) {
            // (arr[i] - min_val) сдвигает все числа в положительную зону
            long long val = (long long)arr[i] - min_val;
            int digit = (val / exp) % 10;
            count[digit]++;
        }

        // Префиксные суммы для определения позиций
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Собираем во временный массив (идем с конца для стабильности)
        for (long long i = (long long)n - 1; i >= 0; i--) {
            long long val = (long long)arr[i] - min_val;
            int digit = (val / exp) % 10;
            temp[count[digit] - 1] = arr[i];
            count[digit]--;
            stats->swaps++; // Считаем переносы как перестановки
        }

        // Возвращаем обратно в оригинальный массив
        for (size_t i = 0; i < n; i++) {
            arr[i] = temp[i];
            stats->swaps++;
        }

        exp *= 10;
    }

    free(temp);
    stats->comparisons = 0; // Radix Sort вообще не сравнивает элементы
    stats->time = (double)(clock() - start) / CLOCKS_PER_SEC;
}

const sort_algo_t SORT_ALGOS[] = {
    {"Пузырьковая", bubble_sort},
    {"Шейкерная",   cocktail_sort},
    {"Вставками", insertion_sort},
    {"Слиянием",    merge_sort},
    {"Быстрая",     quick_sort},
    {"Поразрядная", radix_sort}
};

const size_t SORT_ALGOS_COUNT = sizeof(SORT_ALGOS) / sizeof(SORT_ALGOS[0]);