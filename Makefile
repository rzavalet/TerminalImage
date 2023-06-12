#
# Makefile
# rzavalet, 2023-06-11 22:16
#
CC = clang
CFLAGS = -Wall -Wextra -I/home/rzavalet/opt/stb
LDFLAGS = -lm

all:
	$(CC) $(CFLAGS) main.c -o main $(LDFLAGS)

clean:
	-@rm main
	-@rm *.txt

# vim:ft=make
#
