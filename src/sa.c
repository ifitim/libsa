#include "sa.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// Внутренние кадры для стандартных анимаций
static const sa_frame spinner_frames[] = {
    {"⠋", 100},
    {"⠙", 100},
    {"⠹", 100},
    {"⠸", 100},
    {"⠼", 100},
    {"⠴", 100},
    {"⠦", 100},
    {"⠧", 100},
    {"⠇", 100},
    {"⠏", 100}
};

static const sa_frame dots_frames[] = {
    {".", 300},
    {"..", 300},
    {"...", 300}
};

static const sa_frame bar_frames[] = {
    {"▰▱▱▱", 200},
    {"▰▰▱▱", 200},
    {"▰▰▰▱", 200},
    {"▰▰▰▰", 200}
};

static const sa_frame pulse_frames[] = {
    {"=====", 150},
    {"==== ", 150},
    {"===  ", 150},
    {"==   ", 150},
    {"=    ", 150},
    {"    =", 150},
    {"   ==", 150},
    {"  ====", 150},
    {" =====", 150}
};

// Вспомогательная функция: очистить строку в терминале
static void clear_line() {
    printf("\r\033[K"); // Возврат каретки + очистка строки
}

// Вспомогательная функция: получить кадры для стандартной анимации
static void get_standard_frames(sa_animation_type type, sa_frame **frames, uint32_t *count) {
    switch (type) {
        case SA_SPINNER:
            *frames = (sa_frame *)spinner_frames;
            *count = sizeof(spinner_frames) / sizeof(spinner_frames[0]);
            break;
        case SA_DOTS:
            *frames = (sa_frame *)dots_frames;
            *count = sizeof(dots_frames) / sizeof(dots_frames[0]);
            break;
        case SA_BAR:
            *frames = (sa_frame *)bar_frames;
            *count = sizeof(bar_frames) / sizeof(bar_frames[0]);
            break;
        case SA_PULSE:
            *frames = (sa_frame *)pulse_frames;
            *count = sizeof(pulse_frames) / sizeof(pulse_frames[0]);
            break;
        case SA_CUSTOM:
            // Для SA_CUSTOM кадры передаются в sa_animation
            break;
    }
}

// Основная функция анимации
void saani(sa_animation anim, uint32_t sleep_time_sec) {
    sa_frame *frames = anim.frames;
    uint32_t frame_count = anim.frame_count;
    uint32_t loop = anim.loop;

    // Если анимация стандартная, получаем кадры
    if (anim.type != SA_CUSTOM) {
        get_standard_frames(anim.type, &frames, &frame_count);
    }

    // Время начала анимации
    time_t start_time = time(NULL);
    time_t end_time = start_time + sleep_time_sec;

    // Основной цикл анимации
    while (1) {
        for (uint32_t i = 0; i < frame_count; i++) {
            // Проверяем, не истекло ли время
            if (time(NULL) >= end_time) {
                clear_line();
                return;
            }

            // Выводим текущий кадр
            printf("\r%s", frames[i].frame);
            fflush(stdout);

            // Ждём длительность кадра
            usleep(frames[i].duration_ms * 1000);

            // Проверяем, не истекло ли время после сна
            if (time(NULL) >= end_time) {
                clear_line();
                return;
            }
        }

        // Если анимация не зациклена, выходим после одного прохода
        if (!loop) {
            break;
        }
    }

    // Очищаем строку по завершении
    clear_line();
}
