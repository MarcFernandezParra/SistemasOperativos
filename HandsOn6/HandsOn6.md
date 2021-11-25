Activitat 1

En el primer, el descriptor del fitxer s'asigna independentment pel pare i pel fill, mentre que en el segon, el fill i el pare tenen el descriptor del fitxer asignat abans de crear el fill, per lo que el fill l'hereda.
Aixó provocarà en el primer cas, el contingut del fitxer sigui matxacat per el segon procés que entri, mentres que el segon cas, cuan l'últim dels dos procesos escrigui, l'altre procés ja haurá escrit, i fará append

Activitat 2
```c
#include <stdio.h>
#include <unistd.h>
#include <erno.h>
#include <sys/types.h>

 void main(){
     
     // Declarem el nostre array per emmagatzemar els descriptor associats a una pipe    
     int     fd1[2], fd2[2];
     pid_t   pidFill;
     /* El primer element de la matriu (fd1[0]) està configurat i obert per a la lectura, 
        mentre que el segon element està configurat i obert per escriure (fd1[1]. 
        Totes les dades que viatgen per la canonada es mouen pel nucli. */
     
    
     pipe(fd1); 
     pipe(fd2);

     pidFill = fork();
        
     if(pidFill == -1){
        perror("fork");
        exit(1);
     } else if (pidFill == 0){
         /*El procés fill tanca la escriptura per la pipe*/
         close(fd1[1]);
         close(fd2[0]);
     } else {
         /* El procés pare tanca la lectura per la pipe */
         close(fd1[0]);
         close(fd2[1]);
     }
 }
```

Activitat 3
 - Les dades escrites a la pipe van escrites al pipe buffer, que segons la man page de pipe, tipicament son 64 kb
 - No comparteix, per això necessita que la pipe buffer estigui al kernel

Activitat 4

Crea una pipe i fa un fork.
El fill tanca la lectura de la pipe i escriu 'msg1' mitjançant un buffer.
Després escriu un altre 'msg2'.
No arriba a tancar la pipe per la linea comentada.
Mentrestant, el pare tanca l'escritura de la pipe, i mentre hi hagi missatge el llegeix i l'escriu per pantalla. El problema es que el fill al no tancar mai la seva escriptura, el pare es quedara bloquejat esperant resposta.
Per tant, la linea comentada fa que el pare es desbloqueji i continuï sortint del bucle, i escriurà "No more messages :("
Tot i aixó, aquest programa deixará un zombie, ja que el fill no surt mai del while(1);

Activitat 5
```c
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

 

int main(int argc, char *argv[])

{

    int fd[2];
    char s[100];
    char *p1[] = {"ls", NULL};
    char *p2[] = {"wc", "-l", NULL};


    if (pipe(fd)<0)
    {
        perror("Error de creació del pipe fd[]");
        exit(-1);
    }


    int pid;

    switch (pid = fork()){
    case -1:
        perror("Error fork()");
        exit(-2);
        break;
    case 0:
        close(fd[0]);
        dup2(fd[1], 1);
        execvp("ls",p1);
    default:
        close(fd[1]);
        dup2(fd[0],0);
        execvp("wc",p2);
    }

}

```

Activitat 6

```c
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

 

int main(int argc, char *argv[])

{

    int fd[2], fd2[2];
    char s[100];
    char *p1[] = {"ls", NULL};
    char *p2[] = {"wc", "-l", NULL};


    if (pipe(fd)<0)
    {
        perror("Error de creació del pipe fd[]");
        exit(-1);
    }


    int pid, pid2;
    switch (pid = fork()){
    case -1:
        perror("Error fork()");
        exit(-2);
        break;
    case 0: 
        close(fd[0]);
        dup2(fd[1], 1);
        execvp("ls",p1);    
    default:
        if (pipe(fd2)<0)
        {
            perror("Error de creació del pipe fd[]");
            exit(-1);
        }

        if((pid2 = fork()) == 0){
                close(fd[1]);
                close(fd2[0]);//0  es lectura   
                dup2(fd2[1],1);
                dup2(fd[0],0);
                execvp("wc",p2);
        }else{

                close(fd2[1]);
                close(fd[0]);
                close(fd[1]);
                char car[10];
                read(fd2[0],&car,sizeof(car));
                printf("%s\n",car);
        }

        
    }

}

```
