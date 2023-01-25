#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
	int fd,rd;

	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	char *str = (char*) shmat(shmid,(void*)0,0);

	printf("reading Data from file.........\n\n");

	fd=open("simple.txt",O_RDONLY);

	rd=read(fd,str,32);

	printf("Content of the file sent to the client\n");
	
	//detach from shared memory
	shmdt(str);

	return 0;
}

