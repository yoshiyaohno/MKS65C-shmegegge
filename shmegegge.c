#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define KEY 0x00DEAD00


int main()
{
    int shmid;
    char *mem;
    char line[200];

    printf("PID: %i\n", getpid());

    printf("Generating shmid....\n");
    shmid = shmget(KEY, 200*sizeof(char), 0644 | IPC_CREAT);

    printf("Attaching to memory....\n");
    if((mem = shmat(shmid, NULL, 0)) == (void *)-1)
        perror("shmat");

    if(!*mem)
        printf("Created new shmem segment at %p\n", mem);
    else {
        printf("Found existing memory segment at %p.", mem);
        printf("Segment contains...\n\t%s\n", mem);
    }

    printf("Would you like to change the data in the segment? (y/n)\n>");
    fgets(line, 4, stdin);
    //printf("[DEBUG]\tline: <%s>\n", line);
    if(line[0] == 'y') {
        printf("Enter a new string....\n>");
        fgets(line, 200, stdin);
        strcpy(mem, line);
    }
    printf("Would you like to delete the segment? (y/n)\n>");
    fgets(line, 4, stdin);
    if(*line == 'y')
        if(shmctl(shmid, IPC_RMID, NULL) == -1)
            perror("shmctl");

    printf("Detatching from memory....\n");
    if(shmdt(mem))
        perror("shmdt");
    printf("Finishing....\n");
}
