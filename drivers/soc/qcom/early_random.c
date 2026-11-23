/* Copyright (c) 2013-2014, 2016-2018, The Linux Foundation. All rights
 * reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/hw_random.h>
#include <linux/random.h>
#include <linux/io.h>

#include <soc/qcom/scm.h>

#include <asm/cacheflush.h>

#define TZ_SVC_CRYPTO	10
#define PRNG_CMD_ID	0x01

struct tz_prng_data {
	uint8_t		*out_buf;
	uint32_t	out_buf_sz;
} __packed;

#define RANDOM_BUFFER_SIZE	PAGE_SIZE
char random_buffer[RANDOM_BUFFER_SIZE] __aligned(PAGE_SIZE);

void __init init_random_pool(void)
{
	struct tz_prng_data data;
	int ret;
	struct scm_desc desc;

	data.out_buf = (uint8_t *) virt_to_phys(random_buffer);
	desc.args[0] = (unsigned long) data.out_buf;
	desc.args[1] = data.out_buf_sz = SZ_512;
	desc.arginfo = SCM_ARGS(2, SCM_RW, SCM_VAL);

	dmac_flush_range(random_buffer, random_buffer + RANDOM_BUFFER_SIZE);

	ret = scm_call2(SCM_SIP_FNID(TZ_SVC_CRYPTO, PRNG_CMD_ID), &desc);

	if (!ret) {
		u64 bytes_received = desc.ret[0];

		if (bytes_received != SZ_512)
			pr_warn("Did not receive the expected number of bytes from PRNG: %llu\n",
				bytes_received);

		dmac_inv_range(random_buffer, random_buffer +
						RANDOM_BUFFER_SIZE);
		bytes_received = (bytes_received <= RANDOM_BUFFER_SIZE) ?
					bytes_received : RANDOM_BUFFER_SIZE;
		/*
		 * gts6l-lts: since the 4.14.285 RNG rewrite add_hwgenerator_randomness()
		 * calls kthread_should_stop() and may sleep; from setup_arch() on the
		 * boot task that dereferences a NULL kthread (hang before the console).
		 * This one-shot TZ seed is what add_bootloader_randomness() is for
		 * (credited with CONFIG_RANDOM_TRUST_BOOTLOADER).
		 */
		add_bootloader_randomness(random_buffer, bytes_received);
	}
}

