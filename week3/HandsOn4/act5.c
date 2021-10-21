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
                printf("%d -------------\n",cause);
                printf("Hola sóc en Robb Stark amb pid = %d, soc un fill del matrimoni de la Catelyn Stark i Ned Stark.\n", getpid());
                printf("Soc en Robb amb pid = %d i he estat %s\n", getpid(), causaDeMort(cause));
                exit(cause);
            } else {
                // Mort Ned
                srand(ned);
                int cause = rand() % 2;
                char concat[2];
                char robDed[1];
                
                waitpid(robb, &statusRobb, WUNTRACED);                
                

                char robbChar[1];
                sprintf(robbChar, "%d", statusRobb>>8);
                printf("robbChar == %s \n", robbChar);

                char nedChar[1];
                sprintf(nedChar, "%d", cause);
                printf("nedChar == %s \n", nedChar);

                printf("printo els dos chars == %s .--- %s\n", &robbChar, robbChar);
                //strcpy(concat, robbChar);
                //strcat(concat, nedChar)
                //printf("concat == %s\n", concat);

                //waitpid(robb, 0, WUNTRACED);
                printf("Sóc en Ned amb pid = %d i m’acaben de %s\n", getpid(), causaDeMort(cause));
                //sprintf(values,"%s", cause);
                //sprintf(values[1], "%d",statusRobb);
                //strcat(values, robDed);

                
               fflush(stdout);
                int returnExit = atoi(concat);
                printf("return exit: %d\n", returnExit);
                
               fflush(stdout);
                exit(returnExit);

            }

        } else {
            // Mort Ricard
            waitpid(ned, &statusNed, WUNTRACED);
            char result[2];// = atoi(statusNed>>8);
            //sprintf(result, statusNed>>8);
            printf("%d\n",statusNed>>8);
            printf("%c\n",result[1]);
            printf("En resum el meu fill Robb ha estat %s, en Ned %s i jo en Rickard amb pid = %d i m’han executat.\n", causaDeMort(statusRobb>>8), causaDeMort(statusNed>>8), getpid());
            exit(0);

        }

    } else {

        waitpid(rickard, 0, WUNTRACED);
        printf("The winter is coming!!!!!\n");

    }

}
