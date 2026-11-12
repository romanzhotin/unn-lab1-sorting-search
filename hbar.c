#include "hbar.h"
#include <stdio.h>

static int utf8_len(const char *s) {
    /*
    Считает количество ВИЗУАЛЬНЫХ СИМВОЛОВ в строке UTF-8 (а не байт).
    Стандартный strlen() вернет для "Быстрая" число 14 (русская буква = 2 байта),
    что сломает выравнивание. Нам же нужно получить 7.
    
    В UTF-8 байты-продолжения (вторая половина русской буквы) ВСЕГДА начинаются 
    с битов "10". Маска 0xC0 (11000000) оставляет только первые два бита.
    Если результат равен 0x80 (10000000) — это "хвост", пропускаем. 
    Иначе — начало новой буквы, считаем (len++).
    */
    int len = 0;
    while (*s) {
        if ((*s & 0xC0) != 0x80) len++;
        s++;
    }
    return len;
}

void hbar_chart(const char *title, const char *const *labels,
                const double *values, size_t n, int max_width, int is_time)
{
    if (n == 0 || max_width <= 0) return;

    const char *blocks[] = {"", "▏", "▎", "▍", "▌", "▋", "▊", "▉"};

    double vmax = 0;
    int max_label = 0;
    for (size_t i = 0; i < n; i++) {
        if (values[i] > vmax) vmax = values[i];
        int l = utf8_len(labels[i]);
        if (l > max_label) max_label = l;
    }
    if (vmax <= 0) vmax = 1;

    printf("\n%s\n", title);

    for (size_t i = 0; i < n; i++) {
        printf("%s", labels[i]);
        for (int p = utf8_len(labels[i]); p < max_label; p++) printf(" ");
        printf(" | ");

        // Вычисляем ширину в 1/8 долях (точность до 0.5 под-символа)
        int eighths = (int)((values[i] / vmax) * max_width * 8 + 0.5);

        // Правила отображения нулей
        if (values[i] == 0 && !is_time) {
            eighths = 0; // Для штук ноль — это пусто
        } else if (eighths == 0) {
            eighths = 1; // Для времени 0 (или для очень малых штук) — минимум 1/8
        }

        int full = eighths / 8;
        int rem = eighths % 8;

        for (int b = 0; b < full; b++) printf("█");
        if (rem > 0) printf("%s", blocks[rem]);

        int printed = full + (rem > 0 ? 1 : 0);
        for (int s = printed; s < max_width; s++) printf(" ");

        if (is_time) {
            printf(" | %f\n", values[i]);
        } else {
            printf(" | %.0f\n", values[i]);
        }
    }
}