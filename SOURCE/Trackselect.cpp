// TrackSelect.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "TrackSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackSelect dialog


CTrackSelect::CTrackSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CTrackSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bOk = FALSE;
	bFirst = TRUE;
}


void CTrackSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackSelect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrackSelect, CDialog)
	//{{AFX_MSG_MAP(CTrackSelect)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_CHECK21, OnCheck21)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackSelect message handlers

void CTrackSelect::OnOK() 
{
	// TODO: Add extra validation here
	bOk = TRUE;	
	CDialog::OnOK();
}

void CTrackSelect::ClearButtons()
{
	int array [21] = 
	{
		IDC_CHECK1, 
		IDC_CHECK2, 
		IDC_CHECK3, 
		IDC_CHECK4,
		IDC_CHECK5, 
		IDC_CHECK6, 
		IDC_CHECK7,
		IDC_CHECK8, 
		IDC_CHECK9, 
		IDC_CHECK10,
		IDC_CHECK11, 
		IDC_CHECK12, 
		IDC_CHECK13, 
		IDC_CHECK14,
		IDC_CHECK15, 
		IDC_CHECK16, 
		IDC_CHECK17,
		IDC_CHECK18, 
		IDC_CHECK19, 
		IDC_CHECK20,
		IDC_CHECK21
	};
	for (int i = 0; i < 21; i++)
		CheckDlgButton(array[i], BST_UNCHECKED);
	CheckDlgButton(array[current_track - 2], BST_CHECKED);
}

void CTrackSelect::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (bFirst)
	{
		ClearButtons();
		bFirst = FALSE;
	}
}

void CTrackSelect::OnCheck1() 
{
	current_track = 2;
	ClearButtons();
}

void CTrackSelect::OnCheck2() 
{
	current_track = 3;
	ClearButtons();
}

void CTrackSelect::OnCheck3() 
{
	current_track = 4;
	ClearButtons();
}

void CTrackSelect::OnCheck4() 
{
	current_track = 5;
	ClearButtons();
}

void CTrackSelect::OnCheck5() 
{
	current_track = 6;
	ClearButtons();
}

void CTrackSelect::OnCheck6() 
{
	current_track = 7;
	ClearButtons();
}

void CTrackSelect::OnCheck7() 
{
	current_track = 8;
	ClearButtons();
}

void CTrackSelect::OnCheck8() 
{
	current_track = 9;
	ClearButtons();
}

void CTrackSelect::OnCheck9() 
{
	current_track = 10;
	ClearButtons();
}

void CTrackSelect::OnCheck10() 
{
	current_track = 11;
	ClearButtons();
}

void CTrackSelect::OnCheck11() 
{
	current_track = 12;
	ClearButtons();
}

void CTrackSelect::OnCheck12() 
{
	current_track = 13;
	ClearButtons();
}

void CTrackSelect::OnCheck13() 
{
	current_track = 14;
	ClearButtons();
}

void CTrackSelect::OnCheck14() 
{
	current_track = 15;
	ClearButtons();
}

void CTrackSelect::OnCheck15() 
{
	current_track = 16;
	ClearButtons();
}

void CTrackSelect::OnCheck16() 
{
	current_track = 17;
	ClearButtons();
}

void CTrackSelect::OnCheck17() 
{
	current_track = 18;
	ClearButtons();
}

void CTrackSelect::OnCheck18() 
{
	current_track = 19;
	ClearButtons();
}

void CTrackSelect::OnCheck19() 
{
	current_track = 20;
	ClearButtons();
}

void CTrackSelect::OnCheck20() 
{
	current_track = 21;
	ClearButtons();
}

void CTrackSelect::OnCheck21() 
{
	current_track = 22;
	ClearButtons();
}
