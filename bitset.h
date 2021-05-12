#ifndef BITSET_H
#define BITSET_H
#include <stdlib.h>
#include <assert.h>
#include "error.h"


// Definitions of data types for bitsets
typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

// Frequently used expressions
#define BIT_INDEX(requiredIndex) ((requiredIndex + 1) / 64 + ((((requiredIndex + 1) % 64) != 0) ? 1 : 0)) // Returnes correct index relative to the entire bitfield
#define BITSET_SIZE_DEFINE(size) (size / 64 + 1 + (((size % 64) != 0) ? 1 : 0)) // Is used to define required size of bitfield



// Definitions of static(bitset_create) and dynamic(bitset_alloc) bitset inicialization (impossible to make inline variants of theese functions(so, probably))
#define bitset_create(jmeno_pole, velikost) static_assert(velikost > 0, "Array size error");                                                                \
                                            bitset_index_t jmeno_pole[BITSET_SIZE_DEFINE(velikost)] = {0};                                                  \
                                            jmeno_pole[0] = velikost;

                                            

#define bitset_alloc(jmeno_pole, velikost)  assert(velikost > 0);                                                                                           \
                                            bitset_t jmeno_pole = calloc((BITSET_SIZE_DEFINE(velikost)), sizeof(unsigned long));                            \
                                            if(jmeno_pole == NULL) error_exit("bitset_alloc: Chyba alokace paměti");                                        \
                                            jmeno_pole[0] = velikost;


// If USE_INLINE has been defined with -DUSE_INLINE, bitset.h uses inline variants of functions
#ifdef USE_INLINE

// Frees memory allocated by bitset_alloc 
inline void bitset_free(bitset_t pole)
{
    if (pole == NULL)
    {
        error_exit("Nothing to be freed");
    }
    else free(pole); 
}

// Returns first element of bitset, where the size of the entire bitset is stored ((need to increase stack size))
inline unsigned long bitset_size(bitset_t pole)
{
    return pole[0];
}

// Sets a bit at a definite index (index of bit in bitfield!!!)
inline void bitset_setbit(bitset_t pole, unsigned long index, int vyraz)
{
    if(index < bitset_size(pole))
        if (vyraz != 0)                                                                           
        {
            pole[BIT_INDEX(index)] |= (1l << (index % 64)) ;     
        }                                                                                         
        else                                                                                      
        {
            pole[BIT_INDEX(index)] &= ~(1l << (index % 64)) ;    
        }
    else
    {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)pole[0] - 1);
    } 
}

// Returns value of bit at a definite index(index of bit in bitfield!!!)
inline int bitset_getbit(bitset_t pole, unsigned long index)
{
    if(index < bitset_size(pole))                                                                                                   
    {                                                                                                                                  
        return (pole[BIT_INDEX(index)] >> (index % 64) & 1);
    }
    else 
    {  
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)pole[0] - 1);
        return 1;                                                                                                                                  
    }
}


#else // If USE_INLINE is undefined


// Macro variants of functions above
#define bitset_free(jmeno_pole) (jmeno_pole == NULL) ? error_exit("Nothing to be freed") : free(jmeno_pole);

/* returns size of bitset (contained in first element of bitset  */
#define bitset_size(jmeno_pole) jmeno_pole[0] 

/* Sets bit from bitset "jmeno_pole" with index "index" (INDEX OF BIT!!!) to value "vyraz" (if != 0 => sets 1)*/
#define bitset_setbit(jmeno_pole,index,vyraz)   ((index < bitset_size(jmeno_pole))                                                                                                  \
                                                ?                                                                                                                                   \
                                                ((vyraz != 0)                                                                                                                       \
                                                ?                                                                                                                                   \
                                                (jmeno_pole[BIT_INDEX(index)] |= (1l << (index % 64))) /*1l = UL 1*/                                                                \
                                                :                                                                                                                                   \
                                                (jmeno_pole[BIT_INDEX(index)] &= ~(1l << (index % 64))))                                                                            \
                                                :/* ELSE for (index < bitset_size(jmeno_pole)) */                                                                                   \
                                                (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1), 1))

                                                
                                                 
                                                
                                                

/* Returns value if bit from bitset "jmeno_pole" in index "index" (INDEX OF BIT) */
#define bitset_getbit(jmeno_pole, index)    ((index < bitset_size(jmeno_pole))                                                                                                  \
                                            ?                                                                                                                                   \
                                            (jmeno_pole[BIT_INDEX(index)] >> (index % 64) & 1)                                                                                  \
                                            :                                                                                                                                   \
                                            (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1), 1))
                                            

                                            



#endif // #ifdef USE_INLINE ending
#endif // #ifndef BITSET_H ending
