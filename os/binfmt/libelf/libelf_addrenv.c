/****************************************************************************
 *
 * Copyright 2019 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * os/binfmt/libelf/libelf_addrenv.c
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>

#include <errno.h>
#include <debug.h>

#include <tinyara/arch.h>
#include <tinyara/kmalloc.h>
#ifdef CONFIG_APP_BINARY_SEPARATION
#include <tinyara/mm/mm.h>
#endif
#include "libelf.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Constant Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/
#ifdef CONFIG_ARM_MPU
uint8_t mpu_log2regionceil(uintptr_t base, size_t size);
#endif

/****************************************************************************
 * Name: elf_addrenv_alloc
 *
 * Description:
 *   Allocate memory for the ELF image (textalloc and dataalloc). If
 *   CONFIG_ARCH_ADDRENV=n, textalloc will be allocated using kmm_zalloc() and
 *   dataalloc will be a offset from textalloc.  If CONFIG_ARCH_ADDRENV-y, then
 *   textalloc and dataalloc will be allocated using up_addrenv_create().  In
 *   either case, there will be a unique instance of textalloc and dataalloc
 *   (and stack) for each instance of a process.
 *
 * Input Parameters:
 *   loadinfo - Load state information
 *   textsize - The size (in bytes) of the .text address environment needed
 *     for the ELF image (read/execute).
 *   datasize - The size (in bytes) of the .bss/.data address environment
 *     needed for the ELF image (read/write).
 *   heapsize - The initial size (in bytes) of the heap address environment
 *     needed by the task.  This region may be read/write only.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int elf_addrenv_alloc(FAR struct elf_loadinfo_s *loadinfo, size_t textsize, size_t datasize, size_t heapsize)
{
#ifdef CONFIG_ARCH_ADDRENV
	FAR void *vtext;
	FAR void *vdata;
	int ret;

	/* Create an address environment for the new ELF task */

	ret = up_addrenv_create(textsize, datasize, heapsize, &loadinfo->addrenv);
	if (ret < 0) {
		berr("ERROR: up_addrenv_create failed: %d\n", ret);
		return ret;
	}

	/* Get the virtual address associated with the start of the address
	 * environment.  This is the base address that we will need to use to
	 * access the ELF image (but only if the address environment has been
	 * selected.
	 */

	ret = up_addrenv_vtext(&loadinfo->addrenv, &vtext);
	if (ret < 0) {
		berr("ERROR: up_addrenv_vtext failed: %d\n", ret);
		return ret;
	}

	ret = up_addrenv_vdata(&loadinfo->addrenv, textsize, &vdata);
	if (ret < 0) {
		berr("ERROR: up_addrenv_vdata failed: %d\n", ret);
		return ret;
	}

	loadinfo->textalloc = (uintptr_t) vtext;
	loadinfo->dataalloc = (uintptr_t) vdata;
	return OK;
#else
	/* Allocate memory to hold the ELF image */

#ifdef CONFIG_APP_BINARY_SEPARATION
#ifdef CONFIG_OPTIMIZE_APP_RELOAD_TIME
	uint32_t datamemsize = loadinfo->datasize + loadinfo->binp->ramsize;
	uint32_t rosize = loadinfo->rosize;
	/* loadinfo->datasize contains the size of both data and bss sections.
	 * But we need to backup only the data section in the RO region. So,
	 * we need to extend the rosize by just the data section size only. Hence,
	 * we are subtracting bsssize from loadinfo->datasize.
	 */
	loadinfo->rosize += loadinfo->datasize - loadinfo->binp->bsssize;
#ifdef CONFIG_ARM_MPU
	loadinfo->textsize = 1 << mpu_log2regionceil(0, loadinfo->textsize);
	loadinfo->rosize = 1 << mpu_log2regionceil(0, loadinfo->rosize);
	datamemsize = 1 << mpu_log2regionceil(0, datamemsize);
	loadinfo->binp->ramsize = datamemsize;
#endif
#endif

#ifdef CONFIG_OPTIMIZE_APP_RELOAD_TIME
	loadinfo->textalloc = kumm_memalign(loadinfo->textsize, loadinfo->textsize);
	loadinfo->roalloc = kumm_memalign(loadinfo->rosize, loadinfo->rosize);
	loadinfo->dataalloc = kumm_memalign(datamemsize, datamemsize);

	loadinfo->binp->data_backup = loadinfo->roalloc + rosize;
	loadinfo->binp->uheap_size = datamemsize - loadinfo->datasize - sizeof(struct mm_heap_s);
#else
	/* Allocate the RAM partition to load the app into */
	loadinfo->binp->ramstart = kumm_memalign(loadinfo->binp->ramsize, loadinfo->binp->ramsize);
	if (!loadinfo->binp->ramstart) {
		berr("ERROR: Failed to allocate RAM partition\n");
		return -ENOMEM;
	}

	loadinfo->textalloc = loadinfo->binp->ramstart;
	loadinfo->dataalloc = loadinfo->textalloc + loadinfo->textsize;
	loadinfo->binp->uheap_size = loadinfo->binp->ramsize - (loadinfo->textsize + loadinfo->datasize) - sizeof(struct mm_heap_s);
#endif
	loadinfo->binp->heapstart = loadinfo->dataalloc + loadinfo->datasize;
#else
	loadinfo->textalloc = (uintptr_t)kumm_malloc(textsize + datasize);
#endif
	if (!loadinfo->textalloc) {
		berr("ERROR: Failed to allocate text section (size = %u)\n", textsize);
		return -ENOMEM;
	}

#ifdef CONFIG_APP_BINARY_SEPARATION
	if (!loadinfo->dataalloc) {
		berr("ERROR: Failed to allocate data section (size = %u)\n", datasize);
		return -ENOMEM;
	}

#ifdef CONFIG_OPTIMIZE_APP_RELOAD_TIME
	if (!loadinfo->roalloc) {
		berr("ERROR: Failed to allocate ro section (size = %u)\n", loadinfo->rosize);
		return -ENOMEM;
	}
#endif
#endif
	return OK;
#endif
}

/****************************************************************************
 * Name: elf_addrenv_free
 *
 * Description:
 *   Release the address environment previously created by
 *   elf_addrenv_alloc().  This function  is called only under certain error
 *   conditions after the module has been loaded but not yet started.
 *   After the module has been started, the address environment will
 *   automatically be freed when the module exits.
 *
 * Input Parameters:
 *   loadinfo - Load state information
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

void elf_addrenv_free(FAR struct elf_loadinfo_s *loadinfo)
{
#ifdef CONFIG_ARCH_ADDRENV
	int ret;

	/* Free the address environment */

	ret = up_addrenv_destroy(&loadinfo->addrenv);
	if (ret < 0) {
		berr("ERROR: up_addrenv_destroy failed: %d\n", ret);
	}
#else
	/* If there is an allocation for the ELF image, free it */

#ifndef CONFIG_APP_BINARY_SEPARATION
	if (loadinfo->textalloc != 0) {
		kumm_free((FAR void *)loadinfo->textalloc);
	}
#endif
#endif

	/* Clear out all indications of the allocated address environment */

	loadinfo->textalloc = 0;
	loadinfo->dataalloc = 0;
	loadinfo->textsize = 0;
	loadinfo->datasize = 0;
}
