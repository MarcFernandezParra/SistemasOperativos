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
BEGIN { print "{\n \t \"pokedex\":[" } \
{ print "\t { \
  \n \t\t \"#\":",$1,
",\n \t\t \"Name\":\"",$2,
",\n \t\t \"Type 1\":",$3,
",\n \t\t \"Type 2\":",$4,
",\n \t\t \"Total\":"$5,
",\n \t\t \"Hp\":", $6,
",\n \t\t \"Attack\":",$7,
",\n \t\t \"Defense\":"$8,
",\n \t\t \"Sp. Atk\":",$9,
",\n \t\t \"Sp. Def\":"$10,
",\n \t\t \"Speed\":"$11,
",\n \t\t \"Generation\":",$12,
",\n \t\t \"Legendary\":",(($13 ==1) ? "True" : "False"),
"\n \t }" }
END { print "\t ]\n}"}' pokedex.csv
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
