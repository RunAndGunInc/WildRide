// Filename.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilename dialog

class CFilename : public CDialog
{
// Construction
public:
	CFilename(CWnd* pParent = NULL);   // standard constructor
	void CFilename::ChangeText(char* text);


// Dialog Data
	//{{AFX_DATA(CFilename)
	enum { IDD = IDD_FILENAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilename)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilename)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
