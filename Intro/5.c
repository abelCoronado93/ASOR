#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
	
printf("Real: %i \n", getuid());
printf("Efectivo: %i \n", geteuid());

return 1;
}
