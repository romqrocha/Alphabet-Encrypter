#include <stdio.h>
#include <stdlib.h>

/* Encrypts input file and returns the total number of letters that were encrypted. */
int encrypt_text(FILE *in, FILE *out, int shift) {
    if (shift < 0) {
        shift = shift % 26 + 26;
    }

    char buffer[4096];
    buffer[0] = '\0';
    fgets(buffer, sizeof(buffer), in);

    int counter = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
            buffer[i] = ((buffer[i] + shift - 'A') % 26) + 'A';
            counter++;
        } else if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] = ((buffer[i] + shift - 'a') % 26) + 'a';
            counter++;
        }
    }

    fputs(buffer, out);
    return counter;
}

/*
 * Use: ./lab3.out <in> <out> <shift>
 * in - Path of text file to be taken as input
 * out - Path of text file where output will be written
 * shift - Number of characters to shift the input by
 */
int main(int argc, char **argv) {
    if (argc != 4) {
        FILE *out = fopen("./error.txt", "w");
        fputs("Error: Incorrect number of command line arguments.", out);
        return -1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        output = fopen("./error.txt", "w");
        fputs("Error: Error opening output file.", output);
        return -1;
    }
   
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        fputs("Error: Error opening input file.", output);
        return -1;
    }

    int numshift = atoi(argv[3]);

    int num_of_encryptions = encrypt_text(input, output, numshift);
    if (num_of_encryptions == 0) {
        fputs("Error: Empty file or no valid characters to encrypt.", output);
        return -1;
    };

    return 0;
}