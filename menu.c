#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "menu.h"
#include "array_utils.h"
#include "common.h"
#include "sorts.h"
#include "searches.h"

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

    srand(time(NULL));
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
                    if (arr) free(arr);
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
                    size_t new_n = 0;
                    if (scanf("%zu", &new_n) == 1 && new_n > 0 && new_n <= MAX_ARRAY_SIZE) {
                        n = new_n;
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
            case 2: {
                if (!arr || n == 0) {
                    printf("Сначала введите или сгенерируйте массив!\n");
                    break;
                }
                printf("\nДоступные сортировки:\n");
                for (size_t i = 0; i < SORT_ALGOS_COUNT; i++) {
                    printf(" %zu. %s\n", i + 1, SORT_ALGOS[i].name);
                }
                printf("Выберите сортировку: ");
                int sort_choice;
                if (scanf("%d", &sort_choice) != 1 || sort_choice < 1 || sort_choice > (int)SORT_ALGOS_COUNT) {
                    while (getchar() != '\n');
                    printf("Неверный выбор!\n");
                    break;
                }
                
                int *work = malloc(n * sizeof(int));
                if (!work) {
                    printf("Ошибка памяти!\n");
                    break;
                }
                memcpy(work, arr, n * sizeof(int));
                
                sort_stats_t stats = {0};
                printf("\nВыполняется сортировка \"%s\"...\n", SORT_ALGOS[sort_choice - 1].name);
                
                SORT_ALGOS[sort_choice - 1].fn(work, n, &stats);
                
                printf("\n--- РЕЗУЛЬТАТЫ ---\n");
                printf("Время: %.6f сек\n", stats.time);
                printf("Сравнений: %llu\n", stats.comparisons);
                printf("Перестановок: %llu\n", stats.swaps);
                
                printf("\nОтсортированный массив (копия):\n");
                print_array(work, n);
                
                free(work);
                break;
            }
            case 3: {
                if (!arr || n == 0) {
                    printf("Сначала введите или сгенерируйте массив!\n");
                    break;
                }
                
                int target;
                printf("\nВведите число для поиска: ");
                if (scanf("%d", &target) != 1) {
                    while (getchar() != '\n');
                    printf("Ошибка ввода!\n");
                    break;
                }

                printf("\nДоступные алгоритмы поиска:\n");
                for (size_t i = 0; i < SEARCH_ALGOS_COUNT; i++) {
                    printf(" %zu. %s\n", i + 1, SEARCH_ALGOS[i].name);
                }
                printf("Выберите алгоритм: ");
                int search_choice;
                if (scanf("%d", &search_choice) != 1 || search_choice < 1 || search_choice > (int)SEARCH_ALGOS_COUNT) {
                    while (getchar() != '\n');
                    printf("Неверный выбор!\n");
                    break;
                }

                int *search_arr = arr; // По умолчанию ищем в оригинале
                int *sorted_copy = NULL;

                // Если алгоритм требует сортировки (например, бинарный поиск)
                if (SEARCH_ALGOS[search_choice - 1].requires_sorted) {
                    printf("Алгоритм \"%s\" требует отсортированного массива.\n", SEARCH_ALGOS[search_choice - 1].name);
                    printf("Создаем копию и сортируем её (Быстрая сортировка)...\n");
                    
                    sorted_copy = malloc(n * sizeof(int));
                    if (!sorted_copy) {
                        printf("Ошибка памяти!\n");
                        break;
                    }
                    memcpy(sorted_copy, arr, n * sizeof(int));
                    
                    // Ищем быструю сортировку в реестре и применяем её к копии
                    for (size_t i = 0; i < SORT_ALGOS_COUNT; i++) {
                        if (strcmp(SORT_ALGOS[i].name, "Быстрая") == 0) {
                            sort_stats_t tmp_stats = {0};
                            SORT_ALGOS[i].fn(sorted_copy, n, &tmp_stats);
                            break;
                        }
                    }
                    search_arr = sorted_copy;
                }

                search_stats_t sstats = {0};
                printf("\nВыполняется поиск \"%s\"...\n", SEARCH_ALGOS[search_choice - 1].name);
                SEARCH_ALGOS[search_choice - 1].fn(search_arr, n, target, &sstats);

                printf("\n--- РЕЗУЛЬТАТЫ ---\n");
                printf("Сравнений: %llu\n", sstats.comparisons);
                if (sstats.index != -1) {
                    printf("Элемент найден! Индекс: %ld\n", sstats.index);
                } else {
                    printf("Элемент НЕ найден\n");
                }

                if (sorted_copy) free(sorted_copy);
                break;
            }
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

    if (arr) free(arr);
}