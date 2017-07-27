#include "functions.h"

int main(int argc, char * argv[])
{

	char *pphrase;
    char *len;
    int input_len;
	char * input_dval;
    char * filename;
    int dval;

	if(argc==1)
    {
        fprintf(stderr, "Malformed command\n");
        exit(0);
    }
    else
    {
    	if(strcmp(argv[1], "rc4")==0)
    	{
    		if(argc<3)
    		{
    			fprintf(stderr, "Malformed command\n" );
    			exit(0);
    		}
    		else
    		{
    			if(argc==3)
    			{
    				if(argv[2][0]=='-' && argv[2][1]=='p')
    				{
    					pphrase = strchr(argv[2], '=');
                        pphrase++;
    					//printf("%s\n", input);
    				}
                    else
                    {
                        fprintf(stderr, "Malformed command\n");
                        exit(0);
                    }
    				input_len = 0;
                    //printf("Len: %d\nPphrase: %s\n", len, input_pphrase );

    			}
    			else
    			{
    				if(argv[2][0]=='-' && argv[2][1]=='p')
    				{
    					pphrase = strchr(argv[2], '=');
                        pphrase++;
    				}

    				if(argv[3][0]=='-' && argv[3][1]=='l')
    				{
    					len = strchr(argv[3], '=');
                        len++;
                        input_len = atoi(len);
    				}
                    else
                    {
                        fprintf(stderr, "Malformed command\n");
                        exit(0);
                    }
    			}
    			
    			rc4(pphrase, input_len);
    		}
    	}

    	else if(strcmp(argv[1], "x1")==0)
    	{
    		if(argc==3)
    		{
    			x1(argv[2]);
    		}
    		else if(argc==2)
    		{
    			x1(NULL);
    		}
    		else
    		{
    			fprintf(stderr, "Malformed command\n");
    		}
    	}
    	else if(strcmp(argv[1], "x2")==0)
    	{
    		if(argc==3)
    		{
    			x2(argv[2]);
    		}
    		else if(argc==2)
    		{
    			x2(NULL);
    		}
    		else
    		{
    			fprintf(stderr, "Malformed command\n");
    		}
    	}
    	else if(strcmp(argv[1], "x3")==0)
    	{
    		if(argc==3)
    		{
    			x3(argv[2]);
    		}
    		else if(argc==2)
    		{
    			x3(NULL);
    		}
    		else
    		{
    			fprintf(stderr, "Malformed command\n");
    		}
    	}
        else if(strcmp(argv[1], "x4")==0)
        {
            if(argc==3)
            {
                x4(argv[2]);
            }
            else if(argc==2)
            {
                x4(NULL);
            }
            else
            {
                fprintf(stderr, "Malformed command\n");
            }
        }
        else if(strcmp(argv[1], "x5")==0)
        {
            if(argc==4)
            {
                if(argv[2][0]=='-' && argv[2][1]=='d')
                {
                    input_dval = strchr(argv[2], '=');
                    input_dval++;
                    dval = atoi(input_dval);
                }
                else
                {
                    fprintf(stderr, "Malformed command\n");
                    exit(0);
                }

                filename = argv[3];
            }
            else if(argc==3)
            {
                if(argv[2][0]=='-' && argv[2][1]=='d')
                {
                    input_dval = strchr(argv[2], '=');
                    input_dval++;
                    dval = atoi(input_dval);
                }
                else
                {
                    fprintf(stderr, "Malformed command\n");
                    exit(0);
                }
                filename = NULL;

            }
            else
            {
                fprintf(stderr, "Malformed command\n");
                exit(0);
            }
            x5(dval, filename);
        }
        else
        {
            fprintf(stderr, "Malformed command\n");
            exit(0);
        }
    }//else
    return 0;
}
