
#include "reg_flash.h"


void reg_flash_init(void)
{

}

void reg_unlock(void)
{
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;
}
void reg_lock(void)
{
	FLASH->CR |=  1<<7;
}

BOOL reg_program_halfword(uint32_t addr,uint16_t halfword)
{
	uint16_t temp = 0;
	// 0.0 PreProgram
	if(addr % 2 != 0)
	{
		return FALSE;
	}
	
	// FPEC --> Flash Program and Erase Controller
	// 1.0 Check Lock bit
	if(FLASH->CR & (1<<7) )
	{
		return FALSE;
	}
	// 2.0 Set PG => Flash programming chosen
	FLASH->CR |= (1<<0);

	// 3.0 write the halfword
	*(uint16_t *)addr = halfword;
	// 4.0 Wait for the BSY bit to be reset
	while(FLASH->SR & (1<<0));

	// 2.1 You must Reset PG
	FLASH->CR &= ~(1<<0);

	// 5.0 read the value and verify
	temp = *(uint32_t *)addr;
	FLASH->CR |= (1<<0);
	if(temp != halfword)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL reg_earse_page(uint32_t addr)
{
	uint16_t i = 0;
	// 0.0 PreEarse
	if(addr % PHY_PAGE_SIZE != 0)
	{
		return FALSE;
	}
	
	// FPEC --> Flash Program and Erase Controller
	// 1.0 Check Lock bit
	if(FLASH->CR & (1<<7) )
	{
		return FALSE;
	}
	// 2.0 Set PER => Page Earse chosen
	FLASH->CR |= (1<<1);

	// 3.0 write the halfword
	FLASH->AR = addr & (~(PHY_PAGE_SIZE-1) );
	// 4.0 Set the STAT bit
	FLASH->CR |= (1<<6);
	// 5.0 Wait for the BSY bit to be reset
	while(FLASH->SR & (1<<0));

	// 2.1 RESet PER
	FLASH->CR &= ~(1<<1);

	// 6.0 read the value and verify
	while(i < PHY_PAGE_SIZE)
	{
		if(*(uint32_t *)(addr + i) != 0xffffffff)
		{
			return FALSE;
		}
		i+= 4;
	}
	return TRUE;
}

// =======================================================
// earse_mass用来擦除用户区，做应用不用调用。否则把代码就擦除了
#if 0
BOOL reg_earse_mass(void)
{
	uint32_t i = 0;
	// FPEC --> Flash Program and Erase Controller
	// 1.0 Check Lock bit
	if(FLASH->CR & (1<<7) )
	{
		return FALSE;
	}
	// 2.0 Set MER => Erase of all user pages chosen
	FLASH->CR |= (1<<2);
	// 4.0 Set the STAT bit
	FLASH->CR |= (1<<6);
	// 5.0 Wait for the BSY bit to be reset
	while(FLASH->SR & (1<<0));

	// 2.1 RESet PER
	FLASH->CR &= ~(1<<2);

	// 6.0 read the value and verify
	while(i < PHY_FLASH_SIZE)
	{
		if(*(uint32_t *)(PHY_START_ADDR + i) != 0xffffffff)
		{
			return FALSE;
		}
		i+= 4;
	}
    return TRUE;
}
#endif

static BOOL reg_read_data(uint32_t addr, void * rBuf, uint32_t rLen,uint8_t rSize)
{
	uint32_t i = 0;
	if(addr + rLen > PHY_END_ADDR)
	{
		return FALSE;
	}
	
	while(i < rLen)
	{
		switch(rSize)
		{
			case 1:
			{
				
				*((uint8_t *)rBuf + i)				= *((uint8_t *)addr + i);
			}break;
			case 2:
			{
				*((uint16_t *)rBuf + i)				= *((uint16_t *)addr + i);
			}break;
			case 4:
			{
				*((uint32_t *)rBuf + i)				= *((uint32_t *)addr + i);
			}break;
			default:
			{
				
			}break;
		}
		i ++;
	}
	return TRUE;
}

BOOL reg_read_byte(uint32_t addr, uint8_t * rBuf, uint32_t rLen)
{
	return reg_read_data(addr,rBuf,rLen,sizeof(uint8_t));
}
BOOL reg_read_halfword(uint32_t addr, uint16_t * rBuf, uint32_t rLen)
{
	return reg_read_data(addr,rBuf,rLen,sizeof(uint16_t));
}
BOOL reg_read_word(uint32_t addr, uint32_t * rBuf, uint32_t rLen)
{
	return reg_read_data(addr,rBuf,rLen,sizeof(uint32_t));
}
