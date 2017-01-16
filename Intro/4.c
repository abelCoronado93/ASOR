#include <unistd.h>    
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>


int main() {
	errno = 0;

	long maxArgs = sysconf(_SC_ARG_MAX);
	long maxHijos = sysconf(_SC_CHILD_MAX);
	long maxFich = sysconf(_SC_OPEN_MAX);

if (errno == 0)
{
   printf ("Numero maximo de argumentos: %ld\n", maxArgs);
   printf ("Numero maximo de hijos: %ld\n", maxHijos);
   printf ("Numero maximo de ficheros: %ld\n", maxFich);
}
else
{
    printf("error: %d\n", errno);
    exit(1);
}

return 1;
}
