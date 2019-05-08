/* ------------------------------------------------------------------
 * Squashfs Utility - File System Information
 * ------------------------------------------------------------------ */

#include "squtil.h"

/**
 * Get compression name by ident.
 */
static const char *get_comp_name_by_id ( int compression )
{
    switch ( compression )
    {
    case ZLIB_COMPRESSION:
        return "ZLIB";
    case LZMA_COMPRESSION:
        return "LZMA";
    case LZO_COMPRESSION:
        return "LZO";
    case XZ_COMPRESSION:
        return "XZ";
    case LZ4_COMPRESSION:
        return "LZ4";
    case ZSTD_COMPRESSION:
        return "ZSTD";
    default:
        return "UNKNOWN";
    }
}

/**
 * Format time structure into a string
 */
static int format_time ( int sec, char *str, size_t len )
{
    time_t time_sec = sec;
    struct tm time_struct;

    /* Decode UNIX timestamp */
    if ( localtime_r ( &time_sec, &time_struct ) == NULL )
    {
        return -1;
    }

    /* Format time to a string */
    strftime ( str, len, "%Y-%m-%d %H:%M:%S", &time_struct );

    return 0;
}

/**
 * Superblock flag description structure
 */

struct flag_desc_t
{
    unsigned int flag;
    const char *name;
};

/**
 * Print superblock flags
 */
static void super_block_print_flags ( int flags )
{
    size_t i;
    size_t nflags = 0;
    size_t nprinted = 0;
    const struct flag_desc_t flag_desc_tab[] = {
        {SQUASHFS_NOI, "NOI"},
        {SQUASHFS_NOD, "NOD"},
        {SQUASHFS_CHECK, "CHECK"},
        {SQUASHFS_NOF, "NOF"},
        {SQUASHFS_NO_FRAG, "NO_FRAG"},
        {SQUASHFS_ALWAYS_FRAG, "ALWAYS_FRAG"},
        {SQUASHFS_EXPORT, "EXPORT"},
        {SQUASHFS_DUPLICATE, "DUPLICATE"},
        {SQUASHFS_NOX, "NOX"},
        {SQUASHFS_NO_XATTR, "NO_XATTR"},
        {SQUASHFS_COMP_OPT, "COMP_OPT"},
        {SQUASHFS_NOID, "NOID"}
    };

    /* Caluclate set flags count */
    for ( i = 0; i < sizeof ( flag_desc_tab ) / sizeof ( struct flag_desc_t ); i++ )
    {
        if ( flags & ( 1 << flag_desc_tab[i].flag ) )
        {
            nflags++;
        }
    }

    /* Show none string if no description found */
    if ( !nflags )
    {
        printf ( "NONE" );
        return;
    }

    /* Print selected flags */
    for ( i = 0; i < sizeof ( flag_desc_tab ) / sizeof ( struct flag_desc_t ); i++ )
    {
        if ( flags & ( 1 << flag_desc_tab[i].flag ) )
        {
            printf ( "%s", flag_desc_tab[i].name );
            if ( nprinted + 1 < nflags )
            {
                printf ( ", " );
                nprinted++;
            }
        }
    }
}

/**
 * Print superblock details
 */
static int super_block_info ( const struct squashfs_super_block *super_block, int endianswap )
{
    int invalid_s_magic = 0;
    unsigned int expected_magic;
    char str[64];

    /* Caluclate expected magic ID */
    expected_magic = swap32 ( SQUASHFS_MAGIC, endianswap );

    /* Validate squashfs magic */
    if ( super_block->s_magic != expected_magic )
    {
        fprintf ( stderr, "bad magic number, found 0x%.8x, expected 0x%.8x\n", super_block->s_magic,
            expected_magic );
        invalid_s_magic = 1;
    }

    /* Show section title */
    printf ( "------- superblock information -------\n" );

    /* Dump details */
    printf ( "magic id    : 0x%.8x %c-%c-%c-%c (%s)\n", super_block->s_magic,
        ( ( const unsigned char * ) super_block )[0],
        ( ( const unsigned char * ) super_block )[1],
        ( ( const unsigned char * ) super_block )[2],
        ( ( const unsigned char * ) super_block )[3], invalid_s_magic ? "BAD" : "OK" );
    printf ( "inodes      : %u\n", swap32 ( super_block->inodes, endianswap ) );

    if ( format_time ( swap32 ( super_block->mkfs_time, endianswap ), str, sizeof ( str ) ) < 0 )
    {
        fprintf ( stderr, "failed to format time\n" );
        return -1;
    }

    printf ( "mkfs_time   : %s\n", str );
    printf ( "block_size  : %u\n", swap32 ( super_block->block_size, endianswap ) );
    printf ( "fragments   : %u\n", swap16 ( super_block->fragments, endianswap ) );
    printf ( "compression : %u (%s)\n", swap16 ( super_block->compression, endianswap ),
        get_comp_name_by_id ( swap16 ( super_block->compression, endianswap ) ) );
    printf ( "block_log   : %u\n", swap16 ( super_block->block_log, endianswap ) );
    printf ( "flags       : %u (", swap16 ( super_block->flags, endianswap ) );
    super_block_print_flags ( swap16 ( super_block->flags, endianswap ) );
    printf ( ")\n" );
    printf ( "no ids      : %u\n", swap16 ( super_block->no_ids, endianswap ) );
    printf ( "major       : %u\n", swap16 ( super_block->s_major, endianswap ) );
    printf ( "minor       : %u\n", swap16 ( super_block->s_minor, endianswap ) );
    printf ( "root inode  : %llu\n", ( long long unsigned int ) swap64 ( super_block->root_inode,
            endianswap ) );
    printf ( "bytes_used  : %lli\n", ( long long int ) swap64 ( super_block->bytes_used,
            endianswap ) );
    printf ( "id          : %lli\n", ( long long int ) swap64 ( super_block->id_table_start,
            endianswap ) );
    printf ( "xattr id    : %lli\n", ( long long int ) swap64 ( super_block->xattr_id_table_start,
            endianswap ) );
    printf ( "inode       : %lli\n", ( long long int ) swap64 ( super_block->inode_table_start,
            endianswap ) );
    printf ( "directory   : %lli\n", ( long long int ) swap64 ( super_block->directory_table_start,
            endianswap ) );
    printf ( "fragment    : %lli\n", ( long long int ) swap64 ( super_block->fragment_table_start,
            endianswap ) );
    printf ( "lookup      : %lli\n", ( long long int ) swap64 ( super_block->lookup_table_start,
            endianswap ) );

    putchar ( '\n' );

    return 0;
}

/**
 * Show squashfs information
 */
int squashfs_info ( const unsigned char *pmaddr, size_t length, int endianswap )
{
    struct squashfs_super_block super_block;

    /* Validate data size */
    if ( length < sizeof ( struct squashfs_super_block ) )
    {
        fprintf ( stderr, "file is too short %lu < %lu\n", ( unsigned long ) length,
            sizeof ( struct squashfs_super_block ) );
        return -1;
    }

    /* Place superblock into buffer */
    memcpy ( &super_block, pmaddr, sizeof ( struct squashfs_super_block ) );

    /* Print superblock details */
    if ( super_block_info ( &super_block, endianswap ) < 0 )
    {
        return -1;
    }

    return 0;
}
