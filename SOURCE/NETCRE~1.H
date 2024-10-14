// NetCreate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetCreate dialog

#ifndef __NETCREATE__
#define __NETCREATE__

#define NET_CANCEL 0
#define NET_JOIN 1
#define NET_START 2

#include "resource.h"
//#include "surfview.h"

class CNetCreate : public CDialog
{
// Construction
public:
	int selection;
	CNetCreate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetCreate)
	enum { IDD = IDD_NET_CREATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetCreate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetCreate)
	afx_msg void OnJoinSession();
	afx_msg void OnStartSession();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif