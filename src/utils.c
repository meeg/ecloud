//#include <ctype.h>
//#include <errno.h>
#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <stdint.h>
#include <string.h>
//#include <getopt.h>
#include "gpib/ib.h"

#include "utils.h"


void handle_error(int dev)
{
	char devstat;
	char err[DATALEN+1];
	ibrsp(dev,&devstat);
	printf("devstat = %d\n",devstat);

	while (devstat&8)
	{
		ibwrt(dev, "OUTPERRO", 8);
		ibrd(dev,err,DATALEN);
		err[ibcnt]='\0';
		printf("error %s",err);
		ibrsp(dev,&devstat);
		printf("devstat = %d\n",devstat);
	}
}

int read_data(int dev, FILE *fd)
{
	char data[DATALEN+1];
	int datacnt = 0;
	do
	{
		ibrd(dev,data,DATALEN);
		if (iberr)
		{
			printf("iberr %d\n",iberr);
			return 0;
		}
		datacnt+=ibcnt;
		data[ibcnt]='\0';
		fputs(data,fd);
		printf("iberr %d, ibsta %x, ibcnt %d\n",iberr, ibsta, ibcnt);
	}
	while (!(ibsta&0x2000)); //no EOI
	printf("Read %d bytes\n",datacnt);
	return datacnt;
}

void write_cmd(int dev, char *command)
{
	ibwrt(dev, command, strlen(command));
	printf("iberr %d, ibsta %x, ibcnt %d, command \"%s\"\n",iberr, ibsta, ibcnt, command);
	handle_error(dev);
}
