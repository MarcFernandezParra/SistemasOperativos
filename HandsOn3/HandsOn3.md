# Hands On 6

### Activitat 0 (Test del Hands-On)

Són els simbols \r i \n, que tiren el cursor fins a l'inici i salten de linia respectivament.
Si no els poséssim, no imprimiría cada missatge en una linia nova.

### Activitat 1

El que succeeix es que al executar la SYSCALL amb un paràmetre, aquest paràmetre s'escriurà al kernel log amb la funcio printk.
Però el paràmetre es un apuntador, que no te per què se una adreça de memòria del usuari. Pot ser perfectament una adreça de memòria d'un altre usuari, amb informació d'aquest.
Llavors un usuari podria obtenir informació d'un altre. Aquesta es la vulnerabilitat.


### Activitat 2

El que fa el helper.c és afegir un hook a una crida de sistema. Aquest hook, el que fa es executar codi extra al fer la crida original.
En el nostre cas serà nomès printar un missatge, que es algo inofensiu, pero aquest codi injectat podria fer qualsevol cosa, que es una vulnerabilitat clarísima.
