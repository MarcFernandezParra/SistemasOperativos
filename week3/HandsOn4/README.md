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

**L'exercici està resolt a l'arxiu act3.c d'aquest repositori** (La comanda execv no inclou el path, per tant hem afegit la direcció on es troba la comanda "find")


### 4- Explica el funcionament del programa. Indicant quants senyals s'envien, quin procés envia el senyal, i on l'envia.

El programa fa un fork i es divideix en dos blocs: pare i fill. Els dos blocs treballen a la vegada, pero el procés fill s'atura, esperant a que el pare el desperti amb una signal. El procés pas a pas es el següent:

1. Pare i fill printen per pantalla el seu PID a la vegada:
       
        printf("Hola soc el pare i el meu pid=%d \n", getpid());

        printf("Hola soc el fill i el meu pid=%d \n", getpid());
        
2. Una vegada han printat el seu missatge, el fill s'atura i el pare espera a que el fill s'aturi. No sabem qui acaba primer, per tant s'han de sincronitzar.

        kill(getpid(), SIGSTOP); // El fill s'atura

        waitpid(-1, 0, WUNTRACED); // El pare espera al fill
        
3. Una vegada el pare rep la senyal de que el fill s'ha aturat, continua la seva execució. Printa per pantalla un altre missatge i envia una senyal per continuar al seu fill. Per últim, espera a que el fill acabi la seva execució:

        printf("Hola soc el pare i he de continuar... però millor que ho faci el meu fill xD\n ...Enviant SIGCONT...\n");
        kill(i, SIGCONT);
        waitpid(-1, 0, WUNTRACED);
        
4. El fill printa per pantalla un últim missatge i finalitza la seva execució:

        printf("Hola soc el fill he rebut SIGCONT... ha treballar\n");
        exit(0);

5. Una vegada ha acabat el procés fill, el pare finalitza la seva execució amb un últim printf.


### 5- Programeu un programa pare, fill net que tingui la següent sortida (mantenint l’ordre). A més a més els fills, hauran de generar un enter aleatori entre els valors 0,1 i 2. El 0=apunyalat, 1=decapitat.

**L'exercici està resolt a l'arxiu act5.c d'aquest repositori**
