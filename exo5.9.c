#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

char buffer = 0;
sem_t sem_vide, sem_remplie;

void* emetteur(void* arg) {
    for (int i = 0; i < 10; i++) {
        char c = 'A' + (rand() % 26);
        sem_wait(&sem_vide);   // attend que la place soit libre
        buffer = c;
        printf("Emetteur : envoie '%c'\n", c);
        sem_post(&sem_remplie); // signale donnée disponible
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* recepteur(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&sem_remplie); // attend donnée
        char c = buffer;
        printf("Recepteur : recoit '%c'\n", c);
        sem_post(&sem_vide);    // signale place libre
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    sem_init(&sem_vide, 0, 1);
    sem_init(&sem_remplie, 0, 0);
    
    pthread_t th_em, th_re;
    pthread_create(&th_em, NULL, emetteur, NULL);
    pthread_create(&th_re, NULL, recepteur, NULL);
    
    pthread_join(th_em, NULL);
    pthread_join(th_re, NULL);
    
    sem_destroy(&sem_vide);
    sem_destroy(&sem_remplie);
    return 0;
}
