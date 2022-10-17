Neste laboratório usaremos a interface de chamadas de sistema do Linux.

Inicialmente, considere o programa em C neste link. Este programa lê o conteúdo de um arquivo passado como argumento na linha de comando e escreve na saída padrão (terminal). Em nosso laboratório, chamamos o arquivo de copy.c:

> gcc -Wall -o copy copy.c
> ./copy copy.c

Observe o código de copy.c. A rotina main chama quatro funções definidas neste mesmo arquivo: myopen, myread, mywrite e myclose. Cada uma dessas funções é implementada por uma única linha, que contém uma chamada ao sistema operacional (na verdade, uma chamada a uma função wrapper provida pela biblioteca padrão de C).

As chamadas ao sistema operacional são documentadas na seção 2 do manual do Linux. Para ver a documentação de uma delas, basta escrever, por exemplo:
> man 2 open

Agora você deve substituir a implementação de cada uma das funções (myopen, myread, mywrite e myclose) pelo código assembly equivalente.

Atenção: suas funções assembly não devem chamar as funções da biblioteca de C! Elas devem usar uma interface direta com o SO.

Para implementar o código em assembly utilize o recurso de Assembly Inlining do GCC. Lembre-se da demonstração deste recurso feita pelo professor em sala de aula. Comece substituindo a implementação da função myopen, recompile o programa e teste.

Para descobrir o código das chamadas ao sistema, consulte esta tabela de chamadas. Observe os seguinte pontos:

Para ativar o sistema você vai usar a instrução syscall
O código da chamada (sys_open, sys_read, etc) deve ser passado no registrador %rax.
Os argumentos de funções são passados em %rdi, %rsi, %rdx, %r10, %r8 e %r9, nesta ordem.
O valor de retorno das chamadas de função (e de sistema) ficam no registrador %rax.
Vá comentando, uma a uma, a definição das demais funções no arquivo copy.c e substituindo-as pela implementação em assembly.
A implementação em assembly de chamadas a serviços do sistema operacional que você acabou de fazer é semelhante à implementação das funções wrapper disponíveis na biblioteca padrão de C.