/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Jake Weber
| Date: 3/31/24
|
| To Compile:
| gcc -o checksum checksum.c
|
| To Execute:
| ./checksum inputFile.txt 8
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

int myPow(int base, int power);

int main(int argv, char *argc[]) {
	
	FILE* fp = fopen(argc[1], "r");
	int checkSumSize = atoi(argc[2]);
	long checksum = 0;
	int characterCnt = 0;
	
	if (checkSumSize != 8 && checkSumSize != 16 && checkSumSize != 32) {
		fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
		exit(0);
	}
	
	// Read input
	char *input = (char*) malloc(1 * sizeof(char));
	characterCnt = 0;
	
	char c;
	while((c = fgetc(fp)) != EOF) {
    input = (char*) realloc(input, characterCnt + 2);
		input[characterCnt++] = c;
	}
	
	// Print input
	printf("\n");
	for (int i = 0; i < characterCnt; i++) {
		if (i % 80 == 0 && i > 0)
			printf("\n");
		printf("%c", input[i]);
	}
	
	// Print X's and pad
  int numX = 0;
  if (checkSumSize == 16)
    numX = characterCnt % 2;
  if (checkSumSize == 32)
    numX = 4 - (characterCnt % 4);
  
	for (int i = 0; i < numX; i++) {
		printf("X");
		input[characterCnt++] = 'X';
	}
	printf("\n");
 
	// Calculate checksum
	long temp = 0;
	int inputTraverse = 0;
	for (int i = 0; i < characterCnt / (checkSumSize / 8); i++) {
		for (int j = checkSumSize / 8 - 1; j >= 0; j--)
			temp += (int) input[inputTraverse++] * myPow(2, 8 * j);
		checksum += temp;
		if (checkSumSize == 8)
			checksum &= 0b11111111;
		if (checkSumSize == 16)
			checksum &= 0b1111111111111111;
		if (checkSumSize == 32)
			checksum &= 0b11111111111111111111111111111111;
		temp = 0;
	}
	
	printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);
	return 0;
}

int myPow(int base, int power) {
  int res = 1;
  for (int i = 0; i < power; i++)
    res *= base;
  return res;
}
