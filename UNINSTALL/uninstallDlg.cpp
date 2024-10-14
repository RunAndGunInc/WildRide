// installDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uninstall.h"
#include "uninstallDlg.h"
#include <windows.h>
#include <shellapi.h>   // for SHFileOperation
#include <shlobj.h>     // for SHBroweForFolder

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define SHAREWARE

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

CInstallDlg::CInstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstallDlg::IDD, pParent)
{
#ifdef SHAREWARE
	GetPrivateProfileString("Installation","Directory","c:\\wildride\\",InstallPath,MAX_PATH,"wildride.ini");
#else
	GetPrivateProfileString("FullInstallation","Directory","c:\\wildride\\",InstallPath,MAX_PATH,"wildride.ini");
#endif
	//{{AFX_DATA_INIT(CInstallDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

#ifdef SHAREWARE
	int getit = GetPrivateProfileInt("Installation","WildRideInstalled",0,"wildride.ini");
#else
	int getit = GetPrivateProfileInt("FullInstallation","WildRideInstalled",0,"wildride.ini");
#endif

	if (getit > 0)
	{
		bWRUnInstallable = TRUE;
	}
	else
	{
		bWRUnInstallable = FALSE;
	}
}

void CInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallDlg)
	//}}AFX_DATA_MAP
//	InstallPath = (LPCTSTR) m_Path;
}

BEGIN_MESSAGE_MAP(CInstallDlg, CDialog)
	//{{AFX_MSG_MAP(CInstallDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg message handlers

BOOL CInstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInstallDlg::OnPaint() 
{
	static BOOL bFirstPaint = TRUE;
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (bFirstPaint)
		{
			HWND hwnd = ::GetDlgItem(m_hWnd, IDC_LOGO_SPOT);

			HBITMAP hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_LOGO), IMAGE_BITMAP, 0, 0,
				LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS | LR_CREATEDIBSECTION);

			if (hbm)
				hbm = (HBITMAP)::SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);

			if (hbm)
			    DeleteObject(hbm);

			bFirstPaint = FALSE;
		}
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInstallDlg::OnOK() 
{
	int			i;
    char        dst[MAX_PATH];
	char*		copy_list[] = 
	{
		"wildride.exe",
		"help1.html",
		"help2.html",
		"help3.html",
		"help4.html",
		"help5.html",
		"readme.txt"
	};
	char*		driver_list[] = 
	{
		"msvcrt.dll",
		"mfc42.dll"
	};

    TCHAR * p;
    TCHAR * x;

    /*
     * get our fullpath name and strip the file name
     */
    GetModuleFileName(GetModuleHandle(NULL), ThisPath, sizeof(ThisPath));

    for (x=p=ThisPath; *p; p=AnsiNext(p))
    {
        if (*p == '\\' || *p == '/')
            x = p;
    }
    *x = 0;

    SHFILEOPSTRUCT fileop;

	if (bWRUnInstallable)
	{
        GetWindowsDirectory(dst, sizeof(dst));
        catpath(dst,"wildride.ini");

        /*
         * the directory is valid now delete the bogus file
         */
        fileop.hwnd     = m_hWnd;
        fileop.wFunc    = FO_DELETE;
        fileop.pFrom    = dst;
        fileop.pTo      = NULL;
        fileop.fFlags   = FOF_NOCONFIRMATION;

        SHFileOperation(&fileop);

        GetWindowsDirectory(dst, sizeof(dst));
        catpath(dst,"Start Menu\\Programs\\RUNANDGUN! Inc");

        /*
         * the directory is valid now delete the bogus file
         */
        fileop.hwnd     = m_hWnd;
        fileop.wFunc    = FO_DELETE;
        fileop.pFrom    = dst;
        fileop.pTo      = NULL;
        fileop.fFlags   = FOF_NOCONFIRMATION;

        SHFileOperation(&fileop);

        /*
         * check if there is enough space to install the game
         * NOTE: there is always enough space at the moment :)
         */

        for(i = 0; i < 7; i++ )
	    {
	        lstrcpy( dst, InstallPath );
            catpath( dst, copy_list[i] );

			SetDlgItemText(IDC_INFO, dst); 
			 
	        /*
	         * the directory is valid now delete the bogus file
	         */
	        fileop.hwnd     = m_hWnd;
	        fileop.wFunc    = FO_DELETE;
	        fileop.pFrom    = dst;
	        fileop.pTo      = NULL;
	        fileop.fFlags   = FOF_NOCONFIRMATION;

	        SHFileOperation(&fileop);
		}
        lstrcpy( dst, InstallPath );

		SetDlgItemText(IDC_INFO, dst); 
	    int len = lstrlen(dst);
		if (!(len > 0 && (dst[len-1] != '\\' && dst[len-1] != '/')))
	        dst[len-1] = 0x00;
		dst[len] = 0;
	    dst[len+1] = 0;
			 
        /*
         * the directory is valid now delete the bogus file
         */
        fileop.hwnd     = m_hWnd;
        fileop.wFunc    = FO_DELETE;
        fileop.pFrom    = dst;
        fileop.pTo      = NULL;
        fileop.fFlags   = 0;

        SHFileOperation(&fileop);
		MessageBox("Wild Ride! has completed uninstalling.","Wild Ride! uninstall complete.");
	}
	else
		MessageBox("Wild Ride! is not installed on your system properly.  You will have to manually remove the Wild Ride! folder and Start Menu shortcut.","Wild Ride! uninstall complete.");
	CDialog::OnOK();
}

void CInstallDlg::catpath(char *dst, char *src)
{
    int len = lstrlen(dst);
    if (len > 0 && (dst[len-1] != '\\' && dst[len-1] != '/'))
        lstrcat(dst,"\\");
    lstrcat(dst,src);

    // SHFileOperation needs a double null string.
    len = lstrlen(dst);
    dst[len+1] = 0;
}

