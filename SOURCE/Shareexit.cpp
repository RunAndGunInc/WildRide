// ShareExit.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "ShareExit.h"
//#include <MMSYSTEM.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define TOPMOSTWINDOW // for the top heehaw shit

/////////////////////////////////////////////////////////////////////////////
// CShareExit dialog


CShareExit::CShareExit(CWnd* pParent /*=NULL*/)
	: CDialog(CShareExit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShareExit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShareExit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShareExit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShareExit, CDialog)
	//{{AFX_MSG_MAP(CShareExit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareExit message handlers


int CShareExit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
