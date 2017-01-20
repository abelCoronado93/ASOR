#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	int p_h[2];
	int h_p[2];

	pipe(p_h);
	pipe(h_p);

	pid_t pid = fork();

	if(pid == 0){
		char mensajePadre[256];
		char flag = 'l';

		close(p_h[1]); close(h_p[0]);

		for(int i = 0; i < 10; i++){
			ssize_t bytes = read(p_h[0], mensajePadre, 255);
			mensajePadre[bytes] = '\0';
			printf("[HIJO] Recibido: %s\n", mensajePadre);
			sleep(1);
			if(i == 9) flag = 'q';
			write(h_p[1], &flag, 1);
		}

	} else {
		char flag ='l';
		char mensaje[256];

		close(p_h[0]); close(h_p[1]);

		while(flag != 'q'){
			printf("%s\n", "[PADRE] Mensaje: ");
			ssize_t bytes = read(0, mensaje, 255);
			mensaje[bytes] = '\0';
			write(p_h[1], mensaje, 255);
			read(h_p[0], &flag, 1);
		}
		wait(NULL);
		printf("10 mensajes enviados con éxito. Saliendo...\n");
	}

return 0;
}