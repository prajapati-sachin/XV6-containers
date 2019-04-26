#include "types.h"
#include "stat.h"
#include "user.h"

#define CHILDS 5

int c_ids[CHILDS];
volatile int parent_pid;
volatile int this_child_id;


char *argv[] = { "ls", 0 };

int
main(int argc, char *argv[])
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

	//Parent
	if(getpid()==parent_pid){
		for(int i=0;i<CHILDS;i++) printf(1, "Child %d: Pid = %d\n", i, c_ids[i]);
	}

	//Childs
	else if(this_child_id==0 || this_child_id==1 || this_child_id==2){
		join_container(cont_ids[0]);
		sleep(2);
		
		
		if(this_child_id==2){
			printf(1, "ls outputs for container 1\n");
			int ad = fork();
			if(ad==0){
				exec("ls", argv);
				
				// leave_container();
				exit();
			}

		}
		// ls();
		
		sleep(100);
		char *temp;
		temp = "file_";
		char temp1[30];
		int i;

		int my_pid = getpid();
		for(i=0; i<strlen(temp); i++) temp1[i] = temp[i];
		temp1[i] = my_pid/10 + '0';
		temp1[++i] = my_pid%10 + '0';
		temp1[++i] = '\0';
		fd =open(temp1, 0x200);
		close(fd);

		if(this_child_id==2){
			sleep(200);
			int ad = fork();
			if(ad==0){
				exec("ls", argv);
				
				// leave_container();
				exit();
			}
			
			wait();
			wait();
		}
		// ls();
		exit();
	}
	else if(this_child_id==3){
		join_container(cont_ids[1]);
		sleep(800);
		printf(1, "ls outputs for container 2\n");		
		// ls();
		int ad = fork();
		if(ad==0){
			exec("ls", argv);
			
			// leave_container();
			exit();
		}
		wait();
		char *temp;
		temp = "file_";
		char temp1[30];
		int i;
		int my_pid = getpid();
		for(i=0; i<strlen(temp); i++) temp1[i] = temp[i];
		temp1[i] = my_pid/10 + '0';
		temp1[++i] = my_pid%10 + '0';
		temp1[++i] = '\0';
		fd =open(temp1, 0x200);
		close(fd);
		// sleep(400);
		int bd = fork();
		if(bd==0){
			exec("ls", argv);
			
			// leave_container();
			exit();
		}

		
		wait();
		// ls();
		exit();
	}
	else if(this_child_id==4){
		join_container(cont_ids[2]);
		sleep(1200);      
		printf(1, "ls outputs for container 2\n");				
		// ls();
		int ad = fork();
		if(ad==0){
			exec("ls", argv);
			
			// leave_container();
			exit();
		}
		wait();
		char *temp;
		temp = "file_";
		char temp1[30];
		int i;
		int my_pid = getpid();
		for(i=0; i<strlen(temp); i++) temp1[i] = temp[i];
		temp1[i] = my_pid/10 + '0';
		temp1[++i] = my_pid%10 + '0';
		temp1[++i] = '\0';
		fd =open(temp1, 0x200);
		close(fd);
		int bd = fork();
		if(bd==0){
			exec("ls", argv);
			
			// leave_container();
			exit();
		}

		wait();
		// ls();
		exit();           
	}


	for(int i=0;i<CHILDS;i++) wait();
	for(int i=0;i<3;i++){
		destroy_container(cont_ids[i]);
	}
	exit();
}
