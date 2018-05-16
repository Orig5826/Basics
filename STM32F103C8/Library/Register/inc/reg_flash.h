
#ifndef _REG_FLASH_H_
#define _REG_FLASH_H_

#include "stm32f10x.h"
#include "typedef.h"
// ---------------------------------------
// Start Addr = 0x08000000
// Flash Memery Size  =  64K
// Page Size = 1K
// ---------------------------------------
#define PHY_START_ADDR	0x08000000
#define PHY_FLASH_SIZE	0x10000
#define PHY_PAGE_SIZE	0x400
//
#define PHY_END_ADDR	(PHY_START_ADDR + PHY_FLASH_SIZE)
#define PHY_PAGE_CNT	(PHY_FLASH_SIZE/PHY_PAGE_SIZE)


// ---------------------------------------
// 				Interface
// ---------------------------------------
// read
BOOL reg_read_byte(uint32_t addr, uint8_t * rBuf, uint32_t rLen);
BOOL reg_read_halfword(uint32_t addr, uint16_t * rBuf, uint32_t rLen);
BOOL reg_read_word(uint32_t addr, uint32_t * rBuf, uint32_t rLen);
// write
void reg_unlock(void);
void reg_lock(void);
BOOL reg_program_halfword(uint32_t addr,uint16_t halfword);
// earse
BOOL reg_earse_page(uint32_t addr);

#endif
