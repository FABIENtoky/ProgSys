#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int compt = 0;
int limite;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* incrementer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (compt >= limite) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        compt++;
        pthread_mutex_unlock(&mutex);
        
        int attente = rand() % 5 + 1; // 1 à 5 secondes
        sleep(attente);
    }
    return NULL;
}

void* afficher(void* arg) {
    while (1) {
        sleep(2);
        pthread_mutex_lock(&mutex);
        if (compt >= limite) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("Compteur = %d\n", compt);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <limite>\n", argv[0]);
        return 1;
    }
    limite = atoi(argv[1]);
    srand(time(NULL));
    
    pthread_t t1, t2;
    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, afficher, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Limite atteinte !\n");
    return 0;
}
