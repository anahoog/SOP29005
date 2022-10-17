#include <unistd.h>   
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char *message = "This is a message!!!" ;

int main()
{
    char buf[1024] ;

    int fd1[2];
    int fd2[2];
    int fd3[2];

    pipe(fd1);    /*create pipe*/
    pipe(fd2);    /*create pipe*/
    pipe(fd3);    /*create pipe*/


    if (fork() != 0) { /* Processo P1 */
    	printf("Eu sou o Processo P1\n");
        write(fd1[1], message, strlen (message) + 1) ;  

        if (fork() != 0) { 
    	    if (fork() != 0) { 
    	    
        }else { 
            read(fd3[0], buf, 1024) ;    	
            printf("Eu sou o Processo P4, eu herdei: %s\n", buf);               

        }
    }else { 
        read(fd2[0], buf, 1024) ;    	
        printf("Eu sou o Processo P3, eu herdei: %s\n", buf); 
        buf[strlen(buf)-1] = '3';
        write(fd3[1], buf, strlen (buf) + 1) ;  
        }
    }

    else { /*P2*/
            read(fd1[0], buf, 1024) ;    	
            printf("Eu sou o Processo P2, eu herdei: %s\n", buf);
            buf[strlen(buf)-1] = '2';
            write(fd2[1], buf, strlen (buf) + 1) ;  
        }
}
