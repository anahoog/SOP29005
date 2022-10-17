Neste laboratório vamos discutir alguns detalhes do gerenciamento de processos no Linux. Estes mecanismos são muito similares aos encontrados em qualquer sistema Unix. Quando você executa um programa em seu sistema, o sistema cria um ambiente especial para cada programa. Este ambiente contém tudo que é necessário para que o sistema execute o programa como se nenhum outro programa estivesse compartilhando o sistema. Ou seja, cada processo tem a impressão de estar sozinho no sistema quando executa, apesar de haver outros processos ativos. Este mecanismo de isolamento dos processos e gerenciado pelo sistema operacional.

Sempre que um comando é executado no Unix, o sistema cria, ou inicia, um novo processo. Quando se tenta executar, por exemplo, o comando "ls" para listar o conteúdo de um diretório, um processo é criado. Este processo executa uma instância do programa "/bin/ls". Ou seja, um processo nada mais é do que uma instância de um programa em execução.

O sistema operacional rastreia os processos através de um número identificador conhecido como PID (Process ID). Cada processo no sistema tem um PID único, gerado sequencialmente pelo SO. PIDs podem apenas repetir em casos extremos, quando um sistema roda por tanto tempo que o contador de PID estoura e volta ao valor mínimo. Mas mesmo nestes casos, o SO toma o cuidado para que não existam no sistema, ao mesmo tempo, dois processos com o mesmo PID.

Iniciando um processo

Quando iniciamos um processo (rodando um comando, por exemplo), há duas maneiras de iniciá-lo: em primeiro plano, ou em segundo plano.

Processos em primeiro plano (Foreground Processes)

Por padrão, todo processo iniciado executa em primeiro plano. Assim, ele obtem entradas do teclado e envia suas saídas para a tela padrão. É possível verificar isso, por exemplo, ao executar o comando ls em um terminal. Para listar todos os arquivos no diretório atual, em um terminal digite "ls".

O processo executa em primeiro plano, sua saída é direcionada para a tela. Se o comando "ls" deseja ler alguma entrada (o que não ocorre neste exemplo), ele esperaria pelo teclado. Enquanto um programa executa em primeiro plano ele está consumindo o processamento associado ao sistema, e nenhum outro comando pode ser disparado (e nenhum outro processo poderá ser iniciado) a partir do terminal em que você está conectado.

Processos em segundo plano (Background Processes)

Um processo em segundo plano executa sem estar conectado a um terminal (neste caso, um terminal seria a abstração da tela e do teclado do sistema). Se o processo em segundo plano necessita alguma entrada do teclado, ele aguarda até que o teclado seja conectado a ele. A vantagem de executar processos em segundo plano é que é possível executar outros comandos - não é necessário aguardar o final de um comando para iniciar outro. A maneira mais simples de fazer isso é utilizar um e-comercial (&) ao final de um comando. Por exemplo, digite "ls &".

Neste caso, se o comando "ls" quer uma entrada (o que não ocorre neste exemplo), ele vai entrar em um modo de espera (stop state) até que seja "puxado" para o primeiro plano e, assim, seja conectado ao teclado pelo terminal.

Quando um processo é executado em segundo plano, uma linha de saída é exibida no terminal contendo o "job number" e o PID do processo. O "job number" é um número de "trabalhos" lançados a partir do terminal em que você está. É necessário conhecer o "job number" para alternar os processos entre primeiro e segundo plano. Além disso, quando um processo em segundo plano conclui, essa informação é repassada ao terminal.

Alguns outros comandos interessantes para manipular processos no terminal:

"jobs" - lista de trabalhos (jobs) ativos no momento
"Ctrl+z" - para o processo/job que está em primeiro plano
"bg N" - envia o job N para o segundo plano
"fg N" - traz o job N para o primeiro plano

Listando processos ativos

O programa "ps" (process status) permite listar os processos ativos no sistema, junto de algumas informações sobre estes processos, como seu PID, o terminal em que está conectado, o tempo de execução, o comando que lançou o processo, entre outros. Existem várias opções que podem ser utilizadas junto com o programa:

"ps -f" : inclui mais dados sobre os processos
"ps -a" : mostra informações sobre todos os usuários
"ps -x" : mostra informações sobre processos não conectados a terminais
"ps -u" : mostra informações adicionais

Tente combinar várias opções, digite "ps -aux".

Um outro mecanismo mais dinâmico para observar os processos em execução é o comando "top".

Parando processos

Há diferentes maneiras de terminar um processo. Frequentemente, a partir de um terminal, um processo pode ser morto utilizando a combinação Ctrl+c. Esta combinação é uma combinação padrão no Unix para gerar uma interrupção no processo. Se, ao executar a combinação, houver um processo em primeiro plano, este processo receberá esta notificação de interrupção e terminará.

Se um processo estiver executando em segundo plano, não é possível gerar o Ctrl+c. Neste caso, é necessário obter o PID do processo utilizando o comando "ps". De posse do PID, o comando "kill PID" pode ser utilizado para terminar o processo. Se o processo ignorar o comando "kill" padrão, é possível forçar a terminação do processo utilizando "kill -9 PID".