#include "functions.h"

double threshold3 = 0.0;
int m_backup = 0;

int char_2_dec(char *binstring) // converting binary string to decimal. 
{
  
    int i;
    int sum = 0;
    int m = strlen(binstring);
    int num=0;
    for(i=0;i<strlen(binstring);i++)
    {
        num=(int)binstring[i] - 48;
        sum=sum + (pow(2, m-i-1)*num);
    }
    return sum;
}


char *char_2_bin3(char input) // char to binary string. 
{
    
    int i = 0;
    int bit = 0;
    char * output = calloc(256, 1);

    for(i=0;i<8;++i)
    {
        bit=((input>>i)&1);
        output[7-i]=bit + 48;  
    }
    return output;
                
}

double getalphavalue(int m)
{
    switch(m) // setting m value. 
    {
        case 1: threshold3 =  3.8415; break;
        case 2: threshold3 = 7.8147 ; break;
        case 3: threshold3 =  14.0671; break;
        case 4: threshold3 = 24.9958; break;
        case 5: threshold3 =  44.9853; break;
        case 6: threshold3 =  82.5287; break;
        case 7: threshold3 = 154.3015 ; break;
        case 8: threshold3 = 293.2478; break;
        case 9: threshold3 = 564.6961; break;
        case 10: threshold3 = 1098.5208; break;
        

    }
    return threshold3; 
}

void char_2_bin1(int input)
{
    
    int i;
    int bit = 0;

    for(i=m_backup-1; i>=0; i--)
    {
        bit = (input>>i)&1;
        printf("%d", bit);
    }
}



void x3(char * filename)
{

    char *original_str=(char*)malloc(2222220*sizeof(char));
    memset(original_str,0,2222220);

    FILE * fp;
    if(filename==NULL)
        fp = stdin;
    else
        fp = fopen(filename, "rb");

       
    if(fp==NULL)
    {
        fprintf(stderr,"File does not exist.\n");
        exit(0);
    }

    int n,i;
    char *ch = calloc(1, 1);
    int filesize = 0;
    int ctr = 0;
    char *temp = calloc(8, 1);

    while(!(feof(fp)))
    {
       // memset(temp, NULL, 8);
        temp[0] = '\0';

        ch[0]=(char)fgetc(fp);
        filesize++;
        if(filesize<257)
        {
            if((filesize-1)%16==0 && filesize!=1)
                printf("\n");
            printf("%02x", (unsigned char)ch[0]);
        }
        if(feof(fp))
            break;

        if(feof(fp))
            break;

        temp = char_2_bin3(ch[0]);
        strncat(&original_str[ctr], temp, 8);
        ctr=ctr+8;

    }

    filesize--;

    n = filesize*8;

    printf("\nn = %d\n",n);
    int m = 1;
    int k=0;

    while(floor(n/m)>=5*pow(2, m))
    {
        m++;
    }
    m = m-1;
    k = floor(n/m);
    m_backup = m;

    threshold3=getalphavalue(m);
    

    int loop_limit =n-(n%m);
   
    char *temp_cpy = calloc(m, 1);
    
    //filesize = 5;
    int ctr_array_size = pow(2, m);
    int ctr_array[ctr_array_size];

    // initialise to zero;
    for(i=0;i<ctr_array_size;i++)
        ctr_array[i] = 0;
    
    printf("m = %d\n", m);
    printf("k = %d\n", k );

    int num=0;
    for(i=0;i<filesize*8;i+=m)
    {
        memset(temp_cpy, 0, m);
        if(i<loop_limit) // ignore nits after the multiple
        {
            strncpy(temp_cpy, &original_str[i], m);
            num = char_2_dec(temp_cpy);
            ctr_array[num] +=1;
            temp_cpy[0]='\0';
        }
        else
            break;  

    }

    for(i=0;i<ctr_array_size;i++)
    {
        
        printf("n");
        char_2_bin1(i);
        printf(" = %d\n", ctr_array[i]);

    }

    double pow_val = 0.0;
    for(i=0;i<ctr_array_size;i++)
    {
        pow_val+= pow(ctr_array[i], 2);
    }


    double pow_div=0.0;
    pow_div=((pow(2,m)*pow_val)/(double)k);
    double X3=0.0;
    X3=pow_div-k;
    printf("x3 = %6f\n",X3);
    if(X3<threshold3)
        printf("pass/fail = pass\n");
    else
        printf("pass/fail = fail\n");

}
