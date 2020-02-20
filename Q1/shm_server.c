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
    char *shm, *s, *s2, *shm2;
    

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
    
    // *s = (char) NULL;

    // s2 = shm2;

    // for( c2 = 'a'; c2<= 'z'; c2++ )
    //     *s2++ = c2;

    // *s2 = (char) NULL;

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    
    while( *shm != '3')
        sleep(1);
    printf("GoodBye\n");


    shmdt(s);
    shmdt(s2);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID,NULL);

    return 0;



}
