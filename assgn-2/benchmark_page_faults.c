#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

#define RUSAGE_THREAD 1
#define RUSAGE_SELF 0
#define NUMBER_OF_THREADS 32

void *print_hello_world(void *tid) {
   printf("Hello World. Greetings from thread %d\n", tid);
   pthread_exit(NULL);
}

int main(int argc, char **argv){
    struct rusage usage; 
    int i, execute;
    pid_t child; 
    char *file[10];
    long pagefault;

    getrusage(RUSAGE_SELF, &usage);

    child = fork();
    
    if(child < 0){
        printf("Error has occurred in forking child process\n");
        printf("pid = %d\n", pid);
        perror("fork: ");
        exit(1);
    } else if(child == 0){
        execute = execvp(file[0], file);

        if(execute < 0){
            perror("Executing error: ");
            exit(1);
        } else {
           pagefault = usage.ru_majflt; 
           printf("Number of page faults: %-10ld\t%s\n", pagefault); 
        }
        exit(0);
    }

    waitpid(child, (void *) 0, 0);


    

    }

}