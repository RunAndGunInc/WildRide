// surfView.h : interface of the CsurfView class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __D3DVIEW__
#define __D3DVIEW__

//#define NO_SURFERS // this makes it so that only 1 surfer is loaded
//#define SHAREWARE  // this is for the shareware version, where 3 are loaded
				   // and contest/network are disabled.
#define NO_VOODOO // not fully implemented

#include <MMSystem.h>
#include <DSound.h>
#include "midistrm.h"
#include <Dplay.h>

#include <ddraw.h>
#include <objbase.h>
//#include <initguid.h>
#include <d3drmwin.h>
#include <d3drmobj.h>
#include <math.h>
#include "ddutil.h"
#include "Leroy.h"
#include "LoadProgress.h"
//#include "NetCreate.h"
//#include "NetSelSession.h"
//#include "NetNames.h"

#include "surf.h"
#include "surfDoc.h"
#include "MainFrm.h"
#include "Wave.h"
#include "resource.h"

#define NUMFOAM 8
#define NUMBLOOD 6
#define PI 3.141592654
#define MAXCAMBUFFER 16 // keep this number even... or not.
#define MAXWAVEFRAME 10

#ifndef SHAREWARE
#define NUMSOUNDS 214
#else
#define NUMSOUNDS 138
#endif

#define D3DAPP_MAXMODES 16
#define MAX_NETWORK_DRIVERS 16
#define MAX_3D_DRIVERS 16
#define MAX_DD_DRIVERS 4
#define NUMSPRAY 8
#define NUMSONGS 20
#define NUM_INTR_POS 8
#define NUM_LETTERS 70
#define NUMTEXTURES 23
#define NUMEVENT 11

#define DFRAMEY0 (const float) 6264.353
#define DFRAMEY1 (const float) 5264.353
#define DFRAMEY2 (const float) 74.231
#define DFRAMEY3 (const float) 44.347
#define DFRAMEY4 (const float) 15.516
#define DFRAMEY5 (const float) -7.663
#define DFRAMEY6 (const float) -24.991
#define DFRAMEY7 (const float) -38.846
#define DFRAMEY8 (const float) -46.750
#define DFRAMEY9 (const float) -49.239
#define DFRAMEY10 (const float) -51.000
#define DFRAMEY11 (const float) -53.000

#define DFRAMEZ0 (const float) 418.87402
#define DFRAMEZ1 (const float) 418.87401
#define DFRAMEZ2 (const float) 418.874
#define DFRAMEZ3 (const float) 416.436
#define DFRAMEZ4 (const float) 408.612
#define DFRAMEZ5 (const float) 389.834
#define DFRAMEZ6 (const float) 366.047
#define DFRAMEZ7 (const float) 339.757
#define DFRAMEZ8 (const float) 310.918
#define DFRAMEZ9 (const float) 281.375
#define DFRAMEZ10 (const float) 251.687
#define DFRAMEZ11 (const float) 200.000

static HRESULT CALLBACK EnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID lpThat);
//static BOOL CALLBACK EnumDPCallback(LPGUID lpSPGuid, LPSTR lpFriendlyName,
//							DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpThat);
//static BOOL CALLBACK EnumDPSession(LPDPSESSIONDESC lpDPSGameDesc, LPVOID lpThat,
//							LPDWORD lpdwTimeOut, DWORD dwFlags);
//static BOOL CALLBACK EnumPlayersCallback(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName,
//							DWORD dwFlags, LPVOID lpThat);
static HRESULT CALLBACK Enum3DDrivers(LPGUID lpGuid, LPSTR lpDeviceDescription,
							LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc,
							LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpUserArg);

static HRESULT __cdecl loadTextures(char *name, LPVOID lpThat, LPDIRECT3DRMTEXTURE*tex);
BOOL WINAPI EnumDirectDraw(GUID FAR * lpGUID,
    LPSTR lpDriverDescription, LPSTR lpDriverName,
    LPVOID lpContext);

typedef struct _INTERFACE_TREE_TYPE {
	int			exit[3];
	BYTE		exit_control[3];
	int			move_time[3];
	int			rotate_time[3];
	int			nav_bar_frame;
	float		exit_rotate_offset[3];
	D3DVECTOR	position;
	D3DVECTOR	orientation;
}INTERFACE_TREE_TYPE;

/*
#define MSG_NEW_PLAYER 0x11
#define MSG_USED_CHARS 0x12
#define MSG_PLAYER_IN_USE 0x13
#define MSG_CHAR_SELECT 0x14
#define MSG_UPDATE_WAVE 0x15
#define MSG_ON_WAVE_POS 0x16
#define MSG_WIPE_OUT 0x17
#define MSG_HANGING_OUT 0x18

typedef struct _MSGNEWPLAYER {
	BYTE		MsgType;
}MSGNEWPLAYER, *LPMSGNEWPLAYER;

typedef struct _MSGUSEDCHARS {
	BYTE		MsgType;
	BOOL		AvailiableChars[6];
}MSGUSEDCHARS, *LPMSGUSEDCHARS;

typedef struct _MSGPLAYERINUSE {
	BYTE		MsgType;
}MSGPLAYERINUSE, *LPMSGPLAYERINUSE;

typedef struct _MSGCHARSELECT {
	BYTE		MsgType;
	int			SelectedChar;
}MSGCHARSELECT, *LPMSGCHARSELECT;

typedef struct _MSGUPDATEWAVE {
	BYTE		MsgType;
	float		WaveScale;
}MSGUPDATEWAVE, *LPMSGUPDATEWAVE;

typedef struct _MSGONWAVEPOS {
	BYTE		MsgType;
	int			Surfer;
	float		AnimateTime;
	int			WaveFrame;
	float		WaveFrameRatio;
	float		SurferPosX;
	D3DVECTOR	SurferOrientZ;
	D3DVECTOR	SurferOrientY;
}MSGONWAVEPOS, *LPMSGONWAVEPOS;

typedef struct _MSGWIPEOUT {
	BYTE		MsgType;
	int			Surfer;
	float		AnimateTime;
	D3DVECTOR	SurferPosition;
	D3DVECTOR	SurferOrientZ;
	D3DVECTOR	SurferOrientY;
}MSGWIPEOUT, *LPMSGWIPEOUT;

typedef struct _MSGHANGINGOUT {
	BYTE		MsgType;
	int			Surfer;
}MSGHANGINGOUT, *LPMSGHANGINGOUT;
*/

class CsurfView : public CView
{
//	LPDIRECTPLAY				lpDP;
	LPDIRECTDRAW				lpDD;
	LPDIRECT3DRMDEVICE			m_lpDev;
	LPDIRECT3DRMVIEWPORT		m_view;
	LPDIRECT3DRM				m_lprm;
	LPDIRECTDRAWCLIPPER			lpClipper;
	LPDIRECTDRAWSURFACE			lpFrontBuffer;
	LPDIRECTDRAWSURFACE			lpNavBar;
	LPDIRECTDRAWSURFACE			lpLogo;
	LPDIRECTDRAWSURFACE			lpBackBuffer;
    LPDIRECTDRAWSURFACE			lpZBuffer;
    LPDIRECTDRAWSURFACE			lpSkySource;
	LPDIRECTDRAWSURFACE			lpSpeedometer;
	LPDIRECTDRAWSURFACE			lpIntrBkg;
	LPDIRECTDRAWSURFACE			lpAlphabet;
	LPDIRECTDRAWSURFACE			lpHalfresBuffer;
	LPDIRECT3DRMTEXTURE			lpSprayMap[NUMSPRAY];

	D3DRMTEXTUREQUALITY			TextureFiltering;

	LPDIRECT3DRMANIMATIONSET	surf_animate[6];
	LPDIRECT3DRMANIMATIONSET	barrel_animate;
	LPDIRECT3DRMANIMATIONSET	leftbouy_animate;
	LPDIRECT3DRMANIMATIONSET	ritebouy_animate;
	LPDIRECT3DRMANIMATIONSET	sharkhead_animate;
	LPDIRECT3DRMANIMATIONSET	dolphin_animate;
	LPDIRECT3DRMANIMATIONSET	trophy_animate;
	LPDIRECT3DRMANIMATIONSET	shopguys_animate;

//	LPDIRECT3DRMMESHBUILDER		surf_builder[6];
	LPDIRECT3DRMMESHBUILDER		wave_builder;
	LPDIRECT3DRMMESHBUILDER		curlr_builder;
	LPDIRECT3DRMMESH			wave_mesh;
	LPDIRECT3DRMMESH			curlr_mesh;
	LPDIRECT3DRMTEXTURE			wave_map[8];
 	LPDIRECT3DRMTEXTURE			map[NUMTEXTURES];
	LPDIRECT3DRMFRAME			intro_scene;
	LPDIRECT3DRMFRAME			shopguys;
	LPDIRECT3DRMFRAME			m_scene;
	LPDIRECT3DRMFRAME			pier;
	LPDIRECT3DRMFRAME			oilrig;
	LPDIRECT3DRMFRAME			dolphin;
	LPDIRECT3DRMFRAME			trophy;
	LPDIRECT3DRMFRAME			rock;
	LPDIRECT3DRMFRAME			barrel;
	LPDIRECT3DRMFRAME			leftbouy;
	LPDIRECT3DRMFRAME			ritebouy;
	LPDIRECT3DRMFRAME			sharkfin;
	LPDIRECT3DRMFRAME			sharkhead;
	LPDIRECT3DRMFRAME			m_camera;
    LPDIRECT3DRMFRAME			wave;
    LPDIRECT3DRMFRAME			foam[NUMFOAM];
    LPDIRECT3DRMFRAME			blood[NUMBLOOD];
    LPDIRECT3DRMFRAME			ufo;
    LPDIRECT3DRMFRAME			curl_frame;
    LPDIRECT3DRMFRAME			beach_frame;
    LPDIRECT3DRMFRAME			spray[NUMSPRAY];
	LPDIRECT3DRMFRAME			surfer[6];
	LPDIRECT3DRMFRAME			child_of_the_wave;	
	LPDIRECT3DRMFRAME			light;
    LPDIRECT3DRMLIGHT			light1, light2;
	D3DVECTOR					camera_buffer[MAXCAMBUFFER+1];
	D3DVECTOR					frame_orient[MAXWAVEFRAME+1];
	CLoadProgress				LoadProgress;

    float					surfer_turn;
	float					surfer_velocity;
	float					surfer_speed; // start velocity
	float					surfer_max;
	float					surferstartpos_x;
	float					frame_y[MAXWAVEFRAME+2];
	float					frame_z[MAXWAVEFRAME+2];
	float					joy_center;
	float					joy_half;
	float					joy_y_center;
	float					joy_y_half;
	float					joy_up;
	float					joy_down;
	float					joy_left;
	float					joy_right;
	float					surfer_slide;
	float					rotate_sum;
	float					animate_time;
	float					curlpos_y;
	float					curlpos_z;
	float					curlpos_x;
	float					closeout_off;
	float					curlpos_off;
	float					foam_off;
	float					dolphintime;
	float					wydeltasc;
	float					wzdeltasc;
	float					dydeltasc;
	float					dzdeltasc;
	float					curl_width;

	int						lastp;
	int						splat_time;
	int						last_frame;
	int						letnum;
	int						change_frame[2];
	int						num_change;
	int						stat_turn[6];
	int						stat_speed[6];
	int						stat_max[6];
	int						stat_land[6];
	int						current_surfer;
	int						ModeAx;
	int						ModeAy;
	int						ModeBx;
	int						ModeBy;
	int						ModeCx;
	int						ModeCy;
	int			 			dwZBufferBitDepth;
	int						ModeNumber;
	int						ModeListW[D3DAPP_MAXMODES+1];
	int						ModeListH[D3DAPP_MAXMODES+1];
	int						NumModes;

//	int						NumNetwork;
//	int						NumSessions;
	int						Heat;
	int						gameovert;
//	int						SessionNumber;
//	int						NetworkNumber;
	int						EventNumber[NUMEVENT];
	int						MidiNum;
	int						EventTime[NUMEVENT];
	int						cam_min_z;
	int						cam_min_y;
	int						cam_min_x;
	int						lives;
	int						ConfirmationResponse;
	int						songs[NUMSONGS];
	int						hisurfer[6];
	int						hisurferc[6];
	int						contest_place[6];
	int						sharktime;
	int						scorenum;
	int						camera_type;
	int						trick;
	int						fullscreencountdown;
	int						last_camera;
	int						current_frame;
	float					game_time;
	int						board_condition;
	int						last_save;
	int						last_load;
	int						DolphinSplash;
	int						intube;
	float					fGameSpeed;

	BOOL					bPractice;
	BOOL					bScoreBlit;
	BOOL					bMusicRedundancyCheck;
	BOOL					bAutoCamera;
	BOOL					bOverPier;
	BOOL					bOverBreak;
	BOOL					bOverOilRig;
	BOOL					bFirstRun;
	BOOL					bOkGo;
	BOOL					bNoTextures;
	BOOL					bResizedSelect;
	BOOL					bFps;
	BOOL					bDrop;
	BOOL					bFirstSelect;
	BOOL					bCDMusic;
	BOOL					bSoundFxAllowed;
	BOOL					bSoundFx;
	BOOL					bTubeTuck;
	BOOL					bNaration;
	BOOL					bSurferSounds;
	BOOL					bNormalNavigation;
	BOOL					bWaveTextures;
	BOOL					bHalfres;
	BOOL					bConfirmation;
	BOOL					bSky;
	BOOL					bCloseOut;
	BOOL					bHorizon;
	BOOL					bShowErrors;
	BOOL					bTron;
	BOOL					bSpeedofish;
	BOOL					bBreakingWave;
	BOOL					bFoam;
	BOOL					bGore;
	BOOL					bMinimized;
	BOOL					bMaximized;
	BOOL					bSplat;
	BOOL					bPitch;
	BOOL					bUfo;
	BOOL					bUfoStop;
	BOOL					bUfoStop2;
	BOOL					bSummoned;
	BOOL					bCheatKeys;
	BOOL					bWipeout;
	BOOL					bGameOver;
	BOOL					bCharselect;
	BOOL					bJoystickExists;
	BOOL					bFullscreen;
	BOOL					bSecretTrack;
//	BOOL					firstd3dmode;
	BOOL					bAppActive;
	BOOL			        InitDirectSound();
	BOOL					InitDSBuffers();
	BOOL	                RestoreDSBuffers();
	BOOL					Whooshed;
	BOOL					bInContest[6];
	BOOL					bNotDroppedInYet;
//	BOOL					bOnlySoftRender;
	BOOL					bOnlySystemMemory;
	BOOL					bAppPaused;
//	BOOL					bAllowSize;
	BOOL					bContest;
	BOOL					bSprayOn;
	BOOL					bMIDIMusic;
	BOOL					bHiscore;
	BOOL					spray_used[NUMSPRAY];
	BOOL					GameServer;
//	BOOL					bNetworked;
	BOOL					bNoCollideCheck;
//	BOOL					bUsedChars[6];
	BOOL					bSharkAttack;

	BOOL					bWrongDisplayMode;

	unsigned long int		score;
	unsigned long int		numframes;
	unsigned long int		hiscore[6];
	unsigned long int		hiscorec[6];
	unsigned long int		contest_score[6];
	UINT					m_uiJoyStick;
    UINT					wCDDeviceID;
	char					hiname[6][9];
	char					hinamec[6][9];
	long					TotalVideoMemory;
    long					tempSurfX;
	long					tempCameraX;
//	RECT					rcClient;
	RECT					skysource;
    JOYCAPS					jcCaps;
	void				    CleanupDirectSound();

	float					total_ticks;
	int						num_ticks;
	int						prev_tick;
	int						this_tick;
	
//	LPGUID					lpNetworkGuid[MAX_NETWORK_DRIVERS];
//	char					SessionName[MAX_NETWORK_SESSIONS][32];
//	char					PlayerName[6][32];
	int						D3DDriver;
	int						LastD3DDriver;
	int						NumD3DDrivers;
	int						NumDDDrivers;
	int						CurrentDDDriver;
	int						LastDDDriver;
	GUID					DDGuid[MAX_DD_DRIVERS];
	LPGUID					lpDDGuid[MAX_DD_DRIVERS];
	char					lpDDDeviceName[MAX_DD_DRIVERS][32];
	GUID					D3DGuid[MAX_3D_DRIVERS];
	LPGUID					lpD3DGuid[MAX_3D_DRIVERS];
	char					lpD3DDeviceName[MAX_3D_DRIVERS][32];
	D3DDEVICEDESC			D3DDesc[MAX_3D_DRIVERS];
	LPD3DDEVICEDESC			lpD3DDesc[MAX_3D_DRIVERS];
	BOOL					bHardwareAccel[MAX_3D_DRIVERS];
	int						DDDriverNum[MAX_3D_DRIVERS];
	RECT					letter_rect[NUM_LETTERS];
	char					letters[NUM_LETTERS];
	char*					ConfirmationText;
	char*					names[6];
//	int						SessionPlayers[MAX_NETWORK_SESSIONS];
//	DPSESSIONDESC			SessionDesc[MAX_NETWORK_SESSIONS];
//	DPID					PlayerId[6];
//	int						ThisPlayer;
//	int						NumPlayers;
	float					spray_size[NUMSPRAY];
	DWORD					starttime;
	BYTE					extraCDsong;
	BYTE					lastCDtrack;

	INTERFACE_TREE_TYPE		InterfaceTree[NUM_INTR_POS];

	HANDLE					dphEvent;

	CMIDIStream*			MidiMusic[NUMSONGS];
  
protected: // create from serialization only
	CsurfView();
	DECLARE_DYNCREATE(CsurfView)

// Attributes
public:
	CsurfDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CsurfView)
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int CsurfView::randInt( int low, int high );
//	BOOL CsurfView::SetUpDirectPlay();
//	BOOL CsurfView::EnumDPCallFront(LPGUID lpSPGuid, LPSTR lpFriendlyName);
//	BOOL CsurfView::EnumDPSessionFront(LPDPSESSIONDESC lpDPSGameDesc);
//	BOOL CsurfView::EnumPlayersFront(DPID dpID, LPSTR lpFriendlyName);
	void CsurfView::ConnectNetwork();
	void CsurfView::UncheckNetwork();
	void CsurfView::ResetFps();
	void CsurfView::GoToFullscreen(BOOL bReleased);
	void CsurfView::ReSizeWindow();
	void CsurfView::ReleaseSomeStuff();
	void CsurfView::RestoreSurfaces();
	void CsurfView::UncheckCameraMenu();
	BOOL CsurfView::CreateDevice();
    HRESULT FindDevice(LPDIRECTDRAWSURFACE lpSurface);
    void CsurfView::Render();
    void CsurfView::RenderInterface(int navbarframe);
	void CsurfView::MoveSurfer();
	void CsurfView::UpdateCamera();
	void CsurfView::UpdateWorld();
	void CsurfView::WipeOut();
	void CsurfView::RestartSurfer();
	void CsurfView::ApplyStats();
	BOOL CsurfView::InitAll();
	BOOL CsurfView::DDInit();
//	BOOL CsurfView::D3DRMInit();
	BOOL CsurfView::DDSetMode();
	BOOL CsurfView::D3DRMSetMode();
	BOOL CsurfView::DDCreateSurfaces();
	void CsurfView::GetDDSurfaceDesc(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE lpDDSurf);
	BOOL CsurfView::CreateZBuffer(DWORD depth, DWORD memorytype);
	void CsurfView::CleanUpAndExit();
	void CsurfView::GetHardwareCaps();
	char* CsurfView::MyErrorToString(HRESULT error);
	BOOL CsurfView::EnumerateDisplayModes();
	HRESULT CsurfView::EnumDisplayModesCallFront(int ModeLW, int ModeLH);
	HRESULT CsurfView::loadTexturesCallFront(char *name, LPDIRECT3DRMTEXTURE*tex);
	void CsurfView::MoveWave();
	void CsurfView::AnimateWater();
	void CsurfView::UpdateSpeedometer();
	void CsurfView::SaveStats();
	void CsurfView::ModeUp();
	void CsurfView::ModeDown();
	void CsurfView::SelectCharacter();
	BOOL CsurfView::Fire(BOOL repeat);
	DWORD CsurfView::playCDTrack(BYTE bTrack);
	DWORD CsurfView::setUpCD();
	void CsurfView::stopCD();
	void CsurfView::OnMove();
	void CsurfView::FullscreenFailed(BOOL bReleased);
	void CsurfView::OnTronmode();
	void CsurfView::AddAnnounce(int announcement);
	void CsurfView::AddSurferSound(int announcement);
	HRESULT CsurfView::Enum3DCallFront(LPGUID lpGuid, LPSTR lpDeviceName, LPD3DDEVICEDESC lpDesc, BOOL Hardware);
	BOOL CsurfView::SetUpDrivers();
	void CsurfView::ChangeDriver(BOOL bReleased);
	void CsurfView::ReleaseSurfaces();
	void CsurfView::SaveScreenDimensions();
	void CsurfView::OnSize(UINT nType, int cx, int cy);
	HRESULT CsurfView::EnumDDCallFront(LPGUID lpGuid, LPSTR lpDeviceName);

	virtual ~CsurfView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL CsurfView::InitJoystick();

private:
  LPDIRECTSOUND			m_pDirectSound;
  LPDIRECTSOUNDBUFFER	m_pDSBuffer[NUMSOUNDS];

  // UINT                m_uiTimerID;

// Generated message map functions
protected:
	//{{AFX_MSG(CsurfView)
	afx_msg void OnPaint();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBreakingwave();
	afx_msg void OnHalfres();
	afx_msg void OnSkymap();
	afx_msg void OnWaveTextures();
	afx_msg void OnSpeedometerToggle();
	afx_msg void OnScoreToggle();
	afx_msg void OnBeachCamera();
	afx_msg void OnBeachCamera2();
	afx_msg void OnHelicopterCamera();
	afx_msg void OnMainCamera();
	afx_msg void OnRockVideoCamera();
	afx_msg void OnSatelliteCamera();
	afx_msg void OnTubeCamera();
	afx_msg void OnFullscreen0();
	afx_msg void OnFullscreen1();
	afx_msg void OnFullscreen2();
	afx_msg void OnFullscreen3();
	afx_msg void OnFullscreen4();
	afx_msg void OnFullscreen5();
	afx_msg void OnFullscreen6();
	afx_msg void OnFullscreen7();
	afx_msg void OnFullscreen8();
	afx_msg void OnFullscreen9();
	afx_msg void OnFullscreen10();
	afx_msg void OnFullscreen11();
	afx_msg void OnFullscreen12();
	afx_msg void OnFullscreen13();
	afx_msg void OnFullscreen14();
	afx_msg void OnFullscreen15();
	afx_msg void OnDriver0();
	afx_msg void OnDriver1();
	afx_msg void OnDriver2();
	afx_msg void OnDriver3();
	afx_msg void OnDriver4();
	afx_msg void OnDriver5();
	afx_msg void OnDriver6();
	afx_msg void OnDriver7();
	afx_msg void OnDriver8();
	afx_msg void OnDriver9();
	afx_msg void OnDriver10();
	afx_msg void OnDriver11();
	afx_msg void OnDriver12();
	afx_msg void OnDriver13();
	afx_msg void OnDriver14();
	afx_msg void OnDriver15();
	afx_msg void OnFps();
	afx_msg void OnViewHiscores();
	afx_msg void OnUfo();
	afx_msg void OnSpray();
	afx_msg void OnHorizon();
	afx_msg void OnShowErrors();
	afx_msg void OnMidiMusic();
	afx_msg void OnCdMusic();
	afx_msg void OnSoundFx();
	afx_msg void OnFoam();
//	afx_msg void OnHelpf();
	afx_msg void OnAutoCamera();
	afx_msg void OnNaration();
	afx_msg void OnGore();
	afx_msg void OnPractice();
	afx_msg void OnDestroy();
	afx_msg void OnSurferSounds();
	afx_msg void OnTextureFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in surfView.cpp
inline CsurfDoc* CsurfView::GetDocument()
   { return (CsurfDoc*)m_pDocument; }
#endif

char* LSTRRCHR( const char* lpString, int bChar );

#endif
