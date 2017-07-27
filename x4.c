#include "functions.h"


double threshold4=0.0;



unsigned char *char_2_bin4(unsigned char ch)
{
	unsigned char *binval=(unsigned char*)malloc(sizeof(unsigned char)*8);
	int i;
	int mask = 0x80;
	for(i=0;i<8;i++)
	{
		binval[i] = (ch & mask) >> (7-i);
        mask >>= 1;
	}
	return binval;
}

void x4(char *filename)
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

    int n=0;
    unsigned char *ch = calloc(1, 1);
    int filesize=0;
    int ctr = 0;
    unsigned char *temp = calloc(8, 1);
    int j;
    while(!(feof(fp)))
    {
       	temp[0] = '\0';
        ch[0]=(unsigned char)fgetc(fp);
        filesize++;
        if(filesize<257 )
        {
            if((filesize-1)%16==0 && filesize!=1)
                printf("\n");
            printf("%02x", (unsigned char)ch[0]);
        }
        // if(feof(fp))
        //     break;

        temp = char_2_bin4(ch[0]);
        for(j=0;j<8;j++)
        {
        	original_str[ctr]=temp[j];
        	ctr++;
        }
    }

    filesize--;
    n=filesize*8;

    printf("\nn = %d\n",n);



    int k=1;


    while(((n-k+3)/pow(2,k+2))>=5)
    {
       k++;
    }
 	k=k-1;

 	// double e[k+1];
    double *e=(double*)malloc((k+1)*sizeof(double));
    memset(e,0,k+1);
    // int h;
    // for(h=0;h<=k;h++)
    // {
    //     e[h]=0.000000;
    // }
 	
 	int i;
 	for(i=1;i<=k;i++)
 	{
        e[i]=((double)n-(double)i+3)/pow(2,(double)i+2);
 		// e[i]=(double)((double)(n-i+3)/(double)pow(2,i+2));
        // e[i]=(((double)n-i+3)/(double)pow(2,i+2));
        // e[i]=(double)((double)n-(double)i+(double)3)/(double)(pow(2,(double)i+2));
 	}


 	switch(k)
    {
        case 2: threshold4 =  5.9915; break;
        case 3: threshold4 =  9.4877; break;
        case 4: threshold4 = 12.5916; break;
        case 5: threshold4 =  15.5073; break;
        case 6: threshold4 =  18.3070; break;
        case 7: threshold4 = 21.0261 ; break;
        case 8: threshold4 = 23.6848; break;
        case 9: threshold4 = 26.2962; break;
        case 10: threshold4 = 28.8693; break; 
        case 11: threshold4 = 31.4104; break;    
    } 
    int win_array_size =k+1;
    int win_array_one[win_array_size];
    int win_array_zero[win_array_size];

    // initialise to zero;
    for(i=0;i<win_array_size;i++)
    {
        win_array_one[i] = 0;
        win_array_zero[i] = 0;
    }

    printf("k = %d\n", k);

    //need to calculate b1...bk
    //first i need to calculate no of zeros, then no of ones

    //count no of ones
    int ctr_reset=0;

    for(i=0;i<n;i++)
    {
    	
    	if(original_str[i]==1)
    		ctr_reset++;
    	else
    	{
    		if(ctr_reset<=k)
    		{
    			win_array_one[ctr_reset]+=1;
    		}
    		
            ctr_reset=0;
    	}
    }
    if(ctr_reset!=0)
    {
        if(ctr_reset<=k)
        {
            win_array_one[ctr_reset]+=1;
        }
        
        
    }

    //count no of zeros
    int ctr_reset_zero=0;
    for(i=0;i<n;i++)
    {
        
        if(original_str[i]==0)
            ctr_reset_zero++;
        else
        {
        	if(ctr_reset_zero<=k)
        	{
        		win_array_zero[ctr_reset_zero]+=1;
        	}
            
            ctr_reset_zero=0;
        }
    }
   	if(ctr_reset_zero!=0)
    {
        if(ctr_reset_zero<=k)
        {
            win_array_zero[ctr_reset_zero]+=1;
        }
        
    }

    for(i=1;i<=k;i++)
    {
        printf("e%d = %lf\n",i,e[i]);
        printf("B%d = %d\n",i,win_array_one[i]);
        printf("G%d = %d\n",i,win_array_zero[i]);
       
    }

    //calculate x4;
    double X4=0.0;
    double left_term=0.0;
    double right_term=0.0;
    for(i=1;i<=k;i++)
    {
    	left_term=(double)left_term+(double)(pow(win_array_one[i]-e[i],2))/(double)e[i];
    	right_term=(double)right_term+(double)(pow(win_array_zero[i]-e[i],2))/(double)e[i];

    }
    X4=left_term+right_term;

    printf("x4 = %6lf\n",X4);
  	if(X4<threshold4)
    	printf("pass/fail = pass\n");
  	else
    	printf("pass/fail = fail\n");	

    memset(e,0,k+1);    
}
