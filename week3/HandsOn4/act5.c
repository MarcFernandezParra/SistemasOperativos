#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

char* causaDeMort(int causa) {
    return (causa == 0 ? "apunyalat" : "decapitat");
}

int main(int argc, char* argv[]) {

    time_t t;
    char *causaRobb, *causaNed;
    int rickard, ned, robb;

    srand((unsigned) time(&t));

    // Al fer el fork la memòria es duplica, per tant les causes s'han de calcular previament
    // per tal de poder accedir a elles des de tots els processos.
    causaRobb = causaDeMort(rand() % 2);
    causaNed = causaDeMort(rand() % 2);

    printf("Benvinguts a la casa Stark.\n");

    if ((rickard = fork()) == 0) {

        // Rickard Stark
        printf("Hola sóc Rickard Stark casat amb Lyarra Stark amb pid = %d\n", getpid());

        if ((ned = fork()) == 0) {

            // Ned Stark
            printf("Hola sóc en Ned fill del matrimoni del Richard i la Lyarra amb pid = %d\n", getpid());

            if ((robb = fork()) == 0) {

                // Robb Stark
                printf("Hola sóc en Robb Stark amb pid = %d, soc un fill del matrimoni de la Catelyn Stark i Ned Stark.\n", getpid());
                printf("Soc en Robb amb pid = %d i he estat %s\n", getpid(), causaRobb);

            } else {

                // Mort Ned
                waitpid(robb, 0, WUNTRACED);
                printf("Sóc en Ned amb pid = %d i m’acaben de %s\n", getpid(), causaNed);
                exit(0);

            }

        } else {

            // Mort Ricard
            waitpid(ned, 0, WUNTRACED);
            printf("En resum el meu fill Robb ha estat %s, en Ned %s i jo en Rickard amb pid = %d i m’han executat.\n", causaRobb, causaNed, getpid());
            exit(0);

        }

    } else {

        wait(NULL);
        printf("The winter is coming!!!!!\n");

    }

}