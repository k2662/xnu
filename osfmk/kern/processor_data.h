/*
 * Copyright (c) 2003-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Machine independent per processor data.
 */

#ifndef _KERN_PROCESSOR_DATA_H_
#define _KERN_PROCESSOR_DATA_H_

/*
 * #include kern/processor.h instead of this file.
 */

#ifdef MACH_KERNEL_PRIVATE

#include <ipc/ipc_kmsg.h>
#include <kern/timer.h>

struct processor_data {
	/* Processor state statistics */
	timer_data_t			idle_state;
	timer_data_t			system_state;
	timer_data_t			user_state;

	timer_t					current_state;

	/* Thread execution timers */
	timer_t					thread_timer;
	timer_t					kernel_timer;

	/* Kernel stack cache */
	struct stack_cache {
		vm_offset_t				free;
		unsigned int			count;
	}						stack_cache;

	/* Pending timer callouts */
	queue_head_t			timer_call_queue;

	/* VM event counters */
	vm_statistics_data_t	vm_stat;

	/* IPC free message cache */
	struct ikm_cache {
#define IKM_STASH	16
		ipc_kmsg_t				entries[IKM_STASH];
		unsigned int			avail;
	}						ikm_cache;

	int						slot_num;

	unsigned long			page_grab_count;
	int						start_color;
	void					*free_pages;
};

typedef struct processor_data	processor_data_t;

#define PROCESSOR_DATA(processor, member)	\
					(processor)->processor_data.member

extern	void	processor_data_init(
					processor_t		processor);

#endif /* MACH_KERNEL_PRIVATE */

#endif /* _KERN_PROCESSOR_DATA_H_ */