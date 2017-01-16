#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv){

	pid_t pid = fork();

	switch(pid){

		case 0:
			if(setsid() == -1)
				perror("Error setsid()");
			
			system(argv[1]);
			printf("%s\n", "El comando terminó de ejecutarse"); //SYSTEM RETORNA, EXEC NO
		return -1;

	}

	waitpid(pid); //Queremos que printeé después de ejecutar el comando
	

	return 0;
}
