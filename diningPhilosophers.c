#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define N 5 // number of philosophers and forks

int sem_id; // semaphore set identifier

void grab_forks(int left_fork_id) {
    struct sembuf op[] = {
        { left_fork_id, -1, 0 }, // acquire left fork
        { (left_fork_id + 1) % N, -1, 0 } // acquire right fork
    };
    semop(sem_id, op, 2); // perform both operations atomically
}

void put_away_forks(int left_fork_id) {
    struct sembuf op[] = {
        { left_fork_id, 1, 0 }, // release left fork
        { (left_fork_id + 1) % N, 1, 0 } // release right fork
    };
    semop(sem_id, op, 2); // perform both operations atomically
}

void philosopher(int id) {
    while (1) {
        printf("Philosopher %d is thinking\n", id);
        usleep(random() % 1000000); // simulate thinking
        printf("Philosopher %d is hungry\n", id);
        grab_forks(id);
        printf("Philosopher %d is eating\n", id);
        usleep(random() % 1000000); // simulate eating
        put_away_forks(id);
    }
}

int main() {
    // initialize semaphores
    sem_id = semget(IPC_PRIVATE, N, IPC_CREAT | 0666);
    for (int i = 0; i < N; i++) {
        semctl(sem_id, i, SETVAL, 1); // each semaphore represents a fork
    }
    // create philosopher processes
    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            philosopher(i);
            exit(0);
        }
    }
    // wait for all philosopher processes to finish (should never happen)
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }
    // cleanup semaphores
    semctl(sem_id, 0, IPC_RMID);
    return 0;
}
