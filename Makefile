# fallocate -l $((2**32)) tcp-80

all: http struct

http: http.c
	gcc http.c -o http

struct: struct.c
	gcc struct.c -o struct

