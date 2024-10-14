// Gamespeed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGamespeed dialog

class CGamespeed : public CDialog
{
// Construction
public:
	HWND hWndCtl;
	BOOL bFirst;
	int GameSpeed;
	CGamespeed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGamespeed)
	enum { IDD = IDD_GAMESPEED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGamespeed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGamespeed)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
