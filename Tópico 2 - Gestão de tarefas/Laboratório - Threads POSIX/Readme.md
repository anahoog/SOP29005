Threads de aplicação no Linux
A biblioteca POSIX Threads, ou simplesmente pthreads, é parte do padrão POSIX para programar utilizando threads. O padrão POSIX.1c define a API para criação e manipulação de threads. Esta API é encontrada na maioria dos sistemas baseados no Unix, como Linux, Mac OS X, Solaris, entre outros. Também existem alternativas adaptando a API para sistemas Windows, como a pthreads-w32.

A API da pthreads inclui métodos para criar, manipular e destruir threads, além de outras estruturas de dados para sincronizar as threads, incluindo implementações de mutexes e variáveis de condição.

A API POSIX semaphore, utilizada para sincronização de processos ou threads, também funciona em conjunto com a pthreads, embora sua implementação esteja definida em outro padrão, o POSIX.1b.

Programas em C/C++ que utilizarão a pthreads devem incluir o cabeçalho pthread.h:

#include <pthread.h>
 

Principais elementos da API
pthread_t (struct): estrutura que armazena dados/atributos de uma pthread.
pthread_create: Função que cria uma thread, incializando-a e deixando-a pronta para executar. O código abaixo apresenta um exemplo simples de um programa utilizando pthreads.
#include <pthread.h>

pthread_t threads[2];

void *thread_func(void *arg) {
    // ...
}

int main(int argc, char **argv) {
    int i;
    for(i = 0; i < 2; i++) {
        pthread_create(&(threads[i]), NULL, thread_func,NULL);
    }
    for(i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
}
pthread_join: bloqueia execução de uma thread até que outra thread termine, implementando um comportamento similar à chamada de sistema wait usada em processos Unix.
pthread_exit: encerra a execução de uma thread. A chamada a esta função por uma pthread gera a liberação de outras threads que estejam, eventualmente, bloqueadas nela por uma chamada pthread_join.
O código abaixo apresenta um programa completo utilizando pthreads, onde threads recebem argumentos.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t threads[2];

void *thread_func(void *arg) {
    ptr_thread_arg targ = (ptr_thread_arg) arg;
    int i;

    for(i = targ->idx; i < (targ->idx + targ->length); i++)
        printf(“Thread %d – value %d\n”, pthread_self(), i);
}

int main(int argc, char **argv) {
    thread_arg arguments[2];
    int i;
    for(i = 0; i < 2; i++) {
        arguments[i].idx = i * 10;
        arguments[i].length = 10;
        pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));
    }
    for(i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
}
Ao compilar um programa com pthreads é necessário "linkar" com a biblioteca libpthread. Para isso, deve ser usando a opção -lpthread com o gcc.

gcc ... -lpthread
Desafio
Implemente uma lógica de sincronização das threads  para garantir que as threads do exemplo acima imprimam de forma alternada:
Thread d571a700 – value 0
Thread d4f19700 – value 10
Thread d571a700 – value 1
Thread d4f19700 – value 11
Thread d571a700 – value 2
Thread d4f19700 – value 12
Thread d571a700 – value 3
Thread d4f19700 – value 13
Thread d571a700 – value 4
Thread d4f19700 – value 14
Thread d571a700 – value 5
Thread d4f19700 – value 15
Thread d571a700 – value 6
Thread d4f19700 – value 16
Thread d571a700 – value 7
Thread d4f19700 – value 17
Thread d571a700 – value 8
Thread d4f19700 – value 18
Thread d571a700 – value 9
Thread d4f19700 – value 19