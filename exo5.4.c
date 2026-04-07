#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int* tableau;
    int taille;
} Tableau;

void* generer_tableau(void* arg) {
    Tableau* t = (Tableau*)arg;
    t->tableau = malloc(t->taille * sizeof(int));
    for (int i = 0; i < t->taille; i++) {
        t->tableau[i] = rand() % 100;
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    Tableau T1, T2;
    T1.taille = 3;
    T2.taille = 10;
    
    pthread_t t1, t2;
    pthread_create(&t1, NULL, generer_tableau, &T1);
    pthread_create(&t2, NULL, generer_tableau, &T2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // Affichage pour vérifier
    printf("T1 : ");
    for (int i = 0; i < T1.taille; i++) printf("%d ", T1.tableau[i]);
    printf("\nT2 : ");
    for (int i = 0; i < T2.taille; i++) printf("%d ", T2.tableau[i]);
    printf("\n");
    
    free(T1.tableau);
    free(T2.tableau);
    return 0;
}

int est_inclus(Tableau* T1, Tableau* T2) {
    for (int i = 0; i < T1->taille; i++) {
        int trouve = 0;
        for (int j = 0; j < T2->taille; j++) {
            if (T1->tableau[i] == T2->tableau[j]) {
                trouve = 1;
                break;
            }
        }
        if (!trouve) return 0;
    }
    return 1;
}

volatile int arret = 0;

void* attendre_touche(void* arg) {
    char c = getchar();
    if (c == 'A') {
        printf("Annulation demandée par l'utilisateur.\n");
        arret = 1;
        exit(0);
    }
    return NULL;
}

void* generer_tableau(void* arg) {
    Tableau* t = (Tableau*)arg;
    t->tableau = malloc(t->taille * sizeof(int));
    for (int i = 0; i < t->taille && !arret; i++) {
        t->tableau[i] = rand() % 100;
    }
    return NULL;
}