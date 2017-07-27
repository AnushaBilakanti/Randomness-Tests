hw7: main.o rc4.o x1.o x2.o x5.o x3.o x4.o
	gcc -g  main.o rc4.o x1.o x2.o x5.o x3.o x4.o -o hw7 -lm -lcrypto

main.o: main.c functions.h
	gcc -c -g -Wall main.c  

rc4.o: rc4.c functions.h
	gcc -c -g -Wall rc4.c 

x1.o: x1.c functions.h
	gcc -c -g -Wall x1.c 

x2.o: x2.c functions.h
	gcc -c -g -Wall x2.c 


x5.o: x5.c functions.h
	gcc -c -g -Wall x5.c 

x3.o: x3.c functions.h
	gcc -c -g -Wall x3.c 

x4.o: x4.c functions.h
	gcc -c -g -Wall x4.c 

# millerrabin.o: millerrabin.c functions.h
# 	gcc -c -g -Wall millerrabin.c 

# rndsearch.o: rndsearch.c functions.h
# 	gcc -c -g -Wall rndsearch.c 

	

clean:
	rm *.o
	rm hw7
