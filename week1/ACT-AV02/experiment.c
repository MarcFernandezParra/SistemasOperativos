#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long nanosec(struct timeval t) {
	return((t.tv_sec * 1000000 + t.tv_usec) * 1000);
}

int main() {

	int res;
	float avgT1, avgT2;
	struct timeval t1, t2;

	char *args[] = {"echo", "Test ECHO", NULL};

	res = gettimeofday(&t1, NULL); assert(res == 0);

	if (fork() == 0) {
		execv("/bin/echo", args);
	}else{
		wait(NULL);
	
		res = gettimeofday(&t2, NULL); assert(res == 0);

		avgT1 = (nanosec(t2) - nanosec(t1)) / 2;

		res = gettimeofday(&t1, NULL); assert(res == 0);
		printf("Test PRINTF\n");
		res = gettimeofday(&t2, NULL); assert(res == 0);

		avgT2 = (nanosec(t2) - nanosec(t1)) / 2;

		printf("Time for 1 : %f\n",avgT1);
		printf("Time for 2 : %f\n",avgT2);
		
		exit(0);
	}

}
