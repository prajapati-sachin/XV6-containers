#include "types.h"
#include "stat.h"
#include "user.h"


#define CHILDS 5

int c_ids[CHILDS];
volatile int parent_pid;
volatile int this_child_id;

char *argv[] = { "cat", "my_file" };

int
main(void)
{
	for(int i=0;i<CHILDS;i++) c_ids[i] = -1;
	parent_pid = getpid();

	int cont_ids[3];
	for(int i=0;i<3;i++){
		cont_ids[i] = create_container();
	}
	int fd;
	//creating 5 childs
	for(int i=0;i<CHILDS;i++){
		c_ids[i]=fork();
		if(c_ids[i]==0){
			this_child_id = i;
			break;  
		} 
	}

	char *filename1;
	filename1="my_file";

	//Parent
	if(getpid()==parent_pid){
		for(int i=0;i<CHILDS;i++) printf(1, "Child %d: Pid = %d\n", i, c_ids[i]);
	}

	//Childs
	else if(this_child_id==0 || this_child_id==1 || this_child_id==2){
		join_container(cont_ids[0]);
		sleep(2);
		
		
		if(this_child_id==2){

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
			printf(1, "Child with pid = %d modifying my_file %s\n",pid,temp);
			int ad = fork();
			if(ad==0){
				exec("cat", argv);
				// printf(1, "fd 5: %d\n", fd);
				// leave_container();
				exit();
			}
			wait();

		}
		// ls();
		exit();
	}
	else if(this_child_id==3){
		join_container(cont_ids[1]);
		sleep(100);
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
		printf(1, "Child with pid = %d modifying my_file %s\n",pid,temp);
		int ad = fork();
		if(ad==0){
			exec("cat", argv);
			// printf(1, "fd 5: %d\n", fd);
			// leave_container();
			exit();
		}
		wait();

		exit();
	}
	else if(this_child_id==4){
		join_container(cont_ids[2]);
		sleep(200);
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
		printf(1, "Child with pid = %d modifying my_file: %s\n",pid,temp);
		int ad = fork();
		if(ad==0){
			exec("cat", argv);
			// printf(1, "fd 5: %d\n", fd);
			// leave_container();
			exit();
		}
		wait();
		exit();
	}


	for(int i=0;i<CHILDS;i++) wait();
	exit();


	// int ad = fork();
	// if(ad==0){
	// 	// exec("cat", argv);
	// 	printf(1, "fd 5: %d\n", fd);
	// 	// leave_container();
	// 	exit();
	// }
	// // leave_container();
	// sleep(10);
	// destroy_container(1);
	// wait();
	// exit();
	
}
