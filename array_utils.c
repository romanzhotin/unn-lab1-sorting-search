#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

void generate_random_array(int *arr, size_t n, int min_val, int max_val) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
}

void print_array(const int *arr, size_t n) {
    if (n == 0) {
        printf("Массив пуст\n");
        return;
    }

    if (n > 20) {
        for (size_t i = 0; i < 10; i++) {
            printf("%d ", arr[i]);
        }
        printf("... ");
        for (size_t i = n - 5; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n(Всего элементов: %zu)\n", n);
    } else {
        for (size_t i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int read_array_manual(int *arr, size_t *n, size_t max_n) {
    printf("Введите количество элементов (до %zu): ", max_n);
    
    if (scanf("%zu", n) != 1 || *n == 0 || *n > max_n) {
        printf("Ошибка: неверный размер массива!\n");
        while (getchar() != '\n');
        *n = 0; // СБРАСЫВАЕМ РАЗМЕР, чтобы избежать вылета
        return 0;
    }

    printf("Введите %zu целых чисел через пробел:\n", *n);
    for (size_t i = 0; i < *n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Ошибка при вводе элемента %zu!\n", i + 1);
            while (getchar() != '\n');
            *n = 0; // СБРОС ПРИ ОШИБКЕ ВВОДА ЭЛЕМЕНТА
            return 0;
        }
    }
    return 1;
}