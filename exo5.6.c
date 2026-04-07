#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100

double tableau[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* modifier(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        for (int i = 1; i <= 98; i++) {
            tableau[i] = (tableau[i-1] + tableau[i]) / 3.0;
        }
        pthread_mutex_unlock(&mutex);
        
        int attente = rand() % 3 + 1; // 1 à 3 secondes
        sleep(attente);
    }
    return NULL;
}

void* afficher(void* arg) {
    while (1) {
        sleep(4);
        pthread_mutex_lock(&mutex);
        printf("Tableau : ");
        for (int i = 0; i < N; i++) {
            printf("%.2f ", tableau[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    tableau[0] = 0.0;
    tableau[N-1] = 0.0;
    for (int i = 1; i <= N-2; i++) {
        tableau[i] = (rand() % 10000) / 100.0; // entre 0 et 100
    }
    
    pthread_t t1, t2;
    pthread_create(&t1, NULL, modifier, NULL);
    pthread_create(&t2, NULL, afficher, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
