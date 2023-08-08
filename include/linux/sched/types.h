/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SCHED_TYPES_H
#define _LINUX_SCHED_TYPES_H

#include <uapi/linux/sched/types.h>

/* Kernel-internal since upstream "sched/headers: Move struct sched_param out of uapi":
 * libc (bionic, glibc, musl) defines its own struct sched_param in <sched.h>. */
struct sched_param {
	int sched_priority;
};

#endif /* _LINUX_SCHED_TYPES_H */
