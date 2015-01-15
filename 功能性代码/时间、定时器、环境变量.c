获取当前时间

使用gmtime

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

/*
 * 获取现在的时间
 */
int main(int argc, const char *argv[])
{
    time_t tt;
    tt = time(NULL);
    struct tm *p_tm = gmtime(&tt);
    printf("%04d-%02d-%02d %02d-%02d-%02d\n",
            1900 + p_tm->tm_year,
            1 + p_tm->tm_mon,
            p_tm->tm_mday,
            8 + p_tm->tm_hour,
            p_tm->tm_min,
            p_tm->tm_sec);
    return 0;
}





使用ctime

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    time_t tt;
    time(&tt);
    printf("%s\n", ctime(&tt));
    return 0;
}


定时器

第一种方法alarm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int sig)
{
    printf("BEEP\n");
    alarm(1);
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
        ERR_EXIT("signal");

    alarm(3);

    for(;;)
        pause();

    return 0;
}



第二种方法setitimer


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int sig)
{
    printf("recv SIGALRM\n");
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
        ERR_EXIT("signal");

    struct timeval tv_interval = {1, 0};
    struct timeval tv_value = {1, 0};
    struct itimerval it;
    it.it_interval = tv_interval;
    it.it_value = tv_value;
    setitimer(ITIMER_REAL, &it, NULL);

    for(;;)
        pause();
    return 0;
}



获取环境变量

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int i;
    for(i = 0; environ[i] != NULL; ++i)
    {
        printf("%d : %s\n", i, environ[i]);
    }
    return 0;
}

获取某一项全局变量
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    printf("%s\n", getenv("SHELL"));
    return 0;
}




获取命令行选项

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, char * const argv[])
{
    int opt;
    while(1){
        opt = getopt(argc, argv, "nt:");
        if(opt == '?'){
            exit(EXIT_FAILURE);    
        }
        if(opt == -1){
            break;
        }
        switch (opt){
            case 'n':
                printf("-n\n");
                break;
            case 't':
                printf("-t %d\n", atoi(optarg));
                break;
        }
    }
    return 0;
}
