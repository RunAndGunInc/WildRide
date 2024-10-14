; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFilename
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "install.h"

ClassCount=4
Class1=CInstallApp
Class2=CInstallDlg

ResourceCount=2
Resource2=IDD_INSTALL_DIALOG
Resource1=IDR_MAINFRAME
Class3=CReboot
Class4=CFilename

[CLS:CInstallApp]
Type=0
HeaderFile=install.h
ImplementationFile=install.cpp
Filter=N
LastObject=IDC_INSTALL_DX2

[CLS:CInstallDlg]
Type=0
HeaderFile=installDlg.h
ImplementationFile=installDlg.cpp
Filter=D
LastObject=IDC_LAUNCH_CD
BaseClass=CDialog
VirtualFilter=dWC


[DLG:IDD_INSTALL_DIALOG]
Type=1
Class=CInstallDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308353
Control4=IDC_LOGO_SPOT,static,1342177294
Control5=IDC_INFO,static,1342308352

[CLS:CReboot]
Type=0
HeaderFile=Reboot.h
ImplementationFile=Reboot.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CFilename]
Type=0
HeaderFile=Filename.h
ImplementationFile=Filename.cpp
BaseClass=CDialog
Filter=D
LastObject=CFilename

