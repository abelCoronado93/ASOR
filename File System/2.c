#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
	
	int rc = creat("ejercicio3.txt", S_IRUSR | S_IXUSR | S_IRGRP);

	if (rc == -1){
		perror("Error open()");
		return 1;
	}
	printf("Fichero creado exitosamente\n");	

return 0;
}
