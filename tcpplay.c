/*
abest: cheap tcp
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

// NOT for TCP
#define MAX_PACKET (0xffff - 29)
#define BUFSIZE 1024

int main(int argc, char *argv[])
{

	int sock, r, i;
	int z;
	int len;
	int port = 12345;
	struct sockaddr_in sAddr;
	//struct sockaddr_in cAddr;           
	struct hostent *he;
	char * buf;
	int buflen = 0;
	char * p;

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

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > sock)
	{
		fprintf(stderr, "%s: unable to open socket\n", argv[0]);
		exit(1);
	}
	
	/*
    cAddr.sin_family = AF_INET;
	cAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cAddr.sin_port = htons(0);
	
	if( 0 > bind(sock, (struct sockaddr *) &cAddr, sizeof(cAddr)))
	{
		fprintf(stderr, "%s: unable to bind socket\n", argv[0]);
		exit(1);
	}
	*/
	if(-1 == connect(sock, (struct sockaddr *)&sAddr, sizeof(struct sockaddr)))
	{
		fprintf(stderr, "%s: unable to connect\n", argv[0]);
		exit(1);
	}

	
	// Not exactly the best method.
	len = 0;
	p = buf = malloc(sizeof(char)*BUFSIZE);
	buflen = BUFSIZE;

	if(!buf)
	{
		fprintf(stderr, "%s: malloc failed\n", argv[0]);
		exit(1);
	}

	do
	{
		if(len == buflen)
		{
			buf = (char * )realloc(buf, 
					(sizeof(char) * buflen) + (sizeof(char) * BUFSIZE));
			if(!buf)
			{
				fprintf(stderr, "%s: Realloc failed\n", argv[0]);
				exit(1);
			}
			p = buf;
			p += len;
			buflen += BUFSIZE;
		}
		
		z = fread(p, sizeof(char), buflen-len, stdin);
		if(z > 0)
		{
			len += z;
			p += z;
		}
	} while (z>0);
	
	/*
    fwrite(buf, len, sizeof(char), stdout);
	
	return 1;
	*/
			

	r = send(sock, buf, len, 0);
	if( 0 > r)
	{
		fprintf(stderr, "r = %i\n", r);
		fprintf(stderr, "%s: unable to write to socket\n", argv[0]);
		exit(1);
	}

	return 0;
}
