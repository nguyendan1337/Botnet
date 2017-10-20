#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>

#define LOG_STRING(st) \
	f = fopen("bn.log", "a"); \
	current_time = time(NULL); \
	fprintf(f, "%s: %s\n", \
		strtok(ctime(&current_time),"\n"), st); \
	fclose(f); 

#define ACTIVATE_ZOMBIE(n) \
	kill(zs[n], SIGUSR1); \
	asprintf(&message, "Command and Control center %d activated zombie %d", \
									getpid(), zs[n]); \
	LOG_STRING(message); \
	free(message);

int zs[2];
time_t current_time;
FILE *f;
char *message;

int create_zombie()
{
	int child;
	child = fork();
	if (child) {
		asprintf(&message, "Command and Control center %d created zombie %d", 
									getpid(), child); 
		LOG_STRING(message);
		free(message);
		return child;
	} else {
		char *argv[] = {"zombie", NULL};
		execvp(argv[0], argv);
	}
}

void handle_signal(int signal) {
    switch (signal) {
		case SIGUSR1:
			ACTIVATE_ZOMBIE(0);
			break;
		case SIGUSR2:
			ACTIVATE_ZOMBIE(1);
			break;
		case SIGCHLD:
			LOG_STRING("whodunnit");
			int status;
			waitpid(zs[0], &status, WNOHANG);
			if (kill(zs[0],0) != 0) {
				asprintf(&message, "Zombie %d has been killed", zs[0]);
				LOG_STRING(message);
				ACTIVATE_ZOMBIE(1);
				zs[0] = create_zombie();
			} 
			waitpid(zs[1], &status, WNOHANG);
			if (kill(zs[1],0) != 0) {
				asprintf(&message, "Zombie %d has been killed", zs[1]);
				LOG_STRING(message);
				ACTIVATE_ZOMBIE(0);
				zs[1] = create_zombie();
			}
			break;
		default:
			break;
	}
}


int main()
{
	zs[0] = create_zombie();
	zs[1] = create_zombie();
	signal(SIGUSR1,handle_signal); 
	signal(SIGUSR2,handle_signal); 
	signal(SIGCHLD,handle_signal); 
	for(;;){
		sleep(5);
	}
	return 1;
}
