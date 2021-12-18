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

Activitat 7

Codi de la sala millorat. Hem simplificat la comparacio d'strings entre car i clau, i hem refactoritzat per eliminar un boolean que sobrava, que era jugant. Jugant era un boolea, oposat a atrapats.

```c
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

// Definim dues variables per controlar la situació de la partida. 
int atrapats = 0;

char * color_blue = "\033[01;34m";
char * color_end = "\033[00m";
char * color_red = "\033[01;31m";
char * color_green = "\033[01;32m";

char * args[] = {
  "jugador",
  "jugador",
  NULL
};
// Rutina de tractament de l'alarma, notifiquem per stdout amb color vermell el missatge de DING DONG i modifiquem les variables globals jugant i atrapats per poder procés la situació de la partida.
void alarm_handler();
void alarm_handler() {
  char s[100];
  sprintf(s, "%s**********DING DONG %s\n", color_red, color_end);
  write(1, s, strlen(s));
  atrapats = 1;
}

int main(int argc, char * argv[]) {
  int fd[2];
  char s[100];
  // Per poder utilitzar el programa passarem 3 arguments: el temps de la partida, el nombre de jugadors i la clau per obrir el candau. Per tant, comprovem que ens passin el nombre correcte d'arguments.
  if (argc < 4) {
    fprintf(stderr, "Usage: %s tempsPartida numJugadors clau \n", argv[0]);
    exit(1);
  }

  int numJugadors = atoi(argv[2]);
  int tempsPartida = atoi(argv[1]);
  char * clau = argv[3];
  // Ens guardarem els pids dels n processos en un array (int *). Recordeu que amb malloc reservem de forma dinàmica la memòria d'aquest array.
  int * pids = malloc(numJugadors * sizeof(int));
  // Definirem l'alarma utilitzant el segons entrats com a paràmetre d'entrada.
  signal(SIGALRM, alarm_handler);

  // Obrirem una pipe per comunicar amb els processos fills
  if (pipe(fd) < 0) {
    perror("El procés [Sala]::Error de creació del pipe");
    exit(1);
  }

  sprintf(s, "Inici del Room Escape [%d] (%d segons) \n", getpid(), tempsPartida);
  if (write(1, s, strlen(s)) < 0) perror("write");

  sprintf(s, "--- Entren %d jugadors a la sala \n", numJugadors);
  if (write(1, s, strlen(s)) < 0) perror("write");

  sprintf(s, "--- La paraula a endevinar és = %s\n", clau);
  if (write(1, s, strlen(s)) < 0) perror("write");

  // Crearem els processos fills i ens guardarem els seus pids.
  for (int i = 0; i < numJugadors; i = i + 1) {

    switch (pids[i] = fork()) {

    case -1:
      /* Error en la creació del procés fill */
      perror("Sala::fork()");
      exit(2);
      break;

    case 0:
      // Tanquem la sortida de lectura, el procés fill únicament ha d'escriure.
      if (close(fd[0]) < 0) perror("close");
      // Dupliquem l'escriptura del pipe al descriptor de fitxer 3, en cas de tenir-lo assignat primer el tancarà.
      if (dup2(fd[1], 3) < 0) perror("dup2");
      // Tanquem la sortida escriptura del pipe, ara ja no la necessitem.
      if (close(fd[1]) < 0) perror("close");
      // Fem el recubriment amb el codi de jugador
      execv(args[0], args);
      exit(-1);
    default:
      sprintf(s, "%s EscapeRoom[%d] ha entrat el jugador[%d] %s\n", color_blue, getpid(), pids[i], color_end);
      if (write(1, s, strlen(s)) < 0) perror("write");
    }
  }
  // Tanquem la sortida escriptura, el procés para únicament ha de llegir.
  close(fd[1]);
  // Iniciem la partida
  alarm(tempsPartida);

  char car[4];
  int leidos;

  while ((atrapats == 0) && (read(fd[0], & car, sizeof(car)) > 0)) {
    if (strcmp(car, clau) == 0) {
      sprintf(s, "--- Els jugadors obren el candau amb la clau %s \n", clau);
      if (write(1, s, strlen(s)) < 0) perror("write");
      atrapats = 1;
      break;
    }
  }

  for (int i = 0; i < numJugadors; i++) {
    if (atrapats == 1) {
      sprintf(s, "%s El jugador [%d] ha quedat atrapat i surt de EscapeRoom[%d]. %s\n", color_red, pids[i], getpid(), color_end);
      if (write(1, s, strlen(s)) < 0) perror("write");
    } else {
      sprintf(s, "%s El jugador [%d] ha escapat i surt de EscapeRoom[%d]. %s\n", color_green, pids[i], getpid(), color_end);
      if (write(1, s, strlen(s)) < 0) perror("write");
    }
    kill(pids[i], SIGUSR1);
    wait(NULL);
  }

  if (atrapats == 1) {
    sprintf(s, "--- El jugadors han perdut la partida. Fins aviat. \n");
    if (write(1, s, strlen(s)) < 0) perror("write");
  } else {
    sprintf(s, "--- El jugadors ha guanyat la partida en %d segons. \n", tempsPartida - alarm(tempsPartida));
    if (write(1, s, strlen(s)) < 0) perror("write");
  }
  close(fd[0]);
  exit(0);
}

```
