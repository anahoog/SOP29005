#include <unistd.h>   
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {
    
	string arq_original = argv[1];
	string arq_copia = argv[2];

    int fd[2];
    pipe(fd);  


	if(arq_original.empty()){
        break;
    }

	while(true){
    	string linha;
    	getline(linha, arq_original);
   	 
    	

		while(!arq_original.empty()){
			if (fork() != 0) { /* I am the parent */
        	write(fd[1], cin, strlen (cin) + 1) ;
    		}

		}

	}
    

}
