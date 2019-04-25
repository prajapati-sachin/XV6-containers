#include "types.h"
#include "stat.h"
#include "user.h"


char *argv[] = { "ls", 0 };

int
main(void)
{
	// ps();

	char *filename;
	filename="arr";

	int fd = open(filename, 0);
	
  	close(fd);
	int a = create_container();
	printf(1, "Container 1: %d\n", a);
	int b = create_container();
	printf(1, "Container 2: %d\n", b);

	join_container(1);
	fd = open(filename, 0);
	
  	close(fd);	

  	printf(1, "fd 2: %d\n", fd);

	fd = open(filename, 0);
	
  	close(fd);	

	printf(1, "fd 2: %d\n", fd);

	int ad = fork();
	if(ad==0){
		exec("ls", argv);
		// leave_container();
		exit();
	}
	wait();
	exit();
	
}
