#include <fcntl.h> // this library adds the file control options 
#include <stdlib.h>// this library adds general purpose tools 
#include <unistd.h>// adds the header file
#include <stdio.h>// adds file input and output 
#define BUF_SIZE 500 //sets the buffer size
#define OUTPUT_MODE 0700 //sets the output mode
int main(int argc, char *argv[])// inisalises the class
{
	int in_fd, out_fd;// insalises 2 integers
	int rd_size = 1, wr_size; //sets rd_size to 1 and insalises the integer wr_size
	char buf[BUF_SIZE]; //insalies a char taht is the buffer size
	if (argc != 3) // if the argc is not 3 the it does the following 
		exit(1); // retruns the value 1
	in_fd = open(argv[1], O_RDONLY); //open the file and puts it in the file descriptor
	if (in_fd < 0) // if the in file descriptor is more then 0 it does the following
		exit(2);    // retruns the value 2
	out_fd = creat(argv[2],OUTPUT_MODE); //creates the file
	if (out_fd < 0) // if the out file descriptor is less then 0 it does the following
		exit(3); //returns 3
	while (rd_size > 0) {    //loops through while the read size is more the 0
		rd_size = read(in_fd, buf,BUF_SIZE);//reads the size of the file
		if (rd_size <0)//if the read size is more the 0 it does the following 
			exit(4);//returns 4
		wr_size = write(out_fd, buf, rd_size); //writes the file
		if (wr_size<=0){ //if the write size is less then or equal to 0 it does the following
			close(in_fd); //closes the in file descriptor
			close(out_fd); //closes the out file descriptor
			exit(5); //retruns 5
		}
	
	}
}