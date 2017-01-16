#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <linux/limits.h> //path_max

int main(){

	printf("Id del proceso: %i\n", getpid());
	printf("Id del proceso padre: %i\n", getppid());
	printf("Id del grupo de procesos: %i\n", getpgid(0));
	printf("Id de la sesión: %i\n", getsid(0));

	struct rlimit rlim; //Declaramos en la pila del proceso

	int rc = getrlimit(RLIMIT_NOFILE, &rlim); //Le pasamos la dirección de la estructura

	if(rc == -1){
		perror("Error getrlimit()");
		return -1;
	}

	printf("Máximo número de archivos: %i\n", rlim.rlim_max);

	char *buf;
	printf("Directorio: %s\n", getcwd(buf, PATH_MAX));

return 0;
}


