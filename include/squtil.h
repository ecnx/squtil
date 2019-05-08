/* ------------------------------------------------------------------
 * Squashfs Utility - Share Project Header
 * ------------------------------------------------------------------ */

#include "config.h"

#ifndef SQUTIL_H
#define SQUTIL_H

#define SQUTIL_VER "1.0.18"

/**
 * Show squashfs information
 */
extern int squashfs_info ( const unsigned char *pmaddr, size_t length, int endianswap );

/**
 * Edit superblock data
 */
extern int squashfs_edit ( const unsigned char *pmaddr, size_t length, int endianswap,
    const char *name, unsigned long long value );

/**
 * Clone superblock timestamp
 */
extern int squashfs_clone_mkfs_time ( const unsigned char *pmaddr, size_t length,
    const char *srcpath );

/**
 * Swap 16 bit value bytes depending on flag status
 */
extern uint16_t swap16 ( uint16_t value, int endianswap );

/**
 * Swap 32 bit value bytes depending on flag status
 */
extern uint32_t swap32 ( uint32_t value, int endianswap );

/**
 * Swap 64 bit value bytes depending on flag status
 */
extern uint64_t swap64 ( uint64_t value, int endianswap );

#endif
