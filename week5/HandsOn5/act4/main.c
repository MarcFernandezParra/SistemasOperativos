#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include "pokedex.h"
 
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
 
char *args[] = {"pokemon", "pokemon", NULL};

int probabilities[9];
char numberOfProb = 0;  
void throwPokeball(){

    srand(time(NULL));
    int throw = (rand() % 10) + 1;
    for(int i = 0; i<=numberOfProb; i++){
        if(probabilities[i] == throw){
            throw = 2;
        }
    }
    if (throw == 2 || throw == 7) {
        exit(throw);   
    }
}

void throwBerry(){
    if(numberOfProb<9){
        numberOfProb ++;
        printf("%sS'ha augmentat la probabilitat de captura!%s\n", KGRN, KNRM);
    }else{
        printf("%sLa probabilitat de captura no pot augmentar més.%s\n", KYEL, KNRM);
    }
}
 
int main(int argc, char *argv[]) {

    probabilities[0] = 2;
    probabilities[1] = 1;
    probabilities[2] = 3;
    probabilities[3] = 4;
    probabilities[4] = 5;
    probabilities[5] = 6;
    probabilities[6] = 8;
    probabilities[7] = 9;
    probabilities[8] = 10;

    int endFlag = 1, encounterEndFlag = 1;
    int childProcess, status, throw = 0;

    srand(time(NULL));
    init_pokedex();
 
    while (endFlag == 1) {
 
        char s[100];
        char choice;
        sprintf(s, "################\n# E. Explore \n# Q. Quit\n################\n");

        if (write(1, s, strlen(s)) < 0) perror("Error writting the menu");

            scanf(" %c", &choice);
 
            switch (choice) {

                case 'Q':
                    endFlag = 0;
                    break;

                case 'E':
                
                    childProcess = fork();

                    if (childProcess == 0) {
                        // Child process
                        signal(SIGUSR1, throwPokeball);
                        signal(SIGUSR2, throwBerry);
                        while (1) {
                            raise(SIGSTOP);
                        }

                        exit(0);

                    } else {

                        // Main process
                        printf("Ash: [%d] --> %sWild pokemon appeared! [%d]%s\n", getpid(), KBLU, childProcess, KCYN);
                        show_pokemon(rand() % 151);
                        printf("%s", KNRM);
    
                        waitpid(-1, 0, WUNTRACED); // Waits for child to pause

                        while (encounterEndFlag == 1) {
                            printf("P: Throw Pokeball\nB: Throw Berry\nR: Run\n > ");
                            scanf(" %c", &choice);
                        
                            switch(choice) {

                                case 'P':
                                    kill(childProcess, SIGUSR1);
                                    
                                    kill(childProcess, SIGCONT);
                                    waitpid(-1, &status, WUNTRACED);
                                    
                                    status = status >> 8;
                                    
                                    if (status == 2) {
                                        printf("%sCapturat!!!%s\n", KGRN, KNRM);
                                        encounterEndFlag = 0;
                                    } else if (status == 7) {
                                        printf("%sS'ha escapat...%s\n", KBLU, KNRM);
                                        encounterEndFlag = 0;
                                    } else {
                                        printf("%sSe ha salido de la bola :peeposad:%s\n", KYEL, KNRM);
                                    }
                                    
                                    break;

                                case 'B':
                                
                                    kill(childProcess, SIGUSR2);
                                    
                                    kill(childProcess, SIGCONT);
                                    waitpid(-1, &status, WUNTRACED); //se vuelve a dormir el hijo
                                    
                                    break;

                                case 'R':
                                    kill(childProcess, SIGKILL);
                                    printf("%sHas escapado!%s\n", KGRN, KNRM);
                                    encounterEndFlag = 0;
                                    break;

                                default:
                                    break;
                            }
                        }

                        wait(NULL);
                        numberOfProb = 0;
                        encounterEndFlag = 1;
                    }

                    break;

                default:
                    sprintf(s, "%s!!!!Invalid option. Try again. %s\n", KRED, KNRM);
                    if (write(1, s, strlen(s)) < 0) perror("Error writting invalid option");
            }
    }
 
    char s[100];
    sprintf(s, "%s!!!!I'm tired from all the fun... %s\n", KMAG, KNRM);
    if (write(1, s, strlen(s)) < 0) perror("Error writting the ending msg");
    exit(0);

}