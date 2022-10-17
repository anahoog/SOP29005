Processos no Linux
Syscall FORK
Em um terminal, execute "man fork"
A função da API POSIX fork() aciona uma chamada de sistema (system call - syscall) que cria um novo processo duplicando o processo que realiza a chamada. O novo processo, chamado de filho, é uma cópia exata do processo criador, chamado de pai, exceto por alguns detalhes listados na manpage. O principal destes detalhes para nós agora é o fato de terem PIDs diferentes.
O código dos dois processos (pai e filho) são idênticos;
Os dados dos dois processos (pai e filho) são idênticos NO MOMENTO DA CRIAÇÃO;
Execução do processo filho inicia na próxima instrução do programa (no retorno da chamada FORK);
Não é possível saber qual dos processos (pai ou filho) retormará a execução primeiro - isto fica a cargo do excalonador do SO;
Valores de retorno da chamada FORK:
(-1): erro na criação do processo (ex.: memória insuficiente);
(0): em caso de sucesso, este é o valor de retorno recebido pelo processo filho;
(>0): em caso de sucesso, este é o valor de retorno recebido pelo processo pai;
Syscall JOIN
A syscall JOIN é implementada no POSIX pelo função wait(). Execute "man wait".
Além da função wait(), há também waitpid() e waitid();
Todas estas syscalls são utilizadas para aguardar por mudanças no estado de um processo filho e obter informações sobre o processo filho cujo estado tenha mudado. São consideradas mudanças de estado: o filho terminou; o filho foi finalizado por um sinal (ex.: kill); o filho foi retomado por um sinal (ex.: alarme);
A chamada wait também libera os recursos do processo filho que termina;
wait(): esta função suspende a execução do processo chamador até que UM DOS SEUS FILHOS finalize;
waitpid(): suspende a execução do processo chamador até que UM FILHO ESPECÍFICO finalize;
Syscall EXEC
A syscall EXEC é implementada no POSIX pela família de funções exec(). Execute "man exec".
As principais funções da família são execl(), execlp() e execvp();
Todas estas funções são, na realidade, front-ends (abstrações) para a syscall execve. Esta syscall substitui a imagem do processo corrente (aquele que chama a syscall) pela a imagem de um novo processo;
Os parâmetros passados a estas funções são, basicamente, o nome de um arquivo com a imagem do programa a ser executado (um binário de um programa), e uma lista de parâmetros a serem passados a este novo programa;
Exemplos POSIX utilizando fork/wait/exec
Exemplo 1: fork/wait básico
// ex1: fork/wait básico
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid, status;
    pid = fork();

    if(pid == -1) // fork falhou
    {
        perror("fork falhou!");
        exit(-1);
    }
    else if(pid == 0) // Este é o processo filho
    {
        printf("processo filho\t pid: %d\t pid pai: %d\n", getpid(), getppid());
        exit(0);
    }
    else // Este é o processo pai
    {
        wait(&status);
        printf("processo pai\t pid: %d\t pid pai: %d\n", getpid(), getppid());
        exit(0);
    }
}
arliones@socrates:~/tmp$ gcc ex1.c -o ex1 
arliones@socrates:~/tmp$ ./ex1 
processo filho	 pid: 27858	 pid pai: 27857
processo pai	 pid: 27857	 pid pai: 5337
arliones@socrates:~/tmp$
Exemplo 2: processos pai e filho compartilham código, mas não dados.
// ex2: fork/wait "compartilhando" dados
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid, status, k=0;
    printf("processo %d\t antes do fork\n", getpid());
    pid = fork();
    printf("processo %d\t depois do fork\n", getpid());

    if(pid == -1) // fork falhou
    {
        perror("fork falhou!");
        exit(-1);
    }
    else if(pid == 0) // Este é o processo filho
    {
        k += 1000;
        printf("processo filho\t pid: %d\t K: %d\n", getpid(), k);
        exit(0);
    }
    else // Este é o processo pai
    {
        wait(&status);
        k += 10;
        printf("processo pai\t pid: %d\t K: %d\n", getpid(), k);
        exit(0);
    }
    k += 10;
    printf("processo %d\t K: %d\n", getpid(), k);
    exit(0);
}
arliones@socrates:~/tmp$ gcc ex2.c -o ex2
arliones@socrates:~/tmp$ ./ex2 
processo 18425	 antes do fork
processo 18425	 depois do fork
processo 18426	 depois do fork
processo filho	 pid: 18426	 K: 1000
processo pai	 pid: 18425	 K: 10
arliones@socrates:~/tmp$
Modificação no código: comentar as linhas sublinhadas
arliones@socrates:~/tmp$ gcc ex2.c -o ex2
arliones@socrates:~/tmp$ ./ex2 
processo 32342	 antes do fork
processo 32342	 depois do fork
processo 32343	 depois do fork
processo filho	 pid: 32343	 K: 1000
processo 32343	 K: 1010
processo pai	 pid: 32342	 K: 10
processo 32342	 K: 20
arliones@socrates:~/tmp$
Analise os resultados e busque entender a diferença.
Exercício fork/wait
Excrever um programa C que cria uma árvore de 3 processos, onde o processo A faz um fork() criando um processo B, o processo B, por sua vez, faz um fork() criando um processo C. Cada processo deve exibir uma mensagem "Eu sou o processo XXX, filho de YYY", onde XXX e YYY são PIDs de processos. Utilizar wait() para garantir que o processo C imprima sua resposta antes do B, e que o processo B imprima sua resposta antes do A. Utilizar sleep() (man 3 sleep) para haver um intervalo de 1 segundo entre cada mensagem impressa.

Exercício status/wait
O status passado como parâmetro à função wait(&status) é, na verdade, o mecanismo de retorno de resultado do wait/waitpid. Ao retornar, esta variável contém informações sobre o resultado da execução do processo filho. Por exemplo, se um processo terminou normalmente (i.e., chamou exit), o comando WIFEXITED(status) retorna true. Este comando retorna false se o processo foi abortado (e.g., segmentation fault) ou morto (e.g., kill). Investigue no manual do wait no Linux (man wait) o funcionamento do comando WEXITSTATUS(status), e use-o para modificar o exercício anterior para calcular o 5!, sendo que cada processo pode executar apenas uma multiplicação.

Exercício fork/wait/exec

Crie um terminal "embrionário", que apenas lê caminhos completos de programas (ex.: /usr/bin/ls, /usr/bin/gedit, /usr/bin/firefox), com ou sem '&' ao final. O programa deve criar um processo filho (fork), que por sua vez deve se transformar no programa informado (execve). O programa deve bloquear a entrada (wait) se não houver um '&', ou liberar a entrada do programa para caso não haja o '&'. O programa deve funcionar em um laço que continua lendo novos comandos até que o usuário use o comando "sair".

Última atualização: quarta, 21 Set 2022, 14:00