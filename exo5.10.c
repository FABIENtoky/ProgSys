#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TAILLE 10

char tampon[TAILLE];
int top = 0;  // prochain indice libre
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_places, sem_objets;

void* producteur(void* arg) {
    int id = *(int*)arg;
    free(arg);
    while (1) {
        char produit = rand() % 256;
        sem_wait(&sem_places);   // attend une place libre
        
        pthread_mutex_lock(&mutex);
        tampon[top++] = produit;
        printf("P%d : produit '%c' (top=%d)\n", id, produit, top);
        pthread_mutex_unlock(&mutex);
        
        sem_post(&sem_objets);   // signale un objet dispo
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* consommateur(void* arg) {
    int id = *(int*)arg;
    free(arg);
    while (1) {
        sem_wait(&sem_objets);   // attend un objet
        
        pthread_mutex_lock(&mutex);
        char produit = tampon[--top];
        printf("C%d : consomme '%c' (top=%d)\n", id, produit, top);
        pthread_mutex_unlock(&mutex);
        
        sem_post(&sem_places);   // signale une place libre
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    sem_init(&sem_places, 0, TAILLE);
    sem_init(&sem_objets, 0, 0);
    
    int N, M;
    printf("Nombre de producteurs : ");
    scanf("%d", &N);
    printf("Nombre de consommateurs : ");
    scanf("%d", &M);
    
    pthread_t producteurs[N], consommateurs[M];
    
    for (int i = 0; i < N; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&producteurs[i], NULL, producteur, id);
    }
    for (int i = 0; i < M; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&consommateurs[i], NULL, consommateur, id);
    }
    
    for (int i = 0; i < N; i++) pthread_join(producteurs[i], NULL);
    for (int i = 0; i < M; i++) pthread_join(consommateurs[i], NULL);
    
    sem_destroy(&sem_places);
    sem_destroy(&sem_objets);
    return 0;
}
