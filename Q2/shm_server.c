#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <unistd.h>

/* 
 * shm-server - not sure of the origin of code segment.
 * Old source, not sure of the origin
 *  possibly: David Marshalls course : http://www.cs.cf.ac.uk/Dave/C/CE.html
 * or Steve Holmes : http://www2.its.strath.ac.uk/courses/c/
 */



#define SHMSZ     27


int 
main()
{
    char c,c2;
    int shmid,shmid2;
    key_t key,key2;
    char *shm, *s, *s2, *shm2, *s3, *shm3;
    char *shared, *memory;
    shared = "shared";
    memory = " memory";
    

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 8403;
    key2 = 8912;
    /*
     * Create the string segment.
     */
    if( (shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
    /*
     * Create the integer segment.
     */
    if( (shmid2 = shmget(key2, SHMSZ, IPC_CREAT | 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }


    /*
     * Now we attach the segment to our string data space.
     */
    if( (shm = shmat(shmid, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }
    /*
     * Now we attach the segment to our integer data space.
     */
    if( (shm2 = shmat(shmid2, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;
    *s = '1';
if (*shm == '1'){    
    pid_t pid1 = fork();
    
    if (pid1 < 0){
	printf("PID %d fork failed\n", pid1);
	exit(0);
	}
    else if (pid1 == 0){
	s2 = shm2;
	strcpy(s2, shared);
	for( s2 = shm2; *s2 != (char) NULL; s2++ )
        	putchar(*s2);
    	putchar('\n');
	s = shm;
	*s = '2';
	}
    else{
	//parent
	//printf("Went to the parent\n");
	while(NULL);
	}
}
if (*shm=='2'){
    pid_t pid2 = fork();
    
    if (pid2 < 0){
        printf("PID %d fork failed\n", pid2);
        exit(0);
        }
    else if (pid2 == 0){
        s3 = shm2;
        strcat(s3, memory);
        for( s2 = shm2; *s2 != (char) NULL; s2++ )
                putchar(*s2);
        putchar('\n');
        s = shm;
        *s = '3';
        }
    else{
        //parent
        //printf("Went to the parent\n");
        while(NULL);
        }
}

    //while( *shm != '3')
        //sleep(1);
    if(*shm == '3'){
    printf("GoodBye\n");
}

    shmdt(s);
    shmdt(s2);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID,NULL);

    return 0;

}
