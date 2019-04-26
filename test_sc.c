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
    // for(int i=0;i<CHILDS;i++) c_ids[i] = -1;
    // parent_pid = getpid();

    // int cont_ids[3];
    // for(int i=0;i<3;i++){
    //   cont_ids[i] = create_container();
    // }

    // scheduler_log_on();

    // //creating 5 childs
    // for(int i=0;i<CHILDS;i++){
    //   c_ids[i]=fork();
    //   if(c_ids[i]==0){
    //     this_child_id = i;
    //     break;  
    //   } 
    // }


    // //Parent
    // if(getpid()==parent_pid){
    //   for(int i=0;i<CHILDS;i++) printf(1, "Child %d: Pid = %d\n", i, c_ids[i]);
    // }
    // //Childs
    // else if(this_child_id==0 || this_child_id==1 || this_child_id==2){
    //   join_container(cont_ids[0]);
    //   int t = 10;
    //   while(t--){
    //     wait(2);
    //   }
    //   exit();
    // }
    // else if(this_child_id==3){
    //   join_container(cont_ids[0]);
    //   int t = 10;
    //   while(t--){
    //     wait(2);
    //   }
    //   exit();      
    // }
    // else if(this_child_id==4){
    //   join_container(cont_ids[0]);
    //   int t = 10;
    //   while(t--){
    //     wait(2);
    //   }
    //   exit();            
    // }

    // scheduler_log_off();

    // for(int i=0;i<CHILDS;i++) wait();
    exit();
}
