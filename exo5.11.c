#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define TAILLE 15

char base[TAILLE] = {0};
int lecteurs = 0;
pthread_mutex_t mutex_lecteurs = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_ecriture = PTHREAD_MUTEX_INITIALIZER;

void* lecteur(void* arg) {
    int id = *(int*)arg;
    free(arg);
    while (1) {
        // Demande d'accès en lecture
        pthread_mutex_lock(&mutex_lecteurs);
        lecteurs++;
        if (lecteurs == 1) pthread_mutex_lock(&mutex_ecriture); // 1er lecteur bloque l'écriture
        pthread_mutex_unlock(&mutex_lecteurs);
        
        // Lecture
        int pos = rand() % TAILLE;
        printf("L%d : lit base[%d] = %d\n", id, pos, base[pos]);
        
        // Fin lecture
        pthread_mutex_lock(&mutex_lecteurs);
        lecteurs--;
        if (lecteurs == 0) pthread_mutex_unlock(&mutex_ecriture); // dernier lecteur libère
        pthread_mutex_unlock(&mutex_lecteurs);
        
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* redacteur(void* arg) {
    int id = *(int*)arg;
    free(arg);
    while (1) {
        pthread_mutex_lock(&mutex_ecriture); // un seul écrivain à la fois
        
        int pos = rand() % TAILLE;
        char val = rand() % 256;
        base[pos] = val;
        printf("R%d : ecrit base[%d] = %d\n", id, pos, val);
        
        pthread_mutex_unlock(&mutex_ecriture);
        
        sleep(rand() % 10 + 1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    int N, M;
    printf("Nombre de lecteurs : ");
    scanf("%d", &N);
    printf("Nombre de redacteurs : ");
    scanf("%d", &M);
    
    pthread_t lecteurs_th[N], redacteurs_th[M];
    
    for (int i = 0; i < N; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&lecteurs_th[i], NULL, lecteur, id);
    }
    for (int i = 0; i < M; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&redacteurs_th[i], NULL, redacteur, id);
    }
    
    for (int i = 0; i < N; i++) pthread_join(lecteurs_th[i], NULL);
    for (int i = 0; i < M; i++) pthread_join(redacteurs_th[i], NULL);
    
    return 0;
}