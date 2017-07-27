#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <arpa/inet.h>
#include <openssl/md5.h>


void rc4(char *pphrase, int len);
void x1(char *filename);
char *char_2_bin(char ch);
void x2(char *filename);
void x5(int dval, char *filename);
void x3(char *filename);
void x4(char *filename);
// int * dec2bin(unsigned char c);
// void x2(char * filename);
// void x3(char * filename);
// void x5(int len, char * filename);
// void char_2_bin(int input);
// char * char_2_bin_old(char input);
// int char_2_dec(char * binstring);
