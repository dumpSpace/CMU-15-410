/*
 * base_cpu_init.c
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1994-1996, 1998 University of Utah and the Flux Group.
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

#include <x86/base_trap.h>
#include <x86/base_gdt.h>
#include <x86/base_tss.h>
#include <x86/base_cpu.h>
#include <x86/base_irq.h>
#include <x86/proc_reg.h>
#include <x86/eflags.h>

void base_cpu_init(void)
{
        unsigned int efl, cr0;

	/* Initialize the processor tables.  */
	base_trap_init();
	base_irq_init();
	base_gdt_init();
	base_tss_init();


        /*
         * Setting these flags sets up alignment checking of
         * all memory accesses.
         */
	efl = get_eflags();
        efl |= EFL_AC;
        set_eflags( efl );

        cr0 = get_cr0();
        cr0 |= CR0_AM;
        set_cr0( cr0 );
}

