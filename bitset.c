#include "bitset.h"
#ifdef USE_INLINE

// Extern declaration of functions, if you're using inline variant of bitset.h functions
extern void bitset_free(bitset_t pole);
extern unsigned long bitset_size(bitset_t pole);
extern void bitset_setbit(bitset_t pole, unsigned long index, int vyraz);
extern int bitset_getbit(bitset_t pole, unsigned long index);

#endif
