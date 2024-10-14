; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSoundCard
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "install.h"

ClassCount=5
Class1=CInstallApp
Class2=CInstallDlg

ResourceCount=4
Resource2=IDD_REBOOT
Resource1=IDR_MAINFRAME
Class3=CReboot
Class4=CFilename
Resource3=IDD_SOUNDCARD
Class5=CSoundCard
Resource4=IDD_INSTALL_DIALOG

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
LastObject=IDC_BROWSE
BaseClass=CDialog
VirtualFilter=dWC


[DLG:IDD_INSTALL_DIALOG]
Type=1
Class=CInstallDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_INSTALL_DX2,button,1342242818
Control4=IDC_INSTALL_WR,button,1342242818
Control5=IDC_PATH,edit,1350631552
Control6=IDC_UNINSTALL_WR,button,1342242818
Control7=IDC_STATIC,static,1342308353
Control8=IDC_BROWSE,button,1342242816
Control9=IDC_LOGO_SPOT,static,1342177294
Control10=IDC_LAUNCH_CD,button,1342242816

[DLG:IDD_REBOOT]
Type=1
Class=CReboot
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

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

[DLG:IDD_SOUNDCARD]
Type=1
Class=CSoundCard
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:CSoundCard]
Type=0
HeaderFile=SoundCard.h
ImplementationFile=SoundCard.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

