#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char **argv) {
   struct rusage usage;
   struct timeval start, end;
   int status, i, temp;
   //start time stamp
   getrusage(RUSAGE_SELF, &usage);
   start = usage.ru_utime;
   
   //execute process
   pid_t pid = fork();
   char *bin[10];
   int bincount = 0;
   //bin[0] = 
   if(pid < 0) {//error detected
      printf("Error has occurred in forking child process\n");
      printf("pid = %d\n", pid);
      perror("fork");
      exit(1);
   }   
   else if(pid == 0) { //child process
      if(execvp(bin[0], bin) < 0) {
         printf("Error has occurred executing the command: %s\n", argv[0]);
         perror("command");
         exit(1);
      }
      exit(0);
   }
   //parent process
   waitpid(pid, (void *) 0, 0);
   
   char cwd[100];
   if (getcwd(cwd, sizeof(cwd)) == NULL) {
       printf("Error: cwd is null\n");
   }
   

   //end time stamp
   getrusage(RUSAGE_SELF, &usage);
   end = usage.ru_utime;
   printf("Started at: %ld.%06ds\n", start.tv_sec, start.tv_usec);
   printf("Ended at: %ld.%06ds\n", end.tv_sec, end.tv_usec);
   if(status != 0) {
      printf("Error occurred: code = %d\n", status);
      exit(-1);
   }
   exit(0);
}
