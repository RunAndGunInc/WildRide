// LoadProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadProgress dialog

class CLoadProgress : public CDialog
{
// Construction
public:
	CLoadProgress(CWnd* pParent = NULL);   // standard constructor
	char * Text;
	HWND graph_hwnd;

// Dialog Data
	//{{AFX_DATA(CLoadProgress)
	enum { IDD = IDD_LOAD_PROGRESS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadProgress)
	public:
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoadProgress)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
