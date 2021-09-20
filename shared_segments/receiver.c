#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>

int main()
{
int i;
void *shared_memory;
char buff[100];
int shmid;
while(1){
	shmid=shmget((key_t)2345, 1024, 0666);
//	printf("Key of shared memory is %d\n",shmid);
	if(shmid==-1){
		printf("0\n");
	}else{
		shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
//		printf("Process attached at %p\n",shared_memory);
		printf("El boton ha sido presionado %s vez\n",(char *)shared_memory);
	}
  sleep(1);	
}
}
