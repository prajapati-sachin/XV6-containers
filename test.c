#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	ps();
	int a = create_container();
	printf(1, "Container 1: %d\n", a);
	int b = create_container();
	printf(1, "Container 2: %d\n", b);

	b = destroy_container(1);
	printf(1, "Destroy Container 1: %d\n", b);

	b = create_container();
	printf(1, "Container 3: %d\n", b);
	exit();
}
