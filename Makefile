CC = gcc
CFLAGS = -Wall

all: encode decode

encode: encoding/encoding.c
	$(CC) $(CFLAGS) -o encode encoding/encoding.c

decode: decoding/decoding.c
	$(CC) $(CFLAGS) -o decode decoding/decoding.c

run-encode: encode
	./encode inputFile outputFile

run-decode: decode
	./decode outputFile decoded_outputFile

clean:
	rm -f encode decode outputFile decoded_outputFile

.PHONY: all clean run-encode run-decode

