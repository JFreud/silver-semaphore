#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>



int main(int argc, char *argv[]) {

  int semid;
  key_t key= ftok ("sema.c", 'J');
  int n;

  errno = 0;

  union semun {
    int val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
  };

  if (argv[1] == NULL) {
    printf("Please enter an argument. Options are c N, v, and r.\n");
    exit(1);
  }


  if (strcmp(argv[1], "-c") == 0) {
    n = atoi (argv[2]);
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (semid == -1) {
      printf("semaphore already exists\n");
      exit(1);
    }
    printf("semaphore created: %d\n", semid);
    if (semctl(semid, 0, SETVAL, n) == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(1);
    }
    printf("value set: %d\n", semctl(semid, 0, GETVAL));

  }

  if (strcmp(argv[1], "-v") == 0) {
    semid = semget(key, 1, 0);
    if (semid == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(1);
    }
    //printf("semid: %d\n", semid);
    int gotval = semctl(semid, 0, GETVAL);
    printf("semaphore value: %d\n", gotval);
  }

  if (strcmp(argv[1], "-r") == 0) {
    semid = semget(key, 1, 0);
    if (semid == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(1);
    }
    int removed = semctl(semid, 0, IPC_RMID);
    if (removed == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(1);
    }
    printf("semaphore removed: %d\n", semid);
  }



  return 0;
}
