# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=surf - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to surf - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "surf - Win32 Release" && "$(CFG)" != "surf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "surf.mak" CFG="surf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "surf - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "surf - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "surf - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "surf - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\surf.exe" "$(OUTDIR)\surf.pch"

CLEAN : 
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\Leroy.obj"
	-@erase "$(INTDIR)\LoadProgress.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Midistrm.obj"
	-@erase "$(INTDIR)\Mmio.obj"
	-@erase "$(INTDIR)\ShareExit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\surf.obj"
	-@erase "$(INTDIR)\surf.pch"
	-@erase "$(INTDIR)\surf.res"
	-@erase "$(INTDIR)\surfDoc.obj"
	-@erase "$(INTDIR)\surfView.obj"
	-@erase "$(INTDIR)\TrackSelect.obj"
	-@erase "$(INTDIR)\Wave.obj"
	-@erase "$(OUTDIR)\surf.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/surf.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/surf.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/surf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 d3drm.lib ddraw.lib winmm.lib dsound.lib dxguid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=d3drm.lib ddraw.lib winmm.lib dsound.lib dxguid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/surf.pdb" /machine:I386\
 /out:"$(OUTDIR)/surf.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\Leroy.obj" \
	"$(INTDIR)\LoadProgress.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Midistrm.obj" \
	"$(INTDIR)\Mmio.obj" \
	"$(INTDIR)\ShareExit.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\surf.obj" \
	"$(INTDIR)\surf.res" \
	"$(INTDIR)\surfDoc.obj" \
	"$(INTDIR)\surfView.obj" \
	"$(INTDIR)\TrackSelect.obj" \
	"$(INTDIR)\Wave.obj"

"$(OUTDIR)\surf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "surf - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\surf.exe" "$(OUTDIR)\surf.pch"

CLEAN : 
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\Leroy.obj"
	-@erase "$(INTDIR)\LoadProgress.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Midistrm.obj"
	-@erase "$(INTDIR)\Mmio.obj"
	-@erase "$(INTDIR)\ShareExit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\surf.obj"
	-@erase "$(INTDIR)\surf.pch"
	-@erase "$(INTDIR)\surf.res"
	-@erase "$(INTDIR)\surfDoc.obj"
	-@erase "$(INTDIR)\surfView.obj"
	-@erase "$(INTDIR)\TrackSelect.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Wave.obj"
	-@erase "$(OUTDIR)\surf.exe"
	-@erase "$(OUTDIR)\surf.ilk"
	-@erase "$(OUTDIR)\surf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/surf.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/surf.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/surf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 d3drm.lib ddraw.lib winmm.lib dsound.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=d3drm.lib ddraw.lib winmm.lib dsound.lib dxguid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/surf.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/surf.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\Leroy.obj" \
	"$(INTDIR)\LoadProgress.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Midistrm.obj" \
	"$(INTDIR)\Mmio.obj" \
	"$(INTDIR)\ShareExit.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\surf.obj" \
	"$(INTDIR)\surf.res" \
	"$(INTDIR)\surfDoc.obj" \
	"$(INTDIR)\surfView.obj" \
	"$(INTDIR)\TrackSelect.obj" \
	"$(INTDIR)\Wave.obj"

"$(OUTDIR)\surf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "surf - Win32 Release"
# Name "surf - Win32 Debug"

!IF  "$(CFG)" == "surf - Win32 Release"

!ELSEIF  "$(CFG)" == "surf - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\surf.cpp
DEP_CPP_SURF_=\
	"..\..\dxsdk\Sdk\Inc\d3d.h"\
	"..\..\dxsdk\Sdk\Inc\d3dcaps.h"\
	"..\..\dxsdk\Sdk\Inc\d3drm.h"\
	"..\..\dxsdk\Sdk\Inc\d3drmdef.h"\
	"..\..\dxsdk\Sdk\Inc\d3dtypes.h"\
	"..\..\dxsdk\Sdk\Inc\d3dvec.inl"\
	".\ddutil.h"\
	".\Leroy.h"\
	".\LoadProgress.h"\
	".\Mainfrm.h"\
	".\Midistrm.h"\
	".\Stdafx.h"\
	".\surf.h"\
	".\surfdoc.H"\
	".\surfview.H"\
	".\Wave.h"\
	{$(INCLUDE)}"\D3drmobj.h"\
	{$(INCLUDE)}"\D3drmwin.h"\
	
NODEP_CPP_SURF_=\
	"..\..\dxsdk\Sdk\Inc\d3dcom.h"\
	"..\..\dxsdk\Sdk\Inc\subwtype.h"\
	

"$(INTDIR)\surf.obj" : $(SOURCE) $(DEP_CPP_SURF_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\..\dxsdk\Sdk\Inc\d3d.h"\
	"..\..\dxsdk\Sdk\Inc\d3dcaps.h"\
	"..\..\dxsdk\Sdk\Inc\d3drm.h"\
	"..\..\dxsdk\Sdk\Inc\d3drmdef.h"\
	"..\..\dxsdk\Sdk\Inc\d3dtypes.h"\
	"..\..\dxsdk\Sdk\Inc\d3dvec.inl"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\D3drmobj.h"\
	{$(INCLUDE)}"\D3drmwin.h"\
	
NODEP_CPP_STDAF=\
	"..\..\dxsdk\Sdk\Inc\d3dcom.h"\
	"..\..\dxsdk\Sdk\Inc\subwtype.h"\
	

!IF  "$(CFG)" == "surf - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/surf.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\surf.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "surf - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/surf.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\surf.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\..\dxsdk\Sdk\Inc\d3d.h"\
	"..\..\dxsdk\Sdk\Inc\d3dcaps.h"\
	"..\..\dxsdk\Sdk\Inc\d3drm.h"\
	"..\..\dxsdk\Sdk\Inc\d3drmdef.h"\
	"..\..\dxsdk\Sdk\Inc\d3dtypes.h"\
	"..\..\dxsdk\Sdk\Inc\d3dvec.inl"\
	".\ddutil.h"\
	".\Leroy.h"\
	".\LoadProgress.h"\
	".\Mainfrm.h"\
	".\Midistrm.h"\
	".\Stdafx.h"\
	".\surf.h"\
	".\surfdoc.H"\
	".\surfview.H"\
	".\Wave.h"\
	{$(INCLUDE)}"\D3drmobj.h"\
	{$(INCLUDE)}"\D3drmwin.h"\
	
NODEP_CPP_MAINF=\
	"..\..\dxsdk\Sdk\Inc\d3dcom.h"\
	"..\..\dxsdk\Sdk\Inc\subwtype.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\surfDoc.cpp
DEP_CPP_SURFD=\
	".\Stdafx.h"\
	".\surf.h"\
	".\surfdoc.H"\
	

"$(INTDIR)\surfDoc.obj" : $(SOURCE) $(DEP_CPP_SURFD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\surfView.cpp
DEP_CPP_SURFV=\
	"..\..\dxsdk\Sdk\Inc\d3d.h"\
	"..\..\dxsdk\Sdk\Inc\d3dcaps.h"\
	"..\..\dxsdk\Sdk\Inc\d3drm.h"\
	"..\..\dxsdk\Sdk\Inc\d3drmdef.h"\
	"..\..\dxsdk\Sdk\Inc\d3dtypes.h"\
	"..\..\dxsdk\Sdk\Inc\d3dvec.inl"\
	".\ddutil.h"\
	".\Leroy.h"\
	".\LoadProgress.h"\
	".\Mainfrm.h"\
	".\Midistrm.h"\
	".\ShareExit.h"\
	".\Stdafx.h"\
	".\surf.h"\
	".\surfdoc.H"\
	".\surfview.H"\
	".\Wave.h"\
	{$(INCLUDE)}"\D3drmobj.h"\
	{$(INCLUDE)}"\D3drmwin.h"\
	
NODEP_CPP_SURFV=\
	"..\..\dxsdk\Sdk\Inc\d3dcom.h"\
	"..\..\dxsdk\Sdk\Inc\subwtype.h"\
	

"$(INTDIR)\surfView.obj" : $(SOURCE) $(DEP_CPP_SURFV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\surf.rc
DEP_RSC_SURF_R=\
	".\180-2.wav"\
	".\180.wav"\
	".\360-2.wav"\
	".\360.wav"\
	".\540-2.wav"\
	".\540.wav"\
	".\720-2.wav"\
	".\720.wav"\
	".\900-2.wav"\
	".\900.wav"\
	".\ALAINa\ALAIN.wav"\
	".\ALAINa\ALAINYELL.wav"\
	".\ALAINa\DUHH.wav"\
	".\ALAINa\FLUTTER.wav"\
	".\ALAINa\GRUNT2.wav"\
	".\ALAINa\GRUNT3.wav"\
	".\ALAINa\GRUNT4.wav"\
	".\ALAINa\HA!.wav"\
	".\ALAINa\heldtrk.wav"\
	".\ALAINa\NAWW.wav"\
	".\ALAINa\OOF.wav"\
	".\ALAINa\TUBE.wav"\
	".\ALAINa\WOOP.wav"\
	".\ALAINa\yell4.wav"\
	".\ALAINa\yell5.wav"\
	".\ALAINa\YOHAY.wav"\
	".\alana.mds"\
	".\Alana.ppm"\
	".\alana.x"\
	".\ALIEN2.wav"\
	".\alphabet.BMP"\
	".\AMB2.wav"\
	".\ANNOUNCER\ALAINA.wav"\
	".\ANNOUNCER\AREYOUSUR.wav"\
	".\ANNOUNCER\BUCKY.wav"\
	".\ANNOUNCER\Crowd3.wav"\
	".\ANNOUNCER\DISQUALIF.wav"\
	".\ANNOUNCER\DISQUALIF2.wav"\
	".\ANNOUNCER\GULL2.wav"\
	".\ANNOUNCER\HEATOVER.wav"\
	".\ANNOUNCER\HEATOVR2.wav"\
	".\ANNOUNCER\ISTHATWHAT.wav"\
	".\ANNOUNCER\LEE.wav"\
	".\ANNOUNCER\RUNOVER.wav"\
	".\ANNOUNCER\SANDY.wav"\
	".\ANNOUNCER\TODD.wav"\
	".\ANNOUNCER\ufinished.wav"\
	".\ANNOUNCER\VIC.wav"\
	".\BARREL.ppm"\
	".\barrel.x"\
	".\BARREL1.wav"\
	".\BARRELdave.wav"\
	".\BARRELdave3.wav"\
	".\blood3.ppm"\
	".\blood4.ppm"\
	".\blood5.ppm"\
	".\blood6.ppm"\
	".\blood7.ppm"\
	".\blood8.ppm"\
	".\bluber1.wav"\
	".\BOUY.wav"\
	".\bucky.mds"\
	".\BUCKY.ppm"\
	".\bucky.x"\
	".\bucky\BAHEY.wav"\
	".\bucky\BARK.wav"\
	".\bucky\BKYLAUF.wav"\
	".\bucky\BUCKY.wav"\
	".\bucky\BUCKYell.wav"\
	".\bucky\dropin.wav"\
	".\bucky\FREAK.wav"\
	".\bucky\GRUNT1.wav"\
	".\bucky\TAHOO.wav"\
	".\bucky\TUBED.wav"\
	".\bucky\UTAH.wav"\
	".\bucky\VICBRK.wav"\
	".\bucky\WEWHO.wav"\
	".\bucky\WEWHO2.wav"\
	".\bucky\YELL1.wav"\
	".\bucky\YELL3.wav"\
	".\buildall.ppm"\
	".\choic2.mds"\
	".\choiccn2.mds"\
	".\choiccon.mds"\
	".\choice3.mds"\
	".\collis1.wav"\
	".\collis2.wav"\
	".\cred2.mds"\
	".\crowd.wav"\
	".\CRUNCH.wav"\
	".\Csguy.ppm"\
	".\DOLFHIT.wav"\
	".\DOLFHIT2.wav"\
	".\dolfin3.wav"\
	".\dolfin4.wav"\
	".\dolphin.x"\
	".\DOLPHINdisturb.wav"\
	".\DOUBL.wav"\
	".\DOUBL2.wav"\
	".\finalsplash.BMP"\
	".\finlcurl.x"\
	".\FOAM0.ppm"\
	".\FOAM1.ppm"\
	".\FOAM2.ppm"\
	".\FOAM3.ppm"\
	".\foam4.ppm"\
	".\foam5.ppm"\
	".\foam6.ppm"\
	".\foam7.ppm"\
	".\gameload.mds"\
	".\gameov5.mds"\
	".\GAMEOV7.wav"\
	".\gameover.wav"\
	".\gameovr2.mds"\
	".\GAMEOVR3.wav"\
	".\GAMEOVR6.wav"\
	".\GROOVY.wav"\
	".\GROOVY3.wav"\
	".\GULLS.wav"\
	".\helotrik.wav"\
	".\HISCOR2.wav"\
	".\HISCOR3.wav"\
	".\hiscr2.mds"\
	".\hiskor.mds"\
	".\HITBREK.wav"\
	".\HITBREK2.wav"\
	".\HLGUY.ppm"\
	".\hlshutr.ppm"\
	".\hlxwalls.ppm"\
	".\indian.bmp"\
	".\insane.wav"\
	".\insane2.wav"\
	".\lee.mds"\
	".\lee.ppm"\
	".\lee.x"\
	".\LEEGROBANDIDO\123.wav"\
	".\LEEGROBANDIDO\gargle.wav"\
	".\LEEGROBANDIDO\growl.wav"\
	".\LEEGROBANDIDO\HOT DIG.wav"\
	".\LEEGROBANDIDO\hotdig2.wav"\
	".\LEEGROBANDIDO\HUM.wav"\
	".\LEEGROBANDIDO\ICOULDB.wav"\
	".\LEEGROBANDIDO\Laugh1.wav"\
	".\LEEGROBANDIDO\Laugh2.wav"\
	".\LEEGROBANDIDO\Laugh3.wav"\
	".\LEEGROBANDIDO\Laugh4.wav"\
	".\LEEGROBANDIDO\Laugh6.wav"\
	".\LEEGROBANDIDO\LEE.wav"\
	".\LEEGROBANDIDO\moan.wav"\
	".\LEEGROBANDIDO\ooh.wav"\
	".\LEEGROBANDIDO\yell1.wav"\
	".\LEEGROBANDIDO\yell2.wav"\
	".\LEEGROBANDIDO\yell3.wav"\
	".\LEEGROBANDIDO\YOWHAT.wav"\
	".\leftbouy.x"\
	".\leftwall.x"\
	".\logo.BMP"\
	".\MANGLD3.wav"\
	".\mountain.ppm"\
	".\MUSTHURT.wav"\
	".\nav.BMP"\
	".\Newav1.ppm"\
	".\newav2.ppm"\
	".\Newav3.ppm"\
	".\Newav4.ppm"\
	".\Newav5.ppm"\
	".\Newav6.ppm"\
	".\Newav7.ppm"\
	".\Newav8.ppm"\
	".\newave9jeremy.x"\
	".\newinterface.BMP"\
	".\NEWROC2.wav"\
	".\NEWROC3.wav"\
	".\NEWROCK.wav"\
	".\NXTYEAR.wav"\
	".\OHH2.wav"\
	".\OHH3.wav"\
	".\oilleg.wav"\
	".\oilleg2.wav"\
	".\oilrig.wav"\
	".\oilrig2.wav"\
	".\oilrig2.x"\
	".\options.ppm"\
	".\ORBIT.wav"\
	".\OUCH.wav"\
	".\PEIR2.wav"\
	".\pier.x"\
	".\PIER3.wav"\
	".\PIERaction.wav"\
	".\piermap.ppm"\
	".\QUAD.wav"\
	".\QUAD2.wav"\
	".\REEDIK.wav"\
	".\REEDIK2.wav"\
	".\REEF3.wav"\
	".\res\surf.rc2"\
	".\ritebouy.x"\
	".\ritewall.x"\
	".\ROCKdave.wav"\
	".\rocks.x"\
	".\sandmaster.ppm"\
	".\sandy.mds"\
	".\sandy.ppm"\
	".\sandy.x"\
	".\SANDY\EEK.wav"\
	".\SANDY\GRUNT1.wav"\
	".\SANDY\GRUNT5.wav"\
	".\SANDY\HIYA.wav"\
	".\SANDY\HIYA2.wav"\
	".\SANDY\LAUGH1.wav"\
	".\SANDY\LAUGH2.wav"\
	".\SANDY\SANDRAyell.wav"\
	".\SANDY\SANDY.wav"\
	".\SANDY\WAH.wav"\
	".\SANDY\WHOA.wav"\
	".\SANDY\WHOOPY.wav"\
	".\SANDY\YA.wav"\
	".\SANDY\yell1.wav"\
	".\SANDY\yell2.wav"\
	".\SANDY\yell3.wav"\
	".\SCOOL2.wav"\
	".\sflogo.ppm"\
	".\SHARKarama.wav"\
	".\SHARKarama2.wav"\
	".\sharkfin.x"\
	".\sharkhed.x"\
	".\shopguys.x"\
	".\SKRK+.wav"\
	".\SKRK2.wav"\
	".\spin_speed.bmp"\
	".\splash2.wav"\
	".\SPRAY3.wav"\
	".\SPRAy4.wav"\
	".\SPRAY7.wav"\
	".\spraydekl0.ppm"\
	".\spraydekl1.ppm"\
	".\spraydekl2.ppm"\
	".\spraydekl3.ppm"\
	".\spraydekl4.ppm"\
	".\spraydekl5.ppm"\
	".\spraydekl6.ppm"\
	".\spraydekl7.ppm"\
	".\steamshi.wav"\
	".\SURF2.wav"\
	".\SURF3.wav"\
	".\surf38.ico"\
	".\SURF4.wav"\
	".\surfsign.ppm"\
	".\surfsky.bmp"\
	".\thatch.ppm"\
	".\thebeach.x"\
	".\todd.mds"\
	".\todd.ppm"\
	".\todd.x"\
	".\TODDHEALER\BARRELD.wav"\
	".\TODDHEALER\HEALIT.wav"\
	".\TODDHEALER\HEEHAW.wav"\
	".\TODDHEALER\LAUGH.wav"\
	".\TODDHEALER\LAUGH2.wav"\
	".\TODDHEALER\LAUGH3.wav"\
	".\TODDHEALER\T GRUNT1.wav"\
	".\TODDHEALER\T YELL1.wav"\
	".\TODDHEALER\TODD1.wav"\
	".\TODDHEALER\TODD2.wav"\
	".\TODDHEALER\TYea2.wav"\
	".\TODDHEALER\TYeLL2.wav"\
	".\TODDHEALER\wipeyell.wav"\
	".\TRICK.wav"\
	".\TRIK1.wav"\
	".\TRIK2.wav"\
	".\TRIK3.wav"\
	".\TRIK4.wav"\
	".\TRIK6.wav"\
	".\TRIK7.wav"\
	".\trik8.wav"\
	".\trik9.wav"\
	".\TRIPL2.wav"\
	".\TRIPL3.wav"\
	".\trophy.x"\
	".\TUBE2.wav"\
	".\ufo.wav"\
	".\ufo.x"\
	".\ufo1.wav"\
	".\UFOdave.wav"\
	".\UFOdave2.wav"\
	".\ufomap.ppm"\
	".\vanetc.ppm"\
	".\vic.mds"\
	".\vic.ppm"\
	".\vic.x"\
	".\VICC\go.wav"\
	".\VICC\groan.wav"\
	".\VICC\groan2.wav"\
	".\VICC\laugh1.wav"\
	".\VICC\laugh2.wav"\
	".\VICC\vic2.wav"\
	".\VICC\WO.wav"\
	".\VICC\WO2.wav"\
	".\VICC\woop.wav"\
	".\VICC\WOW.wav"\
	".\VICC\WOW2.wav"\
	".\VICC\WOW3.wav"\
	".\VICC\yell2.wav"\
	".\VICC\yell3.wav"\
	".\VICC\YOWW.wav"\
	".\VICC\YOWW2.wav"\
	".\Vlaachos.bmp"\
	".\WAGON.wav"\
	".\watermaster.ppm"\
	".\wave1.bin"\
	".\WAVMIX2.wav"\
	".\WIPE1.wav"\
	".\WIPE3.wav"\
	".\WIPE6.wav"\
	".\WIPE8.wav"\
	".\WRBEACH.ppm"\
	".\WUSSY.wav"\
	".\xtra.mds"\
	".\xtra10.mds"\
	".\xtra4.mds"\
	".\xtra5.mds"\
	

"$(INTDIR)\surf.res" : $(SOURCE) $(DEP_RSC_SURF_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mmio.cpp
DEP_CPP_MMIO_=\
	".\MMIO.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Mmio.obj" : $(SOURCE) $(DEP_CPP_MMIO_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wave.cpp
DEP_CPP_WAVE_=\
	".\MMIO.h"\
	".\Stdafx.h"\
	".\Wave.h"\
	

"$(INTDIR)\Wave.obj" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddutil.cpp
DEP_CPP_DDUTI=\
	".\ddutil.h"\
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Midistrm.cpp
DEP_CPP_MIDIS=\
	".\Midistrm.h"\
	".\MMIO.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Midistrm.obj" : $(SOURCE) $(DEP_CPP_MIDIS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Leroy.cpp
DEP_CPP_LEROY=\
	".\Leroy.h"\
	".\Stdafx.h"\
	".\surf.h"\
	".\TrackSelect.h"\
	

"$(INTDIR)\Leroy.obj" : $(SOURCE) $(DEP_CPP_LEROY) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LoadProgress.cpp
DEP_CPP_LOADP=\
	".\LoadProgress.h"\
	".\Stdafx.h"\
	".\surf.h"\
	

"$(INTDIR)\LoadProgress.obj" : $(SOURCE) $(DEP_CPP_LOADP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TrackSelect.cpp
DEP_CPP_TRACK=\
	".\Stdafx.h"\
	".\surf.h"\
	".\TrackSelect.h"\
	

"$(INTDIR)\TrackSelect.obj" : $(SOURCE) $(DEP_CPP_TRACK) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ShareExit.cpp
DEP_CPP_SHARE=\
	".\ShareExit.h"\
	".\Stdafx.h"\
	".\surf.h"\
	

"$(INTDIR)\ShareExit.obj" : $(SOURCE) $(DEP_CPP_SHARE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
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
################################################################################
