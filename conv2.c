/************************
perform 1D & 2D Convolutions:

	
	2D Convouluion: size of output convolution Rows = data_row + kernel_row -1
											   Cols = data_col + kernel_col -1

	Due to output convolution size being > input data size the data is set in a padded array
		where padding = data_sz + (k_size-1)*2 for 2D convolutions (Rows and Cols each).

************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval t0, t1;



/*** Functions **/

int conv2d(int **data, int d_r, int d_c, int **k, int k_r, int k_c, int **c);

void display2d(int **a, int r, int c);



int main(){

	 // set up 2D data, kernel for convolution
	int dr= 10; 
	int dc= dr;
	int kr = 3;
	int kc = kr;
	int padr= dr + (kr-1)*2;
	int padc = dc + (kc-1)*2;		
	
	//create and init data array
	int *data2[padr]; 
	for(int i = 0; i<padr; i++){
		data2[i] = (int *)malloc(padc*sizeof(int)); 
	}
	printf("Conv Size: %i\n\n", (dr+kr-1));
	printf("pad row/col:  %i\n", padc);
	printf("Kern row/col: %i\n", kc);
	
	//init data array with data
	int cnt = 1; 
	for(int i = kr-1; i<dr+kr-1; i++){
		for(int j =kc-1; j<dc+kc-1; j++){
			data2[i][j] = cnt++; 
		}
	}
	
	//create kernel
	int *k[kr]; 
	for( int i = 0; i<kr; i++){
		k[i] = (int *)malloc(kc*sizeof(int)); 
	}	
	//init kernel to 1s
	for( int i = 0; i<kr; i++){
		for(int j = 0; j<kc; j++){
			k[i][j] = 1; 
		}
	}

  	//Create padded 2D array for conv output
	int *conv[padr];
	for (int i = 0; i<padr; i++){ 
		conv[i] = (int *)malloc(padc*sizeof(int));
	}



	// printf data array
	printf("Data array: \n"); 
	display2d(data2, padr, padc);
	//printf kernel array
	printf("Kernel array: \n"); 
	display2d(k, kr, kc);
	
	gettimeofday(&t0, NULL);
	conv2d(data2,  padr,  padc, k,  kr,  kc, conv);
	gettimeofday(&t1, NULL);
	
	printf("2 Dimentional Convolution:\n"); 
	display2d(conv, padr, padc); 
	
	printf("2D Conv Time:%i sec and %i usec\n", t1.tv_sec-t0.tv_sec, t1.tv_usec-t0.tv_usec);
	
return 0; 
}//main




/***************************************
	Implement 2D convolution

***************************************/


int conv2d(int **data, int dm, int dn, int **k, int km, int kn, int **c){


	//perform 2D convolution
	
//TODO:
	// 2D conv
	// 1) Use 2 for loops to shift "index pt" (bottom right corner) of kernel along the data array
	// 2) calculate conv with 2 for loops using current index pts and moving backwards

	int kernelR = km-1; 
	int kernelC = kn-1;
	int temp=0; 
	int or=km-2;
	int oc=kn-2; 
	int stopC = dn-((kn-1)*2) +kn;
	
//printf("stopC: %i\n\n", stopC); 	
	for(int i = km-1; i< dm; i++){
		for(int j = kn-1; j< dn; j++){
			//calculate conv from bottom row to top row
			// cal conv from right of kernel to left
			for( int o = i; o > i-km; o--){
				for( int p = j; p > j-kn; p--){
					temp+= k[kernelR][kernelC--]*data[o][p];

				}//for p

				kernelC=kn-1;
				kernelR--;

			}//for o
			// end of calculation for kernel shift, write to out array andreset kernel and out array indices
				kernelR = km-1;
				kernelC = kn-1;
				c[or][oc++]= temp;
				temp = 0; 
		}// for j
		oc = kn-2; 
		or++; 
//printf("\n"); 		
	}//for i
	
	// print output array
//	printf("Conv Output:\n"); 
//	display2d(out, dm, dn); 
return 0; 
}	



void display2d(int **a, int c, int r){

	for (int i = 0; i< c; i++){
		for(int j =0; j<r; j++){
			printf("%i ", a[i][j]); 
		}
		printf("\n"); 
	}
	printf("\n\n"); 
}
