// Reboot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReboot dialog

class CReboot : public CDialog
{
// Construction
public:
	BOOL bOk;
	CReboot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReboot)
	enum { IDD = IDD_REBOOT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReboot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReboot)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
