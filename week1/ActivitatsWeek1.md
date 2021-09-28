# Activitat 1

• Les accions que es produeixen que no siguin explicades al pdf són les seguents:
openat() -> obre els diferents fitxers d'on llegira i escriurà.
read() -> llegeix el contingut del fitxer original
write() -> escriu el contingut del fitxer original
close() -> tanca el fitxer

• Quantes crides a sistema es fan de cada tipus?
Utilitzant la comanda strace -co strace.log cat test.c > test.out
Veiem una taula amb les diferents crides a sistema, tal com aquesta:
<pre><code>
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0         3           read
  0.00    0.000000           0         1           write
  0.00    0.000000           0         6           close
  0.00    0.000000           0         5           fstat
  0.00    0.000000           0         9           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         2           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         1           fadvise64
  0.00    0.000000           0         4           openat
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000           0        41         1 total

</code></pre>
