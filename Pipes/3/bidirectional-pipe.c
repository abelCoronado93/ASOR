#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

	int p_h[2];
	int h_p[2];

	pipe(p_h);
	pipe(h_p);

	pid_t pid=fork();

	switch(pid){

		case 0: /*HIJO*/
			close(p_h[1]);//escribe
			close(h_p[0]);//lee
			char c1[1];
			char mensaje1[257];
			int i;

			for(i=0;i<10;i++){

				ssize_t tam1=read(p_h[0],mensaje1,256);
				mensaje1[tam1]='\0';
				printf("[HIJO] Mensaje : %s ",mensaje1);
				sleep(1);
				if(i==9) c1[0]='q';
				else c1[0]='l';
				tam1=write(h_p[1],c1,1);
			}

			break;

		default: /*PADRE*/
			close(p_h[0]);
			close(h_p[1]);
			char c[1];
			char mensaje [257];
			//read(h_p[0],c,1);// guardo caracter
			if(c[0] != 'q' && c[0]!='l') c[0]='l';
			
			while(c[0] != 'q'){
				printf("[PADRE] Escribe comando \n");
				ssize_t tam =read(0,mensaje,256);
				mensaje[tam]='\0';
				tam = write(p_h[1], mensaje, tam+1);
				read(h_p[0],c,1);
			}

		break;

	}
return 0;
}
