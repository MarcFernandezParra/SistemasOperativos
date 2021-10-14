#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

int main () {
    pid_t p1 = fork();
    if (p1 == 0) {
        printf("Hola sóc el procés fill\n");
    } else {
        wait(NULL);
        printf("Hola sóc el procés pare\n");
    }
}