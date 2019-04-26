#include "types.h"
#include "stat.h"
#include "user.h"


char *argv[] = { "cat", "arrok" };

int
main(void)
{
	// ps();
	int fd;
	// char *filename;
	// filename="arr";
	char *filename1;
	filename1="arrok";

	// char *filename2;
	// filename2="arrokkk";

	// fd = open(filename, 0);
	
 //  	close(fd);
 //  	printf(1, "fd 1: %d\n", fd);

	// fd = open(filename1, 0x200);
	
 //  	close(fd);	

	// printf(1, "fd 2: %d\n", fd);


	int a = create_container();
	printf(1, "Container 1: %d\n", a);
	int b = create_container();
	printf(1, "Container 2: %d\n", b);

	join_container(1);

	// fd = open(filename, 1);
	
 //  	close(fd);	

 //  	printf(1, "fd 2: %d\n", fd);

  	// cat(filename1);



	// fd = open(filename1, 0);
	
 //  	close(fd);	

	// printf(1, "fd 3: %d\n", fd);



	fd = open(filename1, 0x200|0x002);
	int pid = getpid();

	char *towrite;
	towrite = " Modified by: ";
	char temp[20];
	int i = 0;
	for(i=0;i<strlen(towrite);i++) temp[i] = towrite[i];

	temp[i] = (pid/10) + '0';
	temp[++i] = (pid%10) + '0';
	temp[++i] = '\n';

	write(fd,temp,strlen(temp));


	// write (" Modified by: "+ pid);

  	close(fd);	

	printf(1, "fd 4: %d\n", fd);


	// fd = open(filename2, 0);
	
 //  	close(fd);	

	// printf(1, "fd 5: %d\n", fd);

	int ad = fork();
	if(ad==0){
		// exec("cat", argv);
		printf(1, "fd 5: %d\n", fd);
		// leave_container();
		exit();
	}
	// leave_container();
	sleep(10);
	destroy_container(1);
	wait();
	exit();
	
}
