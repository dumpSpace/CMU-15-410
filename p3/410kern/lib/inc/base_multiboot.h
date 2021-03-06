/*
 * base_multiboot.h
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */
/*
 * Copyright (c) 1996, 1998 University of Utah and the Flux Group.
 * All rights reserved.
 * 
 * This file is part of the Flux OSKit.  The OSKit is free software, also known
 * as "open source;" you can redistribute it and/or modify it under the terms
 * of the GNU General Public License (GPL), version 2, as published by the Free
 * Software Foundation (FSF).  To explore alternate licensing terms, contact
 * the University of Utah at csl-dist@cs.utah.edu or +1-801-585-3271.
 * 
 * The OSKit is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GPL for more details.  You should have
 * received a copy of the GPL along with the OSKit; see the file COPYING.  If
 * not, write to the FSF, 59 Temple Place #330, Boston, MA 02111-1307, USA.
 */


/*
 * Functions and data definitions for kernels
 * that want to start up from a MultiBoot boot loader.
 */


#ifndef _BASE_MULTIBOOT_H_
#define _BASE_MULTIBOOT_H_

#include <multiboot.h>

/*
 * This variable holds a copy of the multiboot_info structure
 * which was passed to us by the boot loader.
 */
extern struct multiboot_info boot_info;

/*
 * These variables hold the boot options, such as -h and -d.
 */
extern int oskit_bootargc;
extern char **oskit_bootargv;

/*
 * This function digs through the boot_info structure
 * to find out what physical memory is available to us,
 * and initalizes the malloc_lmm with those memory regions.
 * It is smart enough to skip our own executable, wherever it may be,
 * as well as the important stuff passed by the boot loader
 * such as our command line and boot modules.
 */
void base_multiboot_init_mem(void);

/*
 * This function parses the command-line passed by the boot loader
 * into a nice POSIX-like set of argument and environment strings,
 * and boot-options.
 * It depends on being able to call lmm_alloc with the malloc_lmm.
 */
void base_multiboot_init_cmdline(int *argcp, char ***argvp);

/*
 * This is the first C routine called by crt0/multiboot.o;
 * its default implementation sets up the base kernel environment
 * and then calls main() and exit().
 */
void multiboot_main(unsigned int boot_info_pa);

/*
 * Dump out the boot_info struct nicely.
 */
void multiboot_info_dump(struct multiboot_info *bi);

#endif /* _BASE_MULTIBOOT_H_ */
