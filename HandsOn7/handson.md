Anotacions: Per tal d'executar els scripts, cambiem el contingut de el fitxer test.sh pel codi que tenim a aquest MD
# Activitat 1 :
```sh
#!/bin/sh
OUTPUT=$(ls *.txt | wc -l)
echo "${OUTPUT}"
```

# Activitat 2 : 
```sh
#!/bin/sh
if [ $# -ne 1 ] ; then
    echo "Illegal number of parameters"
fi
mkdir -p $HOME/safe_rm_recycle
cp $1  $HOME/safe_rm_recycle
rm $1
```
--afegir al path:
export PATH=$PATH:~/bin
afegir script a per tal d'accedir desde cualsevol terminal  ~/.bashrc

# Activitat 3 :
```sh
#!/bin/bash 
x=$(pidof -x infinite_loop.sh)
if [ "$x" ] ; then
    echo "[ERROR]: Aquest script ja s’esta executant amb pid $x"
fi
```
# Activitat 4:
```sh
#!/bin/bash 
x=$(pidof -x infinite_loop.sh)
if [ "$x" ] ; then
    echo "[ERROR]: Aquest script ja s’esta executant amb pid $x"
    echo "[INFO]: Eliminant procés amb pid $x"
    kill -9 "$x"
fi

pid=$$
echo "[INFO]: Executant el script amb nom infinite_loop amb el següent pid $pid."
exec ./infinite_loop.sh

# Activitat 5:
#!/bin/bash

N=$1
decimal_expr='^[-+]?[0-9]+([.][0-9]+)?$'
if ! [[ $N =~ $decimal_expr ]] ; then
    echo "error: Not a number" >&2;
    exit 1
fi
```
# Activitat 6:
```sh
#!/bin/bash

check_proc(){
    if [ $# -eq 1 ] 
        then
            echo $1 "$(date)" 
        else
            echo $$ "$(date)"
    fi
}

check_proc

check_proc "1"
```
# Activitat 7:
Agafa el primer argument passat al script, afageix el pid a una string, i per cada proces a la string s'espera a que el procés acabi amb un wait. Si acaba correctament fa complete ++ i si no fail++. Després printa la quantitat de procesos completats i la cuantitat de processos acabats en fail.

# Activitat 8:

```sh
#!/bin/bash
N=$1
complete=0
fail=0
echo "Hi, I am the factory [$$]..."
pids=()
for ((i=0;i<N;i++))
    do
    # Donar a p.sh permissos d'execució abans d'executar.
    ( ./p.sh ) &

    sleep 3
    
    pids[${#pids[@]}]="$!"
    echo "Hi, the factory creates: ${pids[*]}..."
done

for p in "${pids[@]}"; do
    if wait $p; then
    (( complete++ ))
    else
    (( fail++ ))
    fi

done

echo "$complete processes completed successfully."
echo "$fail processes failed to completed."
echo "Done."
```

# Activitat 9:
``` sh
#!/bin/bash
N=$1
F=$2
int_exp='^[0-9]+$'
if [ $# -ne 2 ] 
        then
            echo 2 arguments mandatory.
        else
        if ! [[ $N =~ $int_exp ]] ; 
            then
                echo 1rst argument is not integer
            else 
                if test -f "$F"  
                    then
                    #exists
                        chmod +x "$F"
                        PS3="Opcio 1 : Execute; Opcio 2 Elimina; Opcio 3 remove perms; "
                        select option in Opcio1 Opcio2 Opcio3
                        do
                           if [ $REPLY -eq 1 ] 
                           then
                            #Opció 1: executarà la fàbrica de processos amb els arguments rebuts.
                            $F $N
                                
                            elif [ $REPLY -eq 2 ]
                            then
                            #Opció 2:  eliminarà l’executable passat com a paràmetre.
                                rm $F
                                echo removed file $F
                            elif [ $REPLY -eq 3 ]
                            then
                                #Opció 3:  traurà els permisos d’execució de l’argument 2.
                                chmod -x "$F"
                                echo removed execution permisions for file $F 
                            else    
                                echo invalid option
                           fi
                           exit
                        done
                    else
                    echo 2nd argument is not a file or doesnt exist
                fi
        fi
fi
echo "Done."
```

# Activitat 10:
El problema es el 0 del 071. El 0 fa que bash ho agafi en octal i faci la conversio (071 es 57), per tant dona un resultat no esperat.
Per solucionar-ho, podriem afegir 71 en comptes de 071 al fitxer
