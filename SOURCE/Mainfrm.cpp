// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <d3drmwin.h>

#include "surf.h"
#include "surfDoc.h"
#include "surfView.h"
#include "MainFrm.h"
//#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_MOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
CMainFrame::CMainFrame()
 
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CG: The following line was added by the Splash Screen component.
//	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
#ifdef SHAREWARE
	static char Name[] = "Wild Ride! 1.22 Shareware";
#else
	static char Name[] = "Wild Ride! 1.22";
#endif
	cs.lpszName = Name;
	cs.x = GetPrivateProfileInt("ScreenMode","WindowXPos",114,"wildride.ini");
	if (cs.x > 600) 
		cs.x = 600;
	cs.y = GetPrivateProfileInt("ScreenMode","WindowYPos",56,"wildride.ini");
	if (cs.y > 400) 
		cs.y = 400;
	cs.cx = GetPrivateProfileInt("ScreenMode","WindowWidth",414,"wildride.ini");
	if (cs.cx < 50) 
		cs.cx = 50;
	cs.cy = GetPrivateProfileInt("ScreenMode","WindowHeight",310,"wildride.ini");
	if (cs.cy < 50) 
		cs.cy = 50;

	cs.style = WS_VISIBLE | WS_SYSMENU | WS_CAPTION |
		WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
//	cs.style = WS_POPUP;
//	cs.dwExStyle = WS_MINIMIZE;
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnMove(int x, int y) 
{
	CFrameWnd::OnMove(x, y);
	CsurfApp* pApp = (CsurfApp*)AfxGetApp();
	CsurfView * view = (CsurfView *)pApp->m_pView;
	if (view)	
	{
		view->OnMove();
	}
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	CsurfApp* pApp = (CsurfApp*)AfxGetApp();
	CsurfView * view = (CsurfView *)pApp->m_pView;
	if (view)	
	{
		view->OnSize(nType, cx, cy);
	}
}
