/* ------------------------------------------------------------------
 * Squashfs Utility - Utility Functions
 * ------------------------------------------------------------------ */

#include "squtil.h"

/**
 * Swap 16 bit value bytes depending on flag status
 */
uint16_t swap16 ( uint16_t value, int endianswap )
{
    return endianswap ? __bswap_16 ( value ) : value;
}

/**
 * Swap 32 bit value bytes depending on flag status
 */
uint32_t swap32 ( uint32_t value, int endianswap )
{
    return endianswap ? __bswap_32 ( value ) : value;
}

/**
 * Swap 64 bit value bytes depending on flag status
 */
uint64_t swap64 ( uint64_t value, int endianswap )
{
    return endianswap ? __bswap_64 ( value ) : value;
}
