#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"


int main(void)
{
    clock_t start = clock(); 

    bitset_create(name, 200000000);

    Eratosthenes(name);

    writeLastTenPrimes(name);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
