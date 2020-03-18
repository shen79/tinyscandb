# tinyscandb

## wtf this bro?

This, but a poc.

## set up / build

First you have to create a db file:

	fallocate -l $(( 2**32 )) tcp-80.db
	fallocate -l $(( 2**32 * 2 )) MyStruct.db

Next, build

	make

## http.c

### how to use

We have one byte in this poc/version, so its 8 bits => 8 flags.

| flag name		| value | description |
| ------------- | -----:| ----------- |
| SCANNED     	| 1		| the IP was scanned
| PORT_OPEN   	| 2		| port was open
| IS_HTTP     	| 4		| yes it's http
| IS_SSL      	| 8		| it's SSL
| SVC_DONE    	| 16	| service scan finished
| APP_DONE    	| 32	| application scan finished
| UNASSIGNED  	| 64	| unassigned
| ERROR       	| 128	| set this bit to indicate an error in the last test


you can set and query flags like this:

#### querying an empty value
	./http 127.0.0.1
	address: 2130706433; reading value: 0

#### setting value 1
	./http 127.0.0.1 1
	address: 2130706433; setting value 1
	- port scanned

#### set 7
	# ./http 127.0.0.1 7
	address: 2130706433; setting value 7
	- port scanned
	- port is open
	- it's an http service

#### set 255
	# ./http 127.0.0.1 255
	address: 2130706433; setting value 255
	- port scanned
	- port is open
	- it's an http service
	- SSL enabled service
	- service scane done
	- application scan done
	- shit happened during testing

## struct.c

### how to use

#### query

	./struct 127.0.0.1
	address: 4261412866; reading value: 7b03
	| is_scanned: 1
	|    is_open: 1
	|     is_ssl: 0
	|    is_http: 0
	|   svc_done: 0
	|   app_done: 0
	|      error: 0
	|        TTL: 123

#### set

	./struct 127.0.0.1 error 1
	address: 4261412866; setting value 7b43
	| is_scanned: 1
	|    is_open: 1
	|     is_ssl: 0
	|    is_http: 0
	|   svc_done: 0
	|   app_done: 0
	|      error: 1
	|        TTL: 123

