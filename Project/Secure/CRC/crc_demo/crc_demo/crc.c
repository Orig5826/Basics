/**
 * @file crc.c
 * @author wenjf
 * @brief
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "crc.h"

// �ڲ�ʹ��
#define CRC_ST_CUSTOM			0x10
#define CRC_ST_INIT				0x11
#define CRC_ST_UPDATE			0x13

struct _crc
{
	// basic parameters
	uint16_t init;
	uint16_t xor;
	uint8_t reverse_in;
	uint8_t reverse_out;
	uint8_t mode;
	// result
	uint16_t value;
	// status
	uint8_t st;
	// endian
	uint8_t endian;
}crc;

const uint16_t crc_ccit_table[256] =
{
	0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U,
	0x8108U, 0x9129U, 0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,
	0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52B5U, 0x4294U, 0x72F7U, 0x62D6U,
	0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU,
	0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U,
	0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU,
	0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U,
	0xB75BU, 0xA77AU, 0x9719U, 0x8738U, 0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU,
	0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U,
	0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
	0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U,
	0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU,
	0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U, 0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U,
	0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U,
	0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U,
	0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U,
	0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU,
	0x1080U, 0x00A1U, 0x30C2U, 0x20E3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
	0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU,
	0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
	0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU,
	0x34E2U, 0x24C3U, 0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
	0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U, 0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU,
	0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,
	0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU,
	0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U,
	0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU,
	0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U, 0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U,
	0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U,
	0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
	0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U,
	0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U
};

static uint16_t u16_bit_reverse(uint16_t data)
{
	data = (data & 0xFF00) >> 8 | (data & 0x00FF) << 8;
	data = (data & 0xF0F0) >> 4 | (data & 0x0F0F) << 4;
	data = (data & 0xCCCC) >> 2 | (data & 0x3333) << 2;
	data = (data & 0xAAAA) >> 1 | (data & 0x5555) << 1;
	return data;
}

static uint8_t u8_bit_reverse(uint8_t data)
{
	data = (data & 0xF0) >> 4 | (data & 0x0F) << 4;
	data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
	data = (data & 0xAA) >> 1 | (data & 0x55) << 1;
	return data;
}

/**
 * @brief 0. �Զ������
 * 
 * @param init ��ֵ
 * @param xor ������ֵ
 * @param reverse_in ���������Ƿ���Ҫ��λ��ת
 * @param reverse_out ��������Ƿ���Ҫ��λ��ת
 */
void crc_ccit_custom(uint16_t init, uint16_t xor, uint8_t reverse_in, uint8_t reverse_out)
{
	crc.init = init;
	crc.xor = xor;
	crc.reverse_in = reverse_in;
	crc.reverse_out = reverse_out;
	crc.mode = CRC_CUSTOM;

	crc.st = CRC_ST_CUSTOM;
}

/**
 * @brief 1. ��ʼ��
 *     ���Զ������������Ҫ��ִ��**_custom����
 * @param mode ģʽ���궨��CRC_CCIT_xx��
 * @param endian �����С��
 * @return uint8_t ״̬���궨��CRC_ST_xx��
 */
uint8_t crc_ccit_init(uint8_t mode, uint8_t endian)
{
	if (crc.st != CRC_ST_CUSTOM)
	{
		crc.init = 0x0000;
		crc.xor = 0x0000;
		crc.reverse_in = 0;
		crc.reverse_out = 0;
		crc.mode = mode;

		crc.st = CRC_ST_INIT;
	}

	if (endian != 0 && endian != 1)
	{
		crc.st = CRC_ST_ERR;
		return CRC_ST_ERR;
	}

	crc.value = 0;
	crc.endian = endian;
	switch (mode)
	{
	case CRC_CCIT_KERMIT:
	{
		crc.reverse_in = 1;
		crc.reverse_out = 1;
	}break;
	case CRC_CCIT_XMODEM:
	{
		// crc_calc default mode
	}break;
	case CRC_CCIT_FALSE:
	{
		crc.init = 0xFFFF;
	}break;
	case CRC_CCIT_GENIBUS:
	{
		crc.init = 0xFFFF;
		crc.xor = 0xFFFF;
	}break;
	case CRC_CCIT_X_25:
	{
		crc.init = 0xFFFF;
		crc.xor = 0xFFFF;
		crc.reverse_in = 1;
		crc.reverse_out = 1;
	}break;
	case CRC_CCIT_MCRF4XX:
	{
		crc.init = 0xFFFF;
	}break;
	case CRC_CCIT_AUG_CCIT:
	{
		crc.init = 0x1D0F;
	}break;
	case CRC_CCIT_TMS37157:
	{
		crc.init = 0x89EC;
		crc.reverse_in = 1;
		crc.reverse_out = 1;
	}break;
	case CRC_CCIT_RIELLO:
	{
		crc.init = 0xB2AA;
		crc.reverse_in = 1;
		crc.reverse_out = 1;
	}break;
	case CRC_CCIT_CRC_A:
	{
		crc.init = 0xC6C6;
		crc.reverse_in = 1;
		crc.reverse_out = 1;
	}break;

	case CRC_CUSTOM:
	{
		if (crc.st != CRC_ST_CUSTOM)
		{
			crc.st = CRC_ST_ERR;
			return CRC_ST_ERR;
		}
		crc.st = CRC_ST_INIT;
	}break;
	default:
	{
		crc.st = CRC_ST_ERR;
		return CRC_ST_ERR;
	}/*break;*/
	}

	crc.value = crc.init;
	return CRC_ST_SUCCESS;
}

/**
 * @brief 2. �������ݣ���������
 * 
 * @param bytes ��������
 * @param len ���ݳ���
 * @return uint8_t ״̬���궨��CRC_ST_xx��
 */
uint8_t crc_ccit_update(uint8_t * data, uint32_t len)
{
	uint16_t crc_value;
	uint16_t temp;

	if (crc.st != CRC_ST_INIT && crc.st != CRC_ST_UPDATE)
	{
		crc.st = CRC_ST_ERR;
		return CRC_ST_ERR;
	}

	crc_value = crc.value;
	while (len --)
	{
		temp = (uint16_t)(crc_value >> 8);
		if (crc.reverse_in == 1)
		{
			temp ^= u8_bit_reverse(*data);
		}
		else
		{
			temp ^= *(data);
		}

		crc_value = ((crc_value << 8) ^ crc_ccit_table[temp & 0xff]) & 0xFFFF;
		data++;
	}

	crc.value = crc_value;
	crc.st = CRC_ST_UPDATE;

	return CRC_ST_SUCCESS;
}

/**
 * @brief 3. ȡCRC���
 * 
 * @return uint16_t 
 */
uint16_t crc_ccit_get_result(void)
{
	uint16_t crc_value;
	if (crc.st != CRC_ST_UPDATE)
	{
		return 0;
	}

	crc_value = crc.value;
	if (crc.reverse_out == 1)
	{
		crc_value = u16_bit_reverse(crc_value);
	}
	crc_value = crc_value ^ crc.xor;

	if (crc.endian == 1)
	{
		crc.value = (crc_value & 0xff) << 8 | (crc_value & 0xff00) >> 8;
	}
	else
	{
		crc.value = crc_value;
	}

	// ״̬��Ϊ��Ч
	crc.st = CRC_ST_SUCCESS;
	return crc.value;
}

/**
 * @brief CRC ��Ա����
 * 
 */
crc_t g_crc =
{
	crc_ccit_custom,
	crc_ccit_init,
	crc_ccit_update,
	crc_ccit_get_result,
};
