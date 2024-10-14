// SoundCard.cpp : implementation file
//

#include "stdafx.h"
#include "install.h"
#include "SoundCard.h"
#include "installdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundCard dialog


CSoundCard::CSoundCard(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoundCard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSoundCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundCard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSoundCard, CDialog)
	//{{AFX_MSG_MAP(CSoundCard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundCard message handlers

void CSoundCard::OnCancel() 
{
	WritePrivateProfileString("Audio","MIDIMusic","0","wildride.ini");
	WritePrivateProfileString("Audio","CDMusic","0","wildride.ini");
	WritePrivateProfileString("Audio","SoundFx","0","wildride.ini");
	WritePrivateProfileString("Audio","SoundFxAllowed","0","wildride.ini");
	WritePrivateProfileString("Audio","Naration","0","wildride.ini");
	WritePrivateProfileString("Audio","SurferSounds","0","wildride.ini");
	CDialog::OnCancel();
}

void CSoundCard::OnOK() 
{
#ifdef SHAREWARE
	WritePrivateProfileString("Audio","MIDIMusic","1","wildride.ini");
	WritePrivateProfileString("Audio","CDMusic","0","wildride.ini");
#else
	WritePrivateProfileString("Audio","MIDIMusic","0","wildride.ini");
	WritePrivateProfileString("Audio","CDMusic","1","wildride.ini");
#endif
	WritePrivateProfileString("Audio","SoundFx","1","wildride.ini");
	WritePrivateProfileString("Audio","SoundFxAllowed","1","wildride.ini");
	WritePrivateProfileString("Audio","Naration","1","wildride.ini");
	WritePrivateProfileString("Audio","SurferSounds","1","wildride.ini");
	CDialog::OnOK();
}
