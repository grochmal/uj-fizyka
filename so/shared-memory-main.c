#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHM_SIZE 1024

int main(){
	switch(vfork()){
		case -1:
			perror("blad");
			exit(1);
		case 0:{
			key_t key= ftok("shm.c", 'A');
			int shmid = shmget(key,SHM_SIZE, 0666|IPC_CREAT);
			char* data = shmat(shmid,0,0);
			printf("Wpisuje: Hello World w procesie: %d %d \n",
			       getpid(), shmid);
			strncpy(data, "Hello World", SHM_SIZE);
			sleep(2);
			shmdt(data);
			exit(0);
		}
		default: {
			sleep(2);
			key_t key = ftok("shm.c", 'A');
			int shmid = shmget(key,SHM_SIZE, 0666);
			char* data = shmat(shmid, 0,0);
			printf("Pobralem: %s w procesie: %d\n",
			       data, getpid());
			exit(0);
		}
	}
	return 1;
}

