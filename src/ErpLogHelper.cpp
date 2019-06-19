//============================================================================
// Name        : ErpLogHelper.cpp
// Author      : A. Kwiek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <thread>
using namespace std;


time_t timer;
FILE *fp;

void * log_thread(void*) {

}
char* asctime(const struct tm *timeptr)
{
	static const char wday_name[][4] = {
			"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static const char mon_name[][4] = {
			"Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	static char result[26];
	sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n\r",
			wday_name[timeptr->tm_wday],
			mon_name[timeptr->tm_mon],
			timeptr->tm_mday, timeptr->tm_hour,
			timeptr->tm_min, timeptr->tm_sec,
			1900 + timeptr->tm_year);
	return result;
}

int main() {
	cout << "!!!Hello CV!!!" << endl; // prints !!!Hello CV!!!

	time_t rawtime;
	int min,
	min_c,
	hour_c;

	struct tm * timeinfo;
	string jk;
	char fn[10],
	log[50];
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	min = timeinfo->tm_min;
	sprintf(fn,"%d.%02d.%02d.log", timeinfo->tm_year+1900, timeinfo->tm_mon, timeinfo->tm_mday);
	fp = fopen(fn,"a");
	if(fp!=NULL) {
		printf("ok\n");
		sprintf(log,"%02d.%02d.%02d - %02d:%02d\n\r",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec, hour_c, min_c);
		fwrite(log,sizeof(char),17,fp);
				cout << "min: " << min << " tm_min: " << timeinfo->tm_min << endl;
	} else {
		printf("some fucking problem...\n");
		return -1;
	}
	fclose(fp);

	printf ( "The current date/time is: %s", asctime (timeinfo) );
	printf ( "tm_hour: %d\n", timeinfo->tm_hour );
	printf ( "tm_isdst: %d\n", timeinfo->tm_isdst );
	printf ( "tm_mday: %d\n", timeinfo->tm_mday );
	printf ( "tm_min: %d\n", timeinfo->tm_min );
	printf ( "tm_mon: %d\n", timeinfo->tm_mon );
	printf ( "tm_sec: %d\n", timeinfo->tm_sec );
	printf ( "tm_wday: %d\n", timeinfo->tm_wday );
	printf ( "tm_yday: %d\n", timeinfo->tm_yday );
	printf ( "tm_year: %d\n", timeinfo->tm_year );

	while(1) {

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
//		cout << "min: " << min << " tm_min: " << timeinfo->tm_min << endl;
		if(timeinfo->tm_min != min) {
			fp = fopen(fn,"a");
			if(fp!=NULL) {
				cout << "!!! tick !!!" << endl; // prints !!!Hello CV!!!
			} else {
				printf("some fucking problem...\n");
				return -1;
			}

			cout << "min " << min << " tm_min " << timeinfo->tm_min << endl;
			min_c++;
			if((min_c !=  0)&&(min_c%60 == 0)) {
				hour_c++;
			}
			sprintf(log,"%02d.%02d.%02d - %02d:%02d\n\r",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec, hour_c, min_c);
			fwrite(log,sizeof(char),17,fp);
			fclose(fp);
			min = timeinfo->tm_min;
		}
	}

	return 0;
}
