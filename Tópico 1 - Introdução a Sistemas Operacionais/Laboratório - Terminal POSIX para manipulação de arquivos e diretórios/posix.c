#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

const int N = 128;
char buffer [N];
string pathname;


int main(){
    string cmd;

    while(cmd != "exit"){
	cout << ">"<< endl;
        cin >> cmd;

        if(cmd == "cwd"){
           getcwd(buffer, N);
           cout << buffer << endl;
        }
	    else if (cmd == "mkdir"){
		    cin >> pathname;
	   	    mkdir(pathname.c_str(), 0664);
	    } else if (cmd == "rmdir"){
            cin >> pathname;
            rmdir(pathname.delete())
        }
	    else{
		    cout << "Comando Inválido"<< endl;	
	    }
    }
}
