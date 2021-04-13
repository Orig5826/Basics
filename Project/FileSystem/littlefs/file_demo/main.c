
#include <stdio.h>
#include <stdint.h>

#include "file.h"
#include "lfs.h"

// 硬件属性
#define FILE_PAGE_SIZE		256
#define FILE_BLOCK_SIZE		256


// 文件操作模拟硬件
#define FILE_NAME	"file.bin"

#define flash_read(addr,data,len) \
	file_read(FILE_NAME,(addr),(data),(len))
#define flash_write(addr,data,len) \
	file_write(FILE_NAME,(addr),(data),(len))
#define flash_erase(addr) \
	{\
		uint8_t data[FILE_BLOCK_SIZE];\
		memset(data,0xff,FILE_BLOCK_SIZE);\
		flash_write(addr,data,FILE_BLOCK_SIZE);\
	}

static int _block_read(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, void* buffer, lfs_size_t size)
{
	flash_read(block * c->block_size + off, (uint8_t*)buffer, (uint32_t)size);
	return 0;
}

static int _block_prog(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, const void* buffer, lfs_size_t size)
{
	flash_write(block * c->block_size + off, (uint8_t*)buffer, (uint32_t)size);
	return 0;
}

static int _block_erase(const struct lfs_config* c, lfs_block_t block)
{
	flash_erase(block * c->block_size);
	return 0;
}

static int _block_sync(const struct lfs_config* c)
{
	return 0;
}


lfs_t lfs;
lfs_file_t file;

const struct lfs_config cfg =
{
	// block device operations
	.read = _block_read,
	.prog = _block_prog,
	.erase = _block_erase,
	.sync = _block_sync,

	// block device configuration
	.read_size = 16,
	.prog_size = 16,
	.block_size = 256,	// BLOCK_SIZE
	.block_count = 20,
	.lookahead_size = 256,
	.cache_size = 256,
	.block_cycles = -1,//10,
};


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
	lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
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
