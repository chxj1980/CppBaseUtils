#ifndef RAW_SOCK_H
#define RAW_SOCK_H

#include <cstring>
#include <cmath>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

// ===============================================================
//Macͷ�����ܳ���14�ֽ�
typedef struct _eth_hdr
{
	unsigned char dstmac[6]; //Ŀ��mac��ַ
	unsigned char srcmac[6]; //Դmac��ַ
	unsigned short eth_type; //��̫������
}eth_hdr;

//IPͷ�����ܳ���20�ֽ�
typedef struct _ip_hdr
{
	unsigned char version;   //�汾
	unsigned char tos;       //��������
	unsigned short tot_len;  //�ܳ���
	unsigned short id;       //��־
	unsigned short frag_off; //��Ƭƫ��
	unsigned char ttl;       //����ʱ��
	unsigned char protocol;  //Э��
	unsigned short chk_sum;  //�����
	struct in_addr srcaddr;  //ԴIP��ַ
	struct in_addr dstaddr;  //Ŀ��IP��ַ
}ip_hdr;

//TCPͷ�����ܳ���20�ֽ�
typedef struct _tcp_hdr
{
	unsigned short src_port;    //Դ�˿ں�
	unsigned short dst_port;    //Ŀ�Ķ˿ں�
	unsigned int seq_no;        //���к�
	unsigned int ack_no;        //ȷ�Ϻ�
#if 1
	unsigned char reserved_1:4; //����6λ�е�4λ�ײ�����
	unsigned char thl:4;        //tcpͷ������
	unsigned char flag:6;       //6λ��־
	unsigned char reseverd_2:2; //����6λ�е�2λ
#else
	unsigned char thl:4;        //tcpͷ������
	unsigned char reserved_1:4; //����6λ�е�4λ�ײ�����
	unsigned char reseverd_2:2; //����6λ�е�2λ
	unsigned char flag:6;       //6λ��־ 
#endif
	unsigned short wnd_size;    //16λ���ڴ�С
	unsigned short chk_sum;     //16λTCP�����
	unsigned short urgt_p;      //16Ϊ����ָ��
}tcp_hdr;

//UDPͷ�����ܳ���8�ֽ�
typedef struct _udp_hdr
{
	unsigned short src_port; //Զ�˿ں�
	unsigned short dst_port; //Ŀ�Ķ˿ں�
	unsigned short uhl;      //udpͷ������
	unsigned short chk_sum;  //16λudp�����
}udp_hdr;

//ICMPͷ�����ܳ���4�ֽ�
typedef struct _icmp_hdr
{
	unsigned char icmp_type;   //����
	unsigned char code;        //����
	unsigned short chk_sum;    //16λ�����
}icmp_hdr; 

// ===============================================================
#define PROT_ICMP		1		// Internet Control Message                 [RFC792] 
#define PROT_TCP		6		// Transmission Control                     [RFC793]
#define PROT_UDP		17		// User Datagram                            [RFC768][JBP]

// ===============================================================
#define MAX_PACKET_SIZE		0x40000
#define MAX_ADAPTER_NUMBER	128

// ===============================================================

#define SIO_RCVALL    (IOC_IN|IOC_VENDOR|1)
class CMainFrame;

class CRawSocket
{
public:
	static int EnumAdapters();
	static void DebugAdapters();
	static TCHAR adapter_ip[MAX_ADAPTER_NUMBER][32];
	static TCHAR *adapter_des[MAX_ADAPTER_NUMBER];
	static int adapter_number;

public:
	CRawSocket(int adapter_id, CMainFrame *pMainFrame)
	{
		m_adapter_id = adapter_id;
		m_mainframe = pMainFrame;
		m_enabled = FALSE;

		ZeroMemory(buffer, MAX_PACKET_SIZE);
		s = INVALID_SOCKET;
		flag = 0;
		Init();
	};
	~CRawSocket()
	{
		::closesocket(s);
		s = INVALID_SOCKET;
	};
	void Start(void);
	void Stop(void);
	void* GetSniffData(int *len);

public:
	int			m_adapter_id;
	CMainFrame		*m_mainframe;
	BOOL			m_enabled;

private:
	int Init(void);

	SOCKET			s;
	SOCKADDR_IN		sa;
	int			flag;
	BYTE			buffer[MAX_PACKET_SIZE];
};
#endif
