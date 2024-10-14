// NetNames.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetNames dialog

#define NET_NAMES_CANCEL 64

class CNetNames : public CDialog
{
// Construction
public:
	int						SessionNumber;
	const char*				PlayerName;	
	const char*				SessionName;	
	CNetNames(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetNames)
	enum { IDD = IDD_NET_NAMES };
	CString	m_PlayerName;
	CString	m_SessionName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetNames)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetNames)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
