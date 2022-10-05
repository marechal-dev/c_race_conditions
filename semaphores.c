#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#define N 100000000

sem_t mutex;

int globalCounter = 0;

void* parallelIncrement(void* arg);

int main(void) {
  pthread_t threadA;
  pthread_t threadB;

  void* threadResult;

  int threadCreationStatusCode;
  int threadJoinStatusCode;

  sem_init(&mutex, 0, 1);

  threadCreationStatusCode = pthread_create(
    &threadA,
    NULL,
    parallelIncrement,
    (void *)(100000000)
  );
  if (threadCreationStatusCode != 0) {
    printf("Thread A creation failed!\n");
    return -1;
  }

  threadCreationStatusCode = pthread_create(
    &threadB,
    NULL,
    parallelIncrement,
    (void *)(100000000)
  );
  if (threadCreationStatusCode != 0) {
    printf("Thread B creation failed!\n");
    return -1;
  }

  threadJoinStatusCode = pthread_join(threadA, &threadResult);
  if (threadCreationStatusCode != 0) {
    printf("Thread A join failed!\n");
    return -1;
  }
  printf("Thread A execution finished.\n");

  threadJoinStatusCode = pthread_join(threadB, &threadResult);
  if (threadCreationStatusCode != 0) {
    printf("Thread B join failed!\n");
    return -1;
  }
  printf("Thread B execution finished.\n");

  printf("Global Counter value: %d\n", globalCounter);

  if (globalCounter != N * 2) {
    printf("Race Condition!\n");
  } else {
    printf("No Race Condition!\n");
  }

  sem_destroy(&mutex);

  return 0;
}

void* parallelIncrement(void* arg) {
  sem_wait(&mutex);
  
  for (int i = 0; i < N; i++) {
    globalCounter++;
  }

  sem_post(&mutex);

  pthread_exit(
    ((void*)"Returned from Thread!")
  );
}
