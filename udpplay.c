/*
abest: cheap udp packet
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

	int sock, r, i;
	int z;
	int port = 12345;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	struct hostent *he;

	//ARGS
	if(argc<2)
	{
		fprintf(stderr, "%s <host> <port>\n", argv[0]);
		exit(1);
	}
	port = atoi(argv[2]);

	he = gethostbyname (argv[1]);
	if(he == NULL)
	{		
		fprintf(stderr, "%s: Unable to resolve host '%s' \n", argv[0],
				argv[1]);
		exit(1);
	}

	sAddr.sin_family = he->h_addrtype;
	memcpy((char*) &sAddr.sin_addr.s_addr, he->h_addr_list[0], he->h_length);
	sAddr.sin_port = htons(port);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(0 > sock)
	{
		fprintf(stderr, "%s: unable to open socket\n", argv[0]);
		exit(1);
	}
	
    cAddr.sin_family = AF_INET;
	cAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cAddr.sin_port = htons(0);
	
	if( 0 > bind(sock, (struct sockaddr *) &cAddr, sizeof(cAddr)))
	{
		fprintf(stderr, "%s: unable to bind socket\n", argv[0]);
		exit(1);
	}
	
	// Not exactly the best method.
	do
	{
		char buf[64000];
		//65506
		z = fread(buf, 1, 64000, stdin);
			

		if(z > 0)
		{
			if( 0 > sendto(sock, buf, z, 0,
						(struct sockaddr *) &sAddr,
						sizeof(sAddr)))
			{
				fprintf(stderr, "%s: unable to write to socket\n", argv[0]);
				exit(1);
			}
		}
	} while (z>0);

	return 0;
}
