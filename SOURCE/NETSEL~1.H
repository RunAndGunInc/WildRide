// NetSelSession.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetSelSession dialog

#define MAX_NETWORK_SESSIONS 32
#define NET_SEL_SESSION_CANCEL 64

class CNetSelSession : public CDialog
{
// Construction
public:
	char					SessionName[MAX_NETWORK_SESSIONS][32];
	int						NumSessions;
	BOOL					bFirst;
	int						SessionNumber;
	int						SessionPlayers[MAX_NETWORK_SESSIONS];
	const char*				PlayerName;	
	CNetSelSession(CWnd* pParent = NULL);   // standard constructor
	void CNetSelSession::DrawStuff();

// Dialog Data
	//{{AFX_DATA(CNetSelSession)
	enum { IDD = IDD_NET_SEL_SESSION };
	CString	m_PlayerName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetSelSession)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetSelSession)
	afx_msg void OnPaint();
	afx_msg void OnDblclkLbSession();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
