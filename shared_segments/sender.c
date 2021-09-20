#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include <time.h>

int main()
{
int i;
void *shared_memory;
void *shared_memory2;
int presionado;
int shmid;
int shmid2;

int bool1=0;


time_t now;
struct tm *ts;
char buf[80];

/* Get the current time */
now = time(NULL);
/* Format and print the time, "hh:mm:ss" */
ts = localtime(&now);
strftime(buf, sizeof(buf), "%H:%M:%S", ts);

shmid=shmget((key_t)2345, 1024, 0666);
shmid2=shmget((key_t)2346, 1024, 0666);
printf("Key of shared memory is %d\n",shmid);
if(shmid==-1){
	shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT);
	bool1=1;
}
if(shmid2==-1){
	shmid=shmget((key_t)2346, 1024, 0666|IPC_CREAT);
}

if(bool1){
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
	presionado = 1;
	char a[2] ;
	*a= presionado+'0';
	strcpy(shared_memory,a);
	printf("You wrote : %s\n",(char *)shared_memory);
	shared_memory2=shmat(shmid2,NULL,0); //process attached to shared memory segment
	strcpy(shared_memory2,buf);
	printf("You wrote : %s\n",(char *)shared_memory2);
}else{
	shared_memory=shmat(shmid,NULL,0);
	shared_memory2=shmat(shmid2,NULL,0);
	printf("Found: %s\n",(char *)shared_memory);
	printf("Found: %s\n",(char *)shared_memory2);
	struct tm tm;
	strptime(shared_memory2, "%H:%M:%S", &tm);
	time_t t = mktime(&tm);
	
	struct tm tm2;
	strptime(buf, "%H:%M:%S", &tm2);
	time_t t2 = mktime(&tm2);
	double diff_t;
	diff_t = difftime(t, t2);
	diff_t -= 30708719876;
	diff_t*=-1;
	printf("Execution time = %f\n", diff_t);
	if(diff_t>=8){
		presionado = 1;
	}else if(diff_t>=2){
		if(strcmp(shared_memory, "1") == 0){
			presionado = 2;
		}else if(strcmp(shared_memory, "2") == 0){
			presionado = 3;
		}else{
			presionado = 1;
		}	
	}else{
		goto end;
	}
	char a[2] ;
	*a= presionado+'0';
	strcpy(shared_memory,a);
	printf("You wrote : %s\n",(char *)shared_memory);
	shared_memory2=shmat(shmid2,NULL,0); //process attached to shared memory segment
	strcpy(shared_memory2,buf);
	printf("You wrote : %s\n",(char *)shared_memory2);

}
end:
printf("end");
   return(0);
}
