
// CharsetDetectDemoDlg.h : ͷ�ļ�
//

#pragma once


// CCharsetDetectDemoDlg �Ի���
class CCharsetDetectDemoDlg : public CDialogEx
{
// ����
public:
	CCharsetDetectDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARSETDETECTDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDetectCharset();
	int detectCodepage(char* buf, size_t len);
	CString detectCodepage2(char* buf, size_t len);
};
