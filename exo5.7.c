#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double u = 1.0;
int iterations = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double f1(double x) {
    return (x - 1) * (x - 1) / 4.0;
}

double f2(double x) {
    return (x - 2) * (x - 2) / 6.0;
}

void* thread_f1(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        u = f1(u);
        iterations++;
        printf("T1 : u = %f, itérations = %d\n", u, iterations);
        pthread_mutex_unlock(&mutex);
        
        sleep(rand() % 5 + 1);
    }
    return NULL;
}

void* thread_f2(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        u = f2(u);
        iterations++;
        printf("T2 : u = %f, itérations = %d\n", u, iterations);
        pthread_mutex_unlock(&mutex);
        
        sleep(rand() % 5 + 1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_f1, NULL);
    pthread_create(&t2, NULL, thread_f2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
