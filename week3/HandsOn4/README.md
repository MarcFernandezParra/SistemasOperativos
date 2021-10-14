# Hands On 4

### 1- Repetir els passos amb l'ordre yes > /dev/null. Què fa aquesta ordre? Quines diferències trobeu amb l'execució de l'ordre anterior?

La comanda yes fa un output de l'string "y" repetidament fins que es mata el procés. Amb "> /dev/null", estem redirigint aquest output a l'arxiu /dev/null, que descarta tota aquesta informació. <br>
Al fer CTRL+Z els dos procesos passen a l'estat Stopped, però al executar "bg", el procés "sleep" entra en estat Interrumpible Sleep, mentres que el "yes > /dev/null" entra en estat Running.

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
    
**L'exercici està resolt a l'arxiu act2.c d'aquest repositori**

### 3- Modificar aquest exemple fent anar la funció execv()

    #include <stdio.h>
    #include <unistd.h> 

    int main( void ) {

        char *argv[3] = {"find", ".", NULL};
        int pid = fork();

        if ( pid == 0 ) {
            execvp( "find", argv );
        }

        /* El pare dorm 2 segons (més endavant veure com amb wait podem sincronitzar millor pare i fill*/

        sleep(2);

        printf( "Final del proces pare\n"
        " - el fill no arribarà mai a aquest punt d'execució a causa del recobriment\n" );

        return 0;
    }
        
