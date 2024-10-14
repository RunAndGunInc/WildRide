// Leroy.cpp : implementation file
//

#include "stdafx.h"
#include "surf.h"
#include "Leroy.h"
#include "TrackSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeroy dialog


CLeroy::CLeroy(CWnd* pParent /*=NULL*/)
	: CDialog(CLeroy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLeroy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bScore = FALSE;
	bLives = FALSE;
	bTrackChange = FALSE;
	bTime = FALSE;
}


void CLeroy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeroy)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeroy, CDialog)
	//{{AFX_MSG_MAP(CLeroy)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LIFE, OnLife)
	ON_BN_CLICKED(IDC_NAVMODE, OnNavmode)
	ON_BN_CLICKED(IDC_SCORE, OnScore)
	ON_BN_CLICKED(IDC_CHEATKEYS, OnCheatKeys)
	ON_BN_CLICKED(IDC_TIME, OnTime)
	ON_BN_CLICKED(IDC_TRON, OnTron)
	ON_BN_CLICKED(IDC_UFO, OnUfo)
	ON_BN_CLICKED(IDC_LEROY_FACE, OnLeroyFace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeroy message handlers

void CLeroy::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	static BOOL bFirst = TRUE;
	if (bFirst)
	{
		if (bTron)
			CheckDlgButton(IDC_TRON, BST_CHECKED);
		if (bUfo)
			CheckDlgButton(IDC_UFO, BST_CHECKED);
		if (bCheatKeys)
			CheckDlgButton(IDC_CHEATKEYS, BST_CHECKED);
		if (bNavigation)
			CheckDlgButton(IDC_NAVMODE, BST_CHECKED);
		bOk = FALSE;
	}
}

void CLeroy::OnLife() 
{
	bLives = !bLives;
	if (bLives)
		CheckDlgButton(IDC_LIFE, BST_CHECKED);
	else
		CheckDlgButton(IDC_LIFE, BST_UNCHECKED);
}

void CLeroy::OnNavmode() 
{
	bNavigation = !bNavigation;
	if (bNavigation)
		CheckDlgButton(IDC_NAVMODE, BST_CHECKED);
	else
		CheckDlgButton(IDC_NAVMODE, BST_UNCHECKED);
}

void CLeroy::OnScore() 
{
	bScore = !bScore;
	if (bScore)
		CheckDlgButton(IDC_SCORE, BST_CHECKED);
	else
		CheckDlgButton(IDC_SCORE, BST_UNCHECKED);
}

void CLeroy::OnCheatKeys() 
{
	bCheatKeys = !bCheatKeys;
	if (bCheatKeys)
		CheckDlgButton(IDC_CHEATKEYS, BST_CHECKED);
	else
		CheckDlgButton(IDC_CHEATKEYS, BST_UNCHECKED);
}

void CLeroy::OnTime() 
{
	bTime = !bTime;
	if (bTime)
		CheckDlgButton(IDC_TIME, BST_CHECKED);
	else
		CheckDlgButton(IDC_TIME, BST_UNCHECKED);
}

void CLeroy::OnTron() 
{
	bTron = !bTron;
	if (bTron)
		CheckDlgButton(IDC_TRON, BST_CHECKED);
	else
		CheckDlgButton(IDC_TRON, BST_UNCHECKED);
}

void CLeroy::OnUfo() 
{
	bUfo = !bUfo;
	if (bUfo)
		CheckDlgButton(IDC_UFO, BST_CHECKED);
	else
		CheckDlgButton(IDC_UFO, BST_UNCHECKED);
}

void CLeroy::OnOK() 
{
	bOk = TRUE;
	CDialog::OnOK();
}

void CLeroy::OnLeroyFace() 
{
	CTrackSelect TrackSelect;
	TrackSelect.current_track = current_track;
	TrackSelect.DoModal();
	if (TrackSelect.bOk)
	{
		bTrackChange = TRUE;
		current_track = TrackSelect.current_track;
	}
	delete TrackSelect;
}
