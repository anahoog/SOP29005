Memória compartilhada entre processos
Outra maneira de compartilhar dados entre processos é utilizando memória compartilhada. Nestes casos, o sistema operacional precisa ser utilizado para "mapear" blocos de memória no espaço de endereçamento de cada processo (veremos mais tarde como isto é feito). Sistemas UNIX diponibilizam uma série de SystemCalls para compartilhar memória entre processos:

int shmget(key_t key, size_t size, int shmflg): retorna o identificador de um segmento de memória compartilhado associado a uma chave de identificação (key). Caso a chave solicitada não exista e a flag IPC_CREAT está especificada, um novo segmento de memória compartilhada é criado, com o tamanho size.
void *shmat(int shmid, const void *shmaddr, int shmflg): anexa/mapeia o segmento de memória especificado por shmid (obtido através de um shmget) no endereço shmaddr do espaço de endereçamento do processo.
int shmdt(const void *shmaddr): desfaz o mapeamento do segmento de memória compartilhada que está mapeado em shmaddr.
int shmctl(int shmid, int cmd, struct shmid_ds *buf): realiza a ação de controle indicada por cmd sobre o segmento de memória compartilhada identificado pelo shmid. Caso o cmd utilizado necessite de parâmetros, estes são passados em buf.
O programa abaixo cria um novo segmento de memória compartilhada em um sistema UNIX. A função ftok é utilizada para gerar uma chave única de identificação do segmento de memória (veja "man ftok"). O programa ipcs pode ser utilizado para verificar os segmentos de memória compartilhada disponíveis no sistema.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
#define SHM_SIZE 1024  /* make it a 1K shared memory segment */
 
int main(void)
{
 
       key_t key;
       int shmid;
       char *data;
       int mode;
 
       /* make the key: */
       if ((key = ftok("/tmp", 'X')) == -1) {
            perror("ftok");
            exit(1);
       }
 
       /* create the shared memory segment: */
       if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT )) == -1) {
            perror("shmget");
            exit(1);
       }
 
       return(0);
}
O programa abaixo manipula o segmento criado pelo programa anterior. Perceba que o programa utiliza a função ftok com os mesmos parâmetros passados na criação. O sistema operacional utiliza esta chava única para identificar o segmento de memória a ser utilizado. Se o programa abaixo é executado com um string como parâmetro (ex.: "./shm_test abc123"), ele escreve este parâmetro no segmento de memória. Caso seja executado sem parâmetros (ex.: "./shm_test"), o programa imprime o conteúdo da memória compartilhada.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
#define SHM_SIZE 1024  /* make it a 1K shared memory segment */
 
int main(int argc, char *argv[])
{
 
       key_t key;
       int shmid;
       char *data;
       int mode;
 
 
       /* make the key: */
       if ((key = ftok("/tmp", 'X')) == -1) {
            perror("ftok");
            exit(1);
       }
 
 
       /* connect to the segment.
      NOTE: There's no IPC_CREATE. What happens if you place IPC_CREATE here? */
       if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) {
            perror("shmget");
            exit(1);
       }
 
 
    /* attach to the segment to get a pointer to it: */
        data = shmat(shmid, (void *)0, 0);
        if (data == (char *)(-1)) {
            perror("shmat");
            exit(1);
        }
 
 
        /* read or modify the segment, based on the command line: */
        if (argc == 2) {
            printf("writing to segment: \"%s\"\n", argv[1]);
            strncpy(data, argv[1], SHM_SIZE);
        } else
            printf("segment contains: \"%s\"\n", data);
 
 
        /* detach from the segment: */
        if (shmdt(data) == -1) {
            perror("shmdt");
            exit(1);
        }
 
       return(0);
}
Desafio1: destrua um shm. Crie um programa que destrua o shm utilizado nos programas anteriores. Para isso utilize shmctl com o parâmetro apropriado (veja "man shmctl").