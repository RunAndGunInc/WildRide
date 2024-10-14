// installDlg.cpp : implementation file
//

#include "stdafx.h"
#include "install.h"
#include "installDlg.h"
#include <windows.h>
#include <shellapi.h>   // for SHFileOperation
#include <shlobj.h>     // for SHBroweForFolder
#include "reboot.h"
#include "soundcard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define SHAREWARE
#ifndef SHAREWARE
#include "dsetup.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

CInstallDlg::CInstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstallDlg::IDD, pParent)
{
	char inipath[128];
#ifdef SHAREWARE
	GetPrivateProfileString("Installation","Directory","c:\\wildride\\",inipath,128,"wildride.ini");
#else
	GetPrivateProfileString("FullInstallation","Directory","c:\\wildride\\",inipath,128,"wildride.ini");
#endif
	const char* ini_path = inipath;
	//{{AFX_DATA_INIT(CInstallDlg)
	m_Path = ini_path;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	int getit = GetPrivateProfileInt("Installation","DirectX3Installed",0,"wildride.ini");
	if (getit > 0)
	{
		bInstallDirectX2 = FALSE;
//		bDX2UnInstallable = TRUE;
	}
	else
	{
		bInstallDirectX2 = TRUE;
//		bDX2UnInstallable = FALSE;
	}
#ifdef SHAREWARE
	getit = GetPrivateProfileInt("Installation","WildRideInstalled",0,"wildride.ini");
#else
	getit = GetPrivateProfileInt("FullInstallation","WildRideInstalled",0,"wildride.ini");
#endif
	if (getit > 0)
	{
		bInstallWildRide = FALSE;
		bWRUnInstallable = TRUE;
	}
	else
	{
		bInstallWildRide = TRUE;
		bWRUnInstallable = FALSE;
	}
//	bUnInstallDirectX2 = FALSE;
	bUnInstallWildRide = FALSE;
}

void CInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallDlg)
	DDX_Text(pDX, IDC_PATH, m_Path);
	DDV_MaxChars(pDX, m_Path, 128);
	//}}AFX_DATA_MAP
//	InstallPath = (LPCTSTR) m_Path;
}

BEGIN_MESSAGE_MAP(CInstallDlg, CDialog)
	//{{AFX_MSG_MAP(CInstallDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSTALL_DX2, OnInstallDx2)
	ON_BN_CLICKED(IDC_INSTALL_WR, OnInstallWr)
	ON_BN_CLICKED(IDC_UNINSTALL_WR, OnUninstallWr)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_LAUNCH_CD, OnLaunchCd)
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
#ifndef SHAREWARE
			if (bInstallDirectX2)
				CheckDlgButton(IDC_INSTALL_DX2, BST_CHECKED);
#else
			bInstallDirectX2 = FALSE;
#endif
			if (bInstallWildRide)
				CheckDlgButton(IDC_INSTALL_WR, BST_CHECKED);

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

void CInstallDlg::OnInstallDx2() 
{
#ifndef SHAREWARE
	bInstallDirectX2 = !bInstallDirectX2;
	if (bInstallDirectX2)
	{
//		if (bUnInstallDirectX2)
//		{
//			CheckDlgButton(IDC_UNINSTALL_DX2, BST_UNCHECKED);
//			bUnInstallDirectX2 = FALSE;
//		}
		CheckDlgButton(IDC_INSTALL_DX2, BST_CHECKED);
	}
	else
#endif
	{
		bInstallDirectX2 = FALSE;
		CheckDlgButton(IDC_INSTALL_DX2, BST_UNCHECKED);
	}
}

void CInstallDlg::OnInstallWr() 
{
	bInstallWildRide = !bInstallWildRide;
	if (bInstallWildRide)
	{
		if (bUnInstallWildRide)
		{
			CheckDlgButton(IDC_UNINSTALL_WR, BST_UNCHECKED);
			bUnInstallWildRide = FALSE;
		}
		CheckDlgButton(IDC_INSTALL_WR, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(IDC_INSTALL_WR, BST_UNCHECKED);
	}
}

//void CInstallDlg::OnUninstallDx2() 
//{
//	if (bDX2UnInstallable)
//	{
//		bUnInstallDirectX2 = !bUnInstallDirectX2;
//		if (bUnInstallDirectX2)
//		{
//			if (bInstallDirectX2)
//			{
//				CheckDlgButton(IDC_INSTALL_DX2, BST_UNCHECKED);
//				bInstallDirectX2 = FALSE;
//			}
//			CheckDlgButton(IDC_UNINSTALL_DX2, BST_CHECKED);
//		}
//		else
//		{
//			CheckDlgButton(IDC_UNINSTALL_DX2, BST_UNCHECKED);
//		}
//	}
//}

void CInstallDlg::OnUninstallWr() 
{
	if (bWRUnInstallable)
	{
		bUnInstallWildRide = !bUnInstallWildRide;
		if (bUnInstallWildRide)
		{
			if (bInstallWildRide)
			{
				CheckDlgButton(IDC_INSTALL_WR, BST_UNCHECKED);
				bInstallWildRide = FALSE;
			}
			CheckDlgButton(IDC_UNINSTALL_WR, BST_CHECKED);
		}
		else
		{
			CheckDlgButton(IDC_UNINSTALL_WR, BST_UNCHECKED);
		}
	}
}

void CInstallDlg::OnBrowse() 
{
	BROWSEINFO bi;
    LPITEMIDLIST pidl;
    char ach[MAX_PATH];

    bi.hwndOwner      = m_hWnd;
    bi.pidlRoot       = NULL;
    bi.pszDisplayName = ach;
    bi.lpszTitle      = NULL;
    bi.ulFlags        = BIF_RETURNONLYFSDIRS;
    bi.lpfn           = NULL;
    bi.lParam         = 0;
    bi.iImage         = 0;

    pidl = SHBrowseForFolder(&bi);

    if (pidl)
    {
		SHGetPathFromIDList(pidl, ach);
        SetDlgItemText(IDC_PATH, ach);
//		delete pidl;
    }
}

void CInstallDlg::OnOK() 
{
	int			i;
    char        src[MAX_PATH];
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
    ::GetWindowText( ::GetDlgItem(m_hWnd, IDC_PATH ), InstallPath, sizeof(InstallPath));

    for (x=p=ThisPath; *p; p=AnsiNext(p))
    {
        if (*p == '\\' || *p == '/')
            x = p;
    }
    *x = 0;

    SHFILEOPSTRUCT fileop;

	BOOL bReBoot = FALSE;

#ifndef SHAREWARE
	HRESULT result;
	if (bInstallDirectX2)
	{
        result = DirectXSetup( m_hWnd, NULL, DSETUP_DIRECTX | DSETUP_PROMPTFORDRIVERS);
//        SetInfoText(hDlg, "");
		switch (result)
		{
		case 0: // No Rebooty
			break;
		case 1: // Rebooty
			bReBoot = TRUE;
			break;
		case DSETUPERR_BADSOURCESIZE:
			MessageBox("DSETUPERR_BADSOURCESIZE: One of the files sizes was incorrect or could not be validated.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_BADSOURCETIME:
			MessageBox("DSETUPERR_BADSOURCETIME: One of the files time and date was incorrect or could not be validated.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_BADWINDOWSVERSION:
			MessageBox("DSETUPERR_BADWINDOWSVERSION: The Windows version on your system is not supported by DirectX.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_CANTFINDDIR:
			MessageBox("DSETUPERR_CANTFINDDIR: The setup program could not find the working directory.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_CANTFINDINF:
			MessageBox("DSETUPERR_CANTFINDINF: A required .inf file could not be found.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_INTERNAL:
			MessageBox("DSETUPERR_INTERNAL: An internal error occurred in Microsoft's Direct Setup.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_NOCOPY:
			MessageBox("DSETUPERR_NOCOPY: A file's version could not be verified or was incorrect. If the DSETUP_REINSTALL flag is specified, equal versions will be installed.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_OUTOFDISKSPACE:
			MessageBox("DSETUPERR_OUTOFDISKSPACE: The setup program ran out of disk space during installation.",
				"DirectX 2 Installation Error");
			return;
		case DSETUPERR_SOURCEFILENOTFOUND:
			MessageBox("DSETUPERR_SOURCEFILENOTFOUND: One of the required source files could not be found. ",
				"DirectX 2 Installation Error");
			return;
		}
		WritePrivateProfileString("Installation","DirectX3Installed","1","wildride.ini");
	}
#endif
	if (bInstallWildRide)
	{
		CSoundCard SoundCard;
		SoundCard.DoModal();
		delete SoundCard;

		/* Copy the mfc42 driver into windows\system
		 */
        for(i = 0; i < 2; i++ )
	    {
	        lstrcpy( src, ThisPath );
		    catpath( src, driver_list[i] );

	        GetSystemDirectory(dst, sizeof(dst));
            catpath( dst, driver_list[i] );

			SetDlgItemText(IDC_INFO, dst); 

//            LoadStrFromRes( IDS_CURRENT_FILE_MSG, szBuffer );
//            SetInfoText(hDlg, szBuffer, copy_list[i]);

            fileop.hwnd     = m_hWnd;
            fileop.wFunc    = FO_COPY;
            fileop.pFrom    = src;
            fileop.pTo      = dst;
            fileop.fFlags   = FOF_NOCONFIRMATION;

            if (SHFileOperation(&fileop) == 0)
            {
				SetFileAttributes( dst, FILE_ATTRIBUTE_NORMAL );
            }
		}

		/*
         * verify that the typed in directory is valid
         * by having the SHELL copy WIN.INI to this directory
         * it will also create the directory for us.
         */
        GetWindowsDirectory(src, sizeof(src));
        catpath(src,"WIN.INI");

        lstrcpy(dst,InstallPath);
        catpath(dst,"SMAG.INI");

        fileop.hwnd     = m_hWnd;
        fileop.wFunc    = FO_COPY;
        fileop.pFrom    = src;
        fileop.pTo      = dst;
        fileop.fFlags   = FOF_SILENT | FOF_NOCONFIRMATION;

        if (SHFileOperation(&fileop) != 0)
        {
			// failed, the shell gave the user a error.
			MessageBox("Couldn't create installation directory.",
				"Installation Error");
			return;
        }

        /*
         * the directory is valid now delete the bogus file
         */
        fileop.hwnd     = m_hWnd;
        fileop.wFunc    = FO_DELETE;
        fileop.pFrom    = dst;
        fileop.pTo      = NULL;
        fileop.fFlags   = FOF_SILENT | FOF_NOCONFIRMATION;

        SHFileOperation(&fileop);

		// delete wildride.ini

		int getit = GetPrivateProfileInt("ScreenMode","WindowWidth",-1,"wildride.ini");
		if (getit != -1)
		{
	        GetWindowsDirectory(dst, sizeof(src));
	        catpath(dst,"WILDRIDE.INI");
	
		    fileop.hwnd     = m_hWnd;
	        fileop.wFunc    = FO_DELETE;
		    fileop.pFrom    = dst;
			fileop.pTo      = NULL;
	        fileop.fFlags   = FOF_SILENT | FOF_NOCONFIRMATION;

		    SHFileOperation(&fileop);
		}

        /*
         * check if there is enough space to install the game
         * NOTE: there is always enough space at the moment :)
         */

        for(i = 0; i < 7; i++ )
	    {
	        lstrcpy( src, ThisPath );
		    catpath( src, copy_list[i] );

	        lstrcpy( dst, InstallPath );
            catpath( dst, copy_list[i] );

			SetDlgItemText(IDC_INFO, dst); 
			 
//            LoadStrFromRes( IDS_CURRENT_FILE_MSG, szBuffer );
//            SetInfoText(hDlg, szBuffer, copy_list[i]);

            fileop.hwnd     = m_hWnd;
            fileop.wFunc    = FO_COPY;
            fileop.pFrom    = src;
            fileop.pTo      = dst;
            fileop.fFlags   = FOF_NOCONFIRMATION;

            if (SHFileOperation(&fileop) == 0)
            {
				SetFileAttributes( dst, FILE_ATTRIBUTE_NORMAL );
            }
		}
        MakeShortcut();

#ifdef SHAREWARE
		WritePrivateProfileString("ScreenMode","WindowWidth","414","wildride.ini");
		WritePrivateProfileString("Installation","WildRideInstalled","1","wildride.ini");
		WritePrivateProfileString("Installation","Directory",InstallPath,"wildride.ini");

		MessageBox("Wild Ride! has completed installation.  You can launch it from the Start Menu under RUNANDGUN! Inc.  Run install.exe to uninstall Wild Ride!","Wild Ride! installation complete.");
#else
		WritePrivateProfileString("ScreenMode","WindowWidth","414","wildride.ini");
		WritePrivateProfileString("FullInstallation","WildRideInstalled","1","wildride.ini");
		WritePrivateProfileString("FullInstallation","Directory",InstallPath,"wildride.ini");

		MessageBox("Wild Ride! has completed installation.  You can launch it from the Start Menu under RUNANDGUN! Inc.  Run install.exe or uninst.exe from the CD to uninstall Wild Ride!","Wild Ride! installation complete.");
#endif
	}
//	if (bUnInstallDirectX2)
//	{
//		WritePrivateProfileString("Installation","DirectX2Installed","0","wildride.ini");
//	}
	if (bUnInstallWildRide)
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
	if (bReBoot)
	{
		CReboot Reboot;
		Reboot.DoModal();
		if (Reboot.bOk)
			ExitWindowsEx( EWX_REBOOT, 0 );
		delete Reboot;
	}
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

void CInstallDlg::MakeShortcut()
{
    char buf[512];
    char szSetupIni[MAX_PATH];
    char szExeFile[MAX_PATH];
    int len;
    int fh;

    static char setup_ini[] =
        "[progman.groups]\r\n"
        "groupX=%s\r\n"
        "[groupX]\r\n"
        "\"%s\",\"%s\",,,,\"%s\"\r\n";

    GetWindowsDirectory(szSetupIni, sizeof(szSetupIni));
    catpath(szSetupIni, "SETUP.INI");

    lstrcpy(buf, InstallPath);
    catpath(buf, "WILDRIDE.EXE");
    GetShortPathName(buf, szExeFile, sizeof(szExeFile));

//  lstrcpy(buf, GameDirectory);
//  GetShortPathName(buf, szWork, sizeof(szWork));

    len = wsprintf(buf, setup_ini, "RUNANDGUN! Inc.", "Wild Ride!", 
                   szExeFile, InstallPath);

    fh = _lcreat(szSetupIni, 0);

    if (fh != -1)
    {
        _lwrite(fh, buf, len);
        _lclose(fh);
        WinExec("grpconv -o", SW_HIDE);
    }
}

void CInstallDlg::OnLaunchCd() 
{
	CDialog::OnCancel();
	WinExec("wildride.exe",
		SW_SHOWDEFAULT);
}
