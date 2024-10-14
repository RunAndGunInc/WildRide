// surf.h : main header file for the surf application
//

#ifndef __SURFAPP__
#define __SURFAPP__

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "surfview.h"

/////////////////////////////////////////////////////////////////////////////
// CsurfApp:
// See surf.cpp for the implementation of this class
//

class CsurfApp : public CWinApp
{
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	CsurfView *m_pView;
	CView *m_pView;
	CsurfApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CsurfApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CsurfApp)
	afx_msg void OnAppAbout();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
#endif