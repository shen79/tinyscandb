# fallocate -l $((2**32)) tcp-80

http: http.c
	gcc http.c -o http

all: http
