// NetCreate.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
//#include "surfView.h"
#include "NetCreate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetCreate dialog


CNetCreate::CNetCreate(CWnd* pParent /*=NULL*/)
	: CDialog(CNetCreate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetCreate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNetCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetCreate)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetCreate, CDialog)
	//{{AFX_MSG_MAP(CNetCreate)
	ON_BN_CLICKED(ID_JOIN_SESSION, OnJoinSession)
	ON_BN_CLICKED(ID_START_SESSION, OnStartSession)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetCreate message handlers

void CNetCreate::OnJoinSession() 
{
	selection = NET_JOIN;
	CDialog::OnCancel();
}

void CNetCreate::OnStartSession() 
{
	selection = NET_START;
	CDialog::OnCancel();
}

void CNetCreate::OnCancel() 
{
	// TODO: Add extra cleanup here

	selection = NET_CANCEL;
	CDialog::OnCancel();
}
