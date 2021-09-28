# Anàlisi del codi i explicació

## Anàlisi del codi i explicació
E codi crida a la funció gettimeofday() varies vegades per guardar el timestamp actual en una variable (t1, t2)

Aquestes crides les fa abans i després d'executar la funcio 'getpid()' (que retorna el process ID) moltes vegades.
Un cop te els dos valors d'abans i després, en calcula el temps d'execució mitjà.

Després fa exactament el mateix per la funcio 'foo()'.

Finalment printa els resultats.

## Corregir els warnings generats al compilar:

Dona els següents warnings:

	root@debian-gcaballe:/home/guillem# gcc act_av02_os.c -o act_av02_os.o
	act_av02_os.c: In function ‘main’:
	act_av02_os.c:38:3: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
	38	|  printf("Time for 1 : %f\n",
	act_av02_os.c:38:3: warning: incompatible implicit declaration of built-in function ‘printf’

Per a solucionar-ho, afegeixo la llibreria stdio.h tal com m'indica el compilador

	#include <stdio.h>

## Crida a sistema vs crida a procediment + cost d'aquestes:

Una crida a una funció, per exemple foo(), o una funció d'una llibreria (printf de stdio.h) són el mateix concepte: cridar un tros de codi de l'espai de l'usuari.
En canvi, una crida a sistema apunta a un espai privilegiat, reservat pel kernel.
Aquesta separació aporta molta seguretat al sistema operatiu, però fa que una **crida al sistema sigui molt més costosa**.

Es per això que en el codi d'exemple, la funcio foo() s'executa molt més ràpidament com es veu al output cuan executem el programa.

	root@debian-gcaballe:/home/guillem# ./act_av02_os.o
	Time for 1 : 57.875000
	Time for 2 : 2.080000

## PD: Actualització de variables per entendre millor el programa

Hem canviat els valors de avgT1 i avgT2 per avgSysCallTimeval i avgProcCallTimeval respectivament.
