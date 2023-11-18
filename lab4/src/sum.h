#ifndef SUM_H
#define SUM_H

struct SumArgs {
  int *array;
  int begin;
  int end;
};

// Функция для подсчета суммы элементов массива
int Sum(const struct SumArgs *args);

#endif // SUM_H