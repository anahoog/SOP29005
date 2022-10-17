Neste laboratório, entenderemos como funcionam as interações entre os programas de usuário e o sistema operacionais através de sinais (signals). Para ver a documentação dos sinais do Linux, use o capítulo 7 dos manuais (man 7 signal).

Vamos experimentar hoje com dois sinais: o SIGINT (2) e o SIGKILL (9). O SIGINT é o sinal enviado ao processo quando pressionamos Ctrl+c em um terminal, por exemplo. Por padrão, nossos programas têm um tratador pré-definido para estes sinais, que forçam o programa a terminar. Porém, estes tratadores padrão podem ser substituídos por um tratador na aplicação.

Para isso, escreveremos um programa simples que fica em um laço infinito, imprimindo uma mensagem na tela a cada dois segundos, aguardando os sinais. Vamos usar a função signal (man signal) para capturar sinais do SO.

Faça um programa que não termine quando recebe um SIGINT. Ao invés disso, escreva na tela que recebeu o sinal e continue a execução.