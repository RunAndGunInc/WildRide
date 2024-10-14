// LoadProgress.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "LoadProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LOAD_MESSAGE WM_USER+1
//#define TOPMOSTWINDOW // for the window to be the top one!
/////////////////////////////////////////////////////////////////////////////
// CLoadProgress dialog


CLoadProgress::CLoadProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	graph_hwnd = NULL;
}


void CLoadProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadProgress)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadProgress, CDialog)
	//{{AFX_MSG_MAP(CLoadProgress)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadProgress message handlers

void CLoadProgress::OnPaint() 
{
	static BOOL bFirst = TRUE;
	CPaintDC dc(this); // device context for painting

	if (bFirst)
	{
		bFirst = FALSE;
		graph_hwnd = ::GetDlgItem(m_hWnd, IDC_GRAPH);

		::SendMessage(graph_hwnd, PBM_SETRANGE, 0, MAKELONG(0, 1000));
		::SendMessage(graph_hwnd, PBM_SETPOS, 0, 0);
	}
}

int CLoadProgress::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	CenterWindow((CWnd*)CWnd::GetDesktopWindow);
#ifdef TOPMOSTWINDOW
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE);
#endif
	
	return 0;
}

LRESULT CLoadProgress::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (message == LOAD_MESSAGE)
	{
	    SetDlgItemText(IDC_TEXT, Text);
		::SendMessage(graph_hwnd, PBM_DELTAPOS, 28, 0);
		return TRUE;
	}
	else
		return CDialog::WindowProc(message, wParam, lParam);
}

void CLoadProgress::OnCancel()
{
	CDialog::OnCancel();
}