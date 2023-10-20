#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s seed arraysize\n", argv[0]);
        return 1;
    }

    int seed = atoi(argv[1]);
    if (seed <= 0) {
        printf("seed is a positive number\n");
        return 1;
    }

    int array_size = atoi(argv[2]);
    if (array_size <= 0) {
        printf("array_size is a positive number\n");
        return 1;
    }

    // Создаем новый процесс
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс

        // Используем системный вызов exec для запуска sequential_min_max
        execl("sequential_min_max", "sequential_min_max", argv[1], argv[2], (char *)NULL);

        // Если execl завершился неудачно, то выведем сообщение об ошибке
        perror("execl");
        return 1;
    } else {
        // Родительский процесс
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
