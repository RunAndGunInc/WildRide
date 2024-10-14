// Leroy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeroy dialog
#include "resource.h"

class CLeroy : public CDialog
{
// Construction
public:
	int current_track;
	BOOL bTrackChange;
	BOOL bTron;
	BOOL bUfo;
	BOOL bScore;
	BOOL bLives;
	BOOL bTime;
	BOOL bNavigation;
	BOOL bCheatKeys;
	BOOL bOk;
	CLeroy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLeroy)
	enum { IDD = IDD_LEROY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeroy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLeroy)
	afx_msg void OnPaint();
	afx_msg void OnLife();
	afx_msg void OnNavmode();
	afx_msg void OnScore();
	afx_msg void OnCheatKeys();
	afx_msg void OnTime();
	afx_msg void OnTron();
	afx_msg void OnUfo();
	virtual void OnOK();
	afx_msg void OnLeroyFace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
