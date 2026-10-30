#include <stdio.h>
#include "menu.h"

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
    print_header();

    do {
        print_main_menu();
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: printf("[Заглушка] Ввод массива\n"); break;
            case 2: printf("[Заглушка] Сортировка\n"); break;
            case 3: printf("[Заглушка] Поиск\n"); break;
            case 4: printf("[Заглушка] Сравнение сортировок\n"); break;
            case 5: printf("[Заглушка] Сравнение поисков\n"); break;
            case 6: printf("[Заглушка] Показать массив\n"); break;
            case 7: printf("Выход из программы\n"); break;
            default: printf("Неверный пункт меню! Попробуйте снова\n"); break;
        }
    } while (choice != 7);
}