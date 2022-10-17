Troca de mensagens
Um mecanismo disponibilizado por sistemas UNIX para troca de mensagens entre processos é o PIPE. Pipes são mecanismos de comunicação indireta onde mensagens são trocadas através de mailboxes. Cada mailbox possui um identificador único, permitindo que processos identifiquem o canal de comunicação entre eles. O fluxo de mensagens em um Pipe é:

unidirecional: sobre um mesmo pipe, apenas um processo envia mensagens e um processo recebe mensagens;
FIFO: as mensagens são entregues na ordem de envio;
não-estruturado: não há estrutura pré-definida para o formato da mensagem.
No UNIX, pipes são inicializados através da SystemCall pipe, que possui a seguinte sintaxe:

int pipe(int pipefd[2]): pipe inicializa um novo pipe no sistema e retorna, no array pipefd, os descritores identificando cada uma das pontas do pipe. A primeira posição do array, i.e. pipefd[0], recebe o descritor que pode ser aberto apenas para leitura, enquanto a segunda posição do array, i.e. pipefd[1], recebe o descritor que pode ser aberto apenas para escrita. A função retorna zero no caso de sucesso, ou -1 se ocorrer erro.
As primitivas send/receive para uso de um pipe no UNIX são implementadas por SystemCalls read/write, conforme segue:

ssize_t read(int fd, void *buf, size_t count): “puxa” dados do pipe identificado pelo descritor fd. Os dados recebidos são os apontados pelo ponteiro buf, sendo count a quantidade máxima de bytes a serem recebidos. A função retorna o número de bytes recebidos.
ssize_t write(int fd, const void *buf, size_t count): “empurra” dados no pipe identificado pelo descritor fd. Os dados transmitidos são os apontados pelo ponteiro buf, sendo count a quantidade de bytes a serem transmitidos. A função retorna o número de bytes transmitidos.
Abaixo há um exemplo de programa criando um pipe e compartilhando os descritores entre dois processos (criados via fork()).

#include <unistd.h>   
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char *message = "This is a message!!!" ;

main()
{
    char buf[1024] ;
    int fd[2];
    pipe(fd);    /*create pipe*/
    if (fork() != 0) { /* I am the parent */
        write(fd[1], message, strlen (message) + 1) ;
    }
    else { /*Child code */
        read(fd[0], buf, 1024) ;
        printf("Got this from MaMa!!: %s\n", buf) ;
    }
}
Desafio 1: construa um “pipeline”. Crie um programa que conecta 4 processos através de 3 pipes. Utilize fork() para criar vários processos.
Desafio 2: cópia de arquivo. Projete um programa de cópia de arquivos chamado FileCopy usando pipes comuns. Esse programa receberá dois parâmetros: o primeiro é o nome do arquivo a ser copiado e o segundo é o nome do arquivo copiado. Em seguida, o programa criará um pipe comum e gravará nele o conteúdo do arquivo a ser copiado. O processo filho lerá esse arquivo do pipe e o gravará no arquivo de destino. Por exemplo, se chamarmos o programa como descrito a seguir:
$ FileCopy entrada.txt copia.txt
O arquivo entrada.txt será gravado no pipe. O processo filho lerá o conteúdo desse arquivo e o gravará no arquivo de destino copia.txt. Escreva o programa usando os pipes da API POSIX no Linux.