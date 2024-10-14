// MaxFps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaxFps dialog

class CMaxFps : public CDialog
{
// Construction
public:
	CMaxFps(CWnd* pParent = NULL);   // standard constructor
	BOOL bFirst;

// Dialog Data
	//{{AFX_DATA(CMaxFps)
	enum { IDD = IDD_MAXFPS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaxFps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaxFps)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
