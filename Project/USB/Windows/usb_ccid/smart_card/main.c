
#include <winscard.h>
#include <stdio.h>
#include <stdint.h>

void display(uint8_t * data, uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		printf("%02x ", *(data + i));
	}
	printf("\n");
}

void main()
{
	SCARDHANDLE  m_hCard;
	SCARDCONTEXT m_hContext;
	DWORD m_dwActiveProtocol; //实际使用的协议

	char *mszReaders = NULL;
	DWORD dwReaders = SCARD_AUTOALLOCATE;//自动申请内存
	LONG rv;

	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &m_hContext);
	if (rv != SCARD_S_SUCCESS)
	{
		printf("SCardEstablishContext error\n");
		return;
	}

	rv = SCardListReaders(m_hContext, NULL, (LPSTR)&mszReaders, &dwReaders);
	if (rv != SCARD_S_SUCCESS)
	{
		printf("SCardListReaders error\n");
		return;
	}

	for (uint32_t i = 0; i < dwReaders; i++)
	{
		if (mszReaders[i] != 0x00)
		{
			printf("%c", mszReaders[i]);
		}
	}
	printf("\n");

	rv = SCardConnect(m_hContext, (LPSTR)mszReaders, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &m_hCard, &m_dwActiveProtocol);
	if (rv != SCARD_S_SUCCESS)
	{
		printf("SCardConnect error\n");
		return;
	}

	switch (m_dwActiveProtocol)
	{
	case SCARD_PROTOCOL_T0:
	{
		printf("T0 协议\n");
	}break;
	case SCARD_PROTOCOL_T1:
	{
		printf("T1 协议\n");
	}break;
	default:
		break;
	}
	
	// sm4 加解密算法
	{
		uint8_t send_buf[2048] = {
			0x00,0x03,0x00,0x00};
		uint8_t recv_buf[2048];
		uint32_t datalen = 0;
		DWORD send_len;
		DWORD recv_len = sizeof(recv_buf);

		uint8_t algo = 0x02;  // 0.des/tdes 1.aes 2.sm4 3.sm1
		uint8_t mode = 0x00;  // 0.ecb 1.cbc 2.ofb 3.ctr
		uint8_t type = 0x00;   // 0.encrypt 1.decrypt
		uint32_t keylen = 16;
		uint32_t ivlen = 16;
		uint8_t key[32] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x11,0x22,0x33,0x44,0x55,0x66,0x77, };
		uint8_t iv[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};

		// 00410000 00{$cmd}
		datalen = 3 + 4 + 16 + 16;
		memmove(send_buf, "\x00\x41\x00\x00\x00", 5);
		send_len = datalen + 7;
		send_buf[5] = (datalen >> 8) & 0xff;
		send_buf[6] = datalen & 0xff;
		send_buf[7] = algo;
		send_buf[8] = mode;
		send_buf[9] = type;
		send_buf[10] = (keylen >> 8) & 0xff;
		send_buf[11] = keylen & 0xff;
		memmove(&send_buf[12], key, keylen);
		send_buf[12 + keylen] = (ivlen >> 8) & 0xff;
		send_buf[13 + keylen] = ivlen & 0xff;
		memmove(&send_buf[13 + keylen], iv, ivlen);

		recv_len = 2048;
		rv = SCardTransmit(m_hCard, SCARD_PCI_T1, send_buf, send_len, NULL, recv_buf, &recv_len);
		if (SCARD_S_SUCCESS != rv)
		{
			printf("Failed SCardTransmit[ErrorCode = 0x%08x]\n",rv);
			printf("%d\n",GetLastError());
			exit(1);   // or other appropriate error action
		}

		datalen = 1024;
		memmove(send_buf, "\x00\x41\x00\x01\x00", 5);
		send_len = datalen + 7 + 3;
		send_buf[5] = (datalen >> 8) & 0xff;
		send_buf[6] = datalen & 0xff;
		for (uint32_t i = 0; i < 1024; i++)
		{
			send_buf[7 + i] = i & 0xff;
		}
		send_buf[7 + 1024] = 0x00;
		send_buf[7 + 1024 + 1] = 0x04;
		send_buf[7 + 1024 + 2] = 0x00;

		recv_len = 2048;
		rv = SCardTransmit(m_hCard, SCARD_PCI_T1, send_buf, send_len, NULL, recv_buf, &recv_len);
		if (SCARD_S_SUCCESS != rv)
		{
			printf("Failed SCardTransmit[ErrorCode = 0x%08x]\n", rv);
			printf("%d\n", GetLastError());
			exit(1);   // or other appropriate error action
		}

		memmove(send_buf, "\x00\x41\x00\x02\x00", 5);
		send_len = 5;

		recv_len = 2048;
		rv = SCardTransmit(m_hCard, SCARD_PCI_T1, send_buf, send_len, NULL, recv_buf, &recv_len);
		if (SCARD_S_SUCCESS != rv)
		{
			printf("Failed SCardTransmit[ErrorCode = 0x%08x]\n", rv);
			printf("%d\n", GetLastError());
			exit(1);   // or other appropriate error action
		}
	}

	rv = SCardDisconnect(m_hCard, SCARD_UNPOWER_CARD);
	if (rv != SCARD_S_SUCCESS)
	{
		printf("SCardDisconnect error\n");
		return;
	}
}

