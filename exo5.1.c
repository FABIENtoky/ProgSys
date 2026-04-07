#include <stdio.h>
#include <pthread.h>

void* afficher_tableau(void* arg) {
    int* tab = (int*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    return NULL;
}

int main() {
    int tab[] = {10, 20, 30, 40, 50};
    pthread_t thread;
    pthread_create(&thread, NULL, afficher_tableau, tab);
    pthread_join(thread, NULL);
    return 0;
}
