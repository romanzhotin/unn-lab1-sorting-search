#include <stdio.h>
#include <stdlib.h> // Для malloc
#include <time.h>   // Для srand
#include "menu.h"
#include "array_utils.h"
#include "common.h"

static void print_header(void) {
    printf("============================================================\n");
    printf("ЛАБОРАТОРНАЯ РАБОТА №1\n");
    printf("Сравнение алгоритмов сортировки и поиска\n");
    printf("============================================================\n");
}

static void print_main_menu(void) {
    printf("\n------------------------------------------------------------\n");
    printf("ГЛАВНОЕ МЕНЮ\n");
    printf("------------------------------------------------------------\n");
    printf(" 1. Ввести массив\n");
    printf(" 2. Выполнить сортировку\n");
    printf(" 3. Выполнить поиск\n");
    printf(" 4. Сравнить алгоритмы сортировки\n");
    printf(" 5. Сравнить алгоритмы поиска\n");
    printf(" 6. Показать текущий массив\n");
    printf(" 7. Выход\n");
    printf("------------------------------------------------------------\n");
    printf("Выберите пункт: ");
}

void menu_run(void) {
    int choice;
    int *arr = NULL;
    size_t n = 0;

    srand(time(NULL)); // Инициализация генератора случайных чисел
    print_header();

    do {
        print_main_menu();
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: {
                printf("\n1. Ввести вручную\n");
                printf("2. Сгенерировать случайно\n");
                printf("Выбор: ");
                int subchoice;
                if (scanf("%d", &subchoice) != 1) {
                    while (getchar() != '\n');
                    break;
                }

                if (subchoice == 1) {
                    if (arr) free(arr); // Очищаем старый массив, если он был
                    arr = malloc(MAX_ARRAY_SIZE * sizeof(int));
                    if (!arr) {
                        printf("Ошибка: не удалось выделить память!\n");
                        break;
                    }
                    if (read_array_manual(arr, &n, MAX_ARRAY_SIZE)) {
                        printf("Массив успешно введен! Размер: %zu\n", n);
                    }
                } else if (subchoice == 2) {
                    printf("Введите размер массива (до %d): ", MAX_ARRAY_SIZE);
                    
                    // Безопасное чтение: сначала во временную переменную
                    size_t new_n = 0;
                    if (scanf("%zu", &new_n) == 1 && new_n > 0 && new_n <= MAX_ARRAY_SIZE) {
                        n = new_n; // Обновляем n, только если ввод корректен
                        
                        if (arr) free(arr);
                        arr = malloc(n * sizeof(int));
                        if (!arr) {
                            printf("Ошибка: не удалось выделить память!\n");
                            break;
                        }
                        generate_random_array(arr, n, -1000, 1000);
                        printf("Сгенерирован массив из %zu элементов от -1000 до 1000\n", n);
                    } else {
                        printf("Ошибка: неверный размер!\n");
                        while (getchar() != '\n');
                    }
                }
                break;
            }
            case 2: printf("[Заглушка] Сортировка\n"); break;
            case 3: printf("[Заглушка] Поиск\n"); break;
            case 4: printf("[Заглушка] Сравнение сортировок\n"); break;
            case 5: printf("[Заглушка] Сравнение поисков\n"); break;
            case 6: 
                printf("\nТекущий массив:\n");
                print_array(arr, n);
                break;
            case 7: 
                printf("Выход из программы\n"); 
                break;
            default: 
                printf("Неверный пункт меню!\n"); 
                break;
        }
    } while (choice != 7);

    if (arr) free(arr); // Очистка памяти при выходе
}