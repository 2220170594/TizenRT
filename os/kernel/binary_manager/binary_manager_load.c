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
 * Included Files
 ****************************************************************************/
#include <tinyara/config.h>
#include <stdio.h>
#include <debug.h>
#include <stdlib.h>
#include <errno.h>
#include <crc32.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>

#include <tinyara/mm/mm.h>
#include <tinyara/sched.h>
#include <tinyara/init.h>

#include "task/task.h"
#include "binary_manager.h"

/****************************************************************************
 * Private Definitions
 ****************************************************************************/
struct binary_header_s {
	uint16_t header_size;
	uint16_t bin_type;
	uint32_t bin_size;
	char bin_name[BIN_NAME_MAX];
	char bin_ver[BIN_VER_MAX];
	uint32_t ram_size;
	char kernel_ver[KERNEL_VER_MAX];
	uint32_t jump_addr;
};
typedef struct binary_header_s binary_header_t;

/****************************************************************************
 * Private Functions
 ****************************************************************************/
/* Read header and Check whether header data is valid or not */
static int binary_manager_read_header(int bin_idx, int part_idx, binary_header_t *header_data)
{
	int fd;
	int ret;
	int read_size;
	int file_size;
	uint32_t crc_hash = 0;
	uint32_t check_crc = 0;
	uint8_t crc_buffer[CRC_BUFFER_SIZE];
	char devname[BINMGR_DEVNAME_LEN];

	memset(header_data, 0, sizeof(binary_header_t));

	snprintf(devname, BINMGR_DEVNAME_LEN, BINMGR_DEVNAME_FMT, BIN_PARTNUM(bin_idx, part_idx));
	fd = open(devname, O_RDONLY);
	if (fd < 0) {
		bmdbg("Failed to open %s: %d, errno %d\n", devname, ret, errno);
		return ERROR;
	}

	/* Read the checksum */
	ret = read(fd, (FAR uint8_t *)&crc_hash, CHECKSUM_SIZE);
	if (ret != CHECKSUM_SIZE) {
		bmdbg("Failed to read %s: %d, errno %d\n", devname, ret, errno);
		goto errout_with_fd;
	}

	/* Read the binary header */
	ret = read(fd, (FAR uint8_t *)header_data, sizeof(binary_header_t));
	if (ret != sizeof(binary_header_t)) {
		bmdbg("Failed to read %s: %d, errno %d\n", devname, ret, errno);
		goto errout_with_fd;
	}

	/* Verify header data */
	if (header_data->header_size < 0 || header_data->bin_size < 0 \
		|| header_data->ram_size < 0 || header_data->bin_type != BIN_TYPE_ELF) {
		bmdbg("Invalid header data : headersize %d, binsize %d, ramsize %d, bintype %d\n", header_data->header_size, header_data->bin_size, header_data->ram_size, header_data->bin_type);
		goto errout_with_fd;
	}

	/* Caculate checksum and Verify it */
	check_crc = crc32part((uint8_t *)header_data, header_data->header_size, check_crc);
	file_size = header_data->bin_size;
	while (file_size > 0) {
		read_size = file_size < CRC_BUFFER_SIZE ? file_size : CRC_BUFFER_SIZE;
		ret = read(fd, (FAR uint8_t *)crc_buffer, read_size);
		if (ret < 0 || ret != read_size) {
			bmdbg("Failed to read : %d, errno %d\n", ret, errno);
			goto errout_with_fd;
		}
		check_crc = crc32part(crc_buffer, read_size, check_crc);
		file_size -= read_size;
	}

	if (check_crc != crc_hash) {
		bmdbg("Failed to crc check : %u != %u\n", check_crc, crc_hash);
		goto errout_with_fd;
	}

	bmvdbg("Binary header : %d %d %d %s %s %d %s %d\n", header_data->header_size, header_data->bin_type, header_data->bin_size, header_data->bin_name, header_data->bin_ver, header_data->ram_size, header_data->kernel_ver, header_data->jump_addr);
	close(fd);

	return OK;
errout_with_fd:
	close(fd);

	return ERROR;
}

/* Read binary header and update binary table */
static int binary_manager_load_bininfo(int bin_idx)
{
	int ret;
	int version;
	int part_idx;
	int latest_ver;
	int latest_idx;
	binary_header_t header_data[PARTS_PER_BIN];

	latest_ver = -1;
	latest_idx = -1;

	/* Read header data of binary partitions */
	for (part_idx = 0; part_idx < PARTS_PER_BIN; part_idx++) {
		if (BIN_PARTNUM(bin_idx, part_idx) < 0) {
			break;
		}
		ret = binary_manager_read_header(bin_idx, part_idx, &header_data[part_idx]);
		if (ret == OK) {
			version = (int)atoi(header_data[part_idx].bin_ver);
			bmvdbg("Found valid header in part %d, version %d\n", part_idx, version);
			if (version > latest_ver) {
				latest_ver = version;
				latest_idx = part_idx;
			}
		}
	}

	/* Failed to find valid binary */
	if (latest_ver < 0) {
		bmdbg("Failed to find loadable binary %d\n", bin_idx);
		return ERROR;
	}

	/* Set the data in table from header */
	BIN_USEIDX(bin_idx) = latest_idx;
	BIN_SIZE(bin_idx) = header_data[latest_idx].bin_size;
	BIN_RAMSIZE(bin_idx) = header_data[latest_idx].ram_size;
	BIN_OFFSET(bin_idx) = CHECKSUM_SIZE + header_data[latest_idx].header_size;
	strncpy(BIN_VER(bin_idx), header_data[latest_idx].bin_ver, BIN_VER_MAX);
	strncpy(BIN_KERNEL_VER(bin_idx), header_data[latest_idx].kernel_ver, KERNEL_VER_MAX);
	strncpy(BIN_NAME(bin_idx), header_data[latest_idx].bin_name, BIN_NAME_MAX);

	bmvdbg("BIN TABLE[%d] %d %d %s %s %s\n", bin_idx, BIN_SIZE(bin_idx), BIN_RAMSIZE(bin_idx), BIN_VER(bin_idx), BIN_KERNEL_VER(bin_idx), BIN_NAME(bin_idx));

	return OK;
}

/* Load binary with index in binary table */
int binary_manager_load_binary(int bin_idx)
{
	int ret;
	pid_t pid;
	char devname[BINMGR_DEVNAME_LEN];

	if (bin_idx < 0) {
		bmdbg("Invalid bin idx %d\n", bin_idx);
		return ERROR;
	}

	/* Load binary info */
	ret = binary_manager_load_bininfo(bin_idx);
	if (ret < 0) {
		bmdbg("Failed to get loadable binary %d\n", bin_idx);
		return ERROR;
	}

	/* Load binary */
	snprintf(devname, BINMGR_DEVNAME_LEN, BINMGR_DEVNAME_FMT, BIN_PARTNUM(bin_idx, BIN_USEIDX(bin_idx)));
	bmvdbg("BIN[%d] %s %d %d\n", bin_idx, devname, BIN_SIZE(bin_idx), BIN_OFFSET(bin_idx));
	pid = load_binary(devname, BIN_SIZE(bin_idx), BIN_OFFSET(bin_idx), BIN_RAMSIZE(bin_idx));
	if (pid <= 0) {
		bmdbg("Load '%s' fail, errno %d\n", BIN_NAME(bin_idx), errno);
		return ERROR;
	}
	BIN_ID(bin_idx) = pid;
	bmvdbg("Load '%s' success! pid = %d\n", BIN_NAME(bin_idx), BIN_ID(bin_idx));

	return OK;
}

static int binary_manager_load_all(void)
{
	int ret;
	int bin_idx;
	int load_cnt;
	int bin_count;

	load_cnt = 0;
	bin_count = binary_manager_get_binary_count();

	for (bin_idx = 1; bin_idx <= bin_count; bin_idx++) {
		ret = binary_manager_load_binary(bin_idx);
		if (ret == OK) {
			load_cnt++;
		}
	}

	if (load_cnt > 0) {
		return load_cnt;
	}

	return BINMGR_OPERATION_FAIL;
}

static void reload_kill_each(FAR struct tcb_s *tcb, FAR void *arg)
{
	int ret;
	int binid;

	binid = (int)arg;
	if (binid < 0) {
		return;
	}

	if (tcb->group->tg_loadtask == binid && tcb->pid != binid) {
		ret = task_terminate(tcb->pid, true);
		if (ret < 0) {
			bmdbg("Failed to terminate %d\n", tcb->pid);
		}
	}
}

int reload_kill_binary(int binid)
{
	int ret;

	if (binid < 0) {
		return ERROR;
	}

	sched_lock();

	/* Kill all tasks and pthreads created in a binary which has 'binid' */
	sched_foreach(reload_kill_each, (FAR void *)binid);

	/* Finally, unload binary */
	ret = task_terminate(binid, true);
	if (ret < 0) {
		sched_unlock();
		bmdbg("Failed to unload binary %d, ret %d, errno %d\n", binid, ret, errno);
		return ERROR;
	}
	sched_unlock();
	bmvdbg("Unload binary! pid %d\n", binid);

	return OK;
}

/****************************************************************************
 * Name: binary_manager_reload
 *
 * Description:
 *   This function will terminate all the task/thread created by the binary
 *   i.e input binary name.
 *   If the binary is registered, it terminates its children and unloads binary.
 *   And then, it will load the binary.
 *
 * Input parameters:
 *   bin_name   -   The name of binary to be reload
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/
static int binary_manager_reload(char *bin_name)
{
	int ret;
	int bin_idx;

	if (bin_name == NULL) {
		bmdbg("Invalid bin_name %s\n", bin_name);
		return BINMGR_INVALID_PARAM;
	}

	/* Check whether it is registered in binary manager */
	bin_idx = binary_manager_get_index_with_name(bin_name);
	if (bin_idx < 0) {
		bmdbg("binary %s is not registered\n", bin_name);
		return BINMGR_BININFO_NOT_FOUND;
	}

	/* Kill its children and restart binary if the binary is registered with the binary manager */
	ret = reload_kill_binary(BIN_ID(bin_idx));
	if (ret != OK) {
		return BINMGR_OPERATION_FAIL;
	}
	BIN_ID(bin_idx) = -1;

	/* load binary and update binid */
	ret = binary_manager_load_binary(bin_idx);
	if (ret != OK) {
		bmdbg("Failed to load binary, bin_idx %d\n", bin_idx);
		return BINMGR_OPERATION_FAIL;
	}

	return BINMGR_OK;
}

static int loading_thread(int argc, char *argv[])
{
	int ret;
	int type;

	if (argc <= 1) {
		bmdbg("Invalid arguments\n");
		return -1;
	}

	/* Arguments : [1] type */
	type = (int)atoi(argv[1]);

	ret = BINMGR_INVALID_PARAM;
	switch (type) {
	case LOADCMD_LOAD_ALL:
		ret = binary_manager_load_all();
		break;
	case LOADCMD_RELOAD:
		if (argc <= 2) {
			bmdbg("Invalid arguments for reloading, argc %d\n", argc);
			break;
		}
		/* [2] bin_name for reloading */
		ret = binary_manager_reload(argv[2]);
		break;
	default:
		bmdbg("Invalid loading type %d\n", type);
	}
	bmvdbg("Loading result %d\n", ret);

	return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/
/****************************************************************************
 * Name: binary_manager_loading
 *
 * Description:
 *   This function create loading thread to load/unload binary.
 *
 ****************************************************************************/
int binary_manager_loading(char *loading_data[])
{
	int ret;

	ret = kernel_thread(LOADINGTHD_NAME, LOADINGTHD_PRIORITY, LOADINGTHD_STACKSIZE, loading_thread, (char * const *)loading_data);
	if (ret > 0) {
		bmvdbg("Execute loading thread with pid %d\n", ret);
	} else {
		bmdbg("Loading Fail\n");
	}

	return ret;
}
