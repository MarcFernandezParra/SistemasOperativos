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

void attackPoke(){

    srand(time(NULL));
}

void endBattle(){

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

void finishCombat(){
    
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
        sprintf(s, "################\n# E. Explore \n F. Figth \n# Q. Quit\n################\n");

        if (write(1, s, strlen(s)) < 0) perror("Error writting the menu");

            scanf(" %c", &choice);
 
            switch (choice) {

                case 'Q':
                    endFlag = 0;
                    break;

                case 'F':
                    int fd1[2], fd2[2], fd3[2];
                    signal(SIGUSR1, attackPoke);
                    signal(SIGUSR2, endBattle);
                    
                    int random;
                    
                    int turn = rand() % 1;
                    childProcess = fork();                    
                    int childProcess2;
                    pipe(fd1);
                    pipe(fd2);
                    pipe(fd3);
                    
                    
                    srand(time(NULL));
                    random = rand() % 151; 
                    Pokemon poke1 = get_pokemon(random);
                    srand(time(NULL));
                    random = rand() % 151;
                    Pokemon poke2 = get_pokemon(random);

                    if(childProcess == 0){
                        //fill 1
                        signal(SIGUSR1, finishCombat);

                        raise(SIGCONT);
                        close(fd1[1]);
                        close(fd2[0]);
                        close(fd3[0]);

                        read(fd3[1], childProcess2, sizeof(int));

                        int hp = pokemon_hp(poke1);
                        int damage = 0;

                        while(hp != 0){
                            printf("%s######## %s [%d/%d]%s", KCYN, pokemon_name(poke1), pokemon_hp(poke1), hp, KNRM);

                            if(turn % 2 == 0) {
                                damage = rand() % 20;
                                write(fd1[0],damage, sizeof(int));
                                printf("%s######## %s %s---(Send attack with damage(%d))--->%s[%d]%s", KCYN, pokemon_name(poke1), KGRN, damage, KMAG, pokemon_name(poke2), childProcess2, KNRM);
                            } else {
                                read(fd2[1], damage, sizeof(int));
                                hp -= damage;
                                printf("%s######## %s %s---(Recieves attack with damage(%d))--->%s[%d]%s", KCYN, pokemon_name(poke1), KRED, damage, KMAG, pokemon_name(poke2), childProcess2, KNRM);
                            }

                            turn ++;
                        }

                        exit(0);
                    
                    }else{
                        childProcess2= fork();
                        close(fd3[1]);
                        write(fd3[0], childProcess2, sizeof(int));
                    }

                    if(childProcess2 == 0){
                        //fill 2
                        signal(SIGUSR1, finishCombat);

                        raise(SIGCONT);
                        close(fd1[0]);
                        close(fd2[1]);
                        close(fd3[0]);
                        close(fd3[1]);

                        int hp = pokemon_hp(poke2);
                        int damage =0;

                        while(hp != 0) {
                            printf("%s######## %s [%d/%d]%s", KMAG, pokemon_name(poke2), pokemon_hp(poke2), hp, KNRM);
                            
                            if(turn % 2 == 1) {
                                damage = rand() % 20;
                                write(fd2[0],damage, sizeof(int));
                                printf("%s######## %s %s---(Send attack with damage(%d))--->%s[%d]%s", KMAG, pokemon_name(poke2), KGRN, damage, KCYN, pokemon_name(poke1), childProcess, KNRM);
                            } else {
                                read(fd1[1], damage, sizeof(int));
                                hp -= damage;
                                printf("%s######## %s %s---(Recieves attack with damage(%d))--->%s[%d]%s", KMAG, pokemon_name(poke2), KRED, damage, KCYN, pokemon_name(poke1), childProcess, KNRM);
                            }

                            turn ++;
                        }

                        exit(0);
                    }
                    
                    pause();
                    pause();
                    printf("[%d] The pokemons are ready to figth...\n", getpid());
                    /*endFlag = 0;
                    while (endFlag == 0)
                    {
                        if(turn == 0){
                            //ataca 1
                            if(childProcess== 0){
                                
                            }
                            turn = 1;
                        }else{
                            //ataca 2
                            if(childProcess2==0){

                            }                            
                            turn = 0;
                        }
                    }*/
                    
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