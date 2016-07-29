#pragma once
#include <afxinet.h>

//����FTP���ӣ�ʵ���ļ��ϴ����ع���
class FtpTask
{
public:
	FtpTask(void);
public:
	~FtpTask(void);

private:
	//���ӵ�Ftp
	bool Connect2Ftp();	
	//�ر�����
	void CloseConnection();
	//����ָ���ļ��ķ�����·��
	CString FindFile(CString name);

public:
	//�ϴ��ļ�
	bool UploadFile(CString strLocalFile ,CString strRemoteDirectory);
	bool UploadFile(CString strLocalFile ,CString strRemoteDirectory,CString fileName);
	//�����ļ�
	bool DownloadFile(CString strRemoteFile,CString strLocalFile,bool boverwrite);	

	//�Ƿ�Ŀ¼
	bool IsDirectory(CString name);
	//�ļ���Ŀ¼�Ƿ����
	bool IsExist(CString name);	
	//��ȡָ��Ŀ¼��������Ŀ¼
	void GetAllSubDirectories(CString directoryName,CStringArray& directories);
	//��ȡָ��Ŀ¼������dwg�ļ�
	void GetAlldwgFilesAtDirectory(CString directory,CStringArray& files);	
	//ɾ��ָ���ļ�
	bool DeleteFile(CString strRemoteFile);

public:
	//����FTP����
	static bool TestFtpConnection(CString server,CString user,CString pwd,INTERNET_PORT port,CString& exceptionInfo);

private:
	CInternetSession sess;
	CFtpConnection* pConnect;
};
