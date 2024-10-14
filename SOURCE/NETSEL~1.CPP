// NetSelSession.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "NetSelSession.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetSelSession dialog


CNetSelSession::CNetSelSession(CWnd* pParent /*=NULL*/)
	: CDialog(CNetSelSession::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetSelSession)
	m_PlayerName = _T("");
	//}}AFX_DATA_INIT
}


void CNetSelSession::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetSelSession)
	DDX_Text(pDX, IDC_PLAYER_NAME, m_PlayerName);
	DDV_MaxChars(pDX, m_PlayerName, 31);
	//}}AFX_DATA_MAP
	PlayerName = (LPCTSTR) m_PlayerName;
}
void CNetSelSession::DrawStuff()
{
	LONG iIndex;
	static char ach[255];

	HWND hWndCtl = ::GetDlgItem(m_hWnd, IDC_LB_SESSION);
	for (int i = 0; i < NumSessions; i++)
	{
		wsprintf(ach, "%s: %d players",SessionName[i],SessionPlayers[i]);
		iIndex = ::SendMessage(hWndCtl, LB_ADDSTRING, 0, (LPARAM) ach);
	}
	::SetFocus(hWndCtl);
    ::SendMessage(hWndCtl, LB_SETCURSEL, (WPARAM)SessionNumber, 0);
}



BEGIN_MESSAGE_MAP(CNetSelSession, CDialog)
	//{{AFX_MSG_MAP(CNetSelSession)
	ON_WM_PAINT()
	ON_LBN_DBLCLK(IDC_LB_SESSION, OnDblclkLbSession)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetSelSession message handlers

void CNetSelSession::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (bFirst)
	{
		DrawStuff();
		bFirst = FALSE;
	}
//	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}

void CNetSelSession::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	SessionNumber = NET_SEL_SESSION_CANCEL;
	CDialog::OnCancel();
}

void CNetSelSession::OnOK() 
{
	// TODO: Add extra validation here
	HWND hWndCtl = ::GetDlgItem(m_hWnd, IDC_LB_SESSION);
    SessionNumber = ::SendMessage(hWndCtl, LB_GETCURSEL, 0, 0);
	if ((SessionNumber < 0) || (SessionNumber >= NumSessions))
		SessionNumber = 0;

	CDialog::OnOK();
}

void CNetSelSession::OnDblclkLbSession() 
{
	// TODO: Add your control notification handler code here
	OnOK();

}


