#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <linux/limits.h> //path_max

int main(){
	
	pid_t pid = fork();

	switch(pid){
		case 0:

			sleep(1000);
			printf("%s\n","----DEMONIO----");
			setsid();
			int rc = chdir("/tmp");
			printf("Id del demonio: %i\n", getpid());
			printf("Id del proceso padre: %i\n", getppid());
			printf("Id del grupo de procesos: %i\n", getpgid(0));
			printf("Id de la sesión: %i\n", getsid(0));
			char *buf;
			printf("Directorio: %s\n", getcwd(buf, PATH_MAX));

			/*CÓDIGO DEL DEMONIO*/

		break;

		default:

			printf("%s\n","----PADRE----");
			printf("Id del proceso: %i\n", getpid());
			printf("Id del proceso padre: %i\n", getppid());
			printf("Id del grupo de procesos: %i\n", getpgid(0));
			printf("Id de la sesión: %i\n", getsid(0));
			
		break;
	}

return 0;
}
