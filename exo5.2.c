#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int* tableau;
    int taille;
} TableauRetour;

void* generer_tableau(void* arg) {
    int taille = *(int*)arg;
    int* tab = malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++) {
        tab[i] = rand() % 100;
    }
    TableauRetour* res = malloc(sizeof(TableauRetour));
    res->tableau = tab;
    res->taille = taille;
    return (void*)res;
}

int main() {
    srand(time(NULL));
    int taille = 10;
    pthread_t thread;
    pthread_create(&thread, NULL, generer_tableau, &taille);
    TableauRetour* resultat;
    pthread_join(thread, (void**)&resultat);
    
    for (int i = 0; i < resultat->taille; i++) {
        printf("%d ", resultat->tableau[i]);
    }
    printf("\n");
    
    free(resultat->tableau);
    free(resultat);
    return 0;
}
