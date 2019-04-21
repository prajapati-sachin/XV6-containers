#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	ps();
	scheduler_log_on();
	int a = create_container();
	printf(1, "Container 1: %d\n", a);
	int b = create_container();
	printf(1, "Container 2: %d\n", b);
	int ad = fork();
	if(ad==0){
		join_container(1);
		int b = 2;
		while(b--){
			sleep(10);
		}
		// leave_container();
		exit();
	}
	else{
		join_container(1);
	// 	printf(1, "C: %d\n", ad);
	// 	ps();
	// 	printf(1, "C: %d\n", ad);
	// 	ps();
		int t = 2;
		while(t--){
			sleep(10);
		}
		wait();
	}
	exit();
}
