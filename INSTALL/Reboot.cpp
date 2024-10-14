// Reboot.cpp : implementation file
//

#include "stdafx.h"
#include "install.h"
#include "Reboot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReboot dialog


CReboot::CReboot(CWnd* pParent /*=NULL*/)
	: CDialog(CReboot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReboot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bOk = FALSE;
}


void CReboot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReboot)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReboot, CDialog)
	//{{AFX_MSG_MAP(CReboot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReboot message handlers

void CReboot::OnOK() 
{
	bOk = TRUE;
	CDialog::OnOK();
}
