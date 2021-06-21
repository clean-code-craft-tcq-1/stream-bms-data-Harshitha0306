#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "bms_Rx.h"


void signal_handler(int sig) 
{ 
  if (sig == SIGINT)
  { 
    sig_caught=1; 
    printf("got signal");
  } 
} 
int main()
{
	
    if (signal(SIGINT, signal_handler) == SIG_ERR) 
    { 
    fprintf(stderr, "signal func registration failed\n"); 
    return 1; 
    }

	BMSDataReceiverCalc();
}

