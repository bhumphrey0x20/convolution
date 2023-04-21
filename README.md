# convolution
1-D and 2-D Convolution in C

A while back I saw a job announcment for an embedded C engineer. They really wanted someone would could code a convolution ( I think it was mentioned 3 times in the ad). I decided to dust off my Signals and Systems skills and implement one. This was not written for an embedded system but could be easily transfer to one. 

The input data and the kernel are simple box functions. The input data array is prepadded and the same size as the output array also padded. To change the data or the kernel size or shape, you will need to manually do so in the .c file. 

These files were written in C and compiled in Linux using gcc. 


conv.c is a simple 1 dimensional convolution. 

conv2.c is a 2-dimensional convolution. 

