#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_COUNT 200

void ParentProcess(void) {
    for (int i = 0; i < MAX_COUNT; i++) {
        printf("Parent Process: pid=%d, value=%d\n", getpid(), i);
        usleep(10000);
    }
}

void ChildProcess(void) {
    for (int i = 0; i < MAX_COUNT; i++) {
        printf("Child Process: pid=%d, value=%d\n", getpid(), i);
        usleep(10000);
    }
}

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child code
        ChildProcess();
    } else {
        // Parent code
        ParentProcess();
    }

    return 0;
}
