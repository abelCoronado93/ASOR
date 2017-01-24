#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
    
#include <string.h>

int main() {
	
	int uid = getuid();
	struct passwd *buf;

	buf = getpwuid(uid);

	printf("Nombre: %s\n", buf->pw_name);
	printf("Información: %s\n", buf->pw_gecos);
	printf("Directorio: %s\n", buf->pw_dir);

return 0;
}
