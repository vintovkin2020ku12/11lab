#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

char* message;
/*
    The OPTIONAL parent SIGALRM handler. Does nothing useful apart from logging the SIGALRM received from the child.
*/
void parent_alrm_handler(int signo) {
    printf("Parent proc caught alrm signal\n");
    return;
}

/*
    The child SIGKILL handler.Replays the SIGALRM back to the parent when it receives it.
*/
void child_alrm_handler(int signo){
    printf("sending kill SIGKILLto the parent %d\n", getppid());
    kill(getppid(), SIGKILL);
}

/*
    Since each proc has single timer. I create child proceses when the req for new alarms is made.
*/
void set_alarm(int secs){
    signal(SIGALRM, parent_alrm_handler);
    if( fork() == 0 ){
        signal(SIGALRM, child_alrm_handler);
        alarm(secs);
        pause();
        printf ("message = %s\n", message);
        exit(0);        
    }   
}

int main(int argc, char** argv) {
    if(argc != 3){
        printf("Enter 2 arguments(sec, message)");
        return 0;
    }
    message = argv[2];
    set_alarm(atoi(argv[1])); //alarm sec         
    for(;;)
        pause();
    return 0;
}