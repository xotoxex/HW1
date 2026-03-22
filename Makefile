hw1:
	gcc hw1.c -o hw1
hw1: hw1.c arrop.c converter.c
	gcc hw1.c -o hw1
clear:
	rm hw1
