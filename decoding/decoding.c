#include <stdio.h>

// Function to calculate power of 2
int power(int power) {
    return 1 << power;
}

// Function to convert an integer to its binary representation in an array
void intToBinary(int num, int *numArray) {
    for (int i = 0; i < 8; i++) {
        if (num & (1 << i)) {
            numArray[7 - i] = 1;
        } else {
            numArray[7 - i] = 0;
        }
    }
}

// Function to convert a binary array back to an integer
int binaryToInt(int *numArray) {
    int num = 0;
    for (int i = 0; i < 8; i++) {
        int powerOf = power(i);
        num += (numArray[7 - i] * powerOf);
    }
    return num;
}

// Function to extract the original nibble from a nibble with parity bits
int extractDataBits(int valueWithParity) {
    int binaryArray[8];
    intToBinary(valueWithParity, binaryArray);

    // Extract data bits (d3, d2, d1, d0) from positions 6, 5, 4, 3
    int dataBits[4] = {binaryArray[1], binaryArray[2], binaryArray[3], binaryArray[4]};
    
    int dataBitsArray[8] = {0, 0, 0, 0, dataBits[0], dataBits[1], dataBits[2], dataBits[3]};
    return binaryToInt(dataBitsArray);
}

// Function to decode an encoded byte
void decode(int encodedMsb, int encodedLsb, char *output) {
    // Extract the original nibbles
    int msb = extractDataBits(encodedMsb);
    int lsb = extractDataBits(encodedLsb);

    // Combine the nibbles to form the original byte
    int originalValue = (msb << 4) | lsb;

    *output = originalValue;
}

// Function to read from input file, decode each pair of bytes, and write to output file
void generateDecodedOutput(char *inputFileName, char *outputFileName) {
    FILE *inputf = fopen(inputFileName, "rb");
    if (!inputf) {
        perror("Error opening input file");
        return;
    }

    FILE *outputf = fopen(outputFileName, "wb");
    if (!outputf) {
        perror("Error opening output file");
        fclose(inputf);
        return;
    }

    int encodedMsb, encodedLsb;
    while (1) {
        encodedMsb = fgetc(inputf);
        if (encodedMsb == EOF) {
            break;
        }

        encodedLsb = fgetc(inputf);
        if (encodedLsb == EOF) {
            break;
        }

        char decodedOutput;
        decode(encodedMsb, encodedLsb, &decodedOutput);
        fputc(decodedOutput, outputf);
    }

    fclose(inputf);
    fclose(outputf);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s inputFile outputFile\n", argv[0]);
        return 0;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    generateDecodedOutput(inputFileName, outputFileName);

    return 0;
}
