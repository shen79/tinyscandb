#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SCANNED		1
#define PORT_OPEN	2
#define IS_HTTP		4
#define IS_SSL		8
#define SVC_DONE	16
#define APP_DONE	32
#define UNASSIGNED	64
#define ERROR		128

void decode(char c) {
	if (c & SCANNED)		printf("- port scanned\n");
	if (c & PORT_OPEN)		printf("- port is open\n");
	if (c & IS_HTTP)		printf("- it's an http service\n");
	if (c & IS_SSL)			printf("- SSL enabled service\n");
	if (c & SVC_DONE)		printf("- service scane done\n");
	if (c & APP_DONE)		printf("- application scan done\n");
//	if (c & UNASSIGNED)		printf("- unassigned\n");
	if (c & ERROR)			printf("- shit happened during testing\n");
}

int main (int argc, char** argv) {
	FILE *fp;
	unsigned char data;
	unsigned int adr, ret = 0;
	adr = ntohl(inet_addr(argv[1]));
	fp = fopen("tcp-80.db","r+");
	fseek(fp, adr, SEEK_SET );
	printf("address: %d; ", adr);
	if (argc == 2) { // read
		data = fgetc(fp);
		printf("reading value: %x\n", data);
	}
	else if (argc == 3) { // write
		data = atoi(argv[2]);
		printf("setting value %d\n", data);
		ret = fputc(data, fp);
	}
	fclose(fp);
	decode(data);
	return(ret);
}
