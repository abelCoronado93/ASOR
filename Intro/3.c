#include <sys/utsname.h>     
#include <string.h>
#include <stdio.h>
#include <errno.h>


int main()
{

	int rc;
	struct utsname buf;

	rc = uname(&buf);

	if(rc != -1){
		printf("Operating system name: %s \n", buf.sysname);
		printf("Name within some implementation-defined network: %s \n", buf.nodename);
		printf("Operating system release: %s \n", buf.release);
	    printf("Operating system version: %s \n", buf.version);
	    printf("Hardware identifier: %s \n", buf.machine);
	}

	else
		perror("Error uname()");
	
	return 1;
}
