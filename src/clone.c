/* ------------------------------------------------------------------
 * Squashfs Utility - Superblock Timestamp Clone
 * ------------------------------------------------------------------ */

#include "squtil.h"

/**
 * Clone superblock timestamp
 */
int squashfs_clone_mkfs_time ( const unsigned char *pmaddr, size_t length, const char *srcpath )
{
    int fd;
    size_t read_len;
    struct squashfs_super_block *dst_super_block = ( struct squashfs_super_block * ) pmaddr;
    struct squashfs_super_block src_super_block;

    /* Validate data size */
    if ( length < sizeof ( struct squashfs_super_block ) )
    {
        fprintf ( stderr, "file is too short %lu < %lu\n", ( unsigned long ) length,
            sizeof ( struct squashfs_super_block ) );
        return -1;
    }

    /* Open source file for reading */
    if ( ( fd = open ( srcpath, O_RDONLY ) ) < 0 )
    {
        perror ( srcpath );
        return -1;
    }

    /* Read superblock from source file */
    if ( ( ssize_t ) ( read_len =
            read ( fd, &src_super_block, sizeof ( struct squashfs_super_block ) ) ) < 0 )
    {
        perror ( "read" );
        close ( fd );
        return -1;
    }

    /* Validate read superblock size */
    if ( read_len < sizeof ( struct squashfs_super_block ) )
    {
        fprintf ( stderr, "srcfile is too short %lu < %lu\n", ( unsigned long ) read_len,
            sizeof ( struct squashfs_super_block ) );
        close ( fd );
        return -1;
    }

    /* Clone the timestamp */
    dst_super_block->mkfs_time = src_super_block.mkfs_time;

    /* Close source file fd */
    close ( fd );

    return 0;
}
