# Activitat 1
```awk
awk -F, '/Fire/ {print $2,$3,$4}' pokedex.csv
```

# Activitat 2

```awk
awk ' \
        BEGIN { print "Counting pokemons..." } \
        { ++i }
        /Fire/ { ++n } /Dragon/ {++d} \

        END   { print "Fire: ", n,"\nDragon:",d,"\nOthers:", i-n-d}' pokedex.csv
```

# Activitat 3

```awk
awk -F, '($2 ~ /^[M]/) && (/Fire/ || /Fighting/) { print $2, "types[",$3,$4"]"}' pokedex.csv
```

# Activitat 4
```awk
awk 'BEGIN{FS=OFS=","} {gsub(/\,/, ";")} 1' pokedex.csv
```
# Activitat 5
```awk
 awk -F, ' \
        BEGIN { print "{\npokedex:[\n" } \
        { print "{\n#:", $1,",\nName:",$2, ",\nType 1:", $3, ",\nType 2:", $4,",\nTotal:"$5, ",\nHp:", $6,",\nAttack:",$7,",\nDefense:"$8,",\nSp. Atk:",$9,",\nSp. Def:"$10,",\nSpeed:"$11,",\nGeneration:",$12,",\nLegendary", (($13 ==1) ? "True" : "False"), "\n}" }
        END { print "]\n}"}' pokedex.csv     
```

# Activitat 7
```bash
#!/bin/bash

if [ -f ./memlliure.lst ]; then
	echo "memlliure.lst ja existeix. S'acaba el programa"
	exit 0
fi

duracio=${1:-"60"}

printf "%20s \t %12s \t %12s \t %12s \n" "Time" "MemFree" "MemTotal" "MemAvailable" >> memlliure.lst

for (( i=0; i< duracio; i++))
do

	timestamp=$(date '+%m/%d/%Y:%H:%M:%S')
	memTotal=$(grep -m 1 "MemTotal" /proc/meminfo | awk '{ print $2 }')
	memLliure=$(grep -m 1 "MemFree" /proc/meminfo | awk '{ print $2 }')
	memDisponible=$(grep -m 1 "MemAvailable" /proc/meminfo | awk '{ print $2 }')

	printf "%20s \t %12s \t %12s \t %12s \n" $timestamp $memLliure $memTotal $memDisponible >> memlliure.lst
	sleep 1
done
```
