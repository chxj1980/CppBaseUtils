#include "StdAfx.h"
#include "FtpTask.h"
#include "WorkSpace.h"
#include "Utility.h"

FtpTask::FtpTask(void):pConnect(NULL)
{
	Connect2Ftp();
}

FtpTask::~FtpTask(void)
{
	CloseConnection();
}

//////////////////////////////////////////////////////////////////////////
//����FTP����
bool FtpTask::TestFtpConnection(CString server,CString user,CString pwd,INTERNET_PORT port,CString& exceptionInfo)
{
	try
	{
		CFtpConnection* pConnect = NULL;
		CInternetSession sess;			
		pConnect = sess.GetFtpConnection(server,user,pwd,port);	
		bool ok =  pConnect != NULL;
		if(pConnect != NULL)
			delete pConnect;
		return ok;
	}
	catch (CException* e)
	{
		exceptionInfo = Utility::GetErrorInfoFromException(e);
		return false;
	}	
}

bool FtpTask::Connect2Ftp()
{
	try
	{		
		WorkSpace* ws = WorkSpace::GetCurWorkspace();
		if(ws != NULL)
		{
			CString server= ws->GetFTPServer().c_str();
			CString user=ws->GetFTPLogName().c_str();
			CString pwd=ws->GetFTPPassword().c_str();
			INTERNET_PORT port = ws->GetFTPPort();
			pConnect = sess.GetFtpConnection(server,user,pwd,port);	
			//���õ�ǰĿ¼Ϊ��Ŀ¼
			pConnect->SetCurrentDirectory(_T("/"));
		}
		return pConnect != NULL;
	}
	catch (CException* e)
	{
		//�׳��쳣
		throw CString(_T("����FTPʧ�ܣ�"));
	}	
}

CString FtpTask::FindFile(CString name)
{
	if(pConnect == NULL)
		return _T("");
	CFtpFileFind finder(pConnect);
	if(finder.FindFile(name) == TRUE)
		return finder.GetFileURL();
	return _T("");
}

void FtpTask::CloseConnection()
{
	if(pConnect != NULL)
	{
		pConnect->Close();
		delete pConnect;
		pConnect = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//�ϴ��ļ���������
bool FtpTask::UploadFile(CString strLocalFile ,CString strRemoteDirectory)
{
	if(pConnect != NULL)
	{
		pConnect->SetCurrentDirectory(_T("/"));
		CString fn = Utility::GetFileNameFromFullPath(strLocalFile);
		CString ftppath;
		ftppath.Format(_T("%s/%s"),strRemoteDirectory,fn);
		BOOL bworking = pConnect->PutFile(strLocalFile,ftppath);
		return bworking;
	}
	return false;
}

//�ϴ��ļ�
bool FtpTask::UploadFile(CString strLocalFile ,CString strRemoteDirectory,CString fileName)
{
	if(pConnect != NULL)
	{
		pConnect->SetCurrentDirectory(_T("/"));		
		CString ftppath;
		ftppath.Format(_T("%s/%s"),strRemoteDirectory,fileName);
		BOOL bworking = pConnect->PutFile(strLocalFile,ftppath);
		return bworking;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
//���ط������ϵ��ļ�������
//strRemoteFile:�������ļ�����·����strLocalDirectory�������ļ�����·����boverwrite���Ƿ񸲸Ǳ����ļ�
bool FtpTask::DownloadFile(CString strRemoteFile,CString strLocalFile,bool boverwrite)
{
	if(pConnect != NULL)
	{	
		BOOL bWorking = pConnect->SetCurrentDirectory(_T("/"));
		//GetFile���ļ�����Ϊ��ǰĿ¼�µ����·��
		BOOL bfail = !boverwrite;
		bWorking = pConnect->GetFile(strRemoteFile,strLocalFile,bfail);
		return bWorking;
	}	
	return false;
}


//////////////////////////////////////////////////////////////////////////
//�Ƿ�ΪĿ¼
bool FtpTask::IsDirectory(CString name)
{
	if(pConnect != NULL)
	{
		BOOL bWorking = pConnect->SetCurrentDirectory(name);
		return bWorking;
	}
	return NULL;	 
}


//////////////////////////////////////////////////////////////////////////
//�ļ���Ŀ¼�Ƿ����
bool FtpTask::IsExist(CString name)
{
	if(pConnect != NULL)
	{
		CFtpFileFind finder(pConnect);
		BOOL bWorking = finder.FindFile(name);
		return bWorking;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
//��ȡָ��Ŀ¼��������Ŀ¼
void FtpTask::GetAllSubDirectories(CString directoryName,CStringArray& directories)
{
	if(pConnect == NULL)
		return ;
	BOOL bWorking  = pConnect->SetCurrentDirectory(directoryName);
	if(bWorking)
	{
		CFtpFileFind finder(pConnect);
		bWorking = finder.FindFile(_T("*"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory())
			{
				CString str = finder.GetFilePath();
				CString dd = finder.GetFileName();
				CString name;
				name.Format(_T("%s/%s"),str,dd);
				directories.Add(name);
			}
		}
	}	
}

//////////////////////////////////////////////////////////////////////////
//��ȡĿ¼������dwg�ļ�
void FtpTask::GetAlldwgFilesAtDirectory(CString directory,CStringArray& files)
{
	if(pConnect == NULL)
		return;
	CFtpFileFind finder(pConnect);
	BOOL bWorking  = pConnect->SetCurrentDirectory(directory);
	bWorking = finder.FindFile(_T("*"));
	
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDirectory() && !finder.IsDots())
		{
			CString str = finder.GetFilePath();
			CString name = finder.GetFileName();			
			if (name.Right(4).CompareNoCase(CString(_T(".DWG"))) ==0 )
			{				
				files.Add(name);
			}				
		}		
	}
}

//////////////////////////////////////////////////////////////////////////
//ɾ��FTP�µ��ļ�
bool FtpTask::DeleteFile(CString strRemoteFile)
{
	if(pConnect != NULL)
	{
		BOOL bWorking = pConnect->SetCurrentDirectory(_T("/"));
		if(bWorking)
			bWorking = pConnect->Remove(strRemoteFile);
		return bWorking;
	}
	return false;
}
