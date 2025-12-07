#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void child_work() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    // Seed random for this child (use pid so children differ)
    srandom(time(NULL) ^ (pid << 16));

    int iterations = (int)(random() % 30) + 1;   // 1–30 loops

    for (int i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", pid);

        int sleep_time = (int)(random() % 10) + 1;  // 1–10 seconds
        sleep(sleep_time);

        // Parent might change (if parent exits), so refresh ppid each time
        ppid = getppid();
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",
               pid, ppid);
    }

    // Child terminates cleanly
    exit(0);
}

int main(void) {
    pid_t child1, child2;
    int status;

    // Fork first child
    child1 = fork();
    if (child1 < 0) {
        perror("fork for child1 failed");
        exit(1);
    } else if (child1 == 0) {
        // In first child
        child_work();
    }

    // Fork second child (only in parent)
    child2 = fork();
    if (child2 < 0) {
        perror("fork for child2 failed");
        exit(1);
    } else if (child2 == 0) {
        // In second child
        child_work();
    }

    // Parent waits for both children
    pid_t finished_pid;
    for (int i = 0; i < 2; i++) {
        finished_pid = wait(&status);
        if (finished_pid > 0) {
            printf("Child Pid: %d has completed\n", finished_pid);
        }
    }

    return 0;
}


