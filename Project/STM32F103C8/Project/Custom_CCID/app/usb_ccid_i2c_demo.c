/**
 * @brief ʵ��USB_CCIDתI2CС����
 * 
 * �������ǻ���USB_CCID����תI2C��С����
 * �뷨�������ں���32I1����COS,Ȼ����snooper���߽��е���
 * 
 * @attention
 * �����뻹�����ƣ�����ʵ���˻������ܡ�
 * ��������Ҫ����ʵ���������Ӧ�ĵ���������
 * 1. �����ݷ��ͷְ�����
 * 
 * @file usb_ccid_i2c_demo.c
 * @author wenjf
 * @date 2018-06-08
 * @version v1.0
 */
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include <string.h>
#include "i2c_hard.h"

#define USB_CCID_I2C_DEMO
volatile uint8_t ccid_i2c_dataok_flag = 0;
__IO uint8_t PrevXferComplete;
/**
 * @brief ����һ��ȫ�ֱ�����������ʱ�洢���յ�CCID����
 * 
 */
#define CCID_BUFF_SIZE (0x800 + 10)			//!< ��RAM�ռ��ݶ���СΪ2K
static u8 s_ucCCIDBuffer[CCID_BUFF_SIZE];
static u8 sBuff_CCID[CCID_BUFF_SIZE];		//<! ���������ݹ���������ܳ���


void usb_ep1_send(uint8_t * sBuf,uint32_t sLen)
{
	USB_SIL_Write(EP1_IN, (uint8_t*)sBuf, sLen);
	SetEPTxValid(ENDP1);
	
	UartSendString((uint8_t*)"<- ",0);
	UartSendHex((uint8_t*)sBuf,sLen);
}

// stm32 ʹ�õ���Ȼ��ep1
void usb_ep2_recv(uint8_t * rBuf,uint32_t * rLen)
{
	*rLen = USB_SIL_Read(EP1_OUT, rBuf);
	SetEPRxStatus(ENDP1, EP_RX_VALID);

	UartSendString((uint8_t*)"-> ",0);
	UartSendHex((uint8_t*)rBuf,*rLen);
}

/** \def
 * @brief I2C �ӻ���ַ
 * 
 * ע�⣬�˴��ĵ�ַ��ָ������ʵ�ʵ�ַ����7bit����������дbit
 */
// #define SLAVE_ADDR	0x11

/**
 * @brief CCID Message type (Bulk Out Pipe)
 * 
 */
#define PC_2_RDR_ICCPOWERON 0x62
#define PC_2_RDR_ICCPOWEROFF 0x63
#define PC_2_RDR_GETSLOTSTATUS 0x65
#define PC_2_RDR_XFRBLOCK 0x6F
#define PC_2_RDR_GETPARAMETERS 0x6C
#define PC_2_RDR_RESETPARAMETERS 0x6D
#define PC_2_RDR_SETPARAMETERS 0x61
#define PC_2_RDR_ESCAPE 0x6B
#define PC_2_RDR_ICCCLOCK 0x6E
#define PC_2_RDR_T0APDU 0x6A
#define PC_2_RDR_SECURE 0x69
#define PC_2_RDR_MECHANICAL 0x71
#define PC_2_RDR_ABORT 0x72
#define PC_2_RDR_SETDATARATEANDCLOCK 0x73
/**
 * @brief CCID Message type (Bulk In Pipe)
 * 
 */
#define RDR_2_PC_DATABLOCK 0x80
#define RDR_2_PC_SLOTSTATUS 0x81
#define RDR_2_PC_PARAMETERS 0x82
#define RDR_2_PC_ESCAPE 0x83
#define RDR_2_PC_DATARATEANDCLOCK 0x84
#define RDR_2_PC_NOTIFYSLOTCHANGE 0x50
#define RDR_2_PC_HARDWAREERROR 0x51

/**
 * @brief ����CCID����ʹ�õĽṹ��
 * 
 */
struct _CCID_Common_Msg
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucRFU[3];
};
/**
 * @brief BulkIn Message
 * 
 */
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucPowerSel;
	u8 ucRFU[2];
} IccPowerOn_Msg;
typedef struct _CCID_Common_Msg IccPowerOff_Msg;
typedef struct _CCID_Common_Msg GetSlotStatus_Msg;
typedef struct _CCID_Common_Msg GetParameters_Msg;
typedef struct _CCID_Common_Msg ResetParameters_Msg;
typedef struct _CCID_Common_Msg Abort_Msg;
typedef struct
{
	uint8_t ucMsgType;
	uint8_t ucLength[4];
	uint8_t ucSlot;
	uint8_t ucSeq;
	uint8_t ucBWI;
	u16 usLevelParameter;
	uint8_t ucData[1];
} XfrBlock_Msg;
typedef struct
{
	uint8_t ucMsgType;
	uint8_t ucLength[4];
	uint8_t ucSlot;
	uint8_t ucSeq;
	uint8_t ucProtocolNum;
	uint8_t ucRFU[2];
	uint8_t ucProtocolData[1];
} SetParameters_Msg;
typedef struct
{
	uint8_t ucMsgType;
	uint8_t ucLength[4];
	uint8_t ucSlot;
	uint8_t ucSeq;
	uint8_t ucRFU[3];
	uint8_t ucData[1];
} Escape_Msg;
typedef struct
{
	uint8_t ucMsgType;
	uint8_t ucLength[4];
	uint8_t ucSlot;
	uint8_t ucSeq;
	uint8_t ucClockCmd;
	uint8_t ucRFU[2];
} IccClock_Msg;
typedef struct
{
	uint8_t ucMsgType;
	uint8_t ucLength[4];
	uint8_t ucSlot;
	uint8_t ucSeq;
	uint8_t ucChanges;
	uint8_t ucClassGetResponse;
	uint8_t ucClassEnvelope;
} T0APDU;
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucBWI;
	u16 usLevelParameter;
	u8 ucPINOperation;
	u8 ucPINData[1];
} Secure_Msg;
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucFunction;
	u8 ucRFU[2];
} Mechanical_Msg;
typedef struct _SETDATARATEANDCLOCK_MSG
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucRFU[3];
	u32 uiClockFreq;
	u32 uiDataRate;
} SetDataRateAndClockFreq_Msg;
/**
 * @brief BulkOut Message
 * 
 */
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucStatus;
	u8 ucError;
	u8 ucChainParameter;
	u8 ucData[1];
} DataBlock_Msg;
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucStatus;
	u8 ucError;
	u8 ucClockStatus;
} SlotStatus_Msg;
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucStatus;
	u8 ucError;
	u8 ucProtocolNum;
	u8 ucProtocolData[1];
} Parameters_Msg;
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucStatus;
	u8 ucError;
	u8 ucRFU;
	u8 ucData[1];
} EscapeIn_Msg;
typedef struct
{
	u8 ucMsgType;
	u8 ucLength[4];
	u8 ucSlot;
	u8 ucSeq;
	u8 ucStatus;
	u8 ucError;
	u8 ucRFU;
	u32 uiClockFreq;
	u32 uiDataRate;
} DataRateAndClockFreq_Msg;


/**
 * @brief APDU �ṹ��
 * 
 * ע�����е�pData��ָ��Data��ָ��
 */
typedef struct _APDU
{
	u8 CLA;
	u8 INS;
	u8 P1;
	u8 P2;
	u32 Lc;
	u8 *pData;
	u32 Le;
} APDU;

/**
 * @brief ���յ������ݣ�ֱ������ΪAPDU�ṹ��
 * 
 * �����������APDU���ݽ��д���͵���
 * @param pAPDU APDU�ṹ��ָ��
 * @param APDU_Buff ���յ���apdu�Ļ���
 * @param APDU_Len ʵ�ʽ��յ���apdu���ܳ���
 */
void SetAPDU(APDU *pAPDU, u8 *APDU_Buff, u32 APDU_Len)
{
	pAPDU->CLA = APDU_Buff[0];
	pAPDU->INS = APDU_Buff[1];
	pAPDU->P1 = APDU_Buff[2];
	pAPDU->P2 = APDU_Buff[3];
	//Ԥ��ʼ��,����Case1
	pAPDU->Lc = 0x00;
	pAPDU->pData = NULL;
	pAPDU->Le = 0x00;

	if (APDU_Len >= 4)
	{
		// �ж��Ƿ�Ϊ��չAPDU
		if (APDU_Buff[4] != 0x00)
		{
			if (APDU_Len == 0x05)
			{
				// Case 2
				pAPDU->Le = APDU_Buff[4];
			}
			else
			{
				pAPDU->Lc = APDU_Buff[4];
				pAPDU->pData = &APDU_Buff[5];

				if (pAPDU->Lc + 5 < APDU_Len)
				{
					// Case 4
					pAPDU->Le = APDU_Buff[5 + pAPDU->Lc];
				}
			}
		}
		else
		{
			//��չAPDU����δʵ��
		}
	}
}

/**
 * @brief ö�����ͣ���ʾCASE[1-4]
 * 
 */
typedef enum _emCase
{
	CASE1 = 1,
	CASE2 = 2,
	CASE3 = 3,
	CASE4 = 4
} emCase;
/**
 * @brief �����жϵ�ǰ��APDUָ���Ƿ�ΪCase����ָ����CASE
 * 
 * @param Case �жϵ�CASE
 * 		@arg CASE1
 * 		@arg CASE2
 * 		@arg CASE3
 * 		@arg CASE4
 * @param pAPDU 
 * @return u8 1.��   0.��
 */
u8 isCase(emCase Case,const APDU * pAPDU)
{
	u8 ret = 1;
	switch (Case)
	{
	case CASE1:
	{
		if(pAPDU->Lc != 0x00 || pAPDU ->pData != NULL || pAPDU -> Le != 0x00)
		{
			ret = 0;
		}
	}
	break;
	case CASE2:
	{
		if(pAPDU->Lc != 0x00 || pAPDU ->pData != NULL || pAPDU -> Le == 0x00)
		{
			ret = 0;
		}
	}
	break;
	case CASE3:
	{
		if(pAPDU->Lc == 0x00 || pAPDU ->pData == NULL || pAPDU -> Le != 0x00)
		{
			ret = 0;
		}
	}
	break;
	case CASE4:
	{
		if(pAPDU->Lc == 0x00 || pAPDU ->pData == NULL || pAPDU -> Le == 0x00)
		{
			ret = 0;
		}
	}
	break;
	default:
		ret = 0;
	break;
	}

	return ret;
}

/**
 * @brief User���APDUָ��
 * 
 * ���������պͷ��͵����ݣ���������CCID����ͷ
 * 
 * @param rBuf ���յ������ݻ���
 * @param rLen ���յ������ݳ���
 * @param sBuf ��Ҫ���ص����ݻ���
 * @param sLen ��Ҫ���ص����ݳ���
 */
void UserCommond(u8 *rBuf, u32 rLen, u8 *sBuf, u32 *sLen)
{
#ifndef USB_CCID_I2C_DEMO
	u32 i = 0;
#endif
	APDU pAPDU;

	SetAPDU(&pAPDU, rBuf, rLen);

	*sLen = 2;
	switch (pAPDU.INS)
	{
#ifdef USB_CCID_I2C_DEMO
	case 0xC2:
	{
		/*
		I2C ͨѶ��ӵ�����
		����ƫ��5�ֽڣ�����Ϊsnp���ߵķǱ�׼ָ���װ����
		*/
		memmove(rBuf,rBuf + 5,rLen - 5);
		rLen -= 5;
	} //break;
	default:
	{
#if 0
		// ** ����У��ֵ�������������ֶ� **
		{
			uint8_t temp = 0;
			uint32_t i = 0;
			
			for(i = 0; i < rLen; i++)
			{
				temp ^= rBuf[i];
			}

			memmove(rBuf + 2,rBuf,rLen);
			rBuf[0] = (rLen >> 8) & 0xff;
			rBuf[1] = (rLen     ) & 0xff;
			rLen += 2;
			
			rBuf[rLen] = temp;
			rLen += 1;
			
			I2C_Write(rBuf,rLen);
		}
		Delay(10000);
		{
			uint8_t temp = 0;
			uint32_t i = 0;
			
			I2C_Read(sBuf,(uint16_t *)sLen);
			*sLen -= 1;
			for(i = 0; i < *sLen - 2; i++)
			{
				temp ^= sBuf[2 + i];
			}
			
			if(temp != sBuf[*sLen])
			{
				sBuf[0] = 0x00;
				sBuf[1] = 0x00;
				*sLen = 2;
				return;
			}
			
			*sLen -= 2;
			memmove(sBuf,sBuf + 2,*sLen);
		}
#else
		// ** ����У��ֵ����Ҫ���������ֶ� **
		{
			uint8_t temp = 0;
			uint32_t i = 0;

			memmove(rBuf + 2,rBuf,rLen);
			rBuf[0] = (rLen >> 8) & 0xff;
			rBuf[1] = (rLen     ) & 0xff;
			rLen += 2;
			
			for(i = 0; i < rLen; i++)
			{
				temp ^= rBuf[i];
			}
			rBuf[rLen] = temp;
			rLen += 1;
			
			I2C_Write(rBuf,rLen);
		}
		// Delay(20000);
		{
			uint8_t temp = 0;
			uint32_t i = 0;
			
			I2C_Read(sBuf,(uint16_t *)sLen);
			*sLen -= 1;
			for(i = 0; i < *sLen; i++)
			{
				temp ^= sBuf[i];
			}
			
			if(temp != sBuf[*sLen])
			{
				sBuf[0] = 0x00;
				sBuf[1] = 0x00;
				*sLen = 2;
				return;
			}
			
			*sLen -= 2;
			memmove(sBuf,sBuf + 2,*sLen);
		}
#endif
	}break;
#else
	case 0x84:
	{
		if(!isCase(CASE2,&pAPDU))
		{
			sBuf[0] = 0x6F;
			sBuf[1] = 0x81;
			return;
		}
		if (pAPDU.CLA != 0x00)
		{
			sBuf[0] = 0x6E;
			sBuf[1] = 0x00;
			return;
		}
		if (pAPDU.P1 != 0x00 || pAPDU.P2 != 0x00)
		{
			sBuf[0] = 0x6A;
			sBuf[1] = 0x86;
			return;
		}

		#if 1
		// 1.0 �������������Զ���
		for (i = 0; i < pAPDU.Le; i++)
		{
			sBuf[i] = i;
		}
		#else
		// 1.1 ���������
		TRNG_Init(TRUE_RANDOM_NUMBER);
		Get_RND_Bytes(sBuf,pAPDU.Le);
		#endif
		sBuf[pAPDU.Le] = 0x90;
		sBuf[pAPDU.Le + 1] = 0x00;
		*sLen += pAPDU.Le;
	}
	break;
	case 0x03:
	{
		// ����ָ�������������CCID���ݷְ��Ƿ��
		// ���³���ͨѶ���ȶ�����������õ�
		memcpy(sBuf,pAPDU.pData,pAPDU.Lc);
		
		sBuf[pAPDU.Lc + 0] = 0x90;
		sBuf[pAPDU.Lc + 1] = 0x00;
		*sLen += pAPDU.Lc;
		
		// UartSendHex((uint8_t *)sLen,4);
	}break;
	default:
	{
		sBuf[0] = 0x6D;
		sBuf[1] = 0x00;
	}
	break;
#endif
	}
}

/**
 * @brief CCID��׼����
 * 
 */
void CCID_Command(void)
{
	u32 rLen;
	u32 len;
	u32 ccid_length = 0;
	
	struct _CCID_Common_Msg *pCCID_Cmd;
	memset(s_ucCCIDBuffer, 0x00, CCID_BUFF_SIZE);

	/*
		��CCID���ڵ�main������ѭ�����У�������EP1_OUT�жϵ��У���Ϊÿ�������жϣ�
	��ʵ������64�ֽ����ݣ������ݰ������64�������������Ӧ�õ��´������ж��ٽ���ִ�С�
	����֮ǰ��CCID_Commandֱ�ӷ�����EP1_OUT_Callback�������У��������������ݿ϶�û�������Ž����ҷ���
	���ʵĻ���λ�á����ڲ������ж�����ӱ�����־��Ȼ�����е����ݶ�������while(1)ѭ�����жϡ�
	�������Է�ֹ���ݶ�ʧ����Ȼ�ˣ���ѭ���ȴ���Ҳ�б׶ˣ�������ڵ�ǰ��Ӧ����˵�����ַ�ʽ��Ϊ�ȶ���
	��˲�ȡ���ַ�ʽ��
	*/
	while(ccid_i2c_dataok_flag != 1);
	ccid_i2c_dataok_flag = 0;
	usb_ep2_recv(s_ucCCIDBuffer,&len);
	ccid_length += len;
	
	pCCID_Cmd = (struct _CCID_Common_Msg *)s_ucCCIDBuffer;
	rLen = ((pCCID_Cmd->ucLength[0]) + (pCCID_Cmd->ucLength[1] << 8) + (pCCID_Cmd->ucLength[2] << 16) + (pCCID_Cmd->ucLength[3] << 24)) + 10; //�ڴ�Ҫ�յ������ݳ���
	while(ccid_length != rLen)
	{
		while(ccid_i2c_dataok_flag != 1);
		ccid_i2c_dataok_flag = 0;
		usb_ep2_recv(s_ucCCIDBuffer + ccid_length,&len);
		ccid_length += len;
	}
#if 0
	//��ʵ����Ҫ���յ����ݳ��ȴ���1��������Ҫ���պ����İ�
	if(rLen > 0x40)
	{
		uint8_t *pBuf = s_ucCCIDBuffer + 0x40;
		len = rLen - 0x40;
		while(len > 0x40)
		{
			usb_ep2_recv(pBuf,0x40);
			pBuf += 0x40;
			len -= 0x40;
		}
		usb_ep2_recv(pBuf,len);
	}
	len = 0x40;
	while(len < rLen + 0x10)
	{
		len += 0x40;
		usb_ep2_recv(s_ucCCIDBuffer + len,0x40);
	}
#endif
	// Debug
	// UartSendHex((u8 *)s_ucCCIDBuffer,0x40);

	//5,6 bSlot��bSeq��Ҫ��BulkOut������Ӧ���ݱ���һ��
	sBuff_CCID[5] = pCCID_Cmd->ucSlot;
	sBuff_CCID[6] = pCCID_Cmd->ucSeq;

	switch (pCCID_Cmd->ucMsgType)
	{
	case PC_2_RDR_ICCPOWERON:
	{
		DataBlock_Msg *pDatBlk;
		pDatBlk = (DataBlock_Msg *)sBuff_CCID;

		pDatBlk->ucMsgType = RDR_2_PC_DATABLOCK;
		len = 0x09;
		pDatBlk->ucLength[0] = len & 0xff;
		pDatBlk->ucLength[1] = (len >> 8) & 0xff;
		pDatBlk->ucLength[2] = (len >> 16) & 0xff;
		pDatBlk->ucLength[3] = (len >> 24) & 0xff;

		pDatBlk->ucStatus = 0x00;
		pDatBlk->ucError = 0x00;
		pDatBlk->ucChainParameter = 0x00;

		// �ϵ緵��ATR����
		pDatBlk->ucData[0] = 0x3b;
		pDatBlk->ucData[1] = 0x65;
		pDatBlk->ucData[2] = 0x00;
		pDatBlk->ucData[3] = 0x00;
		pDatBlk->ucData[4] = 0x48;
		pDatBlk->ucData[5] = 0x53;
		pDatBlk->ucData[6] = 0x33;
		pDatBlk->ucData[7] = 0x32;
		pDatBlk->ucData[8] = 0x4b;
	}
	break;
	case PC_2_RDR_ICCPOWEROFF:
	{
		SlotStatus_Msg *pSlotStatus;
		pSlotStatus = (SlotStatus_Msg *)sBuff_CCID;

		pSlotStatus->ucMsgType = RDR_2_PC_SLOTSTATUS;
		memset(pSlotStatus->ucLength, 0x00, 4);
		pSlotStatus->ucStatus = 0x00;
		pSlotStatus->ucError = 0x00;
		pSlotStatus->ucClockStatus = 0x00;
		len = 0;
	}
	break;
	case PC_2_RDR_XFRBLOCK:
	{
		DataBlock_Msg *pDatBlk;
		pDatBlk = (DataBlock_Msg *)sBuff_CCID;

		// �Զ�������
		UserCommond((u8 *)&s_ucCCIDBuffer[10], rLen - 10, (u8 *)&sBuff_CCID[10], &len);

		pDatBlk->ucMsgType = RDR_2_PC_DATABLOCK;
		pDatBlk->ucLength[0] = len & 0xff;
		pDatBlk->ucLength[1] = (len >> 8) & 0xff;
		pDatBlk->ucLength[2] = (len >> 16) & 0xff;
		pDatBlk->ucLength[3] = (len >> 24) & 0xff;

		pDatBlk->ucStatus = 0x00;
		pDatBlk->ucError = 0x00;
		pDatBlk->ucChainParameter = 0x00;
	}
	break;
	default:
	{
		SlotStatus_Msg *pSlotStatus;
		pSlotStatus = (SlotStatus_Msg *)sBuff_CCID;

		pSlotStatus->ucMsgType = RDR_2_PC_SLOTSTATUS;
		memset(pSlotStatus->ucLength, 0x00, 4);
		pSlotStatus->ucStatus = 0x40; //not supported/ incorrect message parameter ???
		pSlotStatus->ucError = 0x00;
		pSlotStatus->ucClockStatus = 0x00;
		len = 0;
	}
	break;
	}

	{
		/*
			����Ҫ����BLOCK_SIZE������������ʱ����Ҫ����෢һ���ֽ�����
			���ַ��ط�ʽ��Ϊ�����snp����
		*/
		uint32_t length = 0;
		uint8_t *pBuf = sBuff_CCID;
		length = 10 + len;

#define BLOCK_SIZE		64
		while(length >= BLOCK_SIZE)
		{
			usb_ep1_send((u8 *)pBuf,BLOCK_SIZE);
			while(PrevXferComplete != 1);
			PrevXferComplete = 0;

			length -= BLOCK_SIZE;
			pBuf += BLOCK_SIZE;
		}
		
		if(length != 0)
		{
			usb_ep1_send((u8 *)pBuf,length);
			while(PrevXferComplete != 1);
			PrevXferComplete = 0;
		}
		else
		{
			uint8_t temp = 0x00;
			usb_ep1_send((u8 *)&temp,1);
			while(PrevXferComplete != 1);
			PrevXferComplete = 0;
		}
	}
}
