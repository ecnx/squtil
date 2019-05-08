/* ------------------------------------------------------------------
 * Squashfs Utility - Superblock Modification
 * ------------------------------------------------------------------ */

#include "squtil.h"

/**
 * Edit superblock data
 */
int squashfs_edit ( const unsigned char *pmaddr, size_t length, int endianswap,
    const char *name, unsigned long long value )
{
    struct squashfs_super_block *super_block = ( struct squashfs_super_block * ) pmaddr;

    /* Validate data size */
    if ( length < sizeof ( struct squashfs_super_block ) )
    {
        fprintf ( stderr, "file is too short %lu < %lu\n", ( unsigned long ) length,
            sizeof ( struct squashfs_super_block ) );
        return -1;
    }

    /* Update superblock data */
    if ( !strcmp ( name, "magic" ) )
    {
        super_block->s_magic = swap32 ( value, endianswap );

    } else if ( !strcmp ( name, "inodes" ) )
    {
        super_block->inodes = swap32 ( value, endianswap );

    } else if ( !strcmp ( name, "mkfs_time" ) )
    {
        super_block->mkfs_time = swap32 ( value, endianswap );

    } else if ( !strcmp ( name, "block_size" ) )
    {
        super_block->block_size = swap32 ( value, endianswap );

    } else if ( !strcmp ( name, "fragments" ) )
    {
        super_block->fragments = swap32 ( value, endianswap );

    } else if ( !strcmp ( name, "compression" ) )
    {
        super_block->compression = swap16 ( value, endianswap );

    } else if ( !strcmp ( name, "block_log" ) )
    {
        super_block->block_log = swap16 ( value, endianswap );

    } else if ( !strcmp ( name, "flags" ) )
    {
        super_block->flags = swap16 ( value, endianswap );

    } else if ( !strcmp ( name, "no_ids" ) )
    {
        super_block->no_ids = swap16 ( value, endianswap );

    } else if ( !strcmp ( name, "major" ) )
    {
        super_block->s_major = swap16 ( value, endianswap );

    } else if ( !strcmp ( name, "minor" ) )
    {
        super_block->s_minor = swap16 ( value, endianswap );

    } else if ( !strcmp ( name, "root_inode" ) )
    {
        super_block->root_inode = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "bytes_used" ) )
    {
        super_block->bytes_used = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "id" ) )
    {
        super_block->id_table_start = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "xattr" ) )
    {
        super_block->xattr_id_table_start = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "inode" ) )
    {
        super_block->inode_table_start = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "directory" ) )
    {
        super_block->directory_table_start = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "fragment" ) )
    {
        super_block->fragment_table_start = swap64 ( value, endianswap );

    } else if ( !strcmp ( name, "lookup" ) )
    {
        super_block->lookup_table_start = swap64 ( value, endianswap );

    } else
    {
        return -1;
    }

    return 0;
}
