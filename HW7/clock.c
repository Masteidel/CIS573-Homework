#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t print_flag = false;

int seconds, minutes, hours;

void handle_alarm(int sig) {
	print_flag = true;
}

int main() {
	time_t rawtime;
	struct tm *info;
	time( &rawtime );
	info = localtime( &rawtime );
	seconds = info->tm_sec;
	minutes = info->tm_min;
	hours = info->tm_hour;

	signal(SIGALRM, handle_alarm);
	alarm(1);
	for (;;) {
		sleep(5);
		if (print_flag) {
			
			if(hours < 10) {
				printf("0%d:", hours);
			} else {
				printf("%d:", hours);
			}

			if(minutes < 10) {
				printf("0%d:", minutes);
			} else {
				printf("%d:", minutes);
			}

			if(seconds < 10) {
				printf("0%d", seconds);
			} else {
				printf("%d", seconds);
			}

			if(seconds < 59) {
				seconds++;
			} else {
				seconds = 0;
				if(minutes < 59) {
					minutes++;
				} else {
					minutes = 0;
					if(hours < 23) {
						hours++;
					} else {
						hours = 0;
					}
				}
			}
			printf("\n");
			print_flag = false;
			alarm(1);
		}
	}
	return 0;
}