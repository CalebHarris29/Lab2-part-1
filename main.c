#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    int value = 13;

    printf("Before fork. Parent pid = %d\n", getpid());

    pid = fork();

    // Check for error
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    // Both processes execute the same loop
    for (int i = 0; i < 8; i++) {
        printf("This line is from pid %d, value %d\n", getpid(), value + i);
        sleep(1);
    }

    return 0;
}
