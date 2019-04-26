#include "types.h"
#include "stat.h"
#include "user.h"

#define CHILDS 5

int c_ids[CHILDS];
volatile int parent_pid;
volatile int this_child_id;


int
main(int argc, char *argv[])
{
  	for(int i=0;i<CHILDS;i++) c_ids[i] = -1;
  	parent_pid = getpid();

  	int cont_ids[3];
  	for(int i=0;i<3;i++){
  		cont_ids[i] = create_container();
      // printf(1, "i %d: container_id = %d\n", i, cont_ids[i]);
  	}


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
      // printf(1, "Processes in container 1\n");
      // sleep(20);
      join_container(cont_ids[0]);
      // sleep(20);
	  	if(this_child_id==2){
	  		// sleep(1000);
	  		printf(1, "Processes in container 1\n");
        // int count=10;
        // while(count--){
	  		 ps();
         // sleep(20);
        // }
	  	}
	  	sleep(200);
      exit();
  	}
  	else if(this_child_id==3){
      // sleep(20);
  		join_container(cont_ids[1]);
  		sleep(4);
  		printf(1, "Processes in container 2\n");
   		ps();
	  	exit();
  	}
  	else if(this_child_id==4){
      // sleep(20);
  		join_container(cont_ids[2]);
  		sleep(6);  		
  		printf(1, "Processes in container 3\n");
  		ps();
	  	exit();  		  		
  	}

    for(int i=0;i<CHILDS;i++) wait();
    for(int i=0;i<3;i++){
      destroy_container(cont_ids[i]);
    }
      exit();

}
