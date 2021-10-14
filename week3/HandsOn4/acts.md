# Hands On 4

### 1- Repetir els passos amb l'ordre yes > /dev/null. Què fa aquesta ordre? Quines diferències trobeu amb l'execució de l'ordre anterior?



### 2- Modificar aquest procés per obtenir una sortida indicant Hola sóc el procés pare i Hola sóc el procés fill.

    #include <sys/types.h>
    #include <unistd.h>
    #include <assert.h>
    #include <stdio.h>
    int main () {
            pid_t p1 = fork();
            assert (p1 >= 0);
            printf("Hola sóc el procés amb pid %d \n", getpid());
    }
    
L'exercici està resolt a l'arxiu act2.c d'aquest repositori

