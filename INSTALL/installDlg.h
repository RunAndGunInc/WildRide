// installDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

//#define SHAREWARE

class CInstallDlg : public CDialog
{
// Construction
public:
	BOOL	bInstallDirectX2;
	BOOL	bInstallWildRide;
//	BOOL	bUnInstallDirectX2;
	BOOL	bUnInstallWildRide;
	BOOL	bDX2UnInstallable;
	BOOL	bWRUnInstallable;
    char	InstallPath[MAX_PATH];
	char	ThisPath[MAX_PATH];
	void	CInstallDlg::MakeShortcut();
	void	CInstallDlg::catpath(char *dst, char *src);
	CInstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInstallDlg)
	enum { IDD = IDD_INSTALL_DIALOG };
	CString	m_Path;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInstallDx2();
	afx_msg void OnInstallWr();
	afx_msg void OnUninstallWr();
	virtual void OnOK();
	afx_msg void OnBrowse();
	afx_msg void OnLaunchCd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
