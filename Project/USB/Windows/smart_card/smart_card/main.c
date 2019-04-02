
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

	rv = SCardListReaders(m_hContext, NULL, (LPWSTR)&mszReaders, &dwReaders);
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

	rv = SCardConnect(m_hContext,(LPWSTR)mszReaders, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0, &m_hCard, &m_dwActiveProtocol);
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
	

	{
		uint8_t send_buf[2048] = {
			0x00,0x03,0x00,0x00};
		uint8_t recv_buf[2048];

		/*
			Windows 平台测试结果：
			short_APDU_MAX= 255		// 这个理解
			extend_APDU_Max = 294	// 这个不是最大值，最大值看规范
			??? 
			关键是后者这个数据没什么特殊性？和win平台有关吗？还是我的底层固件的问题？
			? 确实是固件问题，主要是配置正确CCID设备类就可以了
		*/
		DWORD data_len = 1024;	
		DWORD send_len;
		DWORD recv_len = sizeof(recv_buf);


		if (data_len >= 256)
		{
			send_len = data_len + 7;
			send_buf[4] = 0x00;
			send_buf[5] = (data_len >> 8)& 0xff;
			send_buf[6] = data_len & 0xff;
			memset(send_buf + 7, 0x55, data_len);
		}
		else
		{
			send_len = data_len + 5;
			send_buf[4] = data_len & 0xff;
			memset(send_buf + 5, 0x55, data_len);
		}


		printf("-> ");
		display(send_buf, send_len);
		rv = SCardTransmit(m_hCard, SCARD_PCI_T0, send_buf, send_len, NULL, recv_buf, &recv_len);
		if (SCARD_S_SUCCESS != rv)
		{
			printf("Failed SCardTransmit[ErrorCode = 0x%08x]\n",rv);
			printf("%d\n",GetLastError());
			exit(1);   // or other appropriate error action
		}
		// printf("recv_len = %d\n", recv_len);
		printf("<- ");
		display(recv_buf, recv_len);
	}

	rv = SCardDisconnect(m_hCard, SCARD_UNPOWER_CARD);
	if (rv != SCARD_S_SUCCESS)
	{
		printf("SCardDisconnect error\n");
		return;
	}
}

