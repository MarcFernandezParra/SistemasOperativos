#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include "pokedex.h"
#include "pokemon.h"
 
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

void finishCombat() {
    exit(0);
}

Pokemon getRandomPoke() {
    return get_pokemon(rand() % 151);
}
 
int main(int argc, char *argv[]) {

    init_pokedex();

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
    int childProcess, childProcess2, status, hp, damage, turn, throw = 0;
    int pipe1[2], pipe2[2], pipe3[2];
    char buf[8];

    srand(time(NULL));
 
    while (endFlag == 1) {
 
        char s[100];
        char choice;
        sprintf(s, "################\n# E. Explore \n# F. Figth \n# Q. Quit\n################\n");

        if (write(1, s, strlen(s)) < 0) perror("Error writting the menu");

            scanf(" %c", &choice);
 
            switch (choice) {

                case 'Q':
                    endFlag = 0;
                    break;

                case 'F':
                    turn = rand() % 2;

                    Pokemon pokemon1 = getRandomPoke();
                    Pokemon pokemon2 = getRandomPoke();

                    pipe(pipe1);
                    pipe(pipe2);
                    pipe(pipe3);

                    childProcess = fork();

                    if (childProcess == -1) {
                        perror("Fork 1");
                    } else if (childProcess == 0) {
                        // Pokemon 1
                        signal(SIGALRM, finishCombat);

                        close(pipe1[0]);
                        close(pipe2[1]);
                        close(pipe3[1]);

                        // Reading childProcess2 PID
                        read(pipe3[0], buf, 8);
                        childProcess2 = atoi(buf);

                        hp = pokemon_hp(pokemon1);

                        while (hp > 0) {
                            // New turn

                            if (turn % 2 == 0) {
                                // Sending damage to Pokemon 2
                                printf("%s######## %s [%d/%d]%s\n", KCYN, pokemon_name(pokemon1), hp, pokemon_hp(pokemon1) , KNRM);
                                damage = rand() % 20;
                                sprintf(buf, "%d", damage);
                                write(pipe1[1], buf, sizeof(int));
                                printf("%s######## %s %s---(Send attack with damage(%d))---> %s%s[%d]%s\n", KCYN, pokemon_name(pokemon1), KGRN, damage, KMAG, pokemon_name(pokemon2), childProcess2, KNRM);
                            } else {
                                alarm(1);
                                // Recieving damage from Pokemon 2
                                read(pipe2[0], buf, sizeof(int));
                                damage = atoi(buf);

                                // Recieves value to finish fight
                                if (damage == -2) {
                                    printf("AAAAAAA%d\n", damage);
                                    exit(0);
                                }

                                hp -= damage;
                                printf("%s######## %s %s---(Recieves attack with damage(%d))---> %s%s[%d]%s\n", KCYN, pokemon_name(pokemon1), KRED, damage, KMAG, pokemon_name(pokemon2), childProcess2, KNRM);
                            }

                            turn ++;
                        }

                        // This pokemon has lost the fight
                        printf("El combat ha acabat %s%s[%d] ha derrotat %s%s[%d]%s\n", KMAG, pokemon_name(pokemon2), childProcess2, KCYN, pokemon_name(pokemon1), getpid(), KNRM);
                        sprintf(buf, "%d", -2);
                        write(pipe2[1], buf, sizeof(int));

                        exit(0);
                    } else {
                        childProcess2 = fork();
                        
                        if (childProcess2 == -1) {
                            perror("Fork 2");
                        } else if (childProcess2 != 0) {
                            // Main process
                            close(pipe3[0]);

                            // Sending childProcess2 PID
                            sprintf(buf, "%d", childProcess2);
                            write(pipe3[1], buf, strlen(buf));
                        }
                    }

                    if (childProcess2 == 0) {
                        // Pokemon 2
                        signal(SIGALRM, finishCombat);
                        
                        close(pipe1[1]);
                        close(pipe2[0]);
                        close(pipe3[0]);
                        close(pipe3[1]);

                        fflush(stdout);

                        hp = pokemon_hp(pokemon2);
                        
                        while (hp > 0) {
                            // New turn

                            if (turn % 2 != 0) {
                                // Sending damage to Pokemon 1
                                printf("%s######## %s [%d/%d]%s\n", KMAG, pokemon_name(pokemon2), hp, pokemon_hp(pokemon2), KNRM);
                                damage = rand() % 20;
                                sprintf(buf, "%d", damage);
                                write(pipe2[1], buf, sizeof(int));
                                printf("%s######## %s %s---(Send attack with damage(%d))---> %s%s[%d]%s\n", KMAG, pokemon_name(pokemon2), KGRN, damage, KCYN, pokemon_name(pokemon1), childProcess, KNRM);
                            } else {
                                // Recieving damage from Pokemon 2
                                alarm(1);
                                read(pipe1[0], buf, sizeof(int));
                                damage = atoi(buf);

                                if (damage == -2) {
                                    exit(0);
                                }

                                hp -= damage;
                                printf("%s######## %s %s---(Recieves attack with damage(%d))---> %s%s[%d]%s\n", KMAG, pokemon_name(pokemon2), KRED, damage, KCYN, pokemon_name(pokemon1), childProcess, KNRM);
                            }

                            turn ++;
                        }

                        printf("El combat ha acabat %s%s[%d] ha derrotat %s%s[%d]%s\n", KCYN, pokemon_name(pokemon1), childProcess, KMAG, pokemon_name(pokemon2), getpid(), KNRM);
                        sprintf(buf, "%d", -2);
                        write(pipe2[1], buf, sizeof(int));

                        exit(0);
                    }

                    waitpid(childProcess, &status, WUNTRACED);
                    waitpid(childProcess2, &status, WUNTRACED);

                    printf("Combat finished...\n");

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
                        int random = rand() % 151; 
                        show_pokemon(random);
                        Pokemon current = get_pokemon(random);
                        set_pokemon_seen_true(current);
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
                                        //pokemon capturado ++ 
                                        set_pokemon_captured_true(current);
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
    create_csv();
    if (write(1, s, strlen(s)) < 0) perror("Error writting the ending msg");
    exit(0);

}