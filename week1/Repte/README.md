# Repte primera setmana

## Explicació de la nostra solució

El que hem fet, ha sigut afegir un dimoni amb la comanda dmesg.
Però no volem que imprimeixi tot el log, nomès les linies noves, així que farem la comanda amb el paràmetre -W

dmesg -W&

si llavors invoquem la comanda que feia printk(), que en el nostre cas era instalar un module:

<pre><code>
root@debian-gcaballe:/home/guillem# insmod printk_module.ko
root@debian-gcaballe:/home/guillem# [ 3735.065361] printk_module: loading out-of-tree module taints kernel.
[ 3735.065371] printk_module: module license 'unspecified' taints kernel.
[ 3735.065373] Disabling lock debugging due to kernel taint
[ 3735.065433] printk_module: module verification failed: signature and/or required key missing - tainting kernel
[ 3735.065911] WOW I AM A KERNEL HACKER!!!
</code></pre>