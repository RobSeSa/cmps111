#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#define RUSAGE_THREAD 1
#define RUSAGE_SELF 0
#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid) {
   printf("Hello World. Greetings from thread %d\n", tid);
   pthread_exit(NULL);
}

void *loopdumb(void *tid) {
   int i, j, k = 0;
   for(i = 0; i < 10000; i++) {
      for (j = 0; j < 10000; j++) {
         k += 20;
      }
   }
   pthread_exit(NULL);
}

int main(int argc, char **argv) {
   struct rusage usage;
   struct timeval start, end;
   pthread_t threads[NUMBER_OF_THREADS];
   int status, i, temp;

   for(i = 0; i < NUMBER_OF_THREADS; i++) {
      printf("Main here. Creating thread %d\n", i);
      getrusage(RUSAGE_SELF, &usage);
      start = usage.ru_utime;
      status = pthread_create(&threads[i], NULL, print_hello_world, (void *) i);
      //status = pthread_create(&threads[i], NULL, loopdumb, (void *) i);
      temp = pthread_join(threads[i], NULL);
      if(temp == 0) {
         getrusage(RUSAGE_SELF, &usage);
         end = usage.ru_utime;
      }
      printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
      printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
      if(status != 0) {
         printf("Error occurred: code = %d\n", status);
         exit(-1);
      }
   }
   exit(NULL);
}
