#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>

/* 
 * routine notice the _1 the version number 
 * notice the client handle, not sued here but needs to be 
 * a parameter 
 */

char ** average_1(char **input, CLIENT *client) 
  {
  // Take this out for longer strings. Buffer overflow.
  strcat(*input, " Added by client");
  printf("%s\n", *input);  
  return ( input );
}

/* 
 * server stub 'average_1_svc function handle called in avg_svc that was
 * generated by rpcgen 
 * FYI:
 *   result = (*local)((char *)&argument, rqstp);
 *   where local is (char *(*)(char *, struct svc_req *)) average_1_svc;
 */
 
char ** average_1_svc(char **input, struct svc_req *svc) 
  {
  CLIENT *client;
  return( average_1( input, client) );
  }