CFLAGS = -Wall -Werror

all: udpplay tcpplay repeater dehex


.PHONY: clean

clean:
	-rm udpplay tcpplay repeater dehex
