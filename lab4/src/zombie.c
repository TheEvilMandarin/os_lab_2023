#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Ошибка при создании процесса
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Родительский процесс, PID: %d\n", getpid());
        printf("Дочерний процесс, PID: %d\n", pid);

        // Ждем 10 секунд до вызова wait()
        sleep(10);

        // Очищаем зомби-процесс
        wait(NULL);
        printf("Дочерний процесс был очищен\n");
    } else {
        // Дочерний процесс
        printf("Дочерний процесс, PID: %d\n", getpid());
        exit(0);  // Завершаем дочерний процесс
    }

    return EXIT_SUCCESS;
}

// ps -e -o pid,ppid,state,cmd | grep 'Z'