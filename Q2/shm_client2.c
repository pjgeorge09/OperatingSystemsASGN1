/*
 * shm-client - client program to demonstrate shared memory.
 * shm-client - not sure of the origin of these code segments.
 * possibly: David Marshalls course : http://www.cs.cf.ac.uk/Dave/C/CE.html
 * or Steve Holmes : http://www2.its.strath.ac.uk/courses/c/
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SHMSZ     27

int
main()
{
    int shmid, shmid2;
    key_t key, key2;
    char *shm, *s, *shm2, *s2;
    char *memory;
    memory = " memory";

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 8403;
    key2 = 8912;

   

    /*
     * Locate the string segment.
     */
    if( (shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
    /*
     * Locate the integer segment.
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

    while( *shm != '2' )
        sleep(1);

    s2 = shm2;
    
    /*
     * Now write " memory" to string memory location
     */

    strcat(s2, memory);
    /*
     * Now read what the server put in the memory INTEGER.
     */
    for( s2 = shm2; *s2 != (char) NULL; s2++ )
        putchar(*s2);
    putchar('\n');

    /*
     * Now read what the server put in the memory INTEGER.
     */
    // int i = 0;
    // for( s2 = shm2; *s2 != (char) NULL; s2++ )
    //     thing[i] = *s2;
    //     i++;

    // int x = 0;
    // for ( x = 0; x<strlen(memory); x++)
    //     thing[i] = memory[x];
    //     i++;

    // printf(thing);


    
    s = shm;
    *s = '3';

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    // *shm = '*';
    // *shm2= '*';

    return 0;
}
