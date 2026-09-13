#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    printf("AIOS Process Manager Started\n");

    for (int i = 1; i <= 3; i++) {

        pid_t pid = fork();

        if (pid < 0) {
            printf("Process creation failed!\n");
            return 1;
        }

        if (pid == 0) {
            printf("Child %d created\n", i);
            printf("Child PID: %d\n", getpid());
            printf("Parent PID: %d\n", getppid());

            return 0;
        }
    }

    int status;

    for (int i = 1; i <= 3; i++) {
        pid_t child = wait(&status);

        if (child > 0) {
            printf("Child PID %d terminated\n", child);
        }
    }

    printf("All child processes finished.\n");

    return 0;
}