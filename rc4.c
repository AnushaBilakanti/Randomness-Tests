#include "functions.h"

void rc4(char * p,int len)
{
	
	int i=0;
	int j=0;
	unsigned int key_stream[256]={0};
	unsigned char md5_buf[MD5_DIGEST_LENGTH];
    char *s=malloc(strlen(p)+3);
    int iter=0;
    for (i=0; i < 16; i++) 
    {
        sprintf(s, "%02d%s", i, p);
        MD5((unsigned char *)s, (unsigned int)(strlen(s)), (unsigned char *)md5_buf);
        //fwrite(md5_buf, 1, sizeof(md5_buf), stdout);
        for(j=0;j<MD5_DIGEST_LENGTH;j++)
		{
			key_stream[iter]=(unsigned int)md5_buf[j];
			iter++;
		}

    }
    free(s);


    //rc4init
    int state[256]={0};
    for(i=0;i<256;i++)
    {
    	state[i]=i;
    }
    int t=0;
    int k=0;
    for(i=0,j=0;i<256;i++,j=(j+1)%256)
    {
    	t=state[i];
    	k+=key_stream[j]+t;
    	k=k%256;
    	state[i]=state[k];
    	state[k]=t;
    }
    //rc4step


    int x=0;
    int y=0;
    if(len==0) // print all 256 from state array
	{
		for(j=0;j<256;j++)
		{
			fprintf(stdout, "%c",(unsigned char)state[j]);
		}	
	}
	else
	{
		while(len>0)
		{
			x=(x+1)%256;
			y = (y + state[x])%256;
			t = state[y];
			state[y] = state[x];
			state[x] = t;
			fprintf(stdout, "%c", (unsigned char) state[(state[x]+state[y])%256]);
			len--;
		}
	}
}
