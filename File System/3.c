#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

        mode_t old_mask = umask(0027); //Cambiamos la máscara

	printf("%o\n", old_mask);

	int rc = creat("ejercicio5.txt", 0666); // Queremos crearlo con estos permisos, pero aplica la máscara

	umask(old_mask); //Volvemos a la máscara por defecto del kernel (0022)

	if (rc == -1){
		perror("Error creat()");
		return 1;
	}

	printf("Fichero creado exitosamente\n");	

return 0;
}
