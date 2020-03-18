#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/* scan record
*/

struct MyStruct {
	// flags 1B
	unsigned char
		is_scanned :	1,
		is_open :		1,
		is_ssl :		1,
		is_http :		1,
		svc_done :		1,
		app_done :		1,
		error :			1,
		unassigned :	1;
	// scan values
	unsigned char ttl;
};
/*
	2B --> fallocate -l $(( 2**32 * 2)) MyStruct.db
*/

#define DECODE_FMT "| %10s: %d\n"
#define ifkey(k) if(strcmp(argv[2],k)==0)

void dprint(struct MyStruct d) {
	printf(DECODE_FMT, "is_scanned",	d.is_scanned);
	printf(DECODE_FMT, "is_open",		d.is_open);
	printf(DECODE_FMT, "is_ssl",		d.is_ssl);
	printf(DECODE_FMT, "is_http",		d.is_http);
	printf(DECODE_FMT, "svc_done",		d.svc_done);
	printf(DECODE_FMT, "app_done",		d.app_done);
	printf(DECODE_FMT, "error",			d.error);
	printf(DECODE_FMT, "TTL", d.ttl);
}
int main (int argc, char** argv) {
	FILE *fp;
	struct MyStruct data;
	unsigned long adr;
	unsigned int
		i,
		ret = 0,
		structsize = sizeof(struct MyStruct);

	adr = ntohl(inet_addr(argv[1])) * structsize; // adjust offset based on the size
	fp = fopen("MyStruct.db","r+");
	fseek(fp, adr, SEEK_SET);
	printf("address: %ld; ", adr);
// read
	if (argc == 2) {
		ret = fread(&data, structsize, 1, fp);
		printf("reading value: %x\n", data);
	}
// write
	else if (argc == 4) {
		i = atoi(argv[3]);
		ret = fread(&data, structsize, 1, fp);

		ifkey("is_scanned")	data.is_scanned = i;
		ifkey("is_open")	data.is_open = i;
		ifkey("is_ssl")		data.is_ssl = i;
		ifkey("is_http")	data.is_http = i;
		ifkey("svc_done")	data.svc_done = i;
		ifkey("app_done")	data.app_done = i;
		ifkey("error")		data.error = i;
		ifkey("ttl")		data.ttl = i;

		printf("setting value %x\n", data);
		fseek(fp, adr, SEEK_SET);
		ret = fwrite(&data, structsize, 1, fp);
	}
// usage
	else {
		printf("Usage:\n");
		printf("\t%s <IP>\n", argv[0]);
		printf("\t%s <IP> <struct-member-name> <intvalue>\n", argv[0]);
	}

	fclose(fp);
	dprint(data);
	return(ret);
}
