#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 32
void *matrixThread() {
   int i, j, k, redo;
   int size = 128;
   double A[size][size];
   double B[size][size];
   double C[size][size];
   printf("Initializing Matrices...\n");
   for(i = 0; i < size; i++) {
      for(j = 0; j < size; j++) {
         A[i][j] = rand();
         B[i][j] = rand();
         C[i][j] = 0;
      }
   }
   printf("Computing matrix multiplication...\n");
   for(redo = 0; redo < 100; redo++) {
      for(i = 0; i < size; i++) {
         for(j = 0; j < size; j++) {
            for(k = 0; k < size; k++) {
               C[i][j] += A[i][k] * B[k][j];
            }
         }
      }
   }
   printf("Done computing matrix multiplication\n");
   return NULL;
}

void *printThread() {
   int i, j = 1;
   for(i = 0; i < 10000; i++) {
      if(j > 10) {
         j = 1;
         //printf("\n");
      }
      j++;
      //printf("  %d  ", i);
   }
   //printf("\n");
   return NULL;
}

/* void *getCpuMat(){
   struct rusage usage;
   struct timeval start, end;
   int status = 0;
   pthread_t id;
   printf("***getCpuMat()***\n");
   //start time stamp
   getrusage(RUSAGE_SELF, &usage);
   start = usage.ru_utime;
   //execute process
   pthread_create(&id, NULL, matrixThread, NULL);
   pthread_join(id, NULL);
   //end time stamp
   getrusage(RUSAGE_SELF, &usage);
   end = usage.ru_utime;
   printf("Started at: %ld.%06ds\n", start.tv_sec, start.tv_usec);
   printf("Ended at: %ld.%06ds\n", end.tv_sec, end.tv_usec);
   if(status != 0) {
      printf("Error occurred: code = %d\n", status);
      exit(-1);
   }
   return NULL;
}
void *getCpuPrint(){
   struct rusage usage;
   struct timeval start, end;
   int status = 0;
   pthread_t id;
   printf("***getCpuPrint()***\n");
   //start time stamp
   getrusage(RUSAGE_SELF, &usage);
   start = usage.ru_utime;
   //execute process
   pthread_create(&id, NULL, printThread, NULL);
   pthread_join(id, NULL);
   //end time stamp
   getrusage(RUSAGE_SELF, &usage);
   end = usage.ru_utime;
   printf("Started at: %ld.%06ds\n", start.tv_sec, start.tv_usec);
   printf("Ended at: %ld.%06ds\n", end.tv_sec, end.tv_usec);
   if(status != 0) {
      printf("Error occurred: code = %d\n", status);
      exit(-1);
   }
   return NULL;
}

void *getPageFault(){
    struct rusage usage; 
    pthread_t id; 
    printf("NumberOfPageFaults");


}
*/

int main() {
    struct rusage usage; 
    struct timeval start, end; 
    pthread_t threads[NUMBER_OF_THREADS];
    int i, status;
    long pagefault;
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for(i = 0; i < NUMBER_OF_THREADS; i++){
        status = pthread_create(&threads[i], NULL, matrixThread, NULL);
        if(status != 0){
            printf("Error occurred: code = %d\n", status);
            exit(-1);
        }

        pthread_join(&threads[i], NULL);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    pagefault = usage.ru_majflt; 
    printf("\nStarted at: %ld.%06ds\n", start.tv_sec, start.tv_usec);
    printf("\nEnded at: %ld.%06ds\n", end.tv_sec, end.tv_usec);
    printf("\nNumber of Page Faults: %ld\n", pagefault);
   exit(0);
}
