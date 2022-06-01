#include <stdio.h>
#include "gpib/ib.h"

#include "utils.h"

int main(int argc, char **argv)
{
	FILE *out;
	char devstat;
	int i;
	int dev;
	dev = ibdev(0, 16, 0, T1s, 1, 0);
	printf("device %d\n",dev);
	write_cmd(dev,"DEBUON");
	write_cmd(dev,"FORM4");
	char temp[100];
	for (i=1;i<13;i++)
	{
		sprintf(temp,"OUTPCALC%02d",i);
		write_cmd(dev,temp);
		sprintf(temp,"calc%02d.txt",i);
		out = fopen(temp,"w");
		read_data(dev,out);
		fclose(out);
	}
	ibloc(dev);
}
