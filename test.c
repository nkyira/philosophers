#include <pthread.h>
#include <stdio.h>

void *my_func(void *arg) {
    pthread_t my_id = pthread_self(); // get current thread ID
    printf("Thread ID: %lu\n", (unsigned long)my_id);
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, my_func, NULL);
    pthread_join(tid, NULL);
    return 0;
}
