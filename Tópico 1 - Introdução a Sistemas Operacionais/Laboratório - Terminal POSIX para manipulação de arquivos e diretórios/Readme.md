Neste trabalho, usaremos a API POSIX para implementar um terminal simples no Linux que interpreta e executa comandos de manipulação de arquivos e diretórios.
Bibliotecas POSIX e o Linux/UNIX
Existem dois meios principais para acessar as funcionalidades dos sistemas operacionais Linux/UNIX: System V e POSIX. O System V foi desenvolvido em 1983 na AT&T e muitos sistemas hoje ainda se baseiam nele em algum nível. Os principais competidores eram as variantes do UNIX da BSD que iniciaram a definição de uma API alternativa. Finalmente, em 1988 a IEEE Computer Society decidiu padronizar esta API criando a Portable Operating System Interface (POSIX) com o objetivo de aumentar a compatibilidade entre variantes do UNIX.

A maioria dos sistemas operacionais atuais são ou compatíveis com POSIX, ou quase compatíveis com POSIX. A lista de sistemas inclui MacOS, Windows, Android, VxWorks, iOS, e a maioria das distribuições Linux. Neste link há uma lista das funções de biblioteca C POSIX. A descrição destas funções também estão disponíveis nas manpages do seu Linux.

Comandos do terminal e funções da API POSIX
Você deve implementar um programa que leia continuamente a entrada digidada como um interpretador de comandos. Os comandos e os parâmetros devem ser separados, e a função específica da API POSIX para tratar os comandos devem ser invocadas. A tabela abaixo apresenta a estrutura dos comandos a serem implementados, uma breve descrição e a função da API a ser utilizada.

Comando	Descrição	Função da API POSIX
cwd	Imprime o diretório atual	getcwd
mkdir <nome_do_diretório>	Cria um diretório	mkdir
rmdir <nome_do_diretório>	Deleta um diretório	rmdir
cd <nome_do_diretório>	Muda o diretório atual	chdir
stat <arquivo_ou_diretorio>	Imprime estatísticas	stat
ls	Lista conteúdo do diretório atual	opendir, readdir, closedir