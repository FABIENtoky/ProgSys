#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_T1, sem_T2;

void* T1(void* arg) {
    for (int i = 0; i < 10; i++) {
        printf("T1 : début traitement %d\n", i);
        sleep(2); // traitement de 2 secondes
        printf("T1 : fin traitement, attend T2\n");
        sem_post(&sem_T1);   // signale à T2 que T1 est prêt
        sem_wait(&sem_T2);   // attend T2
        printf("T1 : rendez-vous %d terminé\n", i);
    }
    return NULL;
}

void* T2(void* arg) {
    for (int i = 0; i < 10; i++) {
        int duree = rand() % 6 + 4; // 4 à 9 secondes
        printf("T2 : début traitement %d (%d sec)\n", i, duree);
        sleep(duree);
        printf("T2 : fin traitement, attend T1\n");
        sem_post(&sem_T2);   // signale à T1 que T2 est prêt
        sem_wait(&sem_T1);   // attend T1
        printf("T2 : rendez-vous %d terminé\n", i);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    sem_init(&sem_T1, 0, 0);
    sem_init(&sem_T2, 0, 0);
    
    pthread_t th1, th2;
    pthread_create(&th1, NULL, T1, NULL);
    pthread_create(&th2, NULL, T2, NULL);
    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    
    sem_destroy(&sem_T1);
    sem_destroy(&sem_T2);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int N;
int arrive_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_rendezvous;

void* travail(void* arg) {
    int id = *(int*)arg;
    free(arg);
    
    for (int i = 0; i < 10; i++) {
        int duree = rand() % 5 + 1; // 1 à 5 secondes
        printf("Thread %d : début itération %d (%d sec)\n", id, i, duree);
        sleep(duree);
        
        // Rendez-vous
        pthread_mutex_lock(&mutex);
        arrive_count++;
        if (arrive_count == N) {
            arrive_count = 0;
            for (int j = 0; j < N-1; j++) sem_post(&sem_rendezvous);
        } else {
            pthread_mutex_unlock(&mutex);
            sem_wait(&sem_rendezvous);
            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&mutex);
        
        printf("Thread %d : itération %d terminée\n", id, i);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    srand(time(NULL));
    
    sem_init(&sem_rendezvous, 0, 0);
    
    pthread_t threads[N];
    for (int i = 0; i < N; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, travail, id);
    }
    
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&sem_rendezvous);
    return 0;
}
