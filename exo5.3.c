#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int* tableau;
    int nb_elements;
    int x;
} TypeTableau;

void* generer_tableau(void* arg) {
    TypeTableau* tt = (TypeTableau*)arg;
    tt->tableau = malloc(tt->nb_elements * sizeof(int));
    for (int i = 0; i < tt->nb_elements; i++) {
        tt->tableau[i] = rand() % 100;
    }
    return NULL;
}

void* rechercher_x(void* arg) {
    TypeTableau* tt = (TypeTableau*)arg;
    for (int i = 0; i < tt->nb_elements; i++) {
        if (tt->tableau[i] == tt->x) {
            return (void*)1;
        }
    }
    return (void*)0;
}

int main() {
    srand(time(NULL));
    int taille;
    printf("Nombre d'éléments : ");
    scanf("%d", &taille);
    
    TypeTableau tt;
    tt.nb_elements = taille;
    
    pthread_t gen_thread;
    pthread_create(&gen_thread, NULL, generer_tableau, &tt);
    
    printf("Entrez x : ");
    scanf("%d", &tt.x);
    
    pthread_join(gen_thread, NULL);
    
    pthread_t search_thread;
    pthread_create(&search_thread, NULL, rechercher_x, &tt);
    int* result;
    pthread_join(search_thread, (void**)&result);
    
    printf("%d\n", (int)result);
    
    free(tt.tableau);
    return 0;
}
