/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Jake Weber
| Date: 02/25/2024
|
| To Compile: gcc -o hillcipher hillcipher.c
|
| To Execute: c -> ./hillcipher hillcipherkX.txt hillcipherpX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILE_SIZE 10000

int main(int argc, char* argv[]) {
	
	// Read files
	FILE *key = fopen(argv[1], "r");
	FILE *plaintext = fopen(argv[2], "r");
	if (key == 0 || plaintext == 0) {
		printf("File not found\n");
		exit(1);
	}
	
	// Size of matrix
	char *line = (char*) malloc(3 * sizeof(char));
	int n = atoi(fgets(line, 3, key));
	line = (char*) realloc(line, n * 11 + 1);
	int matrix[n][n];
	
	// Scan in key matrix
	for (int i = 0; i < n; i++) {
		fgets(line, n * 11 + 1, key);
		matrix[i][0] = atoi(strtok(line, "\t"));
		for (int j = 1; j < n; j++)
			matrix[i][j] = atoi(strtok(NULL, "\t"));
	}
	
	// Print key matrix
	printf("\nKey matrix:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%4d", matrix[i][j]);
		printf("\n");
	}
	
	// Scan in plaintext
	char letters[MAX_FILE_SIZE];
	int plaintextSize = 0;
	int x;
	while((x = fgetc(plaintext)) != EOF)
		if (isalpha(x)) letters[plaintextSize++] = tolower(x);
	
	// Add padding characters
	for (int j = 0; j < (plaintextSize % n); j++)
		letters[plaintextSize++] = 'x';
	
	// Print plaintext (letters only)
	printf("\nPlaintext:");
	for (int i = 0; i < plaintextSize; i++) {
		if (i % 80 == 0)
			printf("\n");
		printf("%c", letters[i]);
	}
	
	// Encrypting with matrix multiplication
	char vector[n];
	int newLetters[n];
	for (int i = 0; i < n; i++)
		newLetters[i] = 0;
	char ciphertext[plaintextSize + 1];
	int k = 0;
	
	while (k < plaintextSize) {
		
		// Create vector
		for (int i = 0; i < n; i++)
			vector[i] = letters[k + i];
		
		// Multiplying matrix and vector
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				newLetters[i] += matrix[i][j] * (vector[j] - 'a');
		}
		
		// Inputting into ciphertext array
		for (int i = 0; i < n; i++) {
			ciphertext[k++] = (newLetters[i] % 26) + 'a';
			newLetters[i] = 0;
		}
	}
	
	
	// Print ciphertext
	printf("\n\nCiphertext:");
	for (int i = 0; i < plaintextSize; i++) {
		if (i % 80 == 0)
			printf("\n");
		printf("%c", ciphertext[i]);
	}
	printf("\n");
	
	// Free memory
	free(line);
	fclose(key);
	fclose(plaintext);
	return 0;
}
