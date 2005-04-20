#include <stdio.h>

int main(int argc , char * argv[])
{
	char buf[1024];
	int len = 0;
	char * p;
	int i;
	int o;
	int o1, o2;
	
	while(NULL != fgets(buf, 1024, stdin))
	{
		len = strlen(buf);
		//fprintf(stderr, "Read %i\n", len);
		int c = 0;
		int a;
		int sc = 0;
		o1 = o2 = -1;
		// offset correction.
		o1 = 0;
		a = 0;
		for(i=0; i < len; i++)
		{
			p = &buf[i];
			o = -1;
			if(*p >= '0' && *p <= '9')
				o = *p -'0';
			else if(*p >= 'a' && *p <= 'f')
				o = *p -'a'+10;
			else if(*p >= 'A' && *p <= 'F')
				o = *p -'A'+10;
			else if(*p == ' ' || *p == '\t' || *p == ':')
			{
				// inc space counter
				sc++;
				// if we run into more then 2, its garbage.
				if(sc>2)
					break;
				continue;
			}
			else
				break;
			// we must have got a good char, so reset space counter
			sc = 0;
			

			if(o >= 0)
			{
				c++;
				if(c > 39 )
					break;

				// which part of the octet are we reading?
				if(o1 == -1)
					o1 = o;
				else
					o2 = o;

				// Must have a full octet
				if(o2 != -1)
				{
					int n;

					a++;
					n = (o1 << 4) | o2;
					if(a > 4)
					{
						//printf("%c ", *p);
						//printf("%02x %02x ", o1, o2);
						//printf("%02x ", n);
						printf("%c", n);
					}
					//printf("%02i %02i ", o1, o2);
					o1 = o2 = -1;
				}

			}
			

		}
		//fwrite("\n", sizeof(char), 1, stdout);



	}


	return 0;
}
