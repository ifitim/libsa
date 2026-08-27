#include "sa.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


static void clear_line()
{
    printf("\r\033[K");
    fflush(stdout);
}


/* =========================
   BASIC LOADING
   ========================= */

void sa_spinner(int sec)
{
    const char *f[]={
        "⠋","⠙","⠹","⠸","⠼",
        "⠴","⠦","⠧","⠇","⠏"
    };

    time_t end=time(NULL)+sec;
    int i=0;

    while(time(NULL)<end)
    {
        printf("\r%s%s%s",
               SA_CYAN,
               f[i%10],
               SA_RESET);

        fflush(stdout);

        i++;
        usleep(100000);
    }

    clear_line();
}



void sa_dots(int sec)
{
    time_t end=time(NULL)+sec;
    int i=0;

    while(time(NULL)<end)
    {
        printf("\rLoading%s",
               i%3==0?".":
               i%3==1?"..":"...");

        fflush(stdout);

        i++;
        usleep(300000);
    }

    printf("\n");
}



void sa_pulse(int sec)
{
    time_t end=time(NULL)+sec;

    int i=0;

    while(time(NULL)<end)
    {
        printf("\r");

        for(int j=0;j<(i%10);j++)
            printf("=");

        fflush(stdout);

        i++;
        usleep(150000);
    }

    printf("\n");
}



void sa_progress(int percent)
{
    printf("\rProgress %d%%",percent);
    fflush(stdout);

    if(percent>=100)
        printf("\n");
}



void sa_progress_bar(int percent)
{
    int width=40;
    int fill=percent*width/100;

    printf("\r[");

    for(int i=0;i<width;i++)
    {
        if(i<fill)
            printf("#");
        else
            printf("-");
    }

    printf("] %d%%",percent);

    fflush(stdout);

    if(percent>=100)
        printf("\n");
}



/* =========================
   DOWNLOAD
   ========================= */


void sa_download(long size_mb,int speed_mb)
{
    for(long i=0;i<=size_mb;i++)
    {
        int p=(i*100)/size_mb;

        printf("\r%sDOWNLOAD%s [",
               SA_BCYAN,
               SA_RESET);


        int blocks=p/5;

        for(int j=0;j<20;j++)
            printf(j<blocks?"#":"-");


        printf("] %d%% %ld/%ld MB",
               p,i,size_mb);

        fflush(stdout);

        usleep(80000);
    }

    printf("\n%sDONE%s\n",
           SA_BGREEN,
           SA_RESET);
}



void sa_upload(long size_mb,int speed_mb)
{
    for(long i=0;i<=size_mb;i++)
    {
        int p=i*100/size_mb;

        printf("\r%sUPLOAD%s [",
               SA_BLUE,
               SA_RESET);


        for(int j=0;j<20;j++)
            printf(j<p/5?"#":"-");


        printf("] %d%%",p);

        fflush(stdout);

        usleep(80000);
    }

    printf("\n");
}





/* =========================
   ANIMATIONS
   ========================= */


void sa_marquee(const char *text,int sec)
{
    int len=strlen(text);

    for(int t=0;t<sec*10;t++)
    {
        printf("\r");

        for(int i=0;i<len;i++)
        {
            if(i==t%len)
                printf("%s%c%s",
                       SA_CYAN,
                       text[i],
                       SA_RESET);
            else
                printf("%c",text[i]);
        }

        fflush(stdout);
        usleep(100000);
    }

    printf("\n");
}



void sa_wave(int sec)
{
    const char *w="~^~^~^~^";

    for(int i=0;i<sec*10;i++)
    {
        printf("\r");

        for(int j=0;j<8;j++)
            printf("%c",w[(i+j)%8]);

        fflush(stdout);

        usleep(100000);
    }

    printf("\n");
}



static void rainbow_char(char c,int color)
{
    printf("\033[38;5;%dm%c%s",
           color,
           c,
           SA_RESET);
}



void sa_rainbow(int sec)
{
    const char *text="LIBSA 256 COLOR GRADIENT";

    int shift=0;

    for(int t=0;t<sec*10;t++)
    {
        printf("\r");

        for(int i=0;text[i];i++)
        {
            int color=16+((i+shift)%216);

            rainbow_char(text[i],color);
        }

        fflush(stdout);

        shift++;

        usleep(100000);
    }

    printf("\n");
}



void sa_matrix(int sec)
{
    const char chars[]="01ABCXYZ";

    srand(time(NULL));

    time_t end=time(NULL)+sec;

    while(time(NULL)<end)
    {
        printf("\r");

        for(int i=0;i<30;i++)
        {
            printf("\033[38;5;%dm%c",
                   22+(rand()%20),
                   chars[rand()%8]);
        }

        printf(SA_RESET);

        fflush(stdout);

        usleep(100000);
    }

    printf("\n");
}



void sa_typewriter(const char *text)
{
    while(*text)
    {
        printf("%c",*text);

        fflush(stdout);

        usleep(50000);

        text++;
    }

    printf("\n");
}



void sa_rotate(int sec)
{
    const char *r="|/-\\";

    for(int i=0;i<sec*10;i++)
    {
        printf("\r%c",r[i%4]);

        fflush(stdout);

        usleep(100000);
    }

    printf("\n");
}



void sa_bounce(int sec)
{
    for(int i=0;i<sec*20;i++)
    {
        printf("\r");

        int pos=i%20;

        for(int j=0;j<pos;j++)
            printf(" ");

        printf("●");

        fflush(stdout);

        usleep(80000);
    }

    printf("\n");
}



void sa_glitch(int sec)
{
    const char *g="@#$%&*";

    srand(time(NULL));

    for(int i=0;i<sec*10;i++)
    {
        printf("\r");

        for(int j=0;j<20;j++)
            printf("%c",
                   g[rand()%6]);

        fflush(stdout);

        usleep(100000);
    }

    printf("\n");
}





/* =========================
   MESSAGES
   ========================= */


void sa_ok(const char *msg)
{
    printf("%s✓ %s%s\n",
           SA_BGREEN,
           msg,
           SA_RESET);
}



void sa_error(const char *msg)
{
    printf("%s✗ %s%s\n",
           SA_BRED,
           msg,
           SA_RESET);
}



void sa_warning(const char *msg)
{
    printf("%s! %s%s\n",
           SA_YELLOW,
           msg,
           SA_RESET);
}



void sa_info(const char *msg)
{
    printf("%si %s%s\n",
           SA_BCYAN,
           msg,
           SA_RESET);
}



void sa_status(const char *msg,int sec)
{
    printf("%s%s%s\n",
           SA_BLUE,
           msg,
           SA_RESET);

    sa_spinner(sec);
}



/* =========================
   WIDGETS
   ========================= */


void sa_line(void)
{
    printf("----------------------------------------\n");
}



void sa_box(const char *text)
{
    int len=strlen(text);

    printf("+");

    for(int i=0;i<len+2;i++)
        printf("-");

    printf("+\n");

    printf("| %s |\n",text);

    printf("+");

    for(int i=0;i<len+2;i++)
        printf("-");

    printf("+\n");
}



void sa_banner(const char *text)
{
    printf("\n");

    printf("%s==============================%s\n",
           SA_BMAGENTA,
           SA_RESET);

    printf("%s%s%s\n",
           SA_BCYAN,
           text,
           SA_RESET);

    printf("%s==============================%s\n",
           SA_BMAGENTA,
           SA_RESET);

    printf("\n");
}



void sa_table(const char **items,int count)
{
    for(int i=0;i<count;i++)
    {
        printf("| %d | %s |\n",
               i+1,
               items[i]);
    }
}



/* =========================
   TIME / TASK
   ========================= */


void sa_timer(int sec)
{
    while(sec>=0)
    {
        printf("\r%sTime: %d%s",
               SA_GREEN,
               sec,
               SA_RESET);

        fflush(stdout);

        sleep(1);

        sec--;
    }

    printf("\n");
}



void sa_countdown(int sec)
{
    while(sec>0)
    {
        printf("\rStarting: %d",
               sec);

        fflush(stdout);

        sleep(1);

        sec--;
    }

    printf("\rGO!\n");
}



void sa_task(const char *name,int sec)
{
    printf("%s: ",
           name);

    for(int i=0;i<sec;i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    printf(" %sOK%s\n",
           SA_BGREEN,
           SA_RESET);
}



void sa_speed(long mb,int sec)
{
    long total=mb/sec;

    printf("%sSpeed: %ld MB/s%s\n",
           SA_CYAN,
           total,
           SA_RESET);
}



/* =========================
   SYSTEM PLACEHOLDERS
   ========================= */


void sa_cpu(void)
{
    sa_info("CPU monitor");
}



void sa_ram(void)
{
    sa_info("RAM monitor");
}



void sa_disk(void)
{
    sa_info("Disk monitor");
}



void sa_network(void)
{
    sa_info("Network monitor");
}



void sa_monitor(void)
{
    sa_banner("LIBSA MONITOR");

    sa_cpu();
    sa_ram();
    sa_disk();
    sa_network();
}





/* =========================
   CUSTOM ANIMATION API
   ========================= */


void saani(sa_animation anim, uint32_t sec)
{
    switch(anim.type)
    {

        case SA_SPINNER:
            sa_spinner(sec);
            break;


        case SA_DOTS:
            sa_dots(sec);
            break;


        case SA_BAR:
            for(int i=0;i<=100;i++)
            {
                sa_progress_bar(i);
                usleep(30000);
            }
            break;


        case SA_PULSE:
            sa_pulse(sec);
            break;


        case SA_CUSTOM:

            if(anim.frames == NULL)
                break;


            for(uint32_t loop=0;
                loop < (anim.loop ? sec : 1);
                loop++)
            {
                for(uint32_t i=0;
                    i < anim.frame_count;
                    i++)
                {
                    printf("\r%s",
                           anim.frames[i].frame);

                    fflush(stdout);

                    usleep(anim.frames[i].duration_ms*1000);
                }
            }

            printf("\n");

            break;


        default:
            break;
    }
}



/* =========================
   EXTRA DEMO EFFECTS
   ========================= */


void sa_clear(void)
{
    printf("\033[2J\033[H");
}



void sa_center(const char *text)
{
    printf("\n              %s\n",
           text);
}



void sa_logo(void)
{
    printf(
        "%s"
        " ██████╗ ███████╗ █████╗ \n"
        " ██╔══██╗██╔════╝██╔══██╗\n"
        " ██║  ██║███████╗███████║\n"
        " ██║  ██║╚════██║██╔══██║\n"
        " ██████╔╝███████║██║  ██║\n"
        " ╚═════╝ ╚══════╝╚═╝  ╚═╝\n"
        "%s",
        SA_BCYAN,
        SA_RESET
    );
}


