#ifndef SA_H
#define SA_H

#include <stdint.h>


/* =========================
   ANSI COLORS
   ========================= */

#define SA_RESET   "\033[0m"
#define SA_BOLD    "\033[1m"

#define SA_BLACK   "\033[30m"
#define SA_RED     "\033[31m"
#define SA_GREEN   "\033[32m"
#define SA_YELLOW  "\033[33m"
#define SA_BLUE    "\033[34m"
#define SA_MAGENTA "\033[35m"
#define SA_CYAN    "\033[36m"
#define SA_WHITE   "\033[37m"

#define SA_BRED    "\033[91m"
#define SA_BGREEN  "\033[92m"
#define SA_BYELLOW "\033[93m"
#define SA_BBLUE   "\033[94m"
#define SA_BMAGENTA "\033[95m"
#define SA_BCYAN   "\033[96m"

#define SA_COLOR(n) "\033[38;5;" #n "m"


/* =========================
   Animation
   ========================= */

typedef enum
{
    SA_SPINNER,
    SA_DOTS,
    SA_BAR,
    SA_PULSE,
    SA_CUSTOM

} sa_animation_type;


typedef struct
{
    const char *frame;
    uint32_t duration_ms;

} sa_frame;


typedef struct
{
    sa_animation_type type;
    sa_frame *frames;
    uint32_t frame_count;
    uint32_t loop;

} sa_animation;



/* =========================
   Loading
   ========================= */

void sa_spinner(int sec);

void sa_dots(int sec);

void sa_pulse(int sec);

void sa_progress(int percent);

void sa_progress_bar(int percent);

void sa_download(long size_mb, int speed_mb);

void sa_upload(long size_mb, int speed_mb);

void sa_install(const char *name);

void sa_compile(const char *name);



/* =========================
   Animations
   ========================= */

void sa_marquee(const char *text, int sec);

void sa_wave(int sec);

void sa_rainbow(int sec);

void sa_matrix(int sec);

void sa_typewriter(const char *text);

void sa_bounce(int sec);

void sa_rotate(int sec);

void sa_glitch(int sec);



/* =========================
   Messages
   ========================= */

void sa_ok(const char *msg);

void sa_error(const char *msg);

void sa_warning(const char *msg);

void sa_info(const char *msg);

void sa_status(const char *msg, int sec);



/* =========================
   System
   ========================= */

void sa_cpu(void);

void sa_ram(void);

void sa_disk(void);

void sa_network(void);

void sa_monitor(void);



/* =========================
   Widgets
   ========================= */
void sa_clear(void);

void sa_center(const char *text);

void sa_logo(void);

void sa_box(const char *text);

void sa_banner(const char *text);

void sa_line(void);

void sa_table(const char **items, int count);



/* =========================
   Tools
   ========================= */

void sa_timer(int sec);

void sa_countdown(int sec);

void sa_task(const char *name, int sec);

void sa_speed(long mb, int sec);



/* =========================
   Main API
   ========================= */

void saani(sa_animation anim, uint32_t sec);


#endif
