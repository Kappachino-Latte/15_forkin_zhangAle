#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	int f, status;
	printf ("I am the parent! My PID: %d\nFirst fork\n", getpid());
	f = fork();
	
	if (f) {
		printf ("Second fork\n");
		f = fork();
	}
	
	
	if (!f) {
		int childPID = getpid();
		printf ("I am the child with PID [%d]\n", childPID);
		
		srand (childPID);
		int rand_time = rand() % 9 + 2;
		sleep(rand_time);
		
		printf ("Child with PID [%d] is now finished\n", childPID);
		return rand_time;
	}
	else {
		int childPID = wait(&status);
		printf ("Child with PID [%d] has awoken after [%d] seconds\n", childPID, WEXITSTATUS(status));
		printf ("Parent is now finshed\n");
		return 0;
	}
	
}
