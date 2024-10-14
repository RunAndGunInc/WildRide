// TrackSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrackSelect dialog

class CTrackSelect : public CDialog
{
// Construction
public:
	CTrackSelect(CWnd* pParent = NULL);   // standard constructor
	void CTrackSelect::ClearButtons();
	BOOL bOk;
	BOOL bFirst;
	int current_track;

// Dialog Data
	//{{AFX_DATA(CTrackSelect)
	enum { IDD = IDD_TRACKS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrackSelect)
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnCheck1();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnCheck2();
	afx_msg void OnCheck20();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnCheck21();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
