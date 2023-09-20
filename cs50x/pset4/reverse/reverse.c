#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[]) {
    // Ensure proper usage
    if (argc != 3) {
        printf("Improper usage.\n");
        return 1;
    }

    // Open input file for reading
    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL) {
        printf("Incorrect input.\n");
        fclose(inptr);
        return 1;
    }

    // Read header
    WAVHEADER fheader;
    fread(&fheader, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(fheader) != 0) {
        fclose(inptr);
        return 1;
    }

    // Open output file for writing
    FILE *outptr = fopen(outfile, "wb");

    if (outptr == NULL) {
        printf("Problem with output file.\n");
        fclose(outptr);
        fclose(inptr);
        return 1;
    }
    printf("Files opened for read/write.\n");
    
    // Write header to file
    fwrite(&fheader, sizeof(WAVHEADER), 1, outptr);
    printf("Header written to file.\n");

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(fheader);
    printf("Block size: %i\n", block_size);

    // Write reversed audio to file
    BYTE buffer[block_size];
    printf("Beginning to write reversed audio to file...\n");
    for (fseek(inptr, 0 - block_size, SEEK_END); ftell(inptr) > sizeof(fheader)-block_size; fseek(inptr, 0 - (block_size * 2), SEEK_CUR)) { 
        fread(&buffer, block_size, 1, inptr);
        fwrite(&buffer, block_size, 1, outptr);
    }
  
    printf("Done writing, closing files...\n");
    fclose(inptr);
    fclose(outptr);
    return 0;
    printf("Operation completed successfully.\n");
}



int check_format(WAVHEADER header) {
    int wav[] = {0x57, 0x41, 0x56, 0x45};
    for (int i = 0; i < 4; i++) {
        if (header.format[i] != wav[i]) {
            printf("Not a valid .wav file!\n");
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header) {
    int n = header.numChannels * (header.bitsPerSample /8);
    return n;
}