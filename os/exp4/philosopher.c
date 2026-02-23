#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t room;
sem_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&room);
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
        sem_post(&room);
    }

    return NULL;  
}

int main() {
    pthread_t tid[N];
    int phil[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}