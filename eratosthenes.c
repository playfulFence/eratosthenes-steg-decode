#include <stdio.h>
#include "bitset.h"

// Finds prime numbers from 0 to specified number(size of bitfield) and sets bit at the same index as this number to 0
void Eratosthenes(bitset_t pole)
{
    for(unsigned long sieveIndex = 2; sieveIndex * sieveIndex < bitset_size(pole) ; ++sieveIndex)
    {
        if (bitset_getbit(pole, sieveIndex) == 0)
        {
            for (unsigned long compositeNumber = sieveIndex * sieveIndex; compositeNumber < bitset_size(pole); compositeNumber += sieveIndex)
            {
                bitset_setbit(pole, compositeNumber, 1);
            }
        }
    }
}

// Writes last ten prime numbers from bitset, which was filtered with Eratosthenes func
void writeLastTenPrimes(bitset_t pole)
{
    unsigned long lastTen[10];
    int lastTenCounter = 9;

    for(unsigned long printIndex = bitset_size(pole) - 1; lastTenCounter >= 0; --printIndex)
    {
        if(bitset_getbit(pole, printIndex) == 0)
        {
            lastTen[lastTenCounter] = printIndex;
            lastTenCounter--;
        }
    }

    for (int i = 0; i < 10; i++) printf("%ld\n", lastTen[i]);
}
