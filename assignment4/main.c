#define NB_CHILDREN 8
#define MAX_ITERATIONS 100


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>


void child_routine();
void run(int pid);
void halt(int pid);

int num_iterations;
int status = 0;

int main(int argc, const char * argv[]) {
    pid_t * child_pen = NULL;
    int num_processes = 0;
    while(++num_processes < NB_CHILDREN){
        pid_t pid = fork ();
        if(!pid){
            //Child stuff;
            child_routine(rand() % MAX_ITERATIONS);
            exit(0);
        }
        else{
            if(num_processes == 1){
                child_pen = malloc(NB_CHILDREN * sizeof(pid_t));
            }
            child_pen[num_processes - 1] = pid;
        }
    }
    
    return 0;
}

void parent_routine(pid_t * child_pen, char routine){
    int curr,next = 0;
    int processes_remaining = NB_CHILDREN;
    
    while(processes_remaining>0){
        if(routine == 1){
            //Round Robin
            curr = next;
            if(!(++next<processes_remaining)) next = 0;
        }
        if(routine == 2){
            //Shortest Remaining Time
        }
        if(routine == 3){
            //Priority Scheduling
        }
        
        
    }
}

void child_routine(int num_rand){
    num_iterations = num_rand;
    signal(SIGUSR1,run);
    signal(SIGUSR2,halt);
    while(num_iterations>0){
    }
    exit(0);
}

void run(int pid){
    printf("*** Notified process #%d to run", pid);
    status = 1;
    for (int i=0; i<num_iterations; num_iterations--) {
        if(!status) break;
        printf("/");
        sleep(800);
    }
}

void halt(int pid){
    printf("*** Notified process #%d to stop running", pid);
    status = 0;
}
