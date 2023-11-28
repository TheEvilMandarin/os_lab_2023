#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Глобальные переменные
pthread_mutex_t mutex;
long long result = 1; // Инициализируем результат значением 1
int k, pnum, mod;

// Функция, которую будут выполнять потоки
void* computeFactorial(void* arg) {
    int start = *((int*)arg);
    long long localResult = 1;
    
    for (int i = start; i <= k; i += pnum) {
        localResult = (localResult * i) % mod;
    }
    
    // Захватываем мьютекс для обновления глобального результата
    pthread_mutex_lock(&mutex);
    result = (result * localResult) % mod;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        printf("Использование: %s -k <число> --pnum=<количество потоков> --mod=<модуль>\n", argv[0]);
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0) {
            k = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--pnum") == 0) {
            pnum = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--mod") == 0) {
            mod = atoi(argv[i + 1]);
        }
    }
    
    pthread_t threads[pnum];
    int threadIds[pnum];
    
    pthread_mutex_init(&mutex, NULL);
    
    // Создаем потоки
    for (int i = 0; i < pnum; i++) {
        threadIds[i] = i + 1;
        pthread_create(&threads[i], NULL, computeFactorial, &threadIds[i]);
    }
    
    // Ждем завершения потоков
    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("%d! mod %d = %lld\n", k, mod, result);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
