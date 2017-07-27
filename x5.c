#include "functions.h"


double pos_threshold5 = 1.9600;
double neg_threshold5 = -1.9600;


void x5(int dval, char *filename)
{
    
    unsigned char *original_str=(unsigned char *)malloc(2222220*sizeof(unsigned char));
    memset(original_str,0,2222220);

    FILE * fp;
    if(filename==NULL)
        fp = stdin;
    else
        fp = fopen(filename, "rb");
    
    if(fp==NULL)
    {
        fprintf(stderr, "input file does not exist\n");
        exit(0);
    }

    int filesize=0;
    //there can be more than 256bytes;but only first 256btes must be printed
    char ch=0;
    int counter=0;
    int i,j;
    while(!(feof(fp)))
    {
        ch=0;
        fread(&ch,sizeof(char),1,fp);
        filesize++;
        if(filesize<257)
        {
            if((filesize-1)%16==0 && filesize!=1)
                printf("\n");       
            printf("%02x", (unsigned char)ch);
        }
        int mask = 0x80;
        for(j=0;j<8;j++)
        {
            // original_str[counter]=(ch>>j)&1;
            // counter++;

            original_str[counter] = (ch & mask) >> (7-j);
            mask >>= 1;
            counter++;
        }
    }
    filesize--;
    printf("\n");

    int n = filesize*8;
    printf("n = %d\n", filesize*8 );
    printf("d = %d\n", dval );
  
  
    int n1=0;  

    for(i=0;i<(n-dval);i++)
    {
        if(original_str[i]!=original_str[i+dval])
        {
            n1++;
        }
    }

    printf("A(d) = %d\n", n1 );
    double answer=0.0;
    answer =  (2*( (n1-(n-dval)/2.0) )) / sqrt(n-dval);
    printf("x5 = %6f\n", answer);

    if((neg_threshold5 <answer ) && (answer<pos_threshold5))
        printf("pass/fail = pass\n");
    else
        printf("pass/fail = fail\n");

}
