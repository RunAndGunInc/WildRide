// MaxFps.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "MaxFps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaxFps dialog


CMaxFps::CMaxFps(CWnd* pParent /*=NULL*/)
	: CDialog(CMaxFps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaxFps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bFirst = TRUE;
}


void CMaxFps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaxFps)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaxFps, CDialog)
	//{{AFX_MSG_MAP(CMaxFps)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaxFps message handlers

void CMaxFps::OnOK() 
{
	// TODO: Add extra validation here
	if (IsDlgButtonChecked(IDC_RADIOFPS22))
	{
		WritePrivateProfileString("Details","MaxFps","22","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS20))
	{
		WritePrivateProfileString("Details","MaxFps","20","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS18))
	{
		WritePrivateProfileString("Details","MaxFps","18","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS16))
	{
		WritePrivateProfileString("Details","MaxFps","16","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS14))
	{
		WritePrivateProfileString("Details","MaxFps","14","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS12))
	{
		WritePrivateProfileString("Details","MaxFps","12","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS10))
	{
		WritePrivateProfileString("Details","MaxFps","10","wildride.ini");
	}
	else if (IsDlgButtonChecked(IDC_RADIOFPS8))
	{
		WritePrivateProfileString("Details","MaxFps","8","wildride.ini");
	}
	CDialog::OnOK();
}

void CMaxFps::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (bFirst)
	{
		bFirst = FALSE;
		int MaxFps = GetPrivateProfileInt("Details","MaxFps",16,"wildride.ini");
		if (MaxFps > 20)
			CheckDlgButton(IDC_RADIOFPS22, BST_CHECKED);
		else if (MaxFps > 18)
			CheckDlgButton(IDC_RADIOFPS20, BST_CHECKED);
		else if (MaxFps > 16)
			CheckDlgButton(IDC_RADIOFPS18, BST_CHECKED);
		else if (MaxFps > 14)
			CheckDlgButton(IDC_RADIOFPS16, BST_CHECKED);
		else if (MaxFps > 12)
			CheckDlgButton(IDC_RADIOFPS14, BST_CHECKED);
		else if (MaxFps > 10)
			CheckDlgButton(IDC_RADIOFPS12, BST_CHECKED);
		else if (MaxFps > 8)
			CheckDlgButton(IDC_RADIOFPS10, BST_CHECKED);
		else
			CheckDlgButton(IDC_RADIOFPS8, BST_CHECKED);
	}
}
