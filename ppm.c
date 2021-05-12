#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

// Function moves the cursor to read the file correctly
void moveCursor(FILE* fp)
{
    char cursor; 
    while ((cursor = fgetc(fp)) != '\n')
    {
        cursor = fgetc(fp);
        
        if (cursor == 0) warning_msg("Error reading file data");
    }
}

//Function reads PPM file, writes it to the struct and returns struct with data of image
struct ppm* ppm_read(const char * filename)
{
    unsigned tempXSize = 0;
    unsigned tempYSize = 0;
    short color = 0;

    FILE* startFile = fopen(filename, "rb");
    if(!startFile) 
    {
        warning_msg("File reading failed");
        return NULL;
    }

   char imageFormat[3];
    imageFormat[0] = fgetc(startFile);
    imageFormat[1] = fgetc(startFile);
    imageFormat[2] = '\0';   

    if(strcmp(imageFormat, "P6") != 0)
    {
        warning_msg("Error format");
        fclose(startFile);
        return NULL;
    }
    
    moveCursor(startFile);
    
    fscanf(startFile, "%u %u", &tempXSize, &tempYSize);

    if((tempXSize == 0) || (tempYSize == 0)) 
    {
        warning_msg("Error reading PPM image size");
        fclose(startFile);
        return NULL;
    }
    struct ppm* image = malloc((sizeof(struct ppm)) + (3 * tempXSize * tempYSize));

    if(image == NULL)
    {
        warning_msg("Failed memory allocation");
        fclose(startFile);
        return NULL;
    }

    image->xsize = tempXSize;
    image->ysize = tempYSize;

    fscanf(startFile, "%hi", &color);

    if((color == 0) || (color != 255))
    {
        warning_msg("Error reading color");
        fclose(startFile);
        return NULL;
    }

    moveCursor(startFile);

    size_t readData = fread(image->data, sizeof(char), (3 * tempXSize * tempYSize), startFile);

    if(readData != (3 * tempXSize * tempYSize)) 
    {
        warning_msg("File reading failed");
        fclose(startFile);
        return NULL;
    }

    fclose(startFile);
    return image;
    
}

//Frees memory allocated for struct ppm* 
void ppm_free(struct ppm *p)
{
    if(p == NULL)
    {
        warning_msg("Nothing to be freed");
    }
    else free(p);
}
