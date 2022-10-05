#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100000000

int turn;
int interestedThread[2];
int globalCounter = 0;

void* parallelIncrementA(void* arg);
void* parallelIncrementB(void* arg);

int main(void) {
  pthread_t threadA;
  pthread_t threadB;

  void* threadResult;

  int threadCreationStatusCode;
  int threadJoinStatusCode;

  threadCreationStatusCode = pthread_create(
    &threadA,
    NULL,
    parallelIncrementA,
    (void *)(N)
  );
  if (threadCreationStatusCode != 0) {
    printf("Thread A creation failed!\n");
    return -1;
  }

  threadCreationStatusCode = pthread_create(
    &threadB,
    NULL,
    parallelIncrementB,
    (void *)(N)
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
    printf("Now there is no Race Condition!");
  }

  return 0;
}

void* parallelIncrementA(void* arg) {
  while(1) {
    interestedThread[0] = 1;
    turn = 1;
    while(interestedThread[1] && turn == 1);
    for (int i = 0; i < N; i++) {
      globalCounter++;
    }
    interestedThread[0] = 0;
    pthread_exit(
      ((void*)"Returned from Thread!")
    );
  }
}

void* parallelIncrementB(void* arg) {
  while(1) {
    interestedThread[1] = 1;
    turn = 0;
    while(interestedThread[0] && turn == 0);
    for (int i = 0; i < N; i++) {
      globalCounter++;
    }
    interestedThread[1] = 0;
    pthread_exit(
      ((void*)"Returned from Thread!")
    );
  }
}