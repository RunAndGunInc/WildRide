// NetNames.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "NetNames.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetNames dialog


CNetNames::CNetNames(CWnd* pParent /*=NULL*/)
	: CDialog(CNetNames::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetNames)
	m_PlayerName = _T("");
	m_SessionName = _T("");
	//}}AFX_DATA_INIT
}


void CNetNames::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetNames)
	DDX_Text(pDX, IDC_PLAYER_NAME, m_PlayerName);
	DDV_MaxChars(pDX, m_PlayerName, 31);
	DDX_Text(pDX, IDC_SESSION_NAME, m_SessionName);
	DDV_MaxChars(pDX, m_SessionName, 31);
	//}}AFX_DATA_MAP
	PlayerName = (LPCTSTR) m_PlayerName;
	SessionName = (LPCTSTR) m_SessionName;
}


BEGIN_MESSAGE_MAP(CNetNames, CDialog)
	//{{AFX_MSG_MAP(CNetNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetNames message handlers

void CNetNames::OnOK() 
{
	// TODO: Add extra validation here

	SessionNumber = 0;
	CDialog::OnOK();
}

void CNetNames::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	SessionNumber = NET_NAMES_CANCEL;

	CDialog::OnCancel();
}
