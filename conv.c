/************************
perform 1D & 2D Convolutions:

	1D convolution: size of output convolution = data_size + kernel_size -1
	
	Due to the size of the output convolution array being > the size of the data, the data array is set in a padded array
		where padding = data_sz + (k_size-1)*2.

************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval t0, t1;



/*** Functions **/

void convolution(int *d, int d_sz, int *k, int k_sz, int *c);

void display1d(int *d, int len); 


int main(){

	//1D array
	int sz = 10; // size of input data
	int ksz = 3; // size of kernel array
	int pad = sz +((ksz-1)*2); // size of array storing input data for conv
	int data[pad]; //array storing input data
	memset(data, 0, pad*sizeof(int)); 
	
	int conv[pad];	// convolutional output array
	memset(conv, 0, sizeof(int)*pad ); //set to zero


	//init array data with data
	int cnt=1; 
	for (int i = ksz -1; i< (sz+ksz-1); i++){
			data[i] = 1; 
	}
	
	//1D kernel
	int k[ksz]; 
	//init kernel to 1's
	for (int i = 0; i<ksz; i++){k[i] = 1; }
 
	printf("Printing Input Array:\n"); 
	display1d(data, pad);

	printf("Printing Kernel:\n");
	display1d(k,ksz);
	
	gettimeofday(&t0, NULL);
	convolution(data, pad, k, ksz, conv);
	gettimeofday(&t1, NULL);

	display1d(conv, pad);


	printf("%i sec and %i usec\n", t1.tv_sec-t0.tv_sec, t1.tv_usec-t0.tv_usec);

	
return 0; 
}//main


/* Perform 1 dimensional convolution, flip and shift
	int *d - input data array
	int d_sz - size of input data array
	int *k - kernel array
	int k_sz - size of kernel array
	int *c  - array to hold output of convolution
*/

void convolution( int *d, int d_sz, int *k, int k_sz, int *c){
	
	//perform 1D convolution
	int k_shift=k_sz -1;
	int temp = 0; 
	int out_index= k_sz-2;
	//printf("\n"); 
	
	for (int i = k_sz-1; i<d_sz; i++){
		for (int p = i; p>i-k_sz; p--){
			temp += k[k_shift--]*d[p];
		}
//		printf("\n%i:\t%i\t%i\n", i, out_index, temp); 
		c[out_index++] = temp; 
		temp =0; 
		k_shift= k_sz-1; 
	}
} 


/*
Print 1 dimensional array
	int *c - array to be printed
	int len - size of array
*/ 	

void display1d(int *c, int len){
 
	for (int i = 0; i<len; i++){
			printf("%i ", c[i]);
	}
	printf("\n\n"); 
}

