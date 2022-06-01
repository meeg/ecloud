#include <stdio.h>
#include <string.h>
#include "gpib/ib.h"

#include "utils.h"

int main(int argc, char **argv)
{
	FILE *out;
	char devstat;
	int i;
	int dev;
	dev = ibdev(0, 16, 0, T30s, 1, 0);
	printf("device %d\n",dev);
	ibrsp(dev,&devstat);
	printf("devstat = %d\n",devstat);
	if (devstat&16) read_data(dev,stdout);
	write_cmd(dev,"DEBUON");
	write_cmd(dev,"FORM4");

	write_cmd(dev,"OUTPLIML");
	out = fopen("freq.txt","w");
	read_data(dev,out);
	fclose(out);
	
	write_cmd(dev,"OPC?");
	write_cmd(dev,"SING");
	read_data(dev,stdout);
	
	write_cmd(dev,"OUTPDATA");
	out = fopen("data.txt","w");
	read_data(dev,out);
	fclose(out);
	
	write_cmd(dev,"LOGM");
	write_cmd(dev,"OUTPFORM");
	out = fopen("logmag.txt","w");
	read_data(dev,out);
	fclose(out);
	
	write_cmd(dev,"PHAS");
	write_cmd(dev,"OUTPFORM");
	out = fopen("phase.txt","w");
	read_data(dev,out);
	fclose(out);
	
	write_cmd(dev,"DELA");
	write_cmd(dev,"OUTPFORM");
	out = fopen("delay.txt","w");
	read_data(dev,out);
	fclose(out);
	
	write_cmd(dev,"LOGM");
	write_cmd(dev,"CONT");
	ibloc(dev);
}

