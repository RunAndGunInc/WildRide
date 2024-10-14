// Filename.cpp : implementation file
//

#include "stdafx.h"
#include "install.h"
#include "Filename.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilename dialog


CFilename::CFilename(CWnd* pParent /*=NULL*/)
	: CDialog(CFilename::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilename)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFilename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilename)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CFilename::ChangeText(char* text)
{
	::SetDlgItemText(m_hWnd, IDC_FILENAME_TEXT, text);
}


BEGIN_MESSAGE_MAP(CFilename, CDialog)
	//{{AFX_MSG_MAP(CFilename)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilename message handlers
