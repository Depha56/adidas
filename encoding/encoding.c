
#include <stdio.h>

// Function to calculate power of 2
int power(int power) {
    return 1 << power; // Shift 1 to the left by 'power' positions (i.e., 2^power)
}

// Function to check if the first two elements of an array are equal
// and return the third element if they are, otherwise return the first element
int findParityBit(int *arr) {
    if (arr[0] == arr[1]) {
        return arr[2];
    } else {
        return arr[0];
    }
}

// Function to convert an integer to its binary representation in an array
void intToBinary(int num, int *numArray) {
    for (int i = 0; i < 8; i++) {
        if (num & (1 << i)) { // Check if the ith bit is set in 'num'
            numArray[7 - i] = 1; // Set the corresponding position in 'numArray' to 1
        } else {
            numArray[7 - i] = 0; // Set to 0 if the bit is not set
        }
    }
}

// Function to convert a binary array back to an integer
int binaryToInt(int *numArray) {
    int num = 0;
    for (int i = 0; i < 8; i++) {
        int powerOf = power(i); // Calculate the power of 2 for the current bit position
        num += (numArray[7 - i] * powerOf); // Convert binary bits to decimal number
    }
    return num;
}

// Function to split an integer into two 4-bit nibbles
void makeNibbles(int value, int *msb, int *lsb) {
    int valueBinaryForm[8]; // Array to store binary representation of 'value'
    intToBinary(value, valueBinaryForm); // Convert 'value' to binary array

    // Copy first 4 bits to 'msb' (Most Significant Nibble) and next 4 bits to 'lsb' (Least Significant Nibble)
    for (int i = 0; i < 4; i++) {
        msb[i] = valueBinaryForm[i];
        lsb[i] = valueBinaryForm[i + 4];
    }
}

// Function to add parity bits to a nibble (4 bits)
int addParityBitsToNibble(int *nibble) {
    int d0 = nibble[3]; // LSB of nibble
    int d1 = nibble[2];
    int d2 = nibble[1];
    int d3 = nibble[0]; // MSB of nibble

    // Calculate parity bits for different combinations
    int p0arr[3] = {d0, d1, d2};
    int p1arr[3] = {d0, d1, d3};
    int p2arr[3] = {d2, d1, d3};

    int p0 = findParityBit(p0arr); // Calculate parity bits
    int p1 = findParityBit(p1arr);
    int p2 = findParityBit(p2arr);

    // Create byte with nibble and parity bits
    int byte[8] = {0, d3, d2, d1, d0, p2, p1, p0};

    // Convert binary array 'byte' back to integer
    int value = binaryToInt(byte);

    return value;
}

// Function to encode a value by adding parity bits to its nibbles
void encode(int valueInt, char *output) {
    int msb[4];
    int lsb[4];

    // Split 'valueInt' into two nibbles
    makeNibbles(valueInt, msb, lsb);

    // Add parity bits to both nibbles
    int msbWithParity = addParityBitsToNibble(msb);
    int lsbWithParity = addParityBitsToNibble(lsb);

    // Convert integers with parity bits back to characters
    output[0] = msbWithParity; // Store MSB with parity in first element of 'output'
    output[1] = lsbWithParity; // Store LSB with parity in second element of 'output'
}

// Function to read from input file, encode each byte, and write to output file
void generateOutput(char *inputFileName, char *outputFileName) {
    FILE *inputf = fopen(inputFileName, "r"); // Open input file for reading binary data
    if (!inputf) {
        perror("Error opening input file");
        return;
    }

    FILE *outputf = fopen(outputFileName, "wb"); // Open output file for writing binary data
    if (!outputf) {
        perror("Error opening output file");
        fclose(inputf);
        return;
    }

    int value;
    while (1) {
        value = fgetc(inputf); // Read one byte from input file
        if (value == EOF) {
            break; // Exit loop if end of file is reached
        }

        char output[2];
        encode(value, output); // Encode the byte with parity bits

        // Write encoded bytes to output file
        for (int i = 0; i < 2; i++) {
            fputc(output[i], outputf);
        }
    }

    fclose(inputf); // Close input file
    fclose(outputf); // Close output file
}

int main(int argc, char *argv[]) {
    // Check if input arguments are correct
    if (argc != 3) {
        printf("Usage: %s inputFile outputFile\n", argv[0]);
        return 0;
    }

    // Get input and output file names from command line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    // Generate output file with encoded data
    generateOutput(inputFileName, outputFileName);

    return 0;
}
