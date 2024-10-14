// ShareExit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShareExit dialog

class CShareExit : public CDialog
{
// Construction
public:
	CShareExit(CWnd* pParent = NULL);   // standard constructor
//	DWORD starttime;
// Dialog Data
	//{{AFX_DATA(CShareExit)
	enum { IDD = IDD_SHAREEXIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareExit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShareExit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
