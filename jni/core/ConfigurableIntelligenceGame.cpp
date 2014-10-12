
// ConfigurableIntelligenceGame.cpp : ����Ӧ�ó��������Ϊ��
//


//#include "vld.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ConfigurableIntelligenceGame.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConfigurableIntelligenceGameApp

BEGIN_MESSAGE_MAP(CConfigurableIntelligenceGameApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CConfigurableIntelligenceGameApp::OnAppAbout)
END_MESSAGE_MAP()


// CConfigurableIntelligenceGameApp ����

CConfigurableIntelligenceGameApp::CConfigurableIntelligenceGameApp()
{
	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ConfigurableIntelligenceGame.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CConfigurableIntelligenceGameApp ����

CConfigurableIntelligenceGameApp theApp;


// CConfigurableIntelligenceGameApp ��ʼ��

BOOL CConfigurableIntelligenceGameApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;

	if (!pFrame)
	{
		return FALSE;
	}

	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME,
					  WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
					  NULL);





	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CConfigurableIntelligenceGameApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	return CWinApp::ExitInstance();
}

// CConfigurableIntelligenceGameApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
	public:
		CAboutDlg();

		// �Ի�������
		enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

		// ʵ��
	protected:
		DECLARE_MESSAGE_MAP()
	public:
	protected:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CConfigurableIntelligenceGameApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CConfigurableIntelligenceGameApp ��Ϣ�������
