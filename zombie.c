#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Define the function to be called when ctrl-c (SIGINT) signal is sent to process
void
signal_callback_handler(int signum)
{
   if (signum == SIGUSR1) {
		for(;;) {
		}
   }
}

int main()
{
   // Register signal and signal handler
   signal(SIGUSR1, signal_callback_handler);

   while(1)
   {
      sleep(5);
   }
   return EXIT_SUCCESS;
}

