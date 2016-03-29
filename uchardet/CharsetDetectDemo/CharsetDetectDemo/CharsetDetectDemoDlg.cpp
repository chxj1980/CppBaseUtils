
// CharsetDetectDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CharsetDetectDemo.h"
#include "CharsetDetectDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCharsetDetectDemoDlg �Ի���



CCharsetDetectDemoDlg::CCharsetDetectDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHARSETDETECTDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCharsetDetectDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCharsetDetectDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DETECT_CHARSET, &CCharsetDetectDemoDlg::OnBnClickedButtonDetectCharset)
END_MESSAGE_MAP()


// CCharsetDetectDemoDlg ��Ϣ�������

BOOL CCharsetDetectDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCharsetDetectDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCharsetDetectDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCharsetDetectDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "xtrace.h"
void CCharsetDetectDemoDlg::OnBnClickedButtonDetectCharset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFile = _T("");
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("*.*||"), NULL);
	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		if (!strFile.IsEmpty()) {
			XTRACE(L"filename: %s\n", strFile);

			CFile cfile;
			if (!cfile.Open(strFile, CFile::modeRead | CFile::typeBinary, NULL))
				return;

			int size = (int)cfile.GetLength();
			if (size > 0) {
				char *buf = (char *)malloc(size);
				if (size != cfile.Read(buf, size))
				{
					AfxMessageBox(L"��ȡ�ļ�����", MB_ICONERROR);
				}
				else
				{
					int codepage = detectCodepage(buf, size);
					CString codepage2 = detectCodepage2(buf, size);
					XTRACE(L"code page: %s, %d\n", (LPCWSTR)codepage2, codepage);
				}
				free(buf);
			}
			cfile.Close();
		}
	}
}

#include "../../uchardet/uchardet.h"
#include "../../EncodingMapper.h"
int CCharsetDetectDemoDlg::detectCodepage(char* buf, size_t len)
{
	uchardet_t ud = uchardet_new();
	uchardet_handle_data(ud, buf, len);
	uchardet_data_end(ud);
	const char* cs = uchardet_get_charset(ud);
	int codepage = EncodingMapper::getInstance()->getEncodingFromString(cs);
	uchardet_delete(ud);
	return codepage;
}

CString CCharsetDetectDemoDlg::detectCodepage2(char* buf, size_t len)
{
	USES_CONVERSION;
	uchardet_t ud = uchardet_new();
	uchardet_handle_data(ud, buf, len);
	uchardet_data_end(ud);
	const char* cs = uchardet_get_charset(ud);
	CString result = A2W(cs);
	uchardet_delete(ud);
	return result;
}
