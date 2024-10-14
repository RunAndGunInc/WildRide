# Microsoft Developer Studio Project File - Name="surf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=surf - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Surf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Surf.mak" CFG="surf - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "surf - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "surf - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "surf - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 d3drm.lib ddraw.lib winmm.lib dsound.lib dxguid.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "surf - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 d3drm.lib ddraw.lib winmm.lib dsound.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "surf - Win32 Release"
# Name "surf - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ddutil.cpp
# End Source File
# Begin Source File

SOURCE=.\Leroy.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Midistrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Mmio.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareExit.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\surf.cpp
# End Source File
# Begin Source File

SOURCE=.\surf.rc

!IF  "$(CFG)" == "surf - Win32 Release"

!ELSEIF  "$(CFG)" == "surf - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\surfDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\surfView.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\Wave.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ddutil.h
# End Source File
# Begin Source File

SOURCE=.\Leroy.h
# End Source File
# Begin Source File

SOURCE=.\Mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\Midistrm.h
# End Source File
# Begin Source File

SOURCE=.\MMIO.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\surf.h
# End Source File
# Begin Source File

SOURCE=.\surfdoc.H
# End Source File
# Begin Source File

SOURCE=.\surfview.H
# End Source File
# Begin Source File

SOURCE=.\Wave.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\alphabet.BMP
# End Source File
# Begin Source File

SOURCE=.\Finalsplash.bmp
# End Source File
# Begin Source File

SOURCE=.\indian.bmp
# End Source File
# Begin Source File

SOURCE=.\logo.BMP
# End Source File
# Begin Source File

SOURCE=.\nav.BMP
# End Source File
# Begin Source File

SOURCE=.\Newinterface.bmp
# End Source File
# Begin Source File

SOURCE=.\Spin_speed.bmp
# End Source File
# Begin Source File

SOURCE=.\res\surf.rc2
# End Source File
# Begin Source File

SOURCE=.\surf38.ico
# End Source File
# Begin Source File

SOURCE=.\surfsky.bmp
# End Source File
# Begin Source File

SOURCE=.\Vlaachos.bmp
# End Source File
# Begin Source File

SOURCE=.\wave1.bin
# End Source File
# End Group
# Begin Source File

SOURCE=".\180-2.wav"
# End Source File
# Begin Source File

SOURCE=.\180.wav
# End Source File
# Begin Source File

SOURCE=".\360-2.wav"
# End Source File
# Begin Source File

SOURCE=.\360.wav
# End Source File
# Begin Source File

SOURCE=".\540-2.wav"
# End Source File
# Begin Source File

SOURCE=.\540.wav
# End Source File
# Begin Source File

SOURCE=".\720-2.wav"
# End Source File
# Begin Source File

SOURCE=.\720.wav
# End Source File
# Begin Source File

SOURCE=".\900-2.wav"
# End Source File
# Begin Source File

SOURCE=.\900.wav
# End Source File
# Begin Source File

SOURCE=.\alana.mds
# End Source File
# Begin Source File

SOURCE=.\Alana.ppm
# End Source File
# Begin Source File

SOURCE=.\alana.x
# End Source File
# Begin Source File

SOURCE=.\ALIEN2.wav
# End Source File
# Begin Source File

SOURCE=.\AMB2.wav
# End Source File
# Begin Source File

SOURCE=.\BARREL.ppm
# End Source File
# Begin Source File

SOURCE=.\barrel.x
# End Source File
# Begin Source File

SOURCE=.\BARREL1.wav
# End Source File
# Begin Source File

SOURCE=.\blood3.ppm
# End Source File
# Begin Source File

SOURCE=.\blood4.ppm
# End Source File
# Begin Source File

SOURCE=.\blood5.ppm
# End Source File
# Begin Source File

SOURCE=.\blood6.ppm
# End Source File
# Begin Source File

SOURCE=.\blood7.ppm
# End Source File
# Begin Source File

SOURCE=.\blood8.ppm
# End Source File
# Begin Source File

SOURCE=.\bluber1.wav
# End Source File
# Begin Source File

SOURCE=.\BOUY.wav
# End Source File
# Begin Source File

SOURCE=.\bucky.mds
# End Source File
# Begin Source File

SOURCE=.\BUCKY.ppm
# End Source File
# Begin Source File

SOURCE=.\bucky.x
# End Source File
# Begin Source File

SOURCE=.\buildall.ppm
# End Source File
# Begin Source File

SOURCE=.\choic2.mds
# End Source File
# Begin Source File

SOURCE=.\choiccn2.mds
# End Source File
# Begin Source File

SOURCE=.\choiccon.mds
# End Source File
# Begin Source File

SOURCE=.\choice3.mds
# End Source File
# Begin Source File

SOURCE=.\collis1.wav
# End Source File
# Begin Source File

SOURCE=.\collis2.wav
# End Source File
# Begin Source File

SOURCE=.\cred2.mds
# End Source File
# Begin Source File

SOURCE=.\crowd.wav
# End Source File
# Begin Source File

SOURCE=.\CRUNCH.wav
# End Source File
# Begin Source File

SOURCE=.\Csguy.ppm
# End Source File
# Begin Source File

SOURCE=.\DOLFHIT.wav
# End Source File
# Begin Source File

SOURCE=.\DOLFHIT2.wav
# End Source File
# Begin Source File

SOURCE=.\dolfin3.wav
# End Source File
# Begin Source File

SOURCE=.\dolfin4.wav
# End Source File
# Begin Source File

SOURCE=.\dolphin.x
# End Source File
# Begin Source File

SOURCE=.\DOUBL.wav
# End Source File
# Begin Source File

SOURCE=.\DOUBL2.wav
# End Source File
# Begin Source File

SOURCE=.\finlcurl.x
# End Source File
# Begin Source File

SOURCE=.\FOAM0.ppm
# End Source File
# Begin Source File

SOURCE=.\FOAM1.ppm
# End Source File
# Begin Source File

SOURCE=.\FOAM2.ppm
# End Source File
# Begin Source File

SOURCE=.\FOAM3.ppm
# End Source File
# Begin Source File

SOURCE=.\foam4.ppm
# End Source File
# Begin Source File

SOURCE=.\foam5.ppm
# End Source File
# Begin Source File

SOURCE=.\foam6.ppm
# End Source File
# Begin Source File

SOURCE=.\foam7.ppm
# End Source File
# Begin Source File

SOURCE=.\gameload.mds
# End Source File
# Begin Source File

SOURCE=.\gameov5.mds
# End Source File
# Begin Source File

SOURCE=.\GAMEOV7.wav
# End Source File
# Begin Source File

SOURCE=.\gameover.wav
# End Source File
# Begin Source File

SOURCE=.\gameovr2.mds
# End Source File
# Begin Source File

SOURCE=.\GAMEOVR3.wav
# End Source File
# Begin Source File

SOURCE=.\GAMEOVR6.wav
# End Source File
# Begin Source File

SOURCE=.\GROOVY.wav
# End Source File
# Begin Source File

SOURCE=.\GROOVY3.wav
# End Source File
# Begin Source File

SOURCE=.\GULLS.wav
# End Source File
# Begin Source File

SOURCE=.\helotrik.wav
# End Source File
# Begin Source File

SOURCE=.\HISCOR2.wav
# End Source File
# Begin Source File

SOURCE=.\HISCOR3.wav
# End Source File
# Begin Source File

SOURCE=.\hiscr2.mds
# End Source File
# Begin Source File

SOURCE=.\hiskor.mds
# End Source File
# Begin Source File

SOURCE=.\HITBREK.wav
# End Source File
# Begin Source File

SOURCE=.\HITBREK2.wav
# End Source File
# Begin Source File

SOURCE=.\HLGUY.ppm
# End Source File
# Begin Source File

SOURCE=.\hlshutr.ppm
# End Source File
# Begin Source File

SOURCE=.\hlxwalls.ppm
# End Source File
# Begin Source File

SOURCE=.\insane.wav
# End Source File
# Begin Source File

SOURCE=.\insane2.wav
# End Source File
# Begin Source File

SOURCE=.\lee.mds
# End Source File
# Begin Source File

SOURCE=.\lee.ppm
# End Source File
# Begin Source File

SOURCE=.\lee.x
# End Source File
# Begin Source File

SOURCE=.\leftbouy.x
# End Source File
# Begin Source File

SOURCE=.\leftwall.x
# End Source File
# Begin Source File

SOURCE=.\MANGLD3.wav
# End Source File
# Begin Source File

SOURCE=.\mountain.ppm
# End Source File
# Begin Source File

SOURCE=.\MUSTHURT.wav
# End Source File
# Begin Source File

SOURCE=.\Newav1.ppm
# End Source File
# Begin Source File

SOURCE=.\newav2.ppm
# End Source File
# Begin Source File

SOURCE=.\Newav3.ppm
# End Source File
# Begin Source File

SOURCE=.\Newav4.ppm
# End Source File
# Begin Source File

SOURCE=.\Newav5.ppm
# End Source File
# Begin Source File

SOURCE=.\Newav6.ppm
# End Source File
# Begin Source File

SOURCE=.\Newav7.ppm
# End Source File
# Begin Source File

SOURCE=.\Newav8.ppm
# End Source File
# Begin Source File

SOURCE=.\NEWROC2.wav
# End Source File
# Begin Source File

SOURCE=.\NEWROC3.wav
# End Source File
# Begin Source File

SOURCE=.\NEWROCK.wav
# End Source File
# Begin Source File

SOURCE=.\NXTYEAR.wav
# End Source File
# Begin Source File

SOURCE=.\OHH2.wav
# End Source File
# Begin Source File

SOURCE=.\OHH3.wav
# End Source File
# Begin Source File

SOURCE=.\oilleg.wav
# End Source File
# Begin Source File

SOURCE=.\oilleg2.wav
# End Source File
# Begin Source File

SOURCE=.\oilrig.wav
# End Source File
# Begin Source File

SOURCE=.\oilrig2.wav
# End Source File
# Begin Source File

SOURCE=.\oilrig2.x
# End Source File
# Begin Source File

SOURCE=.\options.ppm
# End Source File
# Begin Source File

SOURCE=.\ORBIT.wav
# End Source File
# Begin Source File

SOURCE=.\OUCH.wav
# End Source File
# Begin Source File

SOURCE=.\PEIR2.wav
# End Source File
# Begin Source File

SOURCE=.\pier.x
# End Source File
# Begin Source File

SOURCE=.\PIER3.wav
# End Source File
# Begin Source File

SOURCE=.\piermap.ppm
# End Source File
# Begin Source File

SOURCE=.\QUAD.wav
# End Source File
# Begin Source File

SOURCE=.\QUAD2.wav
# End Source File
# Begin Source File

SOURCE=.\REEDIK.wav
# End Source File
# Begin Source File

SOURCE=.\REEDIK2.wav
# End Source File
# Begin Source File

SOURCE=.\REEF3.wav
# End Source File
# Begin Source File

SOURCE=.\ritebouy.x
# End Source File
# Begin Source File

SOURCE=.\ritewall.x
# End Source File
# Begin Source File

SOURCE=.\ROCKdave.wav
# End Source File
# Begin Source File

SOURCE=.\rocks.x
# End Source File
# Begin Source File

SOURCE=.\sandy.mds
# End Source File
# Begin Source File

SOURCE=.\sandy.ppm
# End Source File
# Begin Source File

SOURCE=.\sandy.x
# End Source File
# Begin Source File

SOURCE=.\SCOOL2.wav
# End Source File
# Begin Source File

SOURCE=.\sflogo.ppm
# End Source File
# Begin Source File

SOURCE=.\sharkfin.x
# End Source File
# Begin Source File

SOURCE=.\sharkhed.x
# End Source File
# Begin Source File

SOURCE=.\shopguys.x
# End Source File
# Begin Source File

SOURCE=.\SKRK2.wav
# End Source File
# Begin Source File

SOURCE=.\splash2.wav
# End Source File
# Begin Source File

SOURCE=.\SPRAY3.wav
# End Source File
# Begin Source File

SOURCE=.\SPRAy4.wav
# End Source File
# Begin Source File

SOURCE=.\SPRAY7.wav
# End Source File
# Begin Source File

SOURCE=.\steamshi.wav
# End Source File
# Begin Source File

SOURCE=.\SURF2.wav
# End Source File
# Begin Source File

SOURCE=.\SURF3.wav
# End Source File
# Begin Source File

SOURCE=.\SURF4.wav
# End Source File
# Begin Source File

SOURCE=.\surfsign.ppm
# End Source File
# Begin Source File

SOURCE=.\thatch.ppm
# End Source File
# Begin Source File

SOURCE=.\thebeach.x
# End Source File
# Begin Source File

SOURCE=.\todd.mds
# End Source File
# Begin Source File

SOURCE=.\todd.ppm
# End Source File
# Begin Source File

SOURCE=.\todd.x
# End Source File
# Begin Source File

SOURCE=.\TRICK.wav
# End Source File
# Begin Source File

SOURCE=.\TRIK1.wav
# End Source File
# Begin Source File

SOURCE=.\TRIK2.wav
# End Source File
# Begin Source File

SOURCE=.\TRIK3.wav
# End Source File
# Begin Source File

SOURCE=.\TRIK4.wav
# End Source File
# Begin Source File

SOURCE=.\TRIK6.wav
# End Source File
# Begin Source File

SOURCE=.\TRIK7.wav
# End Source File
# Begin Source File

SOURCE=.\trik8.wav
# End Source File
# Begin Source File

SOURCE=.\trik9.wav
# End Source File
# Begin Source File

SOURCE=.\TRIPL2.wav
# End Source File
# Begin Source File

SOURCE=.\TRIPL3.wav
# End Source File
# Begin Source File

SOURCE=.\trophy.x
# End Source File
# Begin Source File

SOURCE=.\TUBE2.wav
# End Source File
# Begin Source File

SOURCE=.\ufo.wav
# End Source File
# Begin Source File

SOURCE=.\ufo.x
# End Source File
# Begin Source File

SOURCE=.\ufo1.wav
# End Source File
# Begin Source File

SOURCE=.\UFOdave.wav
# End Source File
# Begin Source File

SOURCE=.\UFOdave2.wav
# End Source File
# Begin Source File

SOURCE=.\ufomap.ppm
# End Source File
# Begin Source File

SOURCE=.\vanetc.ppm
# End Source File
# Begin Source File

SOURCE=.\vic.mds
# End Source File
# Begin Source File

SOURCE=.\vic.ppm
# End Source File
# Begin Source File

SOURCE=.\vic.x
# End Source File
# Begin Source File

SOURCE=.\WAGON.wav
# End Source File
# Begin Source File

SOURCE=.\WAVMIX2.wav
# End Source File
# Begin Source File

SOURCE=.\WIPE1.wav
# End Source File
# Begin Source File

SOURCE=.\WIPE3.wav
# End Source File
# Begin Source File

SOURCE=.\WIPE6.wav
# End Source File
# Begin Source File

SOURCE=.\WIPE8.wav
# End Source File
# Begin Source File

SOURCE=.\WRBEACH.ppm
# End Source File
# Begin Source File

SOURCE=.\WUSSY.wav
# End Source File
# Begin Source File

SOURCE=.\xtra.mds
# End Source File
# Begin Source File

SOURCE=.\xtra10.mds
# End Source File
# Begin Source File

SOURCE=.\xtra4.mds
# End Source File
# Begin Source File

SOURCE=.\xtra5.mds
# End Source File
# End Target
# End Project
# Section surf : {40286D50-D16F-11CF-8BEA-0080C6047964}
# 	0:8:Splash.h:C:\Jeremy\source\Splash.h
# 	0:10:Splash.cpp:C:\Jeremy\source\Splash.cpp
# 	1:11:IDB_SPLASH1:118
# 	2:10:ResHdrName:resource.h
# 	2:11:ProjHdrName:stdafx.h
# 	2:10:WrapperDef:_SPLASH_SCRN_
# 	2:12:SplClassName:CSplashWnd
# 	2:21:SplashScreenInsertKey:4.0
# 	2:10:HeaderName:Splash.h
# 	2:10:ImplemName:Splash.cpp
# 	2:7:BmpID16:IDB_SPLASH
# End Section
