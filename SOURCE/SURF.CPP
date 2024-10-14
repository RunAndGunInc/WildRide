// surf.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <d3drmwin.h>

#include "surf.h"

#include "MainFrm.h"
#include "surfDoc.h"

#include "surfView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CsurfApp

BEGIN_MESSAGE_MAP(CsurfApp, CWinApp)
	//{{AFX_MSG_MAP(CsurfApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDCLOSE, OnClose)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CsurfApp construction

CsurfApp::CsurfApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CsurfApp object

CsurfApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CsurfApp initialization

BOOL CsurfApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
//	{
//		CCommandLineInfo cmdInfo;
//		ParseCommandLine(cmdInfo);
//
//		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
//	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

//	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CsurfDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CsurfView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo); //did it up there 

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// set max frame rate to 15 fps
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CsurfApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CsurfApp commands

BOOL CsurfApp::OnIdle(LONG lCount) 
{
	CWinApp::OnIdle(lCount);

//	SYSTEMTIME systemtime;
//	float currenttime;

	if (m_pView) 
	{
		CsurfView * view = (CsurfView *)m_pView;
		view->UpdateWorld();
	}
	return TRUE;
}

//BOOL CsurfApp::PreTranslateMessage(MSG* pMsg)
//{
	// CG: The following line was added by the Splash Screen component.
//	CSplashWnd::PreTranslateAppMessage(pMsg);

//	return CWinApp::PreTranslateMessage(pMsg);
//}

void CsurfApp::OnClose() 
{
	PostQuitMessage(0);
}
