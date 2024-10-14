// installDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

class CInstallDlg : public CDialog
{
// Construction
public:
	BOOL	bWRUnInstallable;
    char	InstallPath[MAX_PATH];
	char	ThisPath[MAX_PATH];
	void	CInstallDlg::catpath(char *dst, char *src);
	CInstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInstallDlg)
	enum { IDD = IDD_INSTALL_DIALOG };
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
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
