#ifndef SA_H
#define SA_H

#include <stdint.h>

// Типы анимаций
typedef enum {
    SA_SPINNER,       // Крутящийся спиннер (⠋, ⠙, ⠹, ⠸, ⠼, ⠴, ⠦, ⠧, ⠇, ⠏)
    SA_DOTS,          // Точки (..., .., .)
    SA_BAR,           // Прогресс-бар (▰▱▱▱ → ▰▰▱▱ → ...)
    SA_PULSE,         // Пульсирующая строка (===== → ==== → === → == → =)
    SA_CUSTOM         // Пользовательская анимация (передаётся строками)
} sa_animation_type;

// Структура для кадра анимации
typedef struct {
    const char *frame; // Строка кадра (например, "⠋", "⠙")
    uint32_t duration_ms; // Длительность кадра в миллисекундах
} sa_frame;

// Структура анимации
typedef struct {
    sa_animation_type type; // Тип анимации
    sa_frame *frames;       // Массив кадров (для SA_CUSTOM)
    uint32_t frame_count;   // Количество кадров
    uint32_t loop;          // Зацикливать анимацию? (1 = да, 0 = нет)
} sa_animation;

// Функция для анимации (замена sleep())
// Пример использования: saani(SA_SPINNER, 6); // Спиннер на 6 секунд
void saani(sa_animation anim, uint32_t sleep_time_sec);

#endif // SA_H
