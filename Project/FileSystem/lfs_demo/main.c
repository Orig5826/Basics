
#include <stdio.h>
#include <stdint.h>

#include "file.h"
#include "lfs.h"

lfs_t lfs;
lfs_file_t file;

// 硬件属性
#define LFS_READ_SIZE 256
#define LFS_PAGE_SIZE 256
#define LFS_BLOCK_SIZE 1024
#define LFS_CACHE_SIZE (LFS_PAGE_SIZE)

#define LFS_BLOCK_COUNT 256
#define LFS_LOOKAHEAD_SIZE 16 // (LFS_BLOCK_COUNT/8)
#define LFS_ATTR_BUF_SIZE LFS_BLOCK_SIZE
#define LFS_ATTR_COUNT 10

static uint8_t read_buf[LFS_READ_SIZE];
static uint8_t prog_buf[LFS_PAGE_SIZE];
static uint8_t lookahead_buf[LFS_LOOKAHEAD_SIZE];

static uint8_t file_cfg_buffer[LFS_CACHE_SIZE];
// static struct lfs_attr attrs[LFS_ATTR_SIZE];

// 文件操作模拟硬件
#define FILE_NAME "file.bin"

static int _block_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
	uint32_t addr = block * c->block_size + off;
	file_read(FILE_NAME, addr, (uint8_t *)buffer, size);
	return 0;
}

static int _block_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
	uint32_t addr = block * c->block_size + off;
	file_write(FILE_NAME, addr, (uint8_t *)buffer, size);
	return 0;
}

static int _block_erase(const struct lfs_config *c, lfs_block_t block)
{
	uint8_t data[LFS_BLOCK_SIZE];
	memset(data, 0xff, LFS_BLOCK_SIZE);

	uint32_t addr = block * c->block_size;
	file_write(FILE_NAME, addr, data, LFS_BLOCK_SIZE);
	return 0;
}

static int _block_sync(const struct lfs_config *c)
{
	return 0;
}

const struct lfs_config cfg = {
	// block device operations
	.read = _block_read,
	.prog = _block_prog,
	.erase = _block_erase,
	.sync = _block_sync,

	// block device configuration
	.read_size = LFS_READ_SIZE,
	.prog_size = LFS_PAGE_SIZE,
	.block_size = LFS_BLOCK_SIZE,
	.block_count = LFS_BLOCK_COUNT,
	.cache_size = LFS_CACHE_SIZE,
	.lookahead_size = LFS_LOOKAHEAD_SIZE,
	.block_cycles = -1, // 100,

	.read_buffer = read_buf,
	.prog_buffer = prog_buf,
	.lookahead_buffer = lookahead_buf,
};

const struct lfs_file_config file_cfg = {
	.buffer = file_cfg_buffer,
	.attr_count = 0,
	.attrs = NULL,
};

#if 0
int main()
{
	// mount the filesystem
	int err = lfs_mount(&lfs, &cfg);

	// reformat if we can't mount the filesystem
	// this should only happen on the first boot
	if (err)
	{
		err = lfs_format(&lfs, &cfg);
		lfs_mount(&lfs, &cfg);
	}

	// read current count
	uint32_t boot_count = 0;
	// lfs_file_open(&lfs, &file, "@boot_count=", LFS_O_RDWR | LFS_O_CREAT);
	lfs_file_opencfg(&lfs, &file, "@boot_count=", LFS_O_RDWR | LFS_O_CREAT, &file_cfg);

	lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

	// update boot count
	boot_count += 1;
	lfs_file_rewind(&lfs, &file);
	lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

	// remember the storage is not updated until the file is closed successfully
	lfs_file_close(&lfs, &file);

	// release any resources we were using
	lfs_unmount(&lfs);

	// print the boot count
	printf("boot_count: %d\n", boot_count);

	return 0;
}
#else

#define FILE_SIZE (32 * 1024)
static uint8_t file_data[FILE_SIZE];
static uint8_t temp_buf[FILE_SIZE];

int main()
{
	int32_t length = 0;
	int32_t ret = 0;

	file_init(FILE_NAME, LFS_BLOCK_COUNT * LFS_BLOCK_SIZE);

	for (uint32_t i = 0; i < FILE_SIZE; i++)
	{
		file_data[i] = i / 256;
	}

	// mount the filesystem
	int err = lfs_mount(&lfs, &cfg);

	// reformat if we can't mount the filesystem
	// this should only happen on the first boot
	if (err)
	{
		err = lfs_format(&lfs, &cfg);
		lfs_mount(&lfs, &cfg);
	}

	// lfs_file_open(&lfs, &file, "@boot_count=", LFS_O_RDWR | LFS_O_CREAT);
	ret = lfs_file_opencfg(&lfs, &file, "file", LFS_O_RDWR | LFS_O_CREAT, &file_cfg);
	printf("lfs_file_open: %d\n", ret);

	length = lfs_fs_size(&lfs);
	printf("lfs_fs_size: %d\n", length);

	// update boot count
	lfs_file_rewind(&lfs, &file);
	length = lfs_file_write(&lfs, &file, file_data, FILE_SIZE);
	printf("lfs_file_write: %d\n", length);

	//
	// lfs_file_sync(&lfs, &file);
	length = lfs_file_size(&lfs, &file);
	printf("lfs_file_size: %d\n", length);

	lfs_file_rewind(&lfs, &file);
	lfs_file_read(&lfs, &file, temp_buf, FILE_SIZE);
	for (uint32_t i = 0; i < FILE_SIZE; i++)
	{
		if (temp_buf[i] != file_data[i])
		{
			printf("[%d] %d %d\n", i, temp_buf[i], file_data[i]);
			printf("[ERROR] temp_buf is not equal file_data\n");
			return -1;
		}
	}

	// remember the storage is not updated until the file is closed successfully
	lfs_file_close(&lfs, &file);

	// release any resources we were using
	lfs_unmount(&lfs);

	printf("[OK] succeed!\n");

	return 0;
}

#endif
