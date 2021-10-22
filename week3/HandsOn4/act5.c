#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

char* causaDeMort(int causa) {
    return (causa == 0 ? "apunyalat" : "decapitat");
}

int main(int argc, char* argv[]) {

    time_t t;
    int rickard, ned, robb, statusNed, statusRobb;
    
    
    // Al fer el fork la memòria es duplica, per tant les causes s'han de calcular previament
    // per tal de poder accedir a elles des de tots els processos.

    printf("Benvinguts a la casa Stark.\n");

    if ((rickard = fork()) == 0) {
        
        // Rickard Stark
        printf("Hola sóc Rickard Stark casat amb Lyarra Stark amb pid = %d\n", getpid());

        if ((ned = fork()) == 0) {

            // Ned Stark
            printf("Hola sóc en Ned fill del matrimoni del Richard i la Lyarra amb pid = %d\n", getpid());

            if ((robb = fork()) == 0) {
                // Robb Stark
                srand(robb);
                int cause =rand() % 2;
                printf("Hola sóc en Robb Stark amb pid = %d, soc un fill del matrimoni de la Catelyn Stark i Ned Stark.\n", getpid());
                printf("Soc en Robb amb pid = %d i he estat %s\n", getpid(), causaDeMort(cause));
                exit(cause);
            } else {
                // Mort Ned
                srand(robb);
                int cause = rand() % 2;
                char concat[3];
                char robDed[1];
                
                waitpid(robb, &statusRobb, WUNTRACED);                
                char robbChar[2];
                sprintf(robbChar, "%d", statusRobb>>8);

                char nedChar[2];
                sprintf(nedChar, "%d", cause);
                concat[0] = robbChar[0];
                concat[1] = nedChar[0];
                concat[2] = nedChar[1];
                

                printf("Sóc en Ned amb pid = %d i m’acaben de %s\n", getpid(), causaDeMort(cause));
                
                int returnExit = atoi(concat);
                fflush(stdout);
                exit(returnExit);

            }

        } else {
            // Mort Ricard
            waitpid(ned, &statusNed, WUNTRACED);
            
            char exitCodeStr[3];
            char arrayRob[2];
            char arrayNed[2];
            sprintf(exitCodeStr, "%d", statusNed>>8);
            exitCodeStr[2] = '\0';
            arrayRob[0] = exitCodeStr[0];
            arrayRob[1] = '\0';
            arrayNed[0] = exitCodeStr[1];
            arrayNed[1] = '\0';
            int exitCodeRobb = atoi(arrayRob);
            int exitCodeNed = atoi(arrayNed);
            printf("En resum el meu fill Robb ha estat %s, en Ned %s i jo en Rickard amb pid = %d i m’han executat.\n", causaDeMort(exitCodeRobb), causaDeMort(exitCodeNed), getpid());
            exit(0);

        }

    } else {

        waitpid(rickard, 0, WUNTRACED);
        printf("The winter is coming!!!!!\n");

    }

}
