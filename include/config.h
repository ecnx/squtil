/* ------------------------------------------------------------------
 * Squashfs Utility - Config Header
 * ------------------------------------------------------------------ */

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <byteswap.h>

#include "squashfs_fs.h"

#ifndef SQUTIL_CONFIG_H
#define SQUTIL_CONFIG_H

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#if ARCH == MIPS
extern void *_mmap ( void *addr, size_t length, int prot, int flags, int fd, long offset );
#endif

#endif
