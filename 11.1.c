#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

static void signal_handler(int signo) {
    if (signo == SIGINT)
        printf("Захвачен сигнал SIGINT!\n");
    else if (signo == SIGTERM)
        printf("Захвачен сигнал SIGTERM!\n");
    else if(signo == SIGUSR1)
        printf("Завершение работы програмы!\n");
    else {
    /* это никогда не должно случаться */
    fprintf(stderr, "Неожиданный сигнал!\n");
    exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main (void) {

/*
* Регистрируем signal_handler нак наш обработчик сигнала
* для SIGINT. */
if (signal(SIGINT, signal_handler) == SIG_ERR) {
    fprintf(stderr, "Невозможно обработать SIGINT!\n");
    exit(EXIT_FAILURE);
}
/*
* Регистрируем signal_handler как наш обработчик сигнала
* для SIGTERM. */
if (signal(SIGTERM, signal_handler) == SIG_ERR) {
    fprintf(stderr, "Невозможно обработать SIGTERM!\n");
    exit(EXIT_FAILURE);
}
/* Восстановление поведения по умолчание для сигнала SIGPROF. */
if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
    fprintf(stderr, "Невозможно сбросить SIGPROF!\n");
    exit(EXIT_FAILURE);
}
/* Игнорировать SIGHUP. */
if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
    fprintf(stderr, "Невозможно игнорировать SlGHUP!\n");
    exit(EXIT_FAILURE);
}
/*завершение работы*/
if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
    fprintf(stderr, "Невозможно завершить работу SIGUSR1!\n");
    exit(EXIT_FAILURE);
}
//kill(getpid(), SIGINT);
//kill(getpid(), SIGTERM);
//kill(getpid(), SIGPROF);
kill(getpid(), SIGHUP);
//kill(getpid(), SIGUSR1);
    for (;;)
        pause();
return 0;
}