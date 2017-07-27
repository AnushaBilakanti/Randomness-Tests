#include "functions.h"


double threshold1 = 3.8415;
char *char_2_bin(char ch)
{
	char *binval=(char*)malloc(sizeof(char)*8);
	int i;
	int mask = 0x80;
	for(i=0;i<8;i++)
	{
		binval[i] = (ch & mask) >> (7-i);
        mask >>= 1;
	}
	return binval;
}


void x1(char *filename)
{
	FILE *fp=NULL;
	if(filename==NULL)
	{
		fp=stdin;
	}
	else
	{
		fp=fopen(filename,"rb");
	}
	
	if(fp==NULL)
	{
		fprintf(stderr, "input file does not exist\n");
		exit(0);
	}
	int n=0;
	int i,j;
	char *input=(char*)malloc(256*sizeof(char));
	memset(input,0,256);
	int flag=1;
	int count0=0;
	int count1=0;
	char *binval=(char*)malloc(sizeof(char)*8);

	//there can be more than 256bytes;but only first 256btes must be printed
	while((n = fread(input, sizeof(char), 256, fp))!=0)
	{
		if(n==256)
		{
			if(flag==1)
			{
				for(i=0;i<256;i++)
				{
					if(i%16==0 && i!=0)
							printf("\n");		
					printf("%02x", (unsigned char)input[i]);
				}
				flag=0;
			}
			for(i=0;i<256;i++)
			{
				//read the bits to count number of 0's and 1's
				
				memset(binval,0,8);
				binval=char_2_bin(input[i]);
				for(j=0;j<8;j++)
				{
					if(binval[j]==0)
					{
						count0++;
					}
					else if(binval[j]==1)
					{
						count1++;
					}
				}	
			}
			memset(binval,0,8);	
		}//n==256
		else
		{
			if(flag==1)
			{
				for(i=0;i<n;i++)
				{
					if(i%16==0 && i!=0)
							printf("\n");		
					printf("%02x", (unsigned char)input[i]);
				}
				flag=0;
			}
			for(i=0;i<n;i++)
			{
				//read the bits to count number of 0's and 1's
				
				memset(binval,0,8);
				binval=char_2_bin(input[i]);
				for(j=0;j<8;j++)
				{
					if(binval[j]==0)
					{
						count0++;
					}
					else if(binval[j]==1)
					{
						count1++;
					}
				}	
			}
			memset(binval,0,8);
			
		}
		memset(input,0,256);

	}//while((n = fread(input, sizeof(char), 256, fp))!=0)
	if((count0+count1)<10)
		printf("\nn = %d\nx1: insufficient data\n",count0+count1);
	else
		printf("\nn = %d\nn0 = %d\nn1 = %d\n",count0+count1,count0,count1);
	double numerator=pow((count0-count1),2);
	double sum=(double)count0+(double)count1;
	double X1=(double)numerator/sum;
	printf("x1 = %f\n",X1);
	if(X1<threshold1)
		printf("pass/fail = pass\n");
	else
		printf("pass/fail = fail\n");
	free(binval);
}
