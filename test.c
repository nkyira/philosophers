#include <pthread.h>
#include <stdio.h>

void *func(void *arg) {
    printf("Hello from thread\n");
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, func, NULL);
    pthread_join(t, NULL);
    return 0;
}
