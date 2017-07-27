#include "functions.h"


double threshold2 = 5.9915;

void x2(char *filename)
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
    int i,j,m,l;
    char *input=(char*)malloc(256*sizeof(char));
    memset(input,0,256);
    int flag=1;
    int count0=0;
    int count1=0;
    int count00=0;
    int count01=0;
    int count10=0;
    int count11=0;
    char *binval=(char*)malloc(sizeof(char)*8);

    int prev_bit=0;
    int first_time=1;
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
                if(first_time==0)
                {
                    if(prev_bit==0 && binval[0]==0)
                        count00++;
                    else if(prev_bit==0 && binval[0]==1)
                        count01++;
                    else if(prev_bit==1 && binval[0]==0)
                        count10++;
                    else if(prev_bit==1 && binval[0]==1)
                        count11++;
                }
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
                first_time=0;
                //count 00,01,10,11
                for(m=0,l=m+1;m<7 && l<8;m++,l++)
                {
                    if(binval[m]==binval[l])
                    {
                        if(binval[m]==1 && binval[l]==1)
                            count11++;
                        else if(binval[m]==0 && binval[l]==0)
                            count00++;
                    }
                    else if(binval[m]!=binval[l])
                    {
                        if(binval[m]==1 && binval[l]==0)
                            count10++;
                        else if(binval[m]==0 && binval[l]==1)
                            count01++;
                    }
                }
                prev_bit=binval[7];
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
                if(first_time==0)
                {
                    if(prev_bit==0 && binval[0]==0)
                        count00++;
                    else if(prev_bit==0 && binval[0]==1)
                        count01++;
                    else if(prev_bit==1 && binval[0]==0)
                        count10++;
                    else if(prev_bit==1 && binval[0]==1)
                        count11++;
                }
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
                first_time=0;
                //count 00,01,10,11
                for(m=0,l=m+1;m<7 && l<8;m++,l++)
                {
                    if(binval[m]==binval[l])
                    {
                        if(binval[m]==1 && binval[l]==1)
                            count11++;
                        else if(binval[m]==0 && binval[l]==0)
                            count00++;
                    }
                    else if(binval[m]!=binval[l])
                    {
                        if(binval[m]==1 && binval[l]==0)
                            count10++;
                        else if(binval[m]==0 && binval[l]==1)
                            count01++;
                    }
                }
                prev_bit=binval[7]; 
            }
            memset(binval,0,8);
            
        }
        memset(input,0,256);

    }//while((n = fread(input, sizeof(char), 256, fp))!=0)
    if((count0+count1)<21)
        printf("\nn = %d\nx2: insufficient data\n",count0+count1);
    else
        printf("\nn = %d\nn0 = %d\nn1 = %d\nn00 = %d\nn01 = %d\nn10 = %d\nn11 = %d\n",count0+count1,count0,count1,count00,count01,count10,count11);


    int total_bits=count0+count1;
    double X2=((pow(count00,2)+pow(count01,2)+pow(count10,2)+pow(count11,2))*4/(double)(total_bits-1)) - ((pow(count1,2)+pow(count0,2))*2/(double)total_bits) +1;

    printf("x2 = %6f\n",X2);
    if(X2<threshold2)
        printf("pass/fail = pass\n");
    else
        printf("pass/fail = fail\n");
    free(binval);
}
