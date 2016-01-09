/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by a factor of n where n must a positive integer:
 * 1. open files
 * 2. write new info for width, height, & size in headers
 * 3. scan pixels line by line
 * 4. resize horizontally: duplicate each pixel n times, remembering to add 
 *    padding if needed using fputc()
 * 5. resize vertically: duplicate each row n times
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scale-factor infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // check that n is a positive int
    if (n <= 0)
    {
        printf("first argument must be a positive integer.");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    printf("In file metadata:\n");
    // printf("bfSize: %i\n", bf.bfSize);
    printf("infile biWidth: %i\n", bi.biWidth);
    printf("infile biHeight: %i\n", bi.biHeight);
    printf("infile biSizeImage: %i\n", bi.biSizeImage);
    // printf("biXPelsPerMeter: %i\n", bi.biXPelsPerMeter);
    // printf("biYPelsPerMeter: %i\n", bi.biYPelsPerMeter);
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding of infile for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // headers for outfile, copy file header to outfile
    BITMAPFILEHEADER* bf2 = malloc(sizeof(BITMAPFILEHEADER));
    *bf2 = bf;
    
    BITMAPINFOHEADER bi2;
    
    // write new width, height, and padding
    bi2.biWidth = bi.biWidth * n;
    bi2.biHeight = bi.biHeight * n;
    
    // calculate any padding for outfile
    int paddingOut = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // calculate outfile image size
    bi2.biSizeImage = abs(bi2.biHeight * (bi2.biWidth + paddingOut) * 3);
    
    printf("\nOutfile metadata:\n");
    // printf("bfSize: %i\n", bf.bfSize);
    printf("outfile biWidth: %i\n", bi2.biWidth);
    printf("outfile biHeight: %i\n", bi2.biHeight);
    printf("outfile biSizeImage: %i\n", bi2.biSizeImage);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
