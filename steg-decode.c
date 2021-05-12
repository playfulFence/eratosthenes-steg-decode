#include <stdio.h>
#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"

void ppmDecode(struct ppm* image, bitset_t imageBitset)
{
    int byteCounter = 0;

    char signAscii = 0;

    char* decodedMsg = malloc(sizeof(char));

    char* decodedMsgPointer; //Helping pointer to detect reallocation error.

    int msgCharCounter = 0;

    for(unsigned long eratosthenesImageIndex = 23; eratosthenesImageIndex < (unsigned long)(3 * image->xsize * image->ysize); ++eratosthenesImageIndex)
    {
        if (bitset_getbit(imageBitset, eratosthenesImageIndex) == 0)                        //Find an ASCII symbol with value, which is on prime index and if it's
        {                                                                                   //even writes 0 into char signAscii, else writes 1 using binary OR.
            if ((image->data[eratosthenesImageIndex] % 2) != 0)                             //When count of bits written to a char reaches 8, writes out this char,
            {                                                                               //then refreshes this char and the counter(byteCounter). If signAscii == '\0' - ends decoding process
                signAscii |= (1 << byteCounter);
            }

            byteCounter++;
        }

        

        if(byteCounter == 8)
        {
            decodedMsg[msgCharCounter] = signAscii;

            msgCharCounter++;

            decodedMsgPointer = realloc(decodedMsg, sizeof(char)*msgCharCounter + 1);

            if(decodedMsgPointer == NULL)                                                                       
            {
                free(decodedMsg);
                error_exit("Failed reallocation of decoded message. Freing decoded message...");                           //Control if reallocation went OK.
            }
            else (decodedMsg = decodedMsgPointer);

            if(signAscii == '\0') break;
            signAscii = 0;

            byteCounter = 0;
        }

    }

    if(decodedMsg[msgCharCounter - 1] != '\0') error_exit("Missing string ending sign(\"\0\")");

    printf("%s\n",decodedMsg);

    free(decodedMsg);
}

int main(int argc, char** argv)
{
    if (argc < 2) error_exit("Too few arguments\n");

    struct ppm* image = ppm_read(argv[1]);

    bitset_alloc(imageBitset, (3 * image->xsize * image->ysize));

    Eratosthenes(imageBitset);

    ppmDecode(image, imageBitset);
    
    ppm_free(image);
    bitset_free(imageBitset);

    return 0;
}
