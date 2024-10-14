; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CsurfView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "surf.h"
LastPage=0

ClassCount=15
Class1=CMainFrame
Class2=CsurfApp
Class3=CAboutDlg
Class4=CsurfDoc
Class5=CsurfView

ResourceCount=19
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_ABOUTBOX
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDR_MAINFRAME
Class6=CSplashWnd
Class7=CNetCreate
Class8=CNetSelSession
Class9=CNetNames
Class10=CLeroy
Resource5=IDD_LEROY
Class11=CShareExit
Resource6=IDD_LOAD_PROGRESS
Class12=CLoadProgress
Resource7=IDD_TRACKS
Class13=CTrackSelect
Resource8=IDD_SHAREEXIT
Resource9=IDD_LEROY (English (U.S.))
Resource10=IDD_LOAD_PROGRESS (English (U.S.))
Resource11=IDD_TRACKS (English (U.S.))
Resource12=IDD_SHAREEXIT (Neutral)
Resource13=IDD_TRACKS (Neutral)
Resource14=IDD_GAMESPEED (Neutral)
Resource15=IDD_LEROY (Neutral)
Resource16=IDD_ABOUTBOX (Neutral)
Resource17=IDD_MAXFPS
Class14=CMaxFps
Resource18=IDD_LOAD_PROGRESS (Neutral)
Class15=CGamespeed
Resource19=IDR_MAINFRAME (Neutral)

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=Mainfrm.h
ImplementationFile=Mainfrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[CLS:CsurfApp]
Type=0
BaseClass=CWinApp
HeaderFile=surf.h
ImplementationFile=surf.cpp
LastObject=CsurfApp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=surf.cpp
ImplementationFile=surf.cpp
LastObject=CAboutDlg
Filter=D

[CLS:CsurfDoc]
Type=0
BaseClass=CDocument
HeaderFile=surfdoc.H
ImplementationFile=surfdoc.CPP
Filter=N
LastObject=CsurfDoc
VirtualFilter=DC

[CLS:CsurfView]
Type=0
BaseClass=CView
HeaderFile=surfview.H
ImplementationFile=surfview.CPP
Filter=T
VirtualFilter=VWC
LastObject=CsurfView

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDI_SURF,static,1342177283
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308353

[MNU:IDR_MAINFRAME]
Type=1
Class=CsurfView
Command1=ID_SAVE_PLAYBACK
Command2=ID_LOAD_PLAYBACK
Command3=ID_PLAY_PLAYBACK
Command4=ID_BEGIN_CAPTURE
Command5=ID_STOP_CAPTURE
Command6=ID_VIEW_HISCORES
Command7=IDCLOSE
Command8=ID_MAIN_CAMERA
Command9=ID_HELICOPTER_CAMERA
Command10=ID_TUBE_CAMERA
Command11=ID_BEACH_CAMERA
Command12=ID_SATELLITE_CAMERA
Command13=ID_ROCK_VIDEO_CAMERA
Command14=ID_BEACH_CAMERA2
Command15=ID_AUTO_CAMERA
Command16=ID_FPS
Command17=ID_PRACTICE
Command18=ID_BREAKINGWAVE
Command19=ID_FOAM
Command20=ID_GORE
Command21=ID_HORIZON
Command22=ID_SKYMAP
Command23=ID_SPEEDOMETER_TOGGLE
Command24=ID_SPRAY
Command25=ID_WAVE_TEXTURES
Command26=ID_HALFRES
Command27=ID_MIDI_MUSIC
Command28=ID_CD_MUSIC
Command29=ID_SOUND_FX
Command30=ID_NARATION
Command31=ID_SURFER_SOUNDS
Command32=ID_BREAK_NETWORK
Command33=ID_LIST_PLAYERS
Command34=ID_LOAD_SESSION
Command35=ID_SAVE_SESSION
Command36=ID_HELPF
Command37=ID_APP_ABOUT
CommandCount=37

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CsurfView
Command1=ID_SAVE_PLAYBACK
Command2=ID_LOAD_PLAYBACK
Command3=ID_PLAY_PLAYBACK
Command4=ID_BEGIN_CAPTURE
Command5=ID_STOP_CAPTURE
Command6=ID_VIEW_HISCORES
Command7=IDCLOSE
Command8=ID_MAIN_CAMERA
Command9=ID_HELICOPTER_CAMERA
Command10=ID_TUBE_CAMERA
Command11=ID_BEACH_CAMERA
Command12=ID_SATELLITE_CAMERA
Command13=ID_ROCK_VIDEO_CAMERA
Command14=ID_BEACH_CAMERA2
Command15=ID_AUTO_CAMERA
Command16=ID_FPS
Command17=ID_PRACTICE
Command18=ID_BREAKINGWAVE
Command19=ID_FOAM
Command20=ID_GORE
Command21=ID_HORIZON
Command22=ID_SKYMAP
Command23=ID_SPEEDOMETER_TOGGLE
Command24=ID_SPRAY
Command25=ID_WAVE_TEXTURES
Command26=ID_HALFRES
Command27=ID_MIDI_MUSIC
Command28=ID_CD_MUSIC
Command29=ID_SOUND_FX
Command30=ID_NARATION
Command31=ID_SURFER_SOUNDS
Command32=ID_BREAK_NETWORK
Command33=ID_LIST_PLAYERS
Command34=ID_LOAD_SESSION
Command35=ID_SAVE_SESSION
Command36=ID_HELPF
Command37=ID_APP_ABOUT
CommandCount=37

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FPS
Command2=ID_MAIN_CAMERA
Command3=ID_HELICOPTER_CAMERA
Command4=ID_TUBE_CAMERA
Command5=ID_BEACH_CAMERA
Command6=ID_SATELLITE_CAMERA
Command7=ID_ROCK_VIDEO_CAMERA
Command8=ID_BEACH_CAMERA2
Command9=ID_AUTO_CAMERA
CommandCount=9

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=5
Control1=IDI_SURF,static,1342177283
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308353

[ACL:IDR_MAINFRAME]
Type=1
Command1=ID_FPS
Command2=ID_MAIN_CAMERA
Command3=ID_HELICOPTER_CAMERA
Command4=ID_TUBE_CAMERA
Command5=ID_BEACH_CAMERA
Command6=ID_SATELLITE_CAMERA
Command7=ID_ROCK_VIDEO_CAMERA
Command8=ID_BEACH_CAMERA2
Command9=ID_AUTO_CAMERA
CommandCount=9

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CSplashWnd

[CLS:CNetCreate]
Type=0
HeaderFile=NetCreate.h
ImplementationFile=NetCreate.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL
VirtualFilter=dWC

[CLS:CNetSelSession]
Type=0
HeaderFile=NetSelSession.h
ImplementationFile=NetSelSession.cpp
BaseClass=CDialog
Filter=D
LastObject=CNetSelSession
VirtualFilter=dWC

[CLS:CNetNames]
Type=0
HeaderFile=NetNames.h
ImplementationFile=NetNames.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDCANCEL

[DLG:IDD_LEROY]
Type=1
Class=CLeroy
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEROY_IMAGE,static,1342183438
Control4=IDC_TIME,button,1342242819
Control5=IDC_LIFE,button,1342242819
Control6=IDC_SCORE,button,1342242819
Control7=IDC_UFO,button,1342242819
Control8=IDC_CHEATKEYS,button,1342242819
Control9=IDC_NAVMODE,button,1342242819
Control10=IDC_TRON,button,1342242819
Control11=IDC_LEROY_FACE,button,1342186240

[CLS:CLeroy]
Type=0
HeaderFile=Leroy.h
ImplementationFile=Leroy.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLeroy

[CLS:CShareExit]
Type=0
HeaderFile=ShareExit.h
ImplementationFile=ShareExit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CShareExit

[DLG:IDD_LOAD_PROGRESS]
Type=1
Class=CLoadProgress
ControlCount=3
Control1=IDC_SPLASH_LOGO,static,1342179342
Control2=IDC_TEXT,static,1342312448
Control3=IDC_GRAPH,msctls_progress32,1342177280

[CLS:CLoadProgress]
Type=0
HeaderFile=LoadProgress.h
ImplementationFile=LoadProgress.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoadProgress
VirtualFilter=dWC

[DLG:IDD_TRACKS]
Type=1
Class=CTrackSelect
ControlCount=25
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK1,button,1342185481
Control4=IDC_CHECK2,button,1342185481
Control5=IDC_CHECK3,button,1342185481
Control6=IDC_CHECK4,button,1342185481
Control7=IDC_CHECK5,button,1342185481
Control8=IDC_CHECK6,button,1342185481
Control9=IDC_CHECK7,button,1342185481
Control10=IDC_CHECK8,button,1342185481
Control11=IDC_CHECK9,button,1342185481
Control12=IDC_CHECK10,button,1342185481
Control13=IDC_CHECK11,button,1342185481
Control14=IDC_CHECK12,button,1342185481
Control15=IDC_CHECK13,button,1342185481
Control16=IDC_CHECK14,button,1342185481
Control17=IDC_CHECK15,button,1342185481
Control18=IDC_CHECK16,button,1342185481
Control19=IDC_CHECK17,button,1342185481
Control20=IDC_CHECK18,button,1342185481
Control21=IDC_CHECK19,button,1342185481
Control22=IDC_CHECK20,button,1342185481
Control23=IDC_STATIC,static,1342308352
Control24=IDC_CHECK21,button,1342185481
Control25=IDC_VLAACHOS,static,1342181390

[CLS:CTrackSelect]
Type=0
HeaderFile=TrackSelect.h
ImplementationFile=TrackSelect.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTrackSelect

[DLG:IDD_SHAREEXIT]
Type=1
ControlCount=0

[DLG:IDD_LEROY (English (U.S.))]
Type=1
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEROY_IMAGE,static,1342183438
Control4=IDC_TIME,button,1342242819
Control5=IDC_LIFE,button,1342242819
Control6=IDC_SCORE,button,1342242819
Control7=IDC_UFO,button,1342242819
Control8=IDC_CHEATKEYS,button,1342242819
Control9=IDC_NAVMODE,button,1342242819
Control10=IDC_TRON,button,1342242819
Control11=IDC_LEROY_FACE,button,1342186240

[DLG:IDD_LOAD_PROGRESS (English (U.S.))]
Type=1
ControlCount=3
Control1=IDC_SPLASH_LOGO,static,1342179342
Control2=IDC_TEXT,static,1342312448
Control3=IDC_GRAPH,msctls_progress32,1342177280

[DLG:IDD_TRACKS (English (U.S.))]
Type=1
ControlCount=25
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK1,button,1342185481
Control4=IDC_CHECK2,button,1342185481
Control5=IDC_CHECK3,button,1342185481
Control6=IDC_CHECK4,button,1342185481
Control7=IDC_CHECK5,button,1342185481
Control8=IDC_CHECK6,button,1342185481
Control9=IDC_CHECK7,button,1342185481
Control10=IDC_CHECK8,button,1342185481
Control11=IDC_CHECK9,button,1342185481
Control12=IDC_CHECK10,button,1342185481
Control13=IDC_CHECK11,button,1342185481
Control14=IDC_CHECK12,button,1342185481
Control15=IDC_CHECK13,button,1342185481
Control16=IDC_CHECK14,button,1342185481
Control17=IDC_CHECK15,button,1342185481
Control18=IDC_CHECK16,button,1342185481
Control19=IDC_CHECK17,button,1342185481
Control20=IDC_CHECK18,button,1342185481
Control21=IDC_CHECK19,button,1342185481
Control22=IDC_CHECK20,button,1342185481
Control23=IDC_STATIC,static,1342308352
Control24=IDC_CHECK21,button,1342185481
Control25=IDC_VLAACHOS,static,1342181390

[DLG:IDD_SHAREEXIT (Neutral)]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342179342

[MNU:IDR_MAINFRAME (Neutral)]
Type=1
Class=CsurfView
Command1=ID_SHOW_ERRORS
Command2=ID_VIEW_HISCORES
Command3=ID_MAIN_CAMERA
Command4=ID_HELICOPTER_CAMERA
Command5=ID_TUBE_CAMERA
Command6=ID_BEACH_CAMERA
Command7=ID_SATELLITE_CAMERA
Command8=ID_ROCK_VIDEO_CAMERA
Command9=ID_BEACH_CAMERA2
Command10=ID_AUTO_CAMERA
Command11=ID_FPS
Command12=ID_PRACTICE
Command13=ID_BREAKINGWAVE
Command14=ID_FOAM
Command15=ID_GORE
Command16=ID_HORIZON
Command17=ID_SKYMAP
Command18=ID_SPEEDOMETER_TOGGLE
Command19=ID_SCORETOGGLE
Command20=ID_SPRAY
Command21=ID_WAVE_TEXTURES
Command22=ID_HALFRES
Command23=ID_TEXTURE_FILTER
Command24=ID_MIDI_MUSIC
Command25=ID_SOUND_FX
Command26=ID_NARATION
Command27=ID_SURFER_SOUNDS
Command28=ID_APP_ABOUT
CommandCount=28

[DLG:IDD_ABOUTBOX (Neutral)]
Type=1
ControlCount=5
Control1=IDI_SURF,static,1342177283
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308353

[DLG:IDD_LEROY (Neutral)]
Type=1
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEROY_IMAGE,static,1342183438
Control4=IDC_TIME,button,1342242819
Control5=IDC_LIFE,button,1342242819
Control6=IDC_SCORE,button,1342242819
Control7=IDC_UFO,button,1342242819
Control8=IDC_CHEATKEYS,button,1342242819
Control9=IDC_NAVMODE,button,1342242819
Control10=IDC_TRON,button,1342242819
Control11=IDC_LEROY_FACE,button,1342186240

[DLG:IDD_LOAD_PROGRESS (Neutral)]
Type=1
ControlCount=3
Control1=IDC_TEXT,static,1342312448
Control2=IDC_GRAPH,msctls_progress32,1342177280
Control3=IDC_STATIC,static,1342177294

[DLG:IDD_TRACKS (Neutral)]
Type=1
ControlCount=25
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK1,button,1342185481
Control4=IDC_CHECK2,button,1342185481
Control5=IDC_CHECK3,button,1342185481
Control6=IDC_CHECK4,button,1342185481
Control7=IDC_CHECK5,button,1342185481
Control8=IDC_CHECK6,button,1342185481
Control9=IDC_CHECK7,button,1342185481
Control10=IDC_CHECK8,button,1342185481
Control11=IDC_CHECK9,button,1342185481
Control12=IDC_CHECK10,button,1342185481
Control13=IDC_CHECK11,button,1342185481
Control14=IDC_CHECK12,button,1342185481
Control15=IDC_CHECK13,button,1342185481
Control16=IDC_CHECK14,button,1342185481
Control17=IDC_CHECK15,button,1342185481
Control18=IDC_CHECK16,button,1342185481
Control19=IDC_CHECK17,button,1342185481
Control20=IDC_CHECK18,button,1342185481
Control21=IDC_CHECK19,button,1342185481
Control22=IDC_CHECK20,button,1342185481
Control23=IDC_STATIC,static,1342308352
Control24=IDC_CHECK21,button,1342185481
Control25=IDC_VLAACHOS,static,1342181390

[ACL:IDR_MAINFRAME (Neutral)]
Type=1
Command1=ID_FPS
Command2=ID_MAIN_CAMERA
Command3=ID_HELICOPTER_CAMERA
Command4=ID_TUBE_CAMERA
Command5=ID_BEACH_CAMERA
Command6=ID_SATELLITE_CAMERA
Command7=ID_ROCK_VIDEO_CAMERA
Command8=ID_BEACH_CAMERA2
Command9=ID_AUTO_CAMERA
CommandCount=9

[CLS:CMaxFps]
Type=0
HeaderFile=MaxFps.h
ImplementationFile=MaxFps.cpp
BaseClass=CDialog
Filter=D
LastObject=CMaxFps
VirtualFilter=dWC

[DLG:IDD_MAXFPS]
Type=1
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SPEEDSLIDER,msctls_trackbar32,1342242825
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308354

[DLG:IDD_GAMESPEED (Neutral)]
Type=1
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SPEEDSLIDER,msctls_trackbar32,1342242824
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308353
Control7=IDC_NUMBER,static,1342308352

[CLS:CGamespeed]
Type=0
HeaderFile=Gamespeed.h
ImplementationFile=Gamespeed.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

