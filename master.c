#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define LOG_STRING(st) \
	f = fopen("bn.log", "a"); \
	current_time = time(NULL); \
	fprintf(f, "%s: %s\n", \
		strtok(ctime(&current_time),"\n"), st); \
	fclose(f); 

FILE *f; 
char *message;

int main()
{
	int cc[3];
	int botmaster;
	char *candc[] = {"candc", NULL};
	time_t current_time;
	botmaster = getpid();
	cc[0] = fork();
	if (cc[0]) {
		asprintf(&message,"Botmaster %d created Command and Control Center %d",
					botmaster, cc[0]);
		LOG_STRING(message);
		free(message);
		cc[1] = fork();
		if (cc[1]) {
			asprintf(&message,"Botmaster %d created Command and Control Center %d",
						botmaster, cc[0]);
			LOG_STRING(message);
			free(message);
			cc[2] = fork();
			if (cc[2]) {
				asprintf(&message,"Botmaster %d created Command and Control Center %d",
							botmaster, cc[0]);
				LOG_STRING(message);
				free(message);
				sleep(5);
				kill(cc[2], SIGUSR1);
				for (;;) {
					sleep(10);
					// do evil things
				}
			} else {
				execvp(candc[0], candc);
			}
		} else {
			execvp(candc[0], candc);
		}
	} else {
		execvp(candc[0], candc);
	}

}
