#include <windows.h>

int WINAPI WinMain(HINSTANCE hInst,
				   HINSTANCE hPrevInstance,
				   LPSTR lpszCmdParam, int nCmdShow)
{
	int getit = GetPrivateProfileInt("FullInstallation","WildRideInstalled",0,"wildride.ini");
	if (getit == 0)
	{
//		CreateProcess(
//			"install.exe",	// pointer to name of executable module 
///			NULL,	// pointer to command line string
//			NULL,	// pointer to process security attributes 
///			NULL,	// pointer to thread security attributes 
//			FALSE,	// handle inheritance flag 
//			CREATE_DEFAULT_ERROR_MODE,	// creation flags 
//			NULL,	// pointer to new environment block 
//			NULL,	// pointer to current directory name 
//  /  LPSTARTUPINFO  lpStartupInfo,	// pointer to STARTUPINFO 
//    LPPROCESS_INFORMATION  lpProcessInformation 	// pointer to PROCESS_INFORMATION  
//   );
		WinExec("install.exe",
			SW_SHOWDEFAULT);
	}
	else
	{
		int i = MessageBox(0, "Do you want to run Wild Ride!?","Wild Ride!",MB_YESNO | MB_ICONEXCLAMATION);
		if (i == IDYES)
		{
			char inipath[128];
			int len;
			GetPrivateProfileString("FullInstallation","Directory","satanspoop",inipath,128,"wildride.ini");
			if (lstrcmpi(inipath, "satanspoop"))
			{
			    len = lstrlen(inipath);
			    if (len > 0 && (inipath[len-1] != '\\' && inipath[len-1] != '/'))
					lstrcat(inipath,"\\");
			}
			else
			{
				inipath[0] = 0;
			}
			lstrcat(inipath,"wildride.exe");

		    // SHFileOperation needs a double null string.
		    len = lstrlen(inipath);
		    inipath[len+1] = 0;
			WinExec(inipath,
				SW_SHOWDEFAULT);
		}
	}
	return 0;
}