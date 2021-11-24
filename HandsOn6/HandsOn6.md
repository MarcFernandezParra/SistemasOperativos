Activitat 1

en el primer, el descriptor del fitxer s'asigna independentment pel pare i pel fill, mentre que en el segon, el fill i el pare tenen el descriptor del fitxer asignat abans de crear el fill, per lo que el fill l'hereda.
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

TEST

Crea una pipe i fa un fork.
El fill tanca la lectura de la pipe i escriu 'msg1' mitjançant un buffer.
Després escriu un altre 'msg2'.
Però no arriba a tancar el fd.

Mentrestant, el pare tanca fd d'escriptura i llegeix 100 chars de la pipe.
