#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>

/* run locally on 'server' called by a remote client. */
static double sum_avg;

/* 
 * routine notice the _1 the version number 
 * notice the client handle, not sued here but needs to be 
 * a parameter 
 */

double * average_1(input_data *input, CLIENT *client) 
  {

  /* input is paramters were marshalled by genrated routine */
  /*  a pointer to a double, is set to begining of data array  */
  double *dp = input->input_data.input_data_val;
  int length = input->input_data.input_data_len; //Should be data length for ease of use
  double values[length];
  u_int x;
  sum_avg = 0;

  // A loop for all data from dp
  for (x=0; x<= length; x++){
	values[x] = *dp;
	dp++;
  }

  // Basic sort
  int temp, i, j, k;
  for (j = 0; j < length; ++j){
	for (k = j + 1; k < length; ++k){
		if (values[j] > values[k]){
            		temp = values[j];
            		values[j] = values[k];
            		values[k] = temp;
         	}
      	}
   }
  // Get the median
  double median;
  printf("Length is %i\n",length);
  if (length%2 == 0){
	// For a length, like 6, it should get values[3] values[4], add them, then divide by 2
	printf("Median is between %e and %e\n", values[(length/2)-1], 
			 values[length/2]);
	median= ((values[(length/2)-1]+values[((length/2))])/2);
  }
  else{
	median= (values[length/2]);
  }
  
  // Return the memory address of the created median
  sum_avg = median; // Add this because they use global var
  return ( &sum_avg );
  /* iterate until end of number of times (data_len)
  for( i = 1; i <= input->input_data.input_data_len; i++ )
    {
    sum_avg = sum_avg + *dp;   add what ptrs points  to ( '*' gets content ) 
    dp++;
    }
  */
  //sum_avg = sum_avg / input->input_data.input_data_len;
  
  //return( &sum_avg );
}

/* 
 * server stub 'average_1_svc function handle called in avg_svc that was
 * generated by rpcgen 
 * FYI:
 *   result = (*local)((char *)&argument, rqstp);
 *   where local is (char *(*)(char *, struct svc_req *)) average_1_svc;
 */
 
double * average_1_svc(input_data *input, struct svc_req *svc) 
  {
  CLIENT *client;
  return( average_1( input, client) );
  }
