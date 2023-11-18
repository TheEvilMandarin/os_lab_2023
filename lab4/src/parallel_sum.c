#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <sys/time.h>
#include "sum.h"
#include "utils.h"

pthread_mutex_t lock;

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  int sum = Sum(sum_args);
  return (void *)(size_t)sum;
}

int main(int argc, char **argv) {
  if (argc < 7) {
        fprintf(stderr, "Usage: %s --threads_num <num> --seed <num> --array_size <num>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int threads_num = 0;
    int seed = 0;
    int array_size = 0;

    // Разбор аргументов командной строки
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--threads_num") == 0) {
            threads_num = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--seed") == 0) {
            seed = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--array_size") == 0) {
            array_size = atoi(argv[i + 1]);
        }
    }

    pthread_t threads[threads_num];
    struct SumArgs args[threads_num];
    int *array = malloc(sizeof(int) * array_size);
    GenerateArray(array, array_size, seed);

    int part_size = array_size / threads_num;

    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    // Создание потоков
    for (int i = 0; i < threads_num; i++) {
        args[i].array = array;
        args[i].begin = i * part_size;
        args[i].end = (i == threads_num - 1) ? array_size : (i + 1) * part_size;
        if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
            fprintf(stderr, "Error: pthread_create failed!\n");
            exit(EXIT_FAILURE);
        }
    }

    int total_sum = 0;
    void *sum;
    for (int i = 0; i < threads_num; i++) {
        pthread_join(threads[i], &sum);
        total_sum += (int)(size_t)sum;
    }

    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    long long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + end_time.tv_usec - start_time.tv_usec;


    printf("Total: %d\n", total_sum);
    printf("Elapsed time: %lld microseconds\n", elapsed_time);

    free(array);
    return 0;
}
