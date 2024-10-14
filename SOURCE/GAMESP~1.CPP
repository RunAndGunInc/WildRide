// Gamespeed.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "Gamespeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGamespeed dialog


CGamespeed::CGamespeed(CWnd* pParent /*=NULL*/)
	: CDialog(CGamespeed::IDD, pParent)
{
	bFirst = TRUE;
	//{{AFX_DATA_INIT(CGamespeed)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGamespeed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGamespeed)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGamespeed, CDialog)
	//{{AFX_MSG_MAP(CGamespeed)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGamespeed message handlers

void CGamespeed::OnOK() 
{
	// TODO: Add extra validation here
	GameSpeed = ::SendMessage(hWndCtl, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
	CDialog::OnOK();
}

void CGamespeed::OnPaint() 
{
	char ach[40];
	if (bFirst)
	{
		hWndCtl = ::GetDlgItem(m_hWnd, IDC_SPEEDSLIDER);
		::SendMessage(hWndCtl, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(-999,999));
		::SendMessage(hWndCtl, TBM_SETPOS, (WPARAM)1, (LPARAM)GameSpeed);
		for (int i = -900; i < 999; i += 100)
		{
			::SendMessage(hWndCtl, TBM_SETTIC, (WPARAM)0, (LPARAM)i);
		}
		wsprintf(ach, "%d", GameSpeed);
		SetDlgItemText(IDC_NUMBER, ach);
		bFirst = FALSE;
	}
	else
	{
		GameSpeed = ::SendMessage(hWndCtl, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
		wsprintf(ach, "%d", GameSpeed);
		SetDlgItemText(IDC_NUMBER, ach);
	}
//	CPaintDC dc(this); // device context for painting
}

