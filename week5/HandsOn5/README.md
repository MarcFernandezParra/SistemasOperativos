# Hands On 5

### 1- Quantes senyals estem enviant? Quines? Quina acció fa el procés quan rep les senyals?

CTRL+Z envia un SIGSTP i la comanda "bg" envia un SIGCONT per reanudar els processos parats en background. 
CTRL+C enviaria un SIGINT al procès que s'està executant en primer pla, però el "yes > /dev/null" està en background.

### 2- Quina diferència hi ha entre fer un ctrl+c i la situació de l'exemple 1. En els dos casos es genera un senyal i és tractada pel kernel?

En el primer cas el CTRL+C envia un SIGINT al procés en primer pla que no hi és. En el segón enviem un SIGINT al procés específic.

### 3- Quin problema podria tenir un procés que executa el codi següent, si rebem un SIGINT. Com podem solucionar-ho?

<pre><code>int main(void) {
    FILE *psFile;
    psFile = fopen("temp.txt", "w");
    ...
    fclose(psFile);
    remove("temp.txt");
    return 0;
}
</code></pre>

El fitxer podria quedar obert. Per solucionar-ho podriem ignorar el SIGINT amb:

<pre><code>signal(SIGINT, SIG_IGN);</code></pre>
