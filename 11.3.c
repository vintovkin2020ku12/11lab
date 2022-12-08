#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
       
static void signal_handler(int);
int i, pid1, pid2, status;
 
int main( int argc, char *argv[]){
    if( signal( SIGUSR1, signal_handler) == SIG_ERR  ){
        printf("Pærent: Unable to create handler for SIGUSR1\n");
    }
 
 
    printf( "Parent pid = %d\n", pid1=getpid() );
 
    if( (pid2 = fork()) == 0 ){
        printf( "Child pid = %d\n", getpid() );
        printf( "Child %d: sending parent %d SIGUSR1 \n", getpid(), pid1); 
        sleep(5);
        kill( pid1, SIGUSR1 );
   
        for( ;; ); /* loop forever */
 
    } else {
        wait(&status);
       
        if( WIFEXITED( status ) )
        {
            printf( "Child return - %d\n", WEXITSTATUS( status ) );
        }
        else
        {
            /* Well it didn't exit properly.  Was it a signal? */
            if( WIFSIGNALED( status ) )
            {
                /* 
                 * Yes. A signal killed the child process.  Now we can extract
                 * the signal information from status
                 */
                printf( "Child died on signal - %d\n", WTERMSIG( status ));
            }
        }
    }
 
    return 0;
}
 
static void signal_handler(int signo){
 
    /* signo contains the signal number that was received */
    switch( signo ){
        /* Signal is a SIGUSR1 */
        case SIGUSR1:
            printf( "Process %d: received SIGUSR1 \n", getpid() );
            if(pid1==getpid()) /* it is the parent */
            {
             printf( "Process %d (it is the parent) send SIGUSR1 to %d...\n", getpid(),pid2 );
             kill( pid2, SIGUSR1 );
            }
            else /* it is the child */
            {
              printf( "Process %d send SIGUSR2 to %d...\n", getpid(), pid1 );
              kill(pid1, SIGUSR2);
            }
        break;
        
        /*  It's a SIGUSR2 */
        case SIGUSR2:
            printf( "Process %d: received SIGUSR2 \n", getpid() );
            if(pid1==getpid())
            {
             printf( "Process %d (it is the parent) send SIGUSR2 to %d...\n", getpid(),pid2 );
             kill( pid2, SIGUSR2 );
            }
            else /* it is the child */
            {
              printf( "Process %d will terminate itself using SIGINT\n", getpid());
              kill(getpid(), SIGINT);
              exit(0); //don't work
            }
        break;
 
        default:
        break;
    }
    return;
}