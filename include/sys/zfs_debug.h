/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2005, 2010, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2012, 2017 by Delphix. All rights reserved.
 */

#ifndef _SYS_ZFS_DEBUG_H
#define	_SYS_ZFS_DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef TRUE
#define	TRUE 1
#endif

#ifndef FALSE
#define	FALSE 0
#endif

extern int zfs_flags;
extern int zfs_recover;
extern int zfs_free_leak_on_eio;
extern int zfs_dbgmsg_enable;

#define	ZFS_DEBUG_DPRINTF		(1 << 0)
#define	ZFS_DEBUG_DBUF_VERIFY		(1 << 1)
#define	ZFS_DEBUG_DNODE_VERIFY		(1 << 2)
#define	ZFS_DEBUG_SNAPNAMES		(1 << 3)
#define	ZFS_DEBUG_MODIFY		(1 << 4)
/* 1<<5 was previously used, try not to reuse */
#define	ZFS_DEBUG_ZIO_FREE		(1 << 6)
#define	ZFS_DEBUG_HISTOGRAM_VERIFY	(1 << 7)
#define	ZFS_DEBUG_METASLAB_VERIFY	(1 << 8)
#define	ZFS_DEBUG_SET_ERROR		(1 << 9)
#define	ZFS_DEBUG_INDIRECT_REMAP	(1 << 10)
#define	ZFS_DEBUG_TRIM			(1 << 11)

extern void __zfs_dbgmsg(char *buf);
extern void __dprintf(boolean_t dprint, const char *file, const char *func,
    int line, const char *fmt, ...);
#define	zfs_dbgmsg(...) \
	if (zfs_dbgmsg_enable) \
		__dprintf(B_FALSE, __FILE__, __func__, __LINE__, __VA_ARGS__)

#ifdef ZFS_DEBUG
/*
 * To enable this:
 *
 * $ echo 1 >/sys/module/zfs/parameters/zfs_flags
 */
#define	dprintf(...) \
	if (zfs_flags & ZFS_DEBUG_DPRINTF) \
		__dprintf(B_TRUE, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define	dprintf(...) ((void)0)
#endif /* ZFS_DEBUG */

extern void zfs_panic_recover(const char *fmt, ...);

extern void zfs_dbgmsg_init(void);
extern void zfs_dbgmsg_fini(void);

#ifndef _KERNEL
extern int dprintf_find_string(const char *string);
extern void zfs_dbgmsg_print(const char *tag);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_ZFS_DEBUG_H */
