#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512
 
int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
 
    // Open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }
 
    // Create needed variables
    unsigned char buffer[BUFFER_SIZE];
    char filename[8];
    FILE *outptr = NULL;
    int counter = 0;
 
    // Read input file
    while (fread(buffer, BUFFER_SIZE, 1, inptr) == 1)
    {
        // Check if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous file
            if (counter > 0)
            {
                fclose(outptr);
            }
 
            // Create new file
            sprintf(filename, "%03i.jpg", counter);
            outptr = fopen(filename, "w");
            counter++;
        }
 
        // Write to file
        if (counter > 0)
        {
            fwrite(buffer, BUFFER_SIZE, 1, outptr);
        }
    }
 
    // Close files
    fclose(inptr);
    fclose(outptr);
 
    // Success
    return 0;
}