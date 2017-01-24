#include <unistd.h>    
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>


int main() {

	long maxArgs = sysconf(_SC_ARG_MAX);
	long maxHijos = sysconf(_SC_CHILD_MAX);
	long maxFich = sysconf(_SC_OPEN_MAX);
	
	if(maxArgs == -1 || maxHijos == -1 || maxFich == -1)
		perror("Error: %d\n");
	else {
		printf("Numero maximo de argumentos: %ld\n", maxArgs);
		printf("Numero maximo de hijos: %ld\n", maxHijos);
		printf("Numero maximo de ficheros: %ld\n", maxFich);
	}
	
return 0;
}
