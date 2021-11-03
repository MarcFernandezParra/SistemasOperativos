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
 
int main(int argc, char *argv[]) {

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

                        while (1) {

                            raise(SIGSTOP);

                            throw = (rand() % 10) + 1;

                            if (throw == 2 || throw == 7) {
                                exit(throw);   
                            }

                        }

                        exit(0);

                    } else {

                        // Main process
                        printf("Wild pokemon appeared! [%d] >\n", childProcess);
                        show_pokemon(rand() % 151);

                        waitpid(-1, 0, WUNTRACED); // Waits for child to pause

                        while (encounterEndFlag == 1) {
                            scanf(" %c", &choice);
                        
                            switch(choice) {

                                case 'P':
                                    kill(childProcess, SIGCONT);
                                    waitpid(-1, &status, WUNTRACED);

                                    if (status == 2) {
                                        printf("CAPUTRAO!!!\n");
                                        encounterEndFlag = 0;
                                    } else if (status == 7) {
                                        printf("ESCAPAO...\n");
                                        encounterEndFlag = 0;
                                    } else {
                                        printf("Se ha salido de la bola :peeposad:\n");
                                    }
                                    
                                    break;

                                case 'B':
                                    break;

                                default:
                                    break;
                            }
                        }

                        wait(NULL);

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