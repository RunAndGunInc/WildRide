// surfView.cpp : implementation of the CsurfView class
//
//	This is where I get down to some real nasty shit.
//
#include "stdafx.h"
//#define INITGUID
#include "surfView.h"
//#include "Gamespeed.h"

#ifdef SHAREWARE
#include "ShareExit.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LOADING			WM_USER
#define LOAD_MESSAGE	WM_USER+1
#define MIDI_STOPPED	WM_USER+2

//#pragma warning (disable: 4244)

// char select stuff

#define MOVE_RIGHT		0
#define MOVE_LEFT		1
#define MOVE_FORWARD	2
#define MOVE_BACK		3
#define MOVE_NONE		32

#define POS_START		0
#define POS_CENT_SIGN	1
#define POS_CENT_LIP	2
#define POS_CENT_SHACK	3
#define POS_DOOR_LIP	4
#define POS_INT_LIP		5
#define POS_SHACK		6
#define POS_SIGN		7
#define POS_NONE		32

#define EVENT_NONE		32

// back clipping plane

#define INTR_BACK		1000
#define GAME_BACK		4500

// render window for intro part

#define INTR_LEFT		ModeCx/32
#define INTR_TOP		ModeCy/32
#define INTR_RIGHT		ModeCx/2
#define INTR_BOTTOM		ModeCy*6/8

#define INTR_VLEFT		m_lpDev->GetWidth()/32
#define INTR_VTOP		m_lpDev->GetHeight()/32
#define INTR_VRIGHT		m_lpDev->GetWidth()*15/32+1
#define INTR_VBOTTOM	m_lpDev->GetHeight()*23/32+1

#define INTR_HLEFT		ModeCx/64
#define INTR_HTOP		ModeCy/64
#define INTR_HRIGHT		ModeCx/4
#define INTR_HBOTTOM	ModeCy*3/8

// move surfer engine stuff

#define ABOVE_WAVE		0
#define BELOW_WAVE		MAXWAVEFRAME+2
#define BETWEEN_FRAMES	MAXWAVEFRAME+3
#define ON_FRAMES		MAXWAVEFRAME+4
#define LIP_FRAME		3
#define GRAVITY			2
#define SINK			1.5

// sounds 

#define OCEANSND		0
#define UFOSND			1
#define SPLASH			2
#define WHOOSH			3
#define SEAGULL1		4
#define SEAGULL2		5
#define SINKING			6
#define	GAMEOVERS		7
#define SLALOM			8
#define STEAMSHIPWAVE	9
#define ROCKWAVE		10
#define ROCKWAVE2		11
#define PLIDWAVE		12
#define PLIDWAVE2		13
#define POSTWAVE		14
#define POSTWAVE2		15
#define BARRELWAVE		16
#define BARRELWAVE2		17
#define BOUYWAVE		18
#define BOUYWAVE2		19
#define DOLPHINWAVE		20
#define DOLPHINWAVE2	21
#define DOLPHINHITWAVE	22
#define DOLPHINHITWAVE2 23
#define BREAKHITWAVE	24
#define BREAKHITWAVE2	25
#define OILLEGWAVE		26
#define OILLEGWAVE2		27
#define OILRIGWAVE		28
#define OILRIGWAVE2		29
#define TUBEWAVE		30
#define LANDINGWAVE		31
#define SHARKWAVE		32
#define SHARKWAVE2		33
#define UFOSTOPWAVE		34
#define UFOCWAVE		35

#define S180SOUND1		36
#define S180SOUND2		37
#define S360SOUND1		38
#define S360SOUND2		39
#define S540SOUND1		40
#define S540SOUND2		41
#define S720SOUND1		42
#define S720SOUND2		43
#define S900SOUND1		44
#define S900SOUND2		45
#define INSANESOUND1	46
#define INSANESOUND2	47
#define DOUBLEINSANESOUND1	48
#define DOUBLEINSANESOUND2	49
#define TRIPLEINSANESOUND1	50
#define TRIPLEINSANESOUND2	51
#define QUADRUPLEINSANESOUND1	52
#define QUADRUPLEINSANESOUND2	53
#define RIDICULOUSINSANESOUND1	54
#define RIDICULOUSINSANESOUND2	55
#define SURF1		56
#define SURF2		57
#define SURF3		58
#define REEF1		59
#define WAGON		60
#define WIPEOUT		61
#define WIPEOUT2	62
#define WIPEOUT3	63
#define	WIPEOUT4	64
#define WUSSY		65
#define MUSTHURT	66
#define OUCH		67
#define MANGLED		68
#define AMBULANCE	69
#define SURFSCHOOL	70
#define ROCKDAVE	71
#define SHARKDAVE	72
#define SHARKDAVE2	73
#define BARRELDAVE	74
#define BARRELDAVE2	75
#define DOLPHINDISTURBANCE 76
#define ALIEN		77
#define ORBIT		78
#define OHH			79
#define OHH2		80
#define HISCORE1	81
#define HISCORE2	82
#define GAMEOVERDAVE  83
#define GAMEOVERDAVE2 84
#define GAMEOVERDAVE3 85
#define GROOVYTUBE    86
#define GROOVYTUBE2   87
#define PIERACTION	88
#define UFODAVE		89
#define UFODAVE2	99
#define TRICKSOUND1 91
#define TRICKSOUND2 92
#define TRICKSOUND3 93
#define TRICKSOUND4 94
#define TRICKSOUND5 95
#define TRICKSOUND6 96
#define TRICKSOUND7 97
#define TRICKSOUND8 98
#define TRICKSOUND9 99
#define TRICKSOUND10	100

#ifndef SHAREWARE

#define RUNOVERDAVE		101
#define RUNOVERDAVE2	102
#define HEATOVERDAVE	103
#define HEATOVERDAVE2	104
#define DISQUALIFYDAVE	105
#define DISQUALIFYDAVE2	106
#define DISQUALIFYDAVE3	107
#define USUREDAVE		108
#define USUREDAVE2		109
#define ALANADAVE		110
#define BUCKYDAVE		111
#define LEEDAVE			112
#define SANDYDAVE		113
#define TODDDAVE		114
#define VICDAVE			115

#define	WIPEOUTA1		116
#define	WIPEOUTA2		117
#define	WIPEOUTA3		118
#define	WIPEOUTA4		119
#define	WIPEOUTB1		120
#define	WIPEOUTB2		121
#define	WIPEOUTB3		122
#define	WIPEOUTB4		123
#define	WIPEOUTL1		124
#define	WIPEOUTL2		125
#define	WIPEOUTL3		126
#define	WIPEOUTL4		127
#define	WIPEOUTS1		128
#define	WIPEOUTS2		129
#define	WIPEOUTS3		130
#define	WIPEOUTT1		131
#define	WIPEOUTT2		132
#define	WIPEOUTV1		133
#define	WIPEOUTV2		134
#define	WIPEOUTV3		135
#define	WIPEOUTV4		136

#define TRICKA1			137
#define TRICKA2			138
#define TRICKA3			139
#define TRICKB1			140
#define TRICKB2			141
#define TRICKB3			142
#define TRICKL1			143
#define TRICKL2			144
#define TRICKL3			145
#define TRICKL4			146
#define TRICKS1			147
#define TRICKS2			148
#define TRICKS3			149
#define TRICKS4			150
#define TRICKT1			151
#define TRICKT2			152
#define TRICKV1			153
#define TRICKV2			154
#define TRICKV3			155

#define HOLDA1			156
#define HOLDB1			157
#define HOLDB2			158
#define HOLDL1			159
#define HOLDL2			160
#define HOLDS1			161
#define HOLDS2			162
#define HOLDT1			163
#define HOLDT2			164
#define HOLDV1			165
#define HOLDV2			166

#define S360A1			167
#define S360A2			168
#define S360B1			169
#define S360B2			170
#define S360L1			171
#define S360L2			172
#define S360S1			173
#define S360S2			174
#define S360T1			175
#define S360T2			176
#define S360V1			177
#define S360V2			178

#define TUBEA1			179
#define TUBEA2			180
#define TUBEB1			181
#define TUBEB2			182
#define TUBEL1			183
#define TUBEL2			184
#define TUBES1			185
#define TUBET1			186
#define TUBET2			187
#define TUBEV1			188
#define TUBEV2			189

#define DROPINA1		190
#define DROPINA2		191
#define DROPINA3		192
#define DROPINB1		193
#define DROPINB2		194
#define DROPINL1		195
#define DROPINL2		196
#define DROPINL3		197
#define DROPINS1		198
#define DROPINS2		199
#define DROPINS3		200
#define DROPINT1		201
#define DROPINT2		202
#define DROPINV1		203
#define DROPINV2		204
#define DROPINV3		205

#define INSANITYA1		206
#define INSANITYB1		207
#define INSANITYL1		208
#define INSANITYL2		209
#define INSANITYS1		210
#define INSANITYT1		211
#define INSANITYV1		212
#define UWONDAVE		213

#else

#define ALANADAVE		101
#define LEEDAVE			102
#define	WIPEOUTA1		103
#define	WIPEOUTA2		104
#define	WIPEOUTA3		105
#define	WIPEOUTA4		106
#define	WIPEOUTL1		107
#define	WIPEOUTL2		108
#define	WIPEOUTL3		109
#define	WIPEOUTL4		110

#define TRICKA1			111
#define TRICKA2			112
#define TRICKA3			113
#define TRICKL1			114
#define TRICKL2			115
#define TRICKL3			116
#define TRICKL4			117

#define HOLDA1			118
#define HOLDL1			119
#define HOLDL2			120

#define S360A1			121
#define S360A2			122
#define S360L1			123
#define S360L2			124

#define TUBEA1			125
#define TUBEA2			126
#define TUBEL1			127
#define TUBEL2			128

#define DROPINA1		129
#define DROPINA2		130
#define DROPINA3		131
#define DROPINL1		132
#define DROPINL2		133
#define DROPINL3		134

#define INSANITYA1		135
#define INSANITYL1		136
#define INSANITYL2		137

#endif

// announcer stuff

#define SOUND_PLAY NUMSOUNDS+1
#define SOUND_EMPTY NUMSOUNDS+2
#define SIZE_BUFFER 3
#define WIPEOUT_SOUND 0
#define TRICK_SOUND 1
#define HOLD_SOUND 2
#define S360_SOUND 3
#define TUBE_SOUND 4
#define DROPIN_SOUND 5
#define INSANITY_SOUND 6

// surfers & songs

#define ALANA     0
#define BUCKY     1
#define LEE       2
#define SANDY     3
#define TODD      4
#define VIC       5
#define NO_ONE    64

// cameras

#define MAIN_CAMERA			0
#define HELICOPTER_CAMERA	1
#define TUBE_CAMERA			2
#define BEACH_CAMERA		3
#define SATELLITE_CAMERA	4
#define ROCK_VIDEO_CAMERA	5
#define BEACH_CAMERA2		6

// menus

#define MENU_FILE		0
#define MENU_CAMERAS	1
#define MENU_DETAILS	2
#define MENU_AUDIO		3
#define MENU_NETWORK	4
#define MENU_FULLSCREEN 15
#define MENU_DRIVERS	16

#define NO_CONNECTION 32

// boundary

#define BOUNDARY		3000
#define PIER_SPEED		6
#define OBSTACLE_SPEED	8
#define UFO				6
#define PIER			7
#define POST			8
#define LEFTBOUY		9
#define RITEBOUY		10
#define BARREL			11
#define ROCK			12
#define DOLPHIN			13
#define TUBE			14
#define OILRIG			15
#define NO_COLLIDE		255

// event list

#define E_WAVE100	1
#define E_WAVE60	2
#define E_WAVE75	3
#define E_WAVE25	4
#define E_WAVE0		5
#define E_CURLSTART 6
#define E_CURLDROP	7
#define E_CLOSEOUT	8

// Confirmation flags

#define NO_CONFIRMATION  0
#define YES_RESPONSE 1
#define NO_RESPONSE  2

// WILDRIDE_GUID {6B37E260-DDD9-11cf-8BEA-0080C6047964}
DEFINE_GUID(WILDRIDE_GUID, 0x6b37e260, 0xddd9, 0x11cf, 0x8b, 0xea, 0x0, 0x80, 0xc6, 0x4, 0x79, 0x64);

/////////////////////////////////////////////////////////////////////////////
// CsurfView

IMPLEMENT_DYNCREATE(CsurfView, CView)

BEGIN_MESSAGE_MAP(CsurfView, CView)
	//{{AFX_MSG_MAP(CsurfView)
	ON_WM_PAINT()
//	ON_WM_SIZE()
	ON_WM_CHAR()
	ON_COMMAND(ID_BREAKINGWAVE, OnBreakingwave)
	ON_COMMAND(ID_HALFRES, OnHalfres)
	ON_COMMAND(ID_SKYMAP, OnSkymap)
	ON_COMMAND(ID_WAVE_TEXTURES, OnWaveTextures)
	ON_COMMAND(ID_SPEEDOMETER_TOGGLE, OnSpeedometerToggle)
	ON_COMMAND(ID_SCORETOGGLE, OnScoreToggle)
	ON_COMMAND(ID_SHOW_ERRORS, OnShowErrors)
	ON_COMMAND(ID_BEACH_CAMERA, OnBeachCamera)
	ON_COMMAND(ID_BEACH_CAMERA2, OnBeachCamera2)
	ON_COMMAND(ID_HELICOPTER_CAMERA, OnHelicopterCamera)
	ON_COMMAND(ID_MAIN_CAMERA, OnMainCamera)
	ON_COMMAND(ID_ROCK_VIDEO_CAMERA, OnRockVideoCamera)
	ON_COMMAND(ID_SATELLITE_CAMERA, OnSatelliteCamera)
	ON_COMMAND(ID_TUBE_CAMERA, OnTubeCamera)
	ON_COMMAND(ID_FULLSCREEN0, OnFullscreen0)
	ON_COMMAND(ID_FULLSCREEN1, OnFullscreen1)
	ON_COMMAND(ID_FULLSCREEN2, OnFullscreen2)
	ON_COMMAND(ID_FULLSCREEN3, OnFullscreen3)
	ON_COMMAND(ID_FULLSCREEN4, OnFullscreen4)
	ON_COMMAND(ID_FULLSCREEN5, OnFullscreen5)
	ON_COMMAND(ID_FULLSCREEN6, OnFullscreen6)
	ON_COMMAND(ID_FULLSCREEN7, OnFullscreen7)
	ON_COMMAND(ID_FULLSCREEN8, OnFullscreen8)
	ON_COMMAND(ID_FULLSCREEN9, OnFullscreen9)
	ON_COMMAND(ID_FULLSCREEN10, OnFullscreen10)
	ON_COMMAND(ID_FULLSCREEN11, OnFullscreen11)
	ON_COMMAND(ID_FULLSCREEN12, OnFullscreen12)
	ON_COMMAND(ID_FULLSCREEN13, OnFullscreen13)
	ON_COMMAND(ID_FULLSCREEN14, OnFullscreen14)
	ON_COMMAND(ID_FULLSCREEN15, OnFullscreen15)
	ON_COMMAND(ID_DRIVER0, OnDriver0)
	ON_COMMAND(ID_DRIVER1, OnDriver1)
	ON_COMMAND(ID_DRIVER2, OnDriver2)
	ON_COMMAND(ID_DRIVER3, OnDriver3)
	ON_COMMAND(ID_DRIVER4, OnDriver4)
	ON_COMMAND(ID_DRIVER5, OnDriver5)
	ON_COMMAND(ID_DRIVER6, OnDriver6)
	ON_COMMAND(ID_DRIVER7, OnDriver7)
	ON_COMMAND(ID_DRIVER8, OnDriver8)
	ON_COMMAND(ID_DRIVER9, OnDriver9)
	ON_COMMAND(ID_DRIVER10, OnDriver10)
	ON_COMMAND(ID_DRIVER11, OnDriver11)
	ON_COMMAND(ID_DRIVER12, OnDriver12)
	ON_COMMAND(ID_DRIVER13, OnDriver13)
	ON_COMMAND(ID_DRIVER14, OnDriver14)
	ON_COMMAND(ID_DRIVER15, OnDriver15)
	ON_COMMAND(ID_FPS, OnFps)
	ON_COMMAND(ID_VIEW_HISCORES, OnViewHiscores)
	ON_COMMAND(ID_UFO, OnUfo)
	ON_COMMAND(ID_SPRAY, OnSpray)
	ON_COMMAND(ID_HORIZON, OnHorizon)
	ON_COMMAND(ID_MIDI_MUSIC, OnMidiMusic)
	ON_COMMAND(ID_CD_MUSIC, OnCdMusic)
	ON_COMMAND(ID_SOUND_FX, OnSoundFx)
	ON_COMMAND(ID_FOAM, OnFoam)
//	ON_COMMAND(ID_HELPF, OnHelpf)
	ON_COMMAND(ID_AUTO_CAMERA, OnAutoCamera)
	ON_COMMAND(ID_NARATION, OnNaration)
	ON_COMMAND(ID_GORE, OnGore)
	ON_COMMAND(ID_PRACTICE, OnPractice)
	ON_WM_DESTROY()
	ON_COMMAND(ID_SURFER_SOUNDS, OnSurferSounds)
	ON_COMMAND(ID_TEXTURE_FILTER, OnTextureFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////
// CsurfView construction/destruction

CsurfView::CsurfView()
{
	m_pDirectSound=NULL;

    CsurfApp* pApp = (CsurfApp*)AfxGetApp();
    pApp->m_pView = this;

	names[ALANA]= "Alana";
	names[BUCKY]= "Bucky";
	names[LEE]	= "Lee  ";
	names[SANDY]= "Sandy";
	names[TODD] = "Todd ";
	names[VIC]	= "Vic  ";

	EventNumber[0] = E_CURLSTART;
	EventTime[0] = 80;
	EventNumber[1] = E_WAVE100;
	EventTime[1] = 141;
	EventNumber[2] = E_CLOSEOUT;
	EventTime[2] = 270;
	EventNumber[3] = E_CURLDROP;
	EventTime[3] = 300;
	EventNumber[4] = E_WAVE60;
	EventTime[4] = 500;
	EventNumber[5] = E_CURLSTART;
	EventTime[5] = 540;
	EventNumber[6] = E_WAVE75;
	EventTime[6] = 541;
	EventNumber[7] = E_CLOSEOUT;
	EventTime[7] = 690;
	EventNumber[8] = E_CURLDROP;
	EventTime[8] = 720;
	EventNumber[9] = E_WAVE25;
	EventTime[9] = 1160;
	EventNumber[10] = E_WAVE0;
	EventTime[10] = 1200;

 // Initialize member variables
	for (int i = 0; i < NUMSOUNDS; i++)
		m_pDSBuffer[i] = NULL;
	for (i = 0; i < NUMTEXTURES; i++)
		map[i] = NULL;

//	lpDP = NULL;
	lpFrontBuffer = NULL;
	lpBackBuffer = NULL;
	lpZBuffer = NULL;
	lpClipper = NULL;
	lpDD = NULL;
	lpSkySource = NULL;
	lpNavBar = NULL;
	lpLogo = NULL;
	lpSpeedometer = NULL;
	lpAlphabet = NULL;
	lpHalfresBuffer = NULL;
	lpIntrBkg = NULL;
	lpClipper = NULL;
	wave_builder = NULL;
//	dphEvent = NULL;
	curlr_builder = NULL;
	beach_frame = NULL;
	wave_mesh = NULL;
	curlr_mesh = NULL;
	for (i = 0; i < NUMFOAM; i++)
		foam[i] = NULL;
	for (i = 0; i < NUMBLOOD; i++)
		blood[i] = NULL;
	pier = NULL;
	oilrig = NULL;
	rock = NULL;
	dolphin = NULL;
	dolphin_animate = NULL;
	trophy = NULL;
	trophy_animate = NULL;
	shopguys_animate = NULL;
	shopguys = NULL;
	barrel = NULL;
	barrel_animate = NULL;
	leftbouy = NULL;
	leftbouy_animate = NULL;
	ritebouy = NULL;
	ritebouy_animate = NULL;
	sharkhead = NULL;
	sharkhead_animate = NULL;
	curl_frame = NULL;
	wave = NULL;
	ufo= NULL;
	light = NULL;
	light1 = NULL;
	light2 = NULL;
	for (i = 0; i < 8; i++)
	{
		wave_map[i] = NULL;
	}
	for (i = 0; i < 6; i++)
	{
		surf_animate[i] = NULL;
		surfer[i] = NULL;
//		bUsedChars[i] = FALSE;
		contest_place[i] = i;
		contest_score[i] = 0;
		bInContest[i] = TRUE;
	}
	child_of_the_wave = NULL;
	Heat = 0;
	board_condition = 0;
	bFirstRun = TRUE;
	m_scene = NULL;
	m_camera = NULL;
	m_view = NULL;
	m_lpDev = NULL;
	m_lprm = NULL;
	lpDD = NULL;
	for (i = 0; i < NUMSONGS; i++)
	{
		MidiMusic[i] = NULL;
	}
	for (i = 0; i < NUMSPRAY; i++)
	{
		spray[i] = NULL;
		lpSprayMap[i] = NULL;
	}

	dwZBufferBitDepth = 0;

	total_ticks = (const float)10;
	num_ticks = 10;

	curlpos_y = (const float)1;
	curlpos_z = (const float)413;
	curlpos_x = (const float)0;

	rotate_sum = (const float)0;
//	firstd3dmode = TRUE;
	bNormalNavigation = TRUE;
	bGameOver = FALSE;
	lives = 3;
	bCharselect = TRUE;
	bFirstSelect = TRUE;
//	bNetworked = FALSE;
	bOnlySystemMemory = FALSE;
	bMinimized = FALSE;
	bMaximized = FALSE;

//	bOnlySoftRender = FALSE;
	bAppPaused = FALSE;
	bUfo = FALSE;
	bHiscore = FALSE;
	bCheatKeys = FALSE;
	bConfirmation = FALSE;
	bSecretTrack = FALSE;
	bResizedSelect = FALSE;
	bContest = FALSE;
	bMusicRedundancyCheck = TRUE;
	NumD3DDrivers = 0;
	NumDDDrivers = 0;
	CurrentDDDriver = 0;
	LastDDDriver = 0;

	bOkGo = FALSE;
	bFps = FALSE;
	fullscreencountdown = 0;
	intube = 0;

	letnum = 0;
	ConfirmationResponse = NO_CONFIRMATION;

	lastCDtrack = 125;

	cam_min_z = 200;
	cam_min_y = 20;
	cam_min_x = -200;

// load ini file stuff

	last_camera = camera_type = GetPrivateProfileInt("Cameras","Type",BEACH_CAMERA,"wildride.ini");

	int getit = GetPrivateProfileInt("Cameras","Auto",1,"wildride.ini");
	if (getit > 0)
		bAutoCamera = TRUE;
	else
		bAutoCamera = FALSE;

	last_load = last_save = GetPrivateProfileInt("Details","LastSave",0,"wildride.ini");

	getit = GetPrivateProfileInt("Details","TextureFiltering",1,"wildride.ini");
	if (getit > 0)
		TextureFiltering = D3DRMTEXTURE_LINEAR;
	else
		TextureFiltering = D3DRMTEXTURE_NEAREST;

	getit = GetPrivateProfileInt("Details","Textures",1,"wildride.ini");
	if (getit > 0)
		bNoTextures = FALSE;
	else
		bNoTextures = TRUE;

	getit = GetPrivateProfileInt("Details","ShowErrors",0,"wildride.ini");
	if (getit > 0)
		bShowErrors = TRUE;
	else
		bShowErrors = FALSE;

	bFullscreen = FALSE;

	getit = GetPrivateProfileInt("Details","Spray",1,"wildride.ini");
	if (getit > 0)
		bSprayOn = TRUE;
	else
		bSprayOn = FALSE;

	getit = GetPrivateProfileInt("Details","PracticeMode",0,"wildride.ini");
	if (getit > 0)
		bPractice = TRUE;
	else
		bPractice = FALSE;


	getit = GetPrivateProfileInt("Details","HalfResolution",0,"wildride.ini");
	if (getit > 0)
		bHalfres = TRUE;
	else
		bHalfres = FALSE;

	getit = GetPrivateProfileInt("Details","WaveMaps",1,"wildride.ini");
	if (getit > 0)
	{
		bWaveTextures = TRUE;
	}
	else
		bWaveTextures = FALSE;

	getit = GetPrivateProfileInt("Details","SkyMap",1,"wildride.ini");
	if (getit > 0)
		bSky = TRUE;
	else
		bSky = FALSE;

	getit = GetPrivateProfileInt("Details","Horizon",0,"wildride.ini");
	if (getit > 0)
		bHorizon = TRUE;
	else
		bHorizon = FALSE;

	getit = GetPrivateProfileInt("Details","Speed-O-Fish",1,"wildride.ini");
	if (getit > 0)
		bSpeedofish = TRUE;
	else
		bSpeedofish = FALSE;

	getit = GetPrivateProfileInt("Details","ScoreDisplay",1,"wildride.ini");
	if (getit > 0)
		bScoreBlit = TRUE;
	else
		bScoreBlit = FALSE;

	getit = GetPrivateProfileInt("Details","BreakingWave",1,"wildride.ini");
	if (getit > 0)
		bBreakingWave = TRUE;
	else
		bBreakingWave = FALSE;

	getit = GetPrivateProfileInt("Details","Foam",1,"wildride.ini");
	if (getit > 0)
		bFoam = TRUE;
	else
		bFoam = FALSE;

	D3DDriver = GetPrivateProfileInt("Details","D3DDriver",0,"wildride.ini");
	LastD3DDriver = D3DDriver;

	getit = GetPrivateProfileInt("Details","Gore",1,"wildride.ini");
	if (getit > 0)
		bGore = TRUE;
	else
		bGore = FALSE;

	bTron = FALSE;

	hiscore[0] = GetPrivateProfileInt("HiScores","score0",30000,"wildride.ini");
	hiscore[1] = GetPrivateProfileInt("HiScores","score1",25000,"wildride.ini");
	hiscore[2] = GetPrivateProfileInt("HiScores","score2",20000,"wildride.ini");
	hiscore[3] = GetPrivateProfileInt("HiScores","score3",15000,"wildride.ini");
	hiscore[4] = GetPrivateProfileInt("HiScores","score4",10000,"wildride.ini");
	hiscore[5] = GetPrivateProfileInt("HiScores","score5",5000,"wildride.ini");
	GetPrivateProfileString("HiScores","name0","Bucky",hiname[0],8,"wildride.ini");
	GetPrivateProfileString("HiScores","name1","Sandy",hiname[1],8,"wildride.ini");
	GetPrivateProfileString("HiScores","name2","Todd",hiname[2],8,"wildride.ini");
	GetPrivateProfileString("HiScores","name3","Alana",hiname[3],8,"wildride.ini");
	GetPrivateProfileString("HiScores","name4","Vic",hiname[4],8,"wildride.ini");
	GetPrivateProfileString("HiScores","name5","Lee",hiname[5],8,"wildride.ini");
	hisurfer[0] = GetPrivateProfileInt("HiScores","surfer0",BUCKY,"wildride.ini");
	hisurfer[1] = GetPrivateProfileInt("HiScores","surfer1",SANDY,"wildride.ini");
	hisurfer[2] = GetPrivateProfileInt("HiScores","surfer2",TODD,"wildride.ini");
	hisurfer[3] = GetPrivateProfileInt("HiScores","surfer3",ALANA,"wildride.ini");
	hisurfer[4] = GetPrivateProfileInt("HiScores","surfer4",VIC,"wildride.ini");
	hisurfer[5] = GetPrivateProfileInt("HiScores","surfer5",LEE,"wildride.ini");

#ifndef SHAREWARE
	hiscorec[0] = GetPrivateProfileInt("ContestHiScore","score0",80000,"wildride.ini");
	hiscorec[1] = GetPrivateProfileInt("ContestHiScore","score1",70000,"wildride.ini");
	hiscorec[2] = GetPrivateProfileInt("ContestHiScore","score2",60000,"wildride.ini");
	hiscorec[3] = GetPrivateProfileInt("ContestHiScore","score3",50000,"wildride.ini");
	hiscorec[4] = GetPrivateProfileInt("ContestHiScore","score4",40000,"wildride.ini");
	hiscorec[5] = GetPrivateProfileInt("ContestHiScore","score5",30000,"wildride.ini");
	GetPrivateProfileString("ContestHiScore","name0","bucky",hinamec[0],8,"wildride.ini");
	GetPrivateProfileString("ContestHiScore","name1","sandy",hinamec[1],8,"wildride.ini");
	GetPrivateProfileString("ContestHiScore","name2","todd",hinamec[2],8,"wildride.ini");
	GetPrivateProfileString("ContestHiScore","name3","alana",hinamec[3],8,"wildride.ini");
	GetPrivateProfileString("ContestHiScore","name4","vic",hinamec[4],8,"wildride.ini");
	GetPrivateProfileString("ContestHiScore","name5","lee",hinamec[5],8,"wildride.ini");
	hisurferc[0] = GetPrivateProfileInt("ContestHiScore","surfer0",BUCKY,"wildride.ini");
	hisurferc[1] = GetPrivateProfileInt("ContestHiScore","surfer1",SANDY,"wildride.ini");
	hisurferc[2] = GetPrivateProfileInt("ContestHiScore","surfer2",TODD,"wildride.ini");
	hisurferc[3] = GetPrivateProfileInt("ContestHiScore","surfer3",ALANA,"wildride.ini");
	hisurferc[4] = GetPrivateProfileInt("ContestHiScore","surfer4",VIC,"wildride.ini");
	hisurferc[5] = GetPrivateProfileInt("ContestHiScore","surfer5",LEE,"wildride.ini");
#endif
#ifndef NO_SURFERS
	current_surfer = NO_ONE;
#else
	current_surfer = BUCKY;
#endif

	MidiMusic[0] = new CMIDIStream(
		IDR_LOADMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[1] = new CMIDIStream(
		IDR_ALANAMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[2] = new CMIDIStream(
		IDR_BUCKYMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[3] = new CMIDIStream(
		IDR_LEEMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[4] = new CMIDIStream(
		IDR_SANDYMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[5] = new CMIDIStream(
		IDR_TODDMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[6] = new CMIDIStream(
		IDR_VICMIDS, 
		GetModuleHandle(NULL));
	MidiMusic[7] = new CMIDIStream(
		IDR_CHOICEMIDS1, 
		GetModuleHandle(NULL));
	MidiMusic[8] = new CMIDIStream(
		IDR_CHOICEMIDS2, 
		GetModuleHandle(NULL));
	MidiMusic[9] = new CMIDIStream(
		IDR_CHOICECONTESTMIDS1, 
		GetModuleHandle(NULL));
	MidiMusic[10] = new CMIDIStream(
		IDR_CHOICECONTESTMIDS2, 
		GetModuleHandle(NULL));
	MidiMusic[11] = new CMIDIStream(
		IDR_GAMEOVERMIDS1, 
		GetModuleHandle(NULL));
	MidiMusic[12] = new CMIDIStream(
		IDR_GAMEOVERMIDS2, 
		GetModuleHandle(NULL));
	MidiMusic[13] = new CMIDIStream(
		IDR_HISCOREMIDS1, 
		GetModuleHandle(NULL));
	MidiMusic[14] = new CMIDIStream(
		IDR_HISCOREMIDS2, 
		GetModuleHandle(NULL));
	MidiMusic[15] = new CMIDIStream(
		IDR_XTRAMIDS1, 
		GetModuleHandle(NULL));
	MidiMusic[16] = new CMIDIStream(
		IDR_XTRAMIDS2, 
		GetModuleHandle(NULL));
	MidiMusic[17] = new CMIDIStream(
		IDR_XTRAMIDS3, 
		GetModuleHandle(NULL));
	MidiMusic[18] = new CMIDIStream(
		IDR_XTRAMIDS4, 
		GetModuleHandle(NULL));
	MidiMusic[19] = new CMIDIStream(
		IDR_XTRAMIDS5, 
		GetModuleHandle(NULL));

#ifdef SHAREWARE
	getit = GetPrivateProfileInt("Audio","MIDIMusic",1,"wildride.ini");
#else
	getit = GetPrivateProfileInt("Audio","MIDIMusic",0,"wildride.ini");
#endif
	if (getit > 0)
	{
		bMIDIMusic = TRUE;
	}
	else
		bMIDIMusic = FALSE;

#ifdef SHAREWARE
	getit = GetPrivateProfileInt("Audio","CDMusic",0,"wildride.ini");
#else
	getit = GetPrivateProfileInt("Audio","CDMusic",1,"wildride.ini");
#endif
	if (getit > 0)
	{
		bCDMusic = TRUE;
		bMIDIMusic = FALSE;
	}
	else
		bCDMusic = FALSE;

	getit = GetPrivateProfileInt("Audio","SoundFx",1,"wildride.ini");
	if (getit > 0)
	{
		bSoundFx = TRUE;
	}
	else
		bSoundFx = FALSE;

	getit = GetPrivateProfileInt("Audio","Naration",1,"wildride.ini");
	if (getit > 0)
	{
		bNaration = TRUE;
	}
	else
		bNaration = FALSE;

	getit = GetPrivateProfileInt("Audio","SurferSounds",1,"wildride.ini");
	if (getit > 0)
	{
		bSurferSounds = TRUE;
	}
	else
		bSurferSounds = FALSE;

	getit = GetPrivateProfileInt("Audio","SoundFxAllowed",1,"wildride.ini");
	if (getit > 0)
	{
		bSoundFxAllowed = TRUE;
	}
	else
	{
		bSoundFxAllowed = FALSE;
		bSoundFx = FALSE;
		bNaration = FALSE;
		bSurferSounds = FALSE;
	}

	// Set up the joystick, dammit

	bJoystickExists = InitJoystick();

	InterfaceTree[POS_START].exit[0] = POS_CENT_SIGN;
	InterfaceTree[POS_START].exit[1] = POS_NONE;
	InterfaceTree[POS_START].exit[2] = POS_NONE;
	InterfaceTree[POS_START].exit_control[0] = MOVE_FORWARD;
	InterfaceTree[POS_START].exit_control[1] = MOVE_NONE;
	InterfaceTree[POS_START].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_START].exit_rotate_offset[0] = (const float)PI;
	InterfaceTree[POS_START].exit_rotate_offset[1] = (const float)0;
	InterfaceTree[POS_START].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_START].move_time[0] = 20;
	InterfaceTree[POS_START].move_time[1] = 10;
	InterfaceTree[POS_START].move_time[2] = 10;
	InterfaceTree[POS_START].rotate_time[0] = 20;
	InterfaceTree[POS_START].rotate_time[1] = 10;
	InterfaceTree[POS_START].rotate_time[2] = 10;
	InterfaceTree[POS_START].position.x = (const float)73.1526;
	InterfaceTree[POS_START].position.y = (const float)45;
	InterfaceTree[POS_START].position.z = (const float)-583.642;
	InterfaceTree[POS_START].orientation.x = (const float)-0.0702940;
	InterfaceTree[POS_START].orientation.y = (const float)0;
	InterfaceTree[POS_START].orientation.z = (const float)0.997532;
	InterfaceTree[POS_START].nav_bar_frame = 2;

	InterfaceTree[POS_CENT_SIGN].exit[0] = POS_CENT_LIP;
	InterfaceTree[POS_CENT_SIGN].exit[1] = POS_SIGN;
	InterfaceTree[POS_CENT_SIGN].exit[2] = POS_CENT_SHACK;
	InterfaceTree[POS_CENT_SIGN].exit_control[0] = MOVE_LEFT;
	InterfaceTree[POS_CENT_SIGN].exit_control[1] = MOVE_FORWARD;
	InterfaceTree[POS_CENT_SIGN].exit_control[2] = MOVE_RIGHT;
	InterfaceTree[POS_CENT_SIGN].exit_rotate_offset[0] = (const float)-PI;
	InterfaceTree[POS_CENT_SIGN].exit_rotate_offset[1] = (const float)-PI;
	InterfaceTree[POS_CENT_SIGN].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_CENT_SIGN].move_time[0] = 6;
	InterfaceTree[POS_CENT_SIGN].move_time[1] = 20;
	InterfaceTree[POS_CENT_SIGN].move_time[2] = 6;
	InterfaceTree[POS_CENT_SIGN].rotate_time[0] = 6;
	InterfaceTree[POS_CENT_SIGN].rotate_time[1] = 20;
	InterfaceTree[POS_CENT_SIGN].rotate_time[2] = 6;
	InterfaceTree[POS_CENT_SIGN].position.x = (const float)9.19562;
	InterfaceTree[POS_CENT_SIGN].position.y = (const float)45;
	InterfaceTree[POS_CENT_SIGN].position.z = (const float)-77.3954;
	InterfaceTree[POS_CENT_SIGN].orientation.x = (const float)0.0296437;
	InterfaceTree[POS_CENT_SIGN].orientation.y = (const float)0;
	InterfaceTree[POS_CENT_SIGN].orientation.z = (const float)0.999562;
	InterfaceTree[POS_CENT_SIGN].nav_bar_frame = 3;

	InterfaceTree[POS_CENT_LIP].exit[0] = POS_DOOR_LIP;
	InterfaceTree[POS_CENT_LIP].exit[1] = POS_CENT_SIGN;
	InterfaceTree[POS_CENT_LIP].exit[2] = POS_NONE;
	InterfaceTree[POS_CENT_LIP].exit_control[0] = MOVE_FORWARD;
	InterfaceTree[POS_CENT_LIP].exit_control[1] = MOVE_RIGHT;
	InterfaceTree[POS_CENT_LIP].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_CENT_LIP].exit_rotate_offset[0] = (const float)0;
	InterfaceTree[POS_CENT_LIP].exit_rotate_offset[1] = (const float)PI;
	InterfaceTree[POS_CENT_LIP].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_CENT_LIP].move_time[0] = 20;
	InterfaceTree[POS_CENT_LIP].move_time[1] = 6;
	InterfaceTree[POS_CENT_LIP].move_time[2] = 10;
	InterfaceTree[POS_CENT_LIP].rotate_time[0] = 20;
	InterfaceTree[POS_CENT_LIP].rotate_time[1] = 6;
	InterfaceTree[POS_CENT_LIP].rotate_time[2] = 10;
	InterfaceTree[POS_CENT_LIP].position.x = (const float)9.19562;
	InterfaceTree[POS_CENT_LIP].position.y = (const float)45;
	InterfaceTree[POS_CENT_LIP].position.z = (const float)-77.3954;
	InterfaceTree[POS_CENT_LIP].orientation.x = (const float)-0.539929;
	InterfaceTree[POS_CENT_LIP].orientation.y = (const float)0;
	InterfaceTree[POS_CENT_LIP].orientation.z = (const float)0.841712;
	InterfaceTree[POS_CENT_LIP].nav_bar_frame = 0;

	InterfaceTree[POS_CENT_SHACK].exit[0] = POS_SHACK;
	InterfaceTree[POS_CENT_SHACK].exit[1] = POS_CENT_SIGN;
	InterfaceTree[POS_CENT_SHACK].exit[2] = POS_NONE;
	InterfaceTree[POS_CENT_SHACK].exit_control[0] = MOVE_FORWARD;
	InterfaceTree[POS_CENT_SHACK].exit_control[1] = MOVE_LEFT;
	InterfaceTree[POS_CENT_SHACK].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_CENT_SHACK].exit_rotate_offset[0] = (const float)0;
	InterfaceTree[POS_CENT_SHACK].exit_rotate_offset[1] = (const float)0;
	InterfaceTree[POS_CENT_SHACK].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_CENT_SHACK].move_time[0] = 20;
	InterfaceTree[POS_CENT_SHACK].move_time[1] = 6;
	InterfaceTree[POS_CENT_SHACK].move_time[2] = 10;
	InterfaceTree[POS_CENT_SHACK].rotate_time[0] = 20;
	InterfaceTree[POS_CENT_SHACK].rotate_time[1] = 6;
	InterfaceTree[POS_CENT_SHACK].rotate_time[2] = 10;
	InterfaceTree[POS_CENT_SHACK].position.x = (const float)9.19562;
	InterfaceTree[POS_CENT_SHACK].position.y = (const float)45;
	InterfaceTree[POS_CENT_SHACK].position.z = (const float)-77.3954;
	InterfaceTree[POS_CENT_SHACK].orientation.x = (const float)0.737694;
	InterfaceTree[POS_CENT_SHACK].orientation.y = (const float)0;
	InterfaceTree[POS_CENT_SHACK].orientation.z = (const float)0.675136;
	InterfaceTree[POS_CENT_SHACK].nav_bar_frame = 4;

	InterfaceTree[POS_DOOR_LIP].exit[0] = POS_INT_LIP;
	InterfaceTree[POS_DOOR_LIP].exit[1] = POS_CENT_SIGN;
	InterfaceTree[POS_DOOR_LIP].exit[2] = POS_NONE;
	InterfaceTree[POS_DOOR_LIP].exit_control[0] = MOVE_RIGHT;
	InterfaceTree[POS_DOOR_LIP].exit_control[1] = MOVE_BACK;
	InterfaceTree[POS_DOOR_LIP].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_DOOR_LIP].exit_rotate_offset[0] = (const float)0;
	InterfaceTree[POS_DOOR_LIP].exit_rotate_offset[1] = (const float)PI;
	InterfaceTree[POS_DOOR_LIP].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_DOOR_LIP].move_time[0] = 10;
	InterfaceTree[POS_DOOR_LIP].move_time[1] = 20;
	InterfaceTree[POS_DOOR_LIP].move_time[2] = 10;
	InterfaceTree[POS_DOOR_LIP].rotate_time[0] = 10;
	InterfaceTree[POS_DOOR_LIP].rotate_time[1] = 20;
	InterfaceTree[POS_DOOR_LIP].rotate_time[2] = 10;
	InterfaceTree[POS_DOOR_LIP].position.x = (const float)-139.520;
	InterfaceTree[POS_DOOR_LIP].position.y = (const float)45;
	InterfaceTree[POS_DOOR_LIP].position.z = (const float)57.1743;
	InterfaceTree[POS_DOOR_LIP].orientation.x = (const float)-0.795828;
	InterfaceTree[POS_DOOR_LIP].orientation.y = (const float)0;
	InterfaceTree[POS_DOOR_LIP].orientation.z = (const float)0.605550;
	InterfaceTree[POS_DOOR_LIP].nav_bar_frame = 1;
		
	InterfaceTree[POS_INT_LIP].exit[0] = POS_DOOR_LIP;
	InterfaceTree[POS_INT_LIP].exit[1] = POS_NONE;//POS_CENT_SIGN;
	InterfaceTree[POS_INT_LIP].exit[2] = POS_NONE;
	InterfaceTree[POS_INT_LIP].exit_control[0] = MOVE_LEFT;
	InterfaceTree[POS_INT_LIP].exit_control[1] = MOVE_NONE;//MOVE_RIGHT;
	InterfaceTree[POS_INT_LIP].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_INT_LIP].exit_rotate_offset[0] = (const float)0;
	InterfaceTree[POS_INT_LIP].exit_rotate_offset[1] = (const float)0;
	InterfaceTree[POS_INT_LIP].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_INT_LIP].move_time[0] = 10;
	InterfaceTree[POS_INT_LIP].move_time[1] = 10;//20;
	InterfaceTree[POS_INT_LIP].move_time[2] = 10;
	InterfaceTree[POS_INT_LIP].rotate_time[0] = 10;
	InterfaceTree[POS_INT_LIP].rotate_time[1] = 10;//20;
	InterfaceTree[POS_INT_LIP].rotate_time[2] = 10;
	InterfaceTree[POS_INT_LIP].position.x = (const float)-139.520;
	InterfaceTree[POS_INT_LIP].position.y = (const float)45;
	InterfaceTree[POS_INT_LIP].position.z = (const float)57.1743;
	InterfaceTree[POS_INT_LIP].orientation.x = (const float)-0.0203507;//0.0795651;
	InterfaceTree[POS_INT_LIP].orientation.y = (const float)0;
	InterfaceTree[POS_INT_LIP].orientation.z = (const float)0.999793;//0.996846;
	InterfaceTree[POS_INT_LIP].nav_bar_frame = 6;

	InterfaceTree[POS_SHACK].exit[0] = POS_CENT_SIGN;
	InterfaceTree[POS_SHACK].exit[1] = POS_NONE;
	InterfaceTree[POS_SHACK].exit[2] = POS_NONE;
	InterfaceTree[POS_SHACK].exit_control[0] = MOVE_BACK;
	InterfaceTree[POS_SHACK].exit_control[1] = MOVE_NONE;
	InterfaceTree[POS_SHACK].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_SHACK].exit_rotate_offset[0] = (const float)0;
	InterfaceTree[POS_SHACK].exit_rotate_offset[1] = (const float)0;
	InterfaceTree[POS_SHACK].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_SHACK].move_time[0] = 20;
	InterfaceTree[POS_SHACK].move_time[1] = 10;
	InterfaceTree[POS_SHACK].move_time[2] = 10;
	InterfaceTree[POS_SHACK].rotate_time[0] = 20;
	InterfaceTree[POS_SHACK].rotate_time[1] = 10;
	InterfaceTree[POS_SHACK].rotate_time[2] = 10;
	InterfaceTree[POS_SHACK].position.x = (const float)107.562;
	InterfaceTree[POS_SHACK].position.y = (const float)45;
	InterfaceTree[POS_SHACK].position.z = (const float)11.7831;
	InterfaceTree[POS_SHACK].orientation.x = (const float)0.904279;
	InterfaceTree[POS_SHACK].orientation.y = (const float)0;
	InterfaceTree[POS_SHACK].orientation.z = (const float)0.426986;
	InterfaceTree[POS_SHACK].nav_bar_frame = 5;

	InterfaceTree[POS_SIGN].exit[0] = POS_CENT_SIGN;
	InterfaceTree[POS_SIGN].exit[1] = POS_NONE;
	InterfaceTree[POS_SIGN].exit[2] = POS_NONE;
	InterfaceTree[POS_SIGN].exit_control[0] = MOVE_BACK;
	InterfaceTree[POS_SIGN].exit_control[1] = MOVE_NONE;
	InterfaceTree[POS_SIGN].exit_control[2] = MOVE_NONE;
	InterfaceTree[POS_SIGN].exit_rotate_offset[0] = (const float)PI;
	InterfaceTree[POS_SIGN].exit_rotate_offset[1] = (const float)0;
	InterfaceTree[POS_SIGN].exit_rotate_offset[2] = (const float)0;
	InterfaceTree[POS_SIGN].move_time[0] = 20;
	InterfaceTree[POS_SIGN].move_time[1] = 10;
	InterfaceTree[POS_SIGN].move_time[2] = 10;
	InterfaceTree[POS_SIGN].rotate_time[0] = 20;
	InterfaceTree[POS_SIGN].rotate_time[1] = 10;
	InterfaceTree[POS_SIGN].rotate_time[2] = 10;
	InterfaceTree[POS_SIGN].position.x = (const float)46.4269;
	InterfaceTree[POS_SIGN].position.y = (const float)45;
	InterfaceTree[POS_SIGN].position.z = (const float)313.081;
	InterfaceTree[POS_SIGN].orientation.x = (const float)-0.0203510;
	InterfaceTree[POS_SIGN].orientation.y = (const float)0;
	InterfaceTree[POS_SIGN].orientation.z = (const float)0.999812;
	InterfaceTree[POS_SIGN].nav_bar_frame = 5;

	strcpy(letters, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?abcdefghijklmnopqrstuvwxyz:'/-");
	int k=0;
	int j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 10; j++)
		{
			letter_rect[k].left = j*25;
			letter_rect[k].top = i*36;
			letter_rect[k].right = j*25+25;
			letter_rect[k].bottom = i*36+36;
			k++;
		}
	}
}

CsurfView::~CsurfView()
{
	int i;
	if (bFullscreen)
		lpDD->RestoreDisplayMode();	
	ShowCursor(TRUE);
	delete LoadProgress;
#ifdef SHAREWARE
	CShareExit ShareExit;
	ShareExit.DoModal();
	delete ShareExit;
#endif
	for (i = 0; i < NUMSONGS; i++)
	{
		if (MidiMusic[i])
		{
			MidiMusic[i]->Stop();
			MidiMusic[i]->Close();
			delete MidiMusic[i];
			MidiMusic[i] = NULL;
		}
	}

//	if (lpDP)
//		lpDP->Release();
	if (lpFrontBuffer)
		lpFrontBuffer->Release();
	if (lpBackBuffer)
		lpBackBuffer->Release();
	if (lpZBuffer)
		lpZBuffer->Release();
	if (lpSpeedometer)
		lpSpeedometer->Release();
	if (lpAlphabet)
		lpAlphabet->Release();
	if (lpSkySource)
		lpSkySource->Release();
	if (lpNavBar)
		lpNavBar->Release();
	if (lpLogo)
		lpLogo->Release();
	if (lpHalfresBuffer)
		lpHalfresBuffer->Release();
	if (lpIntrBkg)
		lpIntrBkg->Release();
	if (wave_builder)
		wave_builder->Release();
	if (curlr_builder)
		curlr_builder->Release();
	if (wave_mesh)
		wave_mesh->Release();
	if (curlr_mesh)
		curlr_mesh->Release();
	for (i = 0; i < NUMFOAM; i++)
	{
		if (foam[i])
			foam[i]->Release();
	}
	for (i = 0; i < NUMBLOOD; i++)
	{
		if (blood[i])
			blood[i]->Release();
	}
	for (i = 0; i < NUMTEXTURES; i++)
	{
		if (map[i])
			map[i]->Release();
	}
	if (barrel)
		barrel->Release();
	if (barrel_animate)
		barrel_animate->Release();
	if (leftbouy)
		leftbouy->Release();
	if (leftbouy_animate)
		leftbouy_animate->Release();
	if (ritebouy)
		ritebouy->Release();
	if (ritebouy_animate)
		ritebouy_animate->Release();
	if (sharkhead)
		sharkhead->Release();
	if (sharkhead_animate)
		sharkhead_animate->Release();
	if (pier)
		pier->Release();
	if (oilrig)
		oilrig->Release();
	if (dolphin)
		dolphin->Release();
	if (dolphin_animate)
		dolphin_animate->Release();
	if (trophy)
		trophy->Release();
	if (trophy_animate)
		trophy_animate->Release();
	if (shopguys_animate)
		shopguys_animate->Release();
	if (shopguys)
		shopguys->Release();
	if (rock)
		rock->Release();
	if (curl_frame)
		curl_frame->Release();
	if (wave)
		wave->Release();
	if (ufo)
		ufo->Release();
	if (beach_frame)
		beach_frame->Release();
	if (light1)
		light1->Release();
	if (light2)
		light2->Release();
	if (light)
		light->Release();
//	for (i = 0; i < 8; i++)
//	{
//		if (wave_map[i])
//			wave_map[i]->Release();
//	}
	for (i = 0; i < 6; i++)
	{
		if (surf_animate[i])
			surf_animate[i]->Release();
		if (surfer[i])
			surfer[i]->Release();
	}
	if (child_of_the_wave)
		child_of_the_wave->Release();
	
	// release the sprayframes

	for (i = 0; i < NUMSPRAY; i++)
	{
		if (spray[i])
			spray[i]->Release();
		if (lpSprayMap[i])
			lpSprayMap[i]->Release();
	}
//	if (m_scene)
//		m_scene->Release();
	if (m_camera)
	    m_camera->Release();
	if (m_view)
		m_view->Release();
	if (m_lpDev)
		m_lpDev->Release();
	if (m_lprm)
		m_lprm->Release();
	if (lpClipper)
	    lpClipper->Release();
	CsurfApp* pApp = (CsurfApp*)AfxGetApp();
	pApp->m_pView = NULL;
	if (lpDD)
	    lpDD->Release();
	CleanupDirectSound();
}

BOOL CsurfView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/*
 * Create a simple scene.
 */

// reset fps
void CsurfView::ResetFps()
{
	// Set up the fps counter

	total_ticks = (const float)10;
	num_ticks = 10;
	numframes = this_tick = 0;
	prev_tick = starttime = timeGetTime();
}

// ApplyStats adjusts the controls to match those of the current surfer

void CsurfView::ApplyStats()
{
	if (bContest)
	{
		if (board_condition < 0)
			board_condition = 0;
		else if (board_condition > 320)
			board_condition = 320;

		surfer_turn = (float)(PI/(25-stat_turn[current_surfer]+(board_condition/60)));
		surfer_speed = (float)2 * stat_speed[current_surfer]-(board_condition/60);
		surfer_max = 35 * ((float)stat_max[current_surfer]/5)-(board_condition/25);
		surfer_slide = (float)(10-stat_land[current_surfer])/20;
	}
	else
	{
		surfer_turn = (float)(PI/(25-stat_turn[current_surfer]));
		surfer_speed = (float)2 * stat_speed[current_surfer];
		surfer_max = 30 * ((float)stat_max[current_surfer]/5);
		surfer_slide = (float)(10-stat_land[current_surfer])/20;
	}

}

// Animate water animates the water texture maps in a non-conventional way.
// Instead of Blitting to the texture and then using a Changed(), which is
// rediculously slow, I remove the old texture, and then re-apply a new one
// from a pre-drawn animation.

void CsurfView::AnimateWater()
{
	static int animframe = 0;
	wave->DeleteVisual((LPDIRECT3DRMVISUAL) wave_mesh);
	wave_mesh->Release();
	wave_builder->CreateMesh(&wave_mesh);
	if (bWaveTextures)
	{
		wave_mesh->SetGroupTexture(D3DRMGROUP_ALLGROUPS, wave_map[animframe]);
		wave_mesh->SetGroupMapping(D3DRMGROUP_ALLGROUPS, D3DRMMAP_PERSPCORRECT);
	}
	wave->AddVisual((LPDIRECT3DRMVISUAL) wave_mesh);

	if (bBreakingWave || bContest)
	{
		curl_frame->DeleteVisual((LPDIRECT3DRMVISUAL) curlr_mesh);
		curlr_mesh->Release();
		curlr_builder->CreateMesh(&curlr_mesh);
		if (bWaveTextures)
		{
			curlr_mesh->SetGroupTexture(D3DRMGROUP_ALLGROUPS, wave_map[animframe]);
			curlr_mesh->SetGroupMapping(D3DRMGROUP_ALLGROUPS, D3DRMMAP_PERSPCORRECT);
		}
		curl_frame->AddVisual((LPDIRECT3DRMVISUAL) curlr_mesh);
	}
	if (bHorizon && !bGameOver && !bWipeout)
	{
		D3DVECTOR buffer;
		float x;
		surfer[current_surfer]->GetPosition(m_scene, &buffer);
		x = buffer.x;
		beach_frame->GetPosition(m_scene, &buffer);
		beach_frame->SetPosition(m_scene, x, buffer.y, buffer.z);
	}
	animframe += 1;
	if (animframe > 7)
		animframe -= 8;
}

// This is the char select routine.

void CsurfView::SelectCharacter()
{
#define CREDITS_TEXT		6
#define LOAD_TEXT			7
#define SAVE_TEXT			8
#define HELP_TEXT_1			9
#define HELP_TEXT_2			10
#define HELP_TEXT_3			11
#define HELP_TEXT_4			12
#define PURCHASE_TEXT		13
#define THRASH_STATS_TEXT	14
#define CONTEST_STATS_TEXT	15
#define START_TEXT			16
#define BEACH_TEXT			17
#define PICK_A_SURFER_TEXT	18
#define OPPONENTS_TEXT		19
#define NEED_A_SURFER		20
#define ALANA_WIN			21
#define BUCKY_WIN			22
#define LEE_WIN				23
#define SANDY_WIN			24
#define TODD_WIN			25
#define VIC_WIN				26
#define DEFAULT_TEXT		27
#define FIRST_PLACE			28
#define SECOND_PLACE		29
#define THIRD_PLACE			30
#define FOURTH_PLACE		31
#define FIFTH_PLACE			32
#define LAST_PLACE			33
#define OUT_OF_CONTEST		34
#define GREAT				35
#define GOOD				36
#define FAIR				37
#define POOR				38
#define BOGUS				39
#define DISQUALIFY_TEXT		40
#define NOT_CONTEST_EQUIP_TEXT 41
#define NUMTEXT				42
#define NO_TEXT			NO_ONE

#define LOAD_CONTEST		0
#define SAVE_CONTEST		1
#define ENTER_CONTEST		2
#define EXIT_CONTEST		3
#define PURCHASE_CONFIRMATION 4

// stuff for the interface tree;

	static float animtime = (const float) 151;
	static float camera_animtime = (const float) 0;
	static float shopguys_animtime = (const float) 1;
	static int interface_pos = POS_START;
	static int navbarframe = 2;
	static int move_count = 0;
	static int rotate_count = 0;
	static BOOL alreadyhigh = FALSE;
	static int ConfirmationReason = 0;
	HRESULT LastError;
    DDSURFACEDESC ddsd;
	int old_dither;
	D3DRMRENDERQUALITY old_quality;
	int old_shades;

	static int text_num = START_TEXT;
	static BOOL bTextDraw = FALSE;
	static BOOL bYouWon = FALSE;
	static BOOL bYouLost = FALSE;
	static BOOL bAlreadyPurchased = FALSE;
	static int Purchase = 0;
	static int counter = 0;
	D3DVECTOR buffer, bufferz, buffery;
	int i,j,l,k;
//	int purhold;
	BOOL hisc = FALSE;
	RECT source, dest;
	int getit;
	int temp_current_surfer = NO_ONE;
	int temp_contest_score[6] = {0,0,0,0,0,0};
	int temp_Heat = 0;
	int temp_board_condition = 0;
	BOOL temp_bFirstRun = TRUE;
	int temp_contest_place[6] = {0,1,2,3,4,5};

	char ss[12];
	static char * save_section[6] =
	{
		"SaveGame1",
		"SaveGame2",
		"SaveGame3",
		"SaveGame4",
		"SaveGame5",
		"SaveGame6"
	};

	static char * text[NUMTEXT] = 
	{
		// alana
		"     ALANA       'MRS. NATURAL'                 Don't mess with  Alana. She can    out think,      maneuver,     philosophize,   and SURF just   about anybody.    She shreds     medium sized  waves like a cat shreds a couch.",
		// bucky
		" BUCKY THE PUNK                     INHUMAN.        BIZARRE.       ILLOGICAL.    Bucky is 5 and one half feet ofTWEAK.To pursue him is madness.  To surf as one  with him is a   heck of a good  ol' weird time.                ",
		//lee
		"      LEE        'JERSEY SLIM'       GROBAN        Lee is an     advanced human being; kind and  gentle on dry   land, deranged  in the water.    He can also   communicate with   all of the   creatures of the      sea.      ",
		//sandy
		"  SANDY DUNES                   Sandy's elegant  features hold   the soul of a    twisted surf    speed freak.   She'll make a   sucker out of  anyone who gets   in her way,    and look good     doing it.                    ",
		//todd
		"      TODD        'THE HEALER'      TREANOR                     Todd has a CRAZY  and methodic    approach to     surfing. He   explodes on big or small waves, and is reliably   surefooted.                                   ",
		//vic
		"      VIC       'The Samoan Fro'    HERRERA                        Vic is the    master of big  wave riding. He has an insanely  agressive and  powerful surfingstyle that makes  him one mean     opponent.                    ",
		//credits
		"    Credits                     LEAD PROGRAMMER:  Jeremy Evers   GAME DESIGNER:    Grady Sain     3D ANIMATOR:   Paul Fantastic  LEAD DESIGNER:      Wheat       SOUND DESIGN:    Randy Wilson     ANNOUNCER:     Davey Force   ",
		//load text
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"   LOAD Game!     1 2 3 4 5 6                    Heat:   Run:   Yer in the lead!Your board is ingreat condition!                1. alana 00000002. bucky 00000003. lee   00000004. sandy 00000005. todd  00000006. vic   0000000",
		//save text
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"   SAVE Game!     1 2 3 4 5 6                    Heat:   Run:   Yer in the lead!Your board is ingreat condition!                1. alana 00000002. bucky 00000003. lee   00000004. sandy 00000005. todd  00000006. vic   0000000",
		//help 1
		"      Help                       For a complete online reference to WILD RIDE!,   see the help  file in the help menu. It covers gameplay topics from setup to  advanced tricks   and gameplay    techniques!                   ",
		//help 2
		"      Help                       Make sure you   have chosen a   character. Go  to the middle of the beach and  look around. If you see someone  you like, hit  the space bar orjoystick button to select them.                 ",
		//help 3
		"      Help                       The Save Game  option can only be activated if    you are in    Contest Mode.                   The Load Game    option will    overwrite any    unsaved game    information.                  ",
		//help 4
		"      Help                      WILD RIDE! opensin Thrash Mode.   To activate    Contest Mode,  visit the Stats  option at The   Hairy Lip. If  you switch back to Thrash Mode,  you will lose  any unsaved game  information.  ",
		//purchase
		"   Equipment        Upgrade      Only 1 purchase   per contest!                    Ding Repair                   50,000 points!                                    Surfin' Wax                   30,000 points!                 ",
		//thrash stats
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
	    "  THRASH MODE!    Best Runs:    1.                       00000002.                       00000003.                       00000004.                       00000005.                       00000006.                       0000000",
 	   //contest stats
	    "  CONTEST MODE!  Heat:   Run:   Yer in the lead!Your board is ingreat condition!                Current Rankings                1. alana 00000002. bucky 00000003. lee   00000004. sandy 00000005. todd  00000006. vic   0000000",
		//start text
		"   Welcome to   WILD RIDE Beach!                  Here you can    choose your   character, load and save games, and equip your-  self with surf   accesories.     Explore the    beach and get   ready to RIDE!                 ",
		//beach text thrash
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"    ALLRIGHT        SURFR!!!                      Take a deep   breath, hit that  space bar or  joystick button,then hold on and  get ready to      RIDE THE       WILD ONE!!                    Yeee Haaawww!!                 ",
		//pick a surfer text
		"  Choose yer       Character!     Take a look    around. If you see someone you  like, hit the    space bar or  joystick button  to pick them!    If you don't  want to be that    character,       then try        another!    ",
		//opponents text
		"                  Take a good     look at that  motley crew. Yersurfing against   some of the     baddest wave   pirates of all      time!                         Good Luck!                   You'll need it!!                ",
		//need a surfer lip text
		"   Attention!                   Hey!, you forgot  to choose a    character! Go    back to the    middle of the   beach and look  around. If you see someone you  like, hit the    space bar or  joystick button  to pick them!  ",
		//alana win
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"CONGRATULATIONS      Alana!      You tore it up  like nobody's    business out    there today!   Yer Number 1!!   From now on    everyone, even the mighty Vic, will tremble at yer shapely feet like spineless  jelly people!  ",
		//bucky win
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"CONGRATULATIONS      Bucky!                     Like a force of  nature raging  out of control, you have carved,dodged, pumped,   and launched     yer way to     NUMERO UNO!!                   Bucky RULEZ!!                  ",
		//lee win
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"CONGRATULATIONS       Lee!                      Yer mighty skill  and magical     longboarding   ways have won   you 1st prize!   It's time to  relax, kick backand contemplate  the universe.  After that, more   SURFING!!!   ",
		//sandy win
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"CONGRATULATIONS      Sandy!                     You have won 1stplace! You'll bethe talk of the  town tonight,   after you take   yer winnings  and soup up yer     3 legged       chinchilla       mobile!                     ",
		//todd win
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"CONGRATULATIONS      Todd!                        You are the     champion, my  friend! Now you are an official    WILD RIDE!      SURF GOD!!    You will bask    in glory and   confidence at  WILD RIDE! beach   forever!!!   ",
		//vic win
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
		"CONGRATULATIONS       VIC!        Now that you  have proven yer    mastery of    shredding big  waves, it's time  to take your    winnings and   party all nite   long at the   local disco, TheDancin' Breaker!                ",
		//default text
#ifdef SHAREWARE
		"    Explore     WILD RIDE Beach!                Visit the Hairy Lip to purchase new gear, enter the contest -NOTIN SHAREWARE- or   access yer   game statistics.  Or check out  help and credits  at Ye Bearded       Clam!     ",
#else
		"    Explore     WILD RIDE Beach!                Visit the Hairy Lip to purchase new gear, enter  the contest or    access yer   game statistics.  Or check out   help, credits,  and load save   options at Ye   Bearded Clam!  ",
#endif
		//first place etc.,
	   //0123456789abcdef
	    "Yer in the lead!",
		" Yer in second! ",
		"  Yer in third! ",
		" Yer in fourth! ",
		"  Yer in fifth! ",
		"   Yer in last! ",
		"Yer done surfin!",
		"great",
		" good",
		" fair",
		" poor",
		"bogus",
		//Disqualify text
		"  You've been    DISQUALIFIED   from this year's  contest. You  will have to tryagain next year! Too Bad      !                 1. alana 00000002. bucky 00000003. lee   00000004. sandy 00000005. todd  00000006. vic   0000000",
		//need a surfer lip text
	   //0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
#ifdef SHAREWARE
		"     Sorry!                      You need to be in contest mode to upgrade your     board...                    You can registerfor contest mode at the counter   to your left,  once that you   have the full      version!    "
#else
		"     Sorry!                      You need to be in contest mode to upgrade your     board...                    You can registerfor contest mode at the counter   to your left.                                                 "
#endif
	};


	if (bFirstSelect)
	{	
		fullscreencountdown = 1;
		if (bMIDIMusic)
		{
			bMIDIMusic = FALSE;
			OnMidiMusic();
		}
		if (bCDMusic)
		{
			playCDTrack(9);
		}

		interface_pos = POS_START;

		rotate_count = 0;
		move_count = 0;
		animtime = (const float) 150;
		camera_animtime = (const float)0;

		text_num = START_TEXT;

		if (bContest)
		{
			if (!bInContest[current_surfer])
			{
				bYouLost = TRUE;
				counter = 0;
				text_num = DISQUALIFY_TEXT;
				if (!alreadyhigh)
				{
					alreadyhigh = TRUE;
					for (i = 5; i >= 0; i--)
					{
						if (contest_score[current_surfer] > hiscorec[i])
						{
							scorenum = i;
							hisc = TRUE;
							if (i < 5)
							{
								hiscorec[i+1] = hiscorec[i];
								hisurferc[i+1] = hisurferc[i];
								for (j = 0; j < 8; j++)
								{
									hinamec[i+1][j] = hinamec[i][j];
								}
							}
						}
					}
					if (hisc)
					{
						hiscorec[scorenum] = contest_score[current_surfer];
						hisurferc[scorenum] = current_surfer;
						letnum = 0;
						bHiscore = TRUE;
					}
				}
			}
			else if ((Heat == 5) && (current_surfer != NO_ONE))
			{
				bYouWon = TRUE;
				counter = 0;
				bContest = FALSE;
				text_num = ALANA_WIN+current_surfer;
				if (!alreadyhigh)
				{
					alreadyhigh = TRUE;
					for (i = 5; i >= 0; i--)
					{
						if (contest_score[current_surfer] > hiscorec[i])
						{
							scorenum = i;
							hisc = TRUE;
							if (i < 5)
							{
								hiscorec[i+1] = hiscorec[i];
								hisurferc[i+1] = hisurferc[i];
								for (j = 0; j < 8; j++)
								{
									hinamec[i+1][j] = hinamec[i][j];
								}
							}
						}
					}
					if (hisc)
					{
						hiscorec[scorenum] = contest_score[current_surfer];
						hisurferc[scorenum] = current_surfer;
						letnum = 0;
						bHiscore = TRUE;
					}
				}
			}
		}

#ifdef NO_SURFERS
		i = current_surfer;
#else
#ifdef SHAREWARE
		for (i = 0; i < 3; i +=2)
#else
		for (i = 0; i < 6; i ++)
#endif
#endif
		{
			if (!bContest || (bContest && bInContest[i]))
				m_scene->AddChild(surfer[i]);
			surfer[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
			surfer[i]->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
			surfer[i]->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			surfer[i]->SetOrientation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
			surf_animate[i]->SetTime(D3DVALUE(150));
		}
		if (bSoundFx)
		{
			m_pDSBuffer[OCEANSND]->SetVolume(-800);
			m_pDSBuffer[STEAMSHIPWAVE]->SetVolume(-800);
		}

		if (current_surfer != NO_ONE)
			m_scene->DeleteChild(surfer[current_surfer]);
		m_scene->AddChild(intro_scene);
#ifndef NO_SURFERS
		m_scene->AddChild(shopguys);
		m_scene->AddChild(trophy);
#endif

		m_camera->SetPosition(m_scene, InterfaceTree[POS_START].position.x, InterfaceTree[POS_START].position.y, InterfaceTree[POS_START].position.z);
		m_camera->SetOrientation(m_scene, InterfaceTree[POS_START].orientation.x, InterfaceTree[POS_START].orientation.y, InterfaceTree[POS_START].orientation.z, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
//		m_camera->SetRotation(m_scene, D3DVALUE(0),D3DVALUE(1),D3DVALUE(0),D3DVALUE(0.1));
		if (current_surfer != NO_ONE)
		{
			surfer[current_surfer]->DeleteChild(sharkhead);
			surfer[current_surfer]->DeleteChild(child_of_the_wave);
		}
		for (i = 0; i < NUMBLOOD; i++)
			m_scene->DeleteChild(blood[i]);
		m_scene->DeleteChild(wave);
		m_scene->DeleteChild(curl_frame);
		for (i = 0; i < NUMFOAM; i++)
			m_scene->DeleteChild(foam[i]);
		m_scene->DeleteChild(beach_frame);
		bUfo = TRUE;
		OnUfo();
		for (i = 0; i < NUMSPRAY; i++)
		{
			m_scene->DeleteChild(spray[i]);
		}
		m_scene->DeleteChild(barrel);
		m_scene->DeleteChild(leftbouy);
		m_scene->DeleteChild(ritebouy);
		m_scene->DeleteChild(pier);
		m_scene->DeleteChild(oilrig);
		m_scene->DeleteChild(dolphin);
		m_scene->DeleteChild(rock);

		m_view->Render(m_scene);

		old_dither = m_lpDev->GetDither();
		old_quality = m_lpDev->GetQuality();
		old_shades = m_lpDev->GetShades();
	
		if (m_view != NULL)
		{
			m_view->Release();
			m_view = NULL;
		}
//		m_lpDev->Release();

		if (lpBackBuffer);
		{
			lpBackBuffer->Release();
			lpBackBuffer = NULL;
		}

	    memset(&ddsd,0,sizeof(DDSURFACEDESC));
	    ddsd.dwSize = sizeof( ddsd );

		// back buffer

		if (bFullscreen)
		{
			DDSCAPS ddscaps;
		    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		    LastError = lpFrontBuffer->GetAttachedSurface(&ddscaps, &lpBackBuffer);
		    if(LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "GetAttachedSurface failed to get back buffer.");
		        return;
		    }
//		    GetDDSurfaceDesc(&ddsd, lpBackBuffer);
//		    if (!(ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY))
//		        bOnlySoftRender;
		}
		else
		{
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
			ddsd.dwHeight = ModeCy;
			ddsd.dwWidth = ModeCx;
			if (bOnlySystemMemory)
			    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
			LastError = lpDD->CreateSurface(&ddsd, &lpBackBuffer, NULL);
			if(LastError != DD_OK) 
			{
			    if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Back buffer failed.");
				return;
			}
		}

		if (lpHalfresBuffer);
		{
			lpHalfresBuffer->Release();
			lpHalfresBuffer = NULL;
		}

		// halfres buffer
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		ddsd.dwHeight = ModeCy/2;
		ddsd.dwWidth = ModeCx/2;
		if (bOnlySystemMemory)
		    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
		LastError = lpDD->CreateSurface(&ddsd, &lpHalfresBuffer, NULL );
		if(LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Halfres buffer failed.");
		    return;
		}

		if (bHalfres)
		{
		    LastError = FindDevice(lpHalfresBuffer);
		    if(LastError != DD_OK ) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
		        return;
			}
		}
		else
		{
		    LastError = FindDevice(lpBackBuffer);
		    if(LastError != DD_OK ) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
		        return;
			}
		}
				
		m_lpDev->SetDither(old_dither);
		m_lpDev->SetQuality(old_quality);
		m_lpDev->SetShades(old_shades);
		m_lpDev->SetTextureQuality(TextureFiltering);

	    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
			INTR_VRIGHT, INTR_VBOTTOM, &m_view);

	    m_view->SetBack(D3DVAL(INTR_BACK));

		bFirstSelect = FALSE;
		bResizedSelect = TRUE;
		ResetFps();
	}

	// draw the background and the text

	if (bResizedSelect || (fullscreencountdown > 0))
	{
		fullscreencountdown--;
		bResizedSelect = FALSE;
		source.left = 0;
		source.top = 0;
		source.right = 320;
		source.bottom = 240;

		if (bFullscreen)
		{
			dest.left = 0;
			dest.top = 0;
			dest.right = ModeCx;
			dest.bottom = ModeCy;

			LastError = lpBackBuffer->Blt(&dest, lpIntrBkg, &source, DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
			    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr Bkg to back Blit failed.");
		    }
		}
		dest.left = ModeAx;
		dest.top = ModeAy;
		dest.right = ModeBx;
		dest.bottom = ModeBy;

		LastError = lpFrontBuffer->Blt(&dest, lpIntrBkg, &source, DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr Bkg to front Blit failed.");
	    }

		// logo

		source.left = 0;
		source.top = 0;
		source.right = 255;
		source.bottom = 98;

		dest.left = (long)(ModeCx*((const float)36/64)+ModeAx);
		dest.top = (long)(ModeCy*((const float)25/32)+ModeAy);
		dest.right = (long)(ModeCx*((const float)63/64)+ModeAx);
		dest.bottom = (long)(ModeCy*((const float)63/64)+ModeAy);

		LastError = lpFrontBuffer->Blt(&dest, lpLogo, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr Logo to front Blit failed.");
	    }
		if (bFullscreen)
		{
			dest.left -= ModeAx;
			dest.top -= ModeAy;
			dest.right -= ModeAx;
			dest.bottom -= ModeAy;

			LastError = lpBackBuffer->Blt(&dest, lpLogo, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
			    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr Logo to back Blit failed.");
		    }
		}
		bTextDraw = TRUE;
	}

#ifdef NO_SURFERS
	i = current_surfer;
	{
#else
#ifdef SHAREWARE
	for (i = 0; i < 3; i+=2)
	{
		if (current_surfer != i)
			surf_animate[i]->SetTime(animtime);
		else
#else
	for (i = 0; i < 6; i++)
	{
		if (current_surfer != i)
			surf_animate[i]->SetTime(animtime);
		else
#endif
#endif
			surf_animate[i]->SetTime(D3DVALUE(155.999));
	}

	animtime+= (const float) 0.5;
	if (animtime >= 155)
		animtime = (const float) 150;
#ifndef NO_SURFERS
	shopguys_animate->SetTime(shopguys_animtime);
#endif
#ifndef SHAREWARE
	if (bYouWon)
	{
		counter++;
		if (counter == 1)
		{
			if (bNaration || bSurferSounds || bSoundFx)
			{
				AddAnnounce(UWONDAVE);
				if (bHiscore)
					AddAnnounce(randInt(HISCORE1,HISCORE1+2));
			}
		}
#ifndef NO_SURFERS
		trophy_animate->SetTime(shopguys_animtime/2);
#endif
	}
	else
	{
#endif
#ifndef NO_SURFERS
		trophy_animate->SetTime((const float)10.999);
#endif
#ifndef SHAREWARE
		if (bYouLost)
		{
			counter++;
			if (counter == 1)
			{
				bYouLost = FALSE;
				if (bNaration || bSurferSounds || bSoundFx)
				{
					AddAnnounce(randInt(DISQUALIFYDAVE,DISQUALIFYDAVE+3));
					if (bHiscore)
						AddAnnounce(randInt(HISCORE1,HISCORE1+2));
				}
			}
		}
	}
#endif

	if (interface_pos != POS_START)
	{
		bYouWon = FALSE;
		bYouLost = FALSE;
	}

	shopguys_animtime+= (const float) 0.33;
	if (shopguys_animtime >= 20)
		shopguys_animtime = (const float) 1;

	m_scene->Move(D3DVALUE(1));

	if (bSky)
	{
		m_camera->GetOrientation(m_scene, &bufferz, &buffery);
//		m_camera->GetPosition(m_scene, &buffer); // for testing positions
		skysource.top = 128;
		skysource.bottom = 384;
		skysource.left = (long)(bufferz.x*80+80);
//		skysource.left = (long)(atan(bufferz.z/bufferz.x)/(-PI/2)*160+160);
		if (skysource.left < 0)
			skysource.left = 0;
		else if (skysource.left > 160)
			skysource.left -= 160;
		skysource.right = skysource.left+159;
	}

	RenderInterface(navbarframe);

	if (bTextDraw && (move_count < 1) && (rotate_count < 1))
	{
		bTextDraw = FALSE;
		int text_index = 0;
	
		switch (text_num)
		{
		case BEACH_TEXT:
			for (j = 0; j < 5; j++)
			{
				text[BEACH_TEXT][20+j] = names[current_surfer][j];
			}
			break;

		case CONTEST_STATS_TEXT:
			for (i = 0; i < 6; i++)
			{
				for (j = i; j < 6; j++)
				{
					if (contest_score[contest_place[j]] > contest_score[contest_place[i]])
					{
						l = contest_place[i];
						contest_place[i] = contest_place[j];
						contest_place[j] = l;
					}
				}
				sprintf(ss, "%07d",contest_score[contest_place[i]]);
				for (j = 0; j < 5; j++)
				{
					text[CONTEST_STATS_TEXT][i*16+131+j] = names[contest_place[i]][j];
				}
				for (j = 0; j < 7; j++)
				{
					text[CONTEST_STATS_TEXT][i*16+137+j] = ss[j];
				}
				if (bInContest[contest_place[i]])
				{
					text[CONTEST_STATS_TEXT][i*16+128] = letters[i+1];
					text[CONTEST_STATS_TEXT][i*16+129] = letters[36];
				}
				else 
				{
					text[CONTEST_STATS_TEXT][i*16+128] = 0x20;
					text[CONTEST_STATS_TEXT][i*16+129] = 0x20;
				}
				if (contest_place[i] == current_surfer)
				{
					text[CONTEST_STATS_TEXT][i*16+130] = letters[69];
					text[CONTEST_STATS_TEXT][i*16+136] = letters[69];

					if (!bInContest[current_surfer])
					{
						for (j = 0; j < 16; j++)
						{
							text[CONTEST_STATS_TEXT][32+j] = 
								text[OUT_OF_CONTEST][j];
						}
					}
					else
					{
						for (j = 0; j < 16; j++)
						{
							text[CONTEST_STATS_TEXT][32+j] = 
								text[FIRST_PLACE+i][j];
						}
					}
				}
				else
				{
					text[CONTEST_STATS_TEXT][i*16+130] = 0x20;
					text[CONTEST_STATS_TEXT][i*16+136] = 0x20;
				}
			}
			for (j = 0; j < 5; j++)
			{
				text[CONTEST_STATS_TEXT][64+j] = 
					text[GREAT+(board_condition/80)][j];
			}
			text[CONTEST_STATS_TEXT][23] = letters[Heat+1];
			if (bFirstRun)
			{
				text[CONTEST_STATS_TEXT][30] = letters[1];
			}
			else
			{
				text[CONTEST_STATS_TEXT][30] = letters[2];
			}
			break;

		case DISQUALIFY_TEXT:
			for (j = 0; j < 5; j++)
			{
				text[DISQUALIFY_TEXT][105+j] = names[current_surfer][j];
			}
			for (i = 0; i < 6; i++)
			{
				for (j = i; j < 6; j++)
				{
					if (contest_score[contest_place[j]] > contest_score[contest_place[i]])
					{
						l = contest_place[i];
						contest_place[i] = contest_place[j];
						contest_place[j] = l;
					}
				}
				sprintf(ss, "%07d",contest_score[contest_place[i]]);
				for (j = 0; j < 5; j++)
				{
					text[DISQUALIFY_TEXT][i*16+131+j] = names[contest_place[i]][j];
				}
				for (j = 0; j < 7; j++)
				{
					text[DISQUALIFY_TEXT][i*16+137+j] = ss[j];
				}
				if (bInContest[contest_place[i]])
				{
					text[DISQUALIFY_TEXT][i*16+128] = letters[i+1];
					text[DISQUALIFY_TEXT][i*16+129] = letters[36];
				}
				else 
				{
					text[DISQUALIFY_TEXT][i*16+128] = 0x20;
					text[DISQUALIFY_TEXT][i*16+129] = 0x20;
				}
				if (contest_place[i] == current_surfer)
				{
					text[DISQUALIFY_TEXT][i*16+130] = letters[69];
					text[DISQUALIFY_TEXT][i*16+136] = letters[69];
				}
				else
				{
					text[DISQUALIFY_TEXT][i*16+130] = 0x20;
					text[DISQUALIFY_TEXT][i*16+136] = 0x20;
				}
			}
			break;

		case THRASH_STATS_TEXT:
			for (i = 0; i < 6; i++)
			{
				sprintf(ss, "%07d",hiscore[i]);
				for (j = 0; j < 5; j++)
				{
					text[THRASH_STATS_TEXT][i*32+51+j] = names[hisurfer[i]][j];
				}
				for (j = 0; j < 7; j++)
				{
					text[THRASH_STATS_TEXT][i*32+57+j] = ss[j];
				}
				for (j = 0; j < 8; j++)
				{
					text[THRASH_STATS_TEXT][i*32+35+j] = hiname[i][j];
				}
			}
			break;

		case LOAD_TEXT:

			temp_current_surfer = GetPrivateProfileInt(save_section[last_load],"Character",NO_ONE,"wildride.ini");
			if (temp_current_surfer != NO_ONE)
			{
				temp_contest_score[0] = GetPrivateProfileInt(save_section[last_load],"Score0",0,"wildride.ini");
				temp_contest_score[1] = GetPrivateProfileInt(save_section[last_load],"Score1",0,"wildride.ini");
				temp_contest_score[2] = GetPrivateProfileInt(save_section[last_load],"Score2",0,"wildride.ini");
				temp_contest_score[3] = GetPrivateProfileInt(save_section[last_load],"Score3",0,"wildride.ini");
				temp_contest_score[4] = GetPrivateProfileInt(save_section[last_load],"Score4",0,"wildride.ini");
				temp_contest_score[5] = GetPrivateProfileInt(save_section[last_load],"Score5",0,"wildride.ini");
				temp_Heat = GetPrivateProfileInt(save_section[last_load],"Heat",0,"wildride.ini");
				temp_board_condition = GetPrivateProfileInt(save_section[last_load],"BoardCondition",0,"wildride.ini");
				getit = GetPrivateProfileInt(save_section[last_load],"FirstRun",1,"wildride.ini");
				if (getit > 0)
					temp_bFirstRun = TRUE;
				else
					temp_bFirstRun = FALSE;
			}
			for (i = 0; i < 6; i++)
			{
				for (j = i; j < 6; j++)
				{
					if (temp_contest_score[temp_contest_place[j]] > temp_contest_score[temp_contest_place[i]])
					{
						l = temp_contest_place[i];
						temp_contest_place[i] = temp_contest_place[j];
						temp_contest_place[j] = l;
					}
				}
				sprintf(ss, "%07d",temp_contest_score[temp_contest_place[i]]);
				for (j = 0; j < 5; j++)
				{
					text[LOAD_TEXT][i*16+131+j] = names[temp_contest_place[i]][j];
				}
				for (j = 0; j < 7; j++)
				{
					text[LOAD_TEXT][i*16+137+j] = ss[j];
				}
				if (i >= (6-temp_Heat))
				{
					text[LOAD_TEXT][i*16+128] = 0x20;
					text[LOAD_TEXT][i*16+129] = 0x20;
				}
				else 
				{
					text[LOAD_TEXT][i*16+128] = letters[i+1];
					text[LOAD_TEXT][i*16+129] = letters[36];
				}
				if (temp_contest_place[i] == temp_current_surfer)
				{
					text[LOAD_TEXT][i*16+130] = letters[69];
					text[LOAD_TEXT][i*16+136] = letters[69];
					if (i >= (6-temp_Heat))
					{
						for (j = 0; j < 16; j++)
						{
							text[LOAD_TEXT][64+j] = 
								text[OUT_OF_CONTEST][j];
						}
					}
					else
					{
						for (j = 0; j < 16; j++)
						{
							text[LOAD_TEXT][64+j] = 
								text[FIRST_PLACE+i][j];
						}
					}
				}
				else
				{
					text[LOAD_TEXT][i*16+130] = 0x20;
					text[LOAD_TEXT][i*16+136] = 0x20;
				}
			}
			for (j = 0; j < 5; j++)
			{
				text[LOAD_TEXT][96+j] = 
					text[GREAT+(temp_board_condition/80)][j];
			}
			text[LOAD_TEXT][55] = letters[temp_Heat+1];
			if (temp_bFirstRun)
			{
				text[LOAD_TEXT][62] = letters[1];
			}
			else
			{
				text[LOAD_TEXT][62] = letters[2];
			}
		break;
		case SAVE_TEXT:

			temp_current_surfer = GetPrivateProfileInt(save_section[last_save],"Character",NO_ONE,"wildride.ini");
			if (temp_current_surfer != NO_ONE)
			{
				temp_contest_score[0] = GetPrivateProfileInt(save_section[last_save],"Score0",0,"wildride.ini");
				temp_contest_score[1] = GetPrivateProfileInt(save_section[last_save],"Score1",0,"wildride.ini");
				temp_contest_score[2] = GetPrivateProfileInt(save_section[last_save],"Score2",0,"wildride.ini");
				temp_contest_score[3] = GetPrivateProfileInt(save_section[last_save],"Score3",0,"wildride.ini");
				temp_contest_score[4] = GetPrivateProfileInt(save_section[last_save],"Score4",0,"wildride.ini");
				temp_contest_score[5] = GetPrivateProfileInt(save_section[last_save],"Score5",0,"wildride.ini");
				temp_Heat = GetPrivateProfileInt(save_section[last_save],"Heat",0,"wildride.ini");
				temp_board_condition = GetPrivateProfileInt(save_section[last_save],"BoardCondition",0,"wildride.ini");
				getit = GetPrivateProfileInt(save_section[last_save],"FirstRun",1,"wildride.ini");
				if (getit > 0)
					temp_bFirstRun = TRUE;
				else
					temp_bFirstRun = FALSE;
			}
			for (i = 0; i < 6; i++)
			{
				for (j = i; j < 6; j++)
				{
					if (temp_contest_score[temp_contest_place[j]] > temp_contest_score[temp_contest_place[i]])
					{
						l = temp_contest_place[i];
						temp_contest_place[i] = temp_contest_place[j];
						temp_contest_place[j] = l;
					}
				}
				sprintf(ss, "%07d",temp_contest_score[temp_contest_place[i]]);
				for (j = 0; j < 5; j++)
				{
					text[SAVE_TEXT][i*16+131+j] = names[temp_contest_place[i]][j];
				}
				for (j = 0; j < 7; j++)
				{
					text[SAVE_TEXT][i*16+137+j] = ss[j];
				}
				if (i >= (6-temp_Heat))
				{
					text[SAVE_TEXT][i*16+128] = 0x20;
					text[SAVE_TEXT][i*16+129] = 0x20;
				}
				else 
				{
					text[SAVE_TEXT][i*16+128] = letters[i+1];
					text[SAVE_TEXT][i*16+129] = letters[36];
				}
				if (temp_contest_place[i] == temp_current_surfer)
				{
					text[SAVE_TEXT][i*16+130] = letters[69];
					text[SAVE_TEXT][i*16+136] = letters[69];
					if (i >= (6-temp_Heat))
					{
						for (j = 0; j < 16; j++)
						{
							text[SAVE_TEXT][64+j] = 
								text[OUT_OF_CONTEST][j];
						}
					}
					else
					{
						for (j = 0; j < 16; j++)
						{
							text[SAVE_TEXT][64+j] = 
								text[FIRST_PLACE+i][j];
						}
					}
				}
				else
				{
					text[SAVE_TEXT][i*16+130] = 0x20;
					text[SAVE_TEXT][i*16+136] = 0x20;
				}
			}
			for (j = 0; j < 5; j++)
			{
				text[SAVE_TEXT][96+j] = 
					text[GREAT+(temp_board_condition/80)][j];
			}
			text[SAVE_TEXT][55] = letters[temp_Heat+1];
			if (temp_bFirstRun)
			{
				text[SAVE_TEXT][62] = letters[1];
			}
			else
			{
				text[SAVE_TEXT][62] = letters[2];
			}
		break;
		}

		source.left = 177;
		source.top = 12;
		source.right = 311;
		source.bottom = 180;

		dest.left = (long)(((const float)21/38)*ModeCx+0.5 + ModeAx);
		dest.top = (long)(((const float)1/20)*ModeCy+0.5 + ModeAy);
		dest.right = (long)(((const float)37/38)*ModeCx+0.5 + ModeAx);
		dest.bottom = (long)(((const float)15/20)*ModeCy+0.5 + ModeAy);

		LastError = lpFrontBuffer->Blt(&dest, lpIntrBkg, &source, DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr Clear to front Blit failed.");
	    }
		if (bFullscreen)
		{
			dest.left -= ModeAx;
			dest.top -= ModeAy;
			dest.right -= ModeAx;
			dest.bottom -= ModeAy;

			LastError = lpBackBuffer->Blt(&dest, lpIntrBkg, &source, DDBLT_WAIT, NULL);
			if (LastError != DD_OK) 
			{
			    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr Clear to back Blit failed.");
			}
		}
		for (l = 1; l < 15; l++)
		{
			for (k = 21; k < 37; k++)
			{
				if (text_num != NO_TEXT)
				{
					for (i = 0; i < NUM_LETTERS; i++)
					{
						if (text[text_num][text_index] == letters[i])
						{
							source = letter_rect[i];

							if (((text_num == LOAD_TEXT) && (text_index == (last_load*2+18)))
								|| ((text_num == SAVE_TEXT) && (text_index == (last_save*2+18))))
							{
								dest.left = (long)(((float)k-0.7)*((const float)1/38)*ModeCx + ModeAx);
								dest.top = (long)(((float)l-0.5)*((const float)1/20)*ModeCy + ModeAy);
								dest.right = (long)(((float)k+1.7)*((const float)1/38)*ModeCx + ModeAx);
								dest.bottom = (long)((l+2)*((const float)1/20)*ModeCy + ModeAy);
							}
							else if ((text_num == PURCHASE_TEXT) && 
								(((Purchase == 2) && (l == 6))
								|| ((Purchase == 1) && (l == 11))))
							{
								dest.left = (long)(((float)k-0.1)*((const float)1/38)*ModeCx + ModeAx);
								dest.top = (long)(((float)l-0.5)*((const float)1/20)*ModeCy + ModeAy);
								dest.right = (long)(((float)k+1.1)*((const float)1/38)*ModeCx + ModeAx);
								dest.bottom = (long)((l+2)*((const float)1/20)*ModeCy + ModeAy);
							}

							else
							{
								dest.left = (long)(k*((const float)1/38)*ModeCx + ModeAx);
								dest.top = (long)(l*((const float)1/20)*ModeCy + ModeAy);
								dest.right = (long)((k+1)*((const float)1/38)*ModeCx + ModeAx);
								dest.bottom = (long)((l+1)*((const float)1/20)*ModeCy + ModeAy);
							}

							LastError = lpFrontBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
						    if (LastError != DD_OK) 
							{
							    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr text to front Blit failed.");
						    }
							if (bFullscreen)
							{
								dest.left -= ModeAx;
								dest.top -= ModeAy;
								dest.right -= ModeAx;
								dest.bottom -= ModeAy;

								LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
								if (LastError != DD_OK) 
								{
								    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Intr text to back Blit failed.");
							    }
							}
							i = 255;
						}
					}
					text_index++;
				}
			}
		}
	}

	BYTE move = MOVE_NONE;
	BYTE turn = MOVE_NONE;

	if (bHiscore)
	{
		if (rotate_count > 0)
			rotate_count--;
		else
			m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));

		if (move_count > 0)
			move_count--;
		else 
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
		return;
	}
	else if (bConfirmation)
	{
		if (rotate_count > 0)
			rotate_count--;
		else
			m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));

		if (move_count > 0)
			move_count--;
		else 
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);

		switch (ConfirmationResponse)
		{
		case NO_CONFIRMATION:
			return;
			break;
		case NO_RESPONSE:
			bConfirmation = FALSE;
			break;
		case YES_RESPONSE:
			bConfirmation = FALSE;
			switch (ConfirmationReason)
			{
			case PURCHASE_CONFIRMATION:
				bAlreadyPurchased = TRUE;
				board_condition -= Purchase*160;
				if (board_condition < 0) 
					board_condition = 0;
				Purchase = 0;
				bTextDraw = TRUE;
				if (bSoundFx || bNaration || bSurferSounds)
					m_pDSBuffer[BOUYWAVE2]->Play(0,0,0);
				break;
			case LOAD_CONTEST:
				last_save = last_load;
#ifndef NO_SURFERS
				if (current_surfer != NO_ONE)
				{
					m_scene->AddChild(surfer[current_surfer]);
					surf_animate[current_surfer]->SetTime(D3DVALUE(156));
				}
				current_surfer = GetPrivateProfileInt(save_section[last_load],"Character",NO_ONE,"wildride.ini");
#endif
				if (current_surfer == NO_ONE)
				{
#ifdef NO_SURFERS
					i = current_surfer;
#else
#ifdef SHAREWARE
					for (i = 0; i < 3; i +=2)
#else
					for (i = 0; i < 6; i ++)
#endif
#endif
					{
						m_scene->AddChild(surfer[i]);
					}
					bContest = FALSE;
				}
				else
				{
					bContest = TRUE;
					bAlreadyPurchased = FALSE;
					alreadyhigh = FALSE;
					contest_score[0] = GetPrivateProfileInt(save_section[last_load],"Score0",0,"wildride.ini");
					contest_score[1] = GetPrivateProfileInt(save_section[last_load],"Score1",0,"wildride.ini");
					contest_score[2] = GetPrivateProfileInt(save_section[last_load],"Score2",0,"wildride.ini");
					contest_score[3] = GetPrivateProfileInt(save_section[last_load],"Score3",0,"wildride.ini");
					contest_score[4] = GetPrivateProfileInt(save_section[last_load],"Score4",0,"wildride.ini");
					contest_score[5] = GetPrivateProfileInt(save_section[last_load],"Score5",0,"wildride.ini");
					Heat = GetPrivateProfileInt(save_section[last_load],"Heat",0,"wildride.ini");
					board_condition = GetPrivateProfileInt(save_section[last_load],"BoardCondition",0,"wildride.ini");
					getit = GetPrivateProfileInt(save_section[last_load],"FirstRun",1,"wildride.ini");
					if (getit > 0)
						bFirstRun = TRUE;
					else
						bFirstRun = FALSE;
					getit = GetPrivateProfileInt(save_section[last_load],"Upgrade",0,"wildride.ini");
					if (getit > 0)
						bAlreadyPurchased = TRUE;
					else
						bAlreadyPurchased = FALSE;
					for (i = 0; i < 6; i++)
					{
						for (j = i; j < 6; j++)
						{
							if (contest_score[contest_place[j]] > contest_score[contest_place[i]])
							{
								l = contest_place[i];
								contest_place[i] = contest_place[j];
								contest_place[j] = l;
							}
						}
						if (i >= (6-Heat))
						{
							bInContest[contest_place[i]] = FALSE;
#ifdef NO_SURFERS
							if (i == current_surfer)
#else
#ifdef SHAREWARE
							if ((i == 1) || (i == 3))
#endif
#endif
								m_scene->DeleteChild(surfer[contest_place[i]]);
						}
						else
						{
							bInContest[contest_place[i]] = TRUE;
#ifdef NO_SURFERS
							if (i == current_surfer)
#else
#ifdef SHAREWARE
							if ((i == 1) || (i == 3))
#endif
#endif
								m_scene->AddChild(surfer[contest_place[i]]);
						}
					}
					if (bSoundFx || bNaration || bSurferSounds)
						m_pDSBuffer[BOUYWAVE2]->Play(0,0,0);
				}
				bTextDraw = TRUE;
				break;
			case SAVE_CONTEST:
				last_load = last_save;
				sprintf(ss, "%d",current_surfer);
				WritePrivateProfileString(save_section[last_save],"Character",ss,"wildride.ini");
				sprintf(ss, "%d",contest_score[0]);
				WritePrivateProfileString(save_section[last_save],"Score0",ss,"wildride.ini");
				sprintf(ss, "%d",contest_score[1]);
				WritePrivateProfileString(save_section[last_save],"Score1",ss,"wildride.ini");
				sprintf(ss, "%d",contest_score[2]);
				WritePrivateProfileString(save_section[last_save],"Score2",ss,"wildride.ini");
				sprintf(ss, "%d",contest_score[3]);
				WritePrivateProfileString(save_section[last_save],"Score3",ss,"wildride.ini");
				sprintf(ss, "%d",contest_score[4]);
				WritePrivateProfileString(save_section[last_save],"Score4",ss,"wildride.ini");
				sprintf(ss, "%d",contest_score[5]);
				WritePrivateProfileString(save_section[last_save],"Score5",ss,"wildride.ini");
				sprintf(ss, "%d",Heat);
				WritePrivateProfileString(save_section[last_save],"Heat",ss,"wildride.ini");
				sprintf(ss, "%d",board_condition);
				WritePrivateProfileString(save_section[last_save],"BoardCondition",ss,"wildride.ini");
				if (bFirstRun)
					WritePrivateProfileString(save_section[last_save],"FirstRun","1","wildride.ini");
				else
					WritePrivateProfileString(save_section[last_save],"FirstRun","0","wildride.ini");
				if (bAlreadyPurchased)
					WritePrivateProfileString(save_section[last_save],"Upgrade","1","wildride.ini");
				else
					WritePrivateProfileString(save_section[last_save],"Upgrade","0","wildride.ini");
				bTextDraw = TRUE;
				if (bSoundFx || bNaration || bSurferSounds)
					m_pDSBuffer[BOUYWAVE2]->Play(0,0,0);
				break;
			case EXIT_CONTEST:
				bContest = FALSE;
#ifdef NO_SURFERS
				i = current_surfer;
#else
#ifdef SHAREWARE
				for (i = 0; i < 3; i +=2)
#else
				for (i = 0; i < 6; i ++)
#endif
#endif
				{
					if (i != current_surfer)
						m_scene->AddChild(surfer[i]);
				}

				text_num = THRASH_STATS_TEXT;
				if (bSoundFx || bNaration || bSurferSounds)
					m_pDSBuffer[BOUYWAVE2]->Play(0,0,0);
				bTextDraw = TRUE;
				break;
			case ENTER_CONTEST:
				bContest = TRUE;
				bAlreadyPurchased = FALSE;
				bTextDraw = TRUE;
				for (i = 0; i < 6; i++)
				{
					contest_place[i] = i;
					contest_score[i] = 0;
					bInContest[i] = TRUE;
				}
				Heat = 0;
				board_condition = 0;
				bFirstRun = TRUE;
				text_num = CONTEST_STATS_TEXT;
				alreadyhigh = FALSE;
				if (bSoundFx || bNaration || bSurferSounds)
					m_pDSBuffer[BOUYWAVE2]->Play(0,0,0);
				break;
			}
			break;
		}
	}

	float mul = (const float)1;

  	if (::GetAsyncKeyState(VK_SHIFT) <0)
		mul = (const float)2;

  	if (::GetAsyncKeyState(VK_LEFT) <0)
	{
		move = MOVE_LEFT;
		turn = MOVE_LEFT;
	}

	// keyboard right

  	else if (::GetAsyncKeyState(VK_RIGHT) <0)
	{
		move = MOVE_RIGHT;
		turn = MOVE_RIGHT;
	}

	// keyboard up pressed

  	if (::GetAsyncKeyState(VK_UP) <0)
	{
		move = MOVE_FORWARD;
	}

	// keyboard down pressed

  	else if (::GetAsyncKeyState(VK_DOWN) <0)
	{
		move = MOVE_BACK;
	}

	if (bJoystickExists)
	{
		JOYINFO joyinfo;

		// if no errors, proceed with joystick routines

		if (joyGetPos(m_uiJoyStick, &joyinfo) == JOYERR_NOERROR)
		{
			// joystick left

			if (joyinfo.wXpos < joy_left)
			{
				move = MOVE_LEFT;
				turn = MOVE_LEFT;
			}

			// joystick right

			else if (joyinfo.wXpos > joy_right)   
			{
				move = MOVE_RIGHT;
				turn = MOVE_RIGHT;
			}

			// joystick up

		  	if (joyinfo.wYpos < joy_up)
			{
//				m_camera->SetVelocity(m_camera, D3DVALUE(0),D3DVALUE(0),D3DVALUE(0.5*mul), NULL);
				move = MOVE_FORWARD;
			}

			// joystick down

			else if (joyinfo.wYpos > joy_down)
			{
//				m_camera->SetVelocity(m_camera, D3DVALUE(0),D3DVALUE(0),D3DVALUE(-0.5*mul), NULL);
				move = MOVE_BACK;
			}
		}
	}

	// handle navigation

	if (bNormalNavigation)
	{
		if ((move_count < 1) && (rotate_count < 1))
		{
			navbarframe = InterfaceTree[interface_pos].nav_bar_frame;
			if (move != MOVE_NONE)
			{
				for (i = 0; i < 3; i++)
				{
					if (InterfaceTree[interface_pos].exit_control[i] == move)
					{
						bTextDraw = TRUE;
						rotate_count = InterfaceTree[interface_pos].rotate_time[i];
						move_count = InterfaceTree[interface_pos].move_time[i];
						m_camera->GetOrientation(m_scene, &bufferz, &buffery);
						m_camera->GetPosition(m_scene, &buffer);
						m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), 
							D3DVALUE((atan(bufferz.z
							/bufferz.x)
							-atan(InterfaceTree[InterfaceTree[interface_pos].exit[i]].orientation.z
							/InterfaceTree[InterfaceTree[interface_pos].exit[i]].orientation.x)
							+InterfaceTree[interface_pos].exit_rotate_offset[i])
							/rotate_count));
						interface_pos = InterfaceTree[interface_pos].exit[i];
						m_camera->SetVelocity(m_scene, D3DVALUE(
							(InterfaceTree[interface_pos].position.x
							-buffer.x)/move_count), D3DVALUE(0), D3DVALUE(
							(InterfaceTree[interface_pos].position.z
							-buffer.z)/move_count), FALSE);
						i = 10;
						switch (interface_pos)
						{
						case POS_START:
							text_num = START_TEXT;
							break;
						case POS_SIGN:
							if (current_surfer == NO_ONE)
								text_num = NEED_A_SURFER;
							else if (bContest)
							{
								text_num = CONTEST_STATS_TEXT;
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							else
							{
								text_num = BEACH_TEXT;
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							break;
						case POS_DOOR_LIP:
							if (current_surfer == NO_ONE)
								text_num = NEED_A_SURFER;
							else if (bContest)
							{
								text_num = CONTEST_STATS_TEXT;
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							else
							{
								text_num = THRASH_STATS_TEXT;
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							break;
						case POS_INT_LIP:
							if (bContest)
							{
								text_num = PURCHASE_TEXT;
								if (contest_score[current_surfer] >= 50000)
									Purchase = 2;
								else if (contest_score[current_surfer] >= 30000)
									Purchase = 1;
								else
									Purchase = 0;
								if (bAlreadyPurchased)
									Purchase = 0;
							}
							else 
								text_num = NOT_CONTEST_EQUIP_TEXT;
							break;
						case POS_CENT_SIGN:
							text_num = DEFAULT_TEXT;
							if (current_surfer != NO_ONE)
								m_scene->DeleteChild(surfer[current_surfer]);
							break;
						case POS_CENT_LIP:
						case POS_CENT_SHACK:
							if (current_surfer == NO_ONE)
								text_num = PICK_A_SURFER_TEXT;
							else if (bContest)
							{
								text_num = OPPONENTS_TEXT;
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							else
							{
								text_num = current_surfer;
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							break;
						case POS_SHACK:
#ifdef SHAREWARE
							text_num = CREDITS_TEXT;
#else
							text_num = LOAD_TEXT;
#endif
							if (current_surfer != NO_ONE)
							{
								m_scene->DeleteChild(surfer[current_surfer]);
							}
							break;
						default:
							text_num = NO_TEXT;
							break;
						}
					}	
				}
			}
		}
		if (rotate_count > 0)
			rotate_count--;
		else
			m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));

		if (move_count > 0)
			move_count--;
		else 
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
	}
	else
	{
		if (turn == MOVE_LEFT)
			m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(-0.1));
		else if (turn == MOVE_RIGHT)
			m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(0.1));
		else
			m_camera->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));

		if (move == MOVE_FORWARD)
			m_camera->SetVelocity(m_camera, D3DVALUE(0), D3DVALUE(0), D3DVALUE(1), FALSE);
		else if (move == MOVE_BACK)
			m_camera->SetVelocity(m_camera, D3DVALUE(0), D3DVALUE(0), D3DVALUE(-1), FALSE);
		else
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
	}

#ifndef SHAREWARE
	switch (text_num)
	{
	case PURCHASE_TEXT:
		if (Fire(FALSE))
		{
			if ((Purchase > 0) && !bAlreadyPurchased)
			{
				if (Purchase == 2)
					ConfirmationText = " Ding Repair ";
				else
					ConfirmationText = " Surfin' Wax ";
				ConfirmationResponse = NO_CONFIRMATION;
				bConfirmation = TRUE;
				ConfirmationReason = PURCHASE_CONFIRMATION;
				if (bNaration || bSoundFx || bSurferSounds)
					AddAnnounce(randInt(USUREDAVE,USUREDAVE+2));
			}
		}
/*
		else if ((move == MOVE_FORWARD) && !bAlreadyPurchased)
		{
			if (Purchase < 2)
			{
				purhold = Purchase;
				Purchase++;
				if ((Purchase == 2) && (contest_score[current_surfer] < 50000))
					Purchase = 1;
				if ((Purchase == 1) && (contest_score[current_surfer] < 30000))
					Purchase = 0;
				if (purhold != Purchase)
					bTextDraw = TRUE;
			}
		}
		else if ((move == MOVE_BACK) && !bAlreadyPurchased)
		{
			if (Purchase > 0)
			{
				purhold = Purchase;
				Purchase--;
				if ((Purchase == 2) && (contest_score[current_surfer] < 50000))
					Purchase = 1;
				if ((Purchase == 1) && (contest_score[current_surfer] < 30000))
					Purchase = 0;
				if (purhold != Purchase)
					bTextDraw = TRUE;
			}
		}
	*/
		break;
	case LOAD_TEXT:
		if (Fire(TRUE))
		{
			ConfirmationText = " Load Game   ";
			ConfirmationText[11]=letters[last_load+1];
			ConfirmationResponse = NO_CONFIRMATION;
			bConfirmation = TRUE;
			ConfirmationReason = LOAD_CONTEST;
			if (bNaration || bSoundFx || bSurferSounds)
				AddAnnounce(randInt(USUREDAVE,USUREDAVE+2));
		}
		else if (move == MOVE_RIGHT)
		{
			last_load++;
			if (last_load > 5)
				last_load = 0;
			bTextDraw = TRUE;
		}
		else if (move == MOVE_LEFT)
		{
			last_load--;
			if (last_load < 0)
				last_load = 5;
			bTextDraw = TRUE;
		}
		break;
	case SAVE_TEXT:
		if (Fire(TRUE))
		{
			ConfirmationText = " Save Game   ";
			ConfirmationText[11]=letters[last_save+1];
			ConfirmationResponse = NO_CONFIRMATION;
			ConfirmationReason = SAVE_CONTEST;
			bConfirmation = TRUE;
			if (bNaration || bSoundFx || bSurferSounds)
				AddAnnounce(randInt(USUREDAVE,USUREDAVE+2));
		}
		else if (move == MOVE_RIGHT)
		{
			last_save++;
			if (last_save > 5)
				last_save = 0;
			bTextDraw = TRUE;
		}
		else if (move == MOVE_LEFT)
		{
			last_save--;
			if (last_save < 0)
				last_save = 5;
			bTextDraw = TRUE;
		}
		break;
	}
#endif

	if (Fire(FALSE))
	{
		// select character etc
#ifndef NO_SURFERS
#ifdef SHAREWARE
		if ((interface_pos == POS_CENT_LIP) && !bContest)
		{
			if (current_surfer != NO_ONE)
			{
				m_scene->AddChild(surfer[current_surfer]);
				surf_animate[current_surfer]->SetTime(D3DVALUE(156));
			}
			current_surfer += 2;
			if (current_surfer > LEE)
				current_surfer = ALANA;
			if (bNaration || bSoundFx || bSurferSounds)
#ifdef SHAREWARE
				if (current_surfer == ALANA)
					AddAnnounce(ALANADAVE);
				else
					AddAnnounce(LEEDAVE);
#else
				AddAnnounce(ALANADAVE + current_surfer);
#endif
			text_num = current_surfer;
			bTextDraw = TRUE;
		}
		else
#else
		if ((interface_pos == POS_CENT_LIP) && !bContest)
		{
			if (current_surfer != NO_ONE)
			{
				m_scene->AddChild(surfer[current_surfer]);
				surf_animate[current_surfer]->SetTime(D3DVALUE(156));
			}
			if (current_surfer/2 != (int)((float)current_surfer/2+0.5))
				current_surfer = ALANA-2;
			current_surfer += 2;
			if (current_surfer > TODD)
				current_surfer = ALANA;
			if (bNaration || bSoundFx || bSurferSounds)
				AddAnnounce(ALANADAVE + current_surfer);
			text_num = current_surfer;
			bTextDraw = TRUE;
		}
		else if ((interface_pos == POS_CENT_SHACK) && !bContest)
		{
			if (current_surfer != NO_ONE)
			{
				m_scene->AddChild(surfer[current_surfer]);
				surf_animate[current_surfer]->SetTime(D3DVALUE(156));
			}
			if (current_surfer/2 == (int)((float)current_surfer/2+0.5))
				current_surfer = BUCKY-2;
			current_surfer += 2;
			if (current_surfer > VIC)
				current_surfer = BUCKY;
			if (bNaration || bSoundFx || bSurferSounds)
				AddAnnounce(ALANADAVE + current_surfer);
			text_num = current_surfer;
			bTextDraw = TRUE;
		}
		else
#endif
#endif
		// lip shit

#ifndef SHAREWARE
		if ((interface_pos == POS_DOOR_LIP) &&
			current_surfer != NO_ONE)
		{
			if (bContest)
			{
				ConfirmationText = " Exit Contest";
				ConfirmationReason = EXIT_CONTEST;
			}
			else
			{
				ConfirmationText = "Enter Contest";
				ConfirmationReason = ENTER_CONTEST;
			}
			ConfirmationResponse = NO_CONFIRMATION;
			bConfirmation = TRUE;
			if (bNaration || bSoundFx || bSurferSounds)
				AddAnnounce(randInt(USUREDAVE,USUREDAVE+2));
		}
		else 
#endif
		// shack shit

		if (interface_pos == POS_SHACK)
		{
			text_num++;
			if (text_num > HELP_TEXT_4)
				text_num = CREDITS_TEXT;
#ifdef SHAREWARE
			else if (text_num == LOAD_TEXT)
				text_num = HELP_TEXT_1;
#endif
			else if ((text_num == SAVE_TEXT) && (!bContest || !bInContest[current_surfer]))
				text_num++;
			bTextDraw = TRUE;
		}

		// surf!

		else if ((interface_pos == POS_SIGN) && (current_surfer != NO_ONE))
		{
			if (!bContest || bInContest[current_surfer])
			{
				bCharselect = FALSE;
				bFirstSelect = TRUE;
				if (bMIDIMusic)
				{
					bMIDIMusic = FALSE;
					OnMidiMusic();
				}
				if (bCDMusic)
				{
					playCDTrack(current_surfer+3);
				}
#ifndef NO_SURFERS
#ifdef SHAREWARE
				for (i = 0; i < 3; i+=2)
				{
					if (i != current_surfer)
						m_scene->DeleteChild(surfer[i]);
				}
#else
				for (i = 0; i < 6; i ++)
				{
					if (i != current_surfer)
						m_scene->DeleteChild(surfer[i]);
				}
#endif
#endif
				m_scene->AddChild(surfer[current_surfer]);
				surfer[current_surfer]->AddChild(child_of_the_wave);

				m_scene->AddChild(wave);
				if (bBreakingWave || bContest)
					m_scene->AddChild(curl_frame);
				if (bFoam)
				{
					for (i = 0; i < NUMFOAM; i++)
					{
						m_scene->AddChild(foam[i]);
						foam[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
					}
				}
				if (bGore)
				{
					for (i = 0; i < NUMBLOOD; i++)
						m_scene->AddChild(blood[i]);
				}
				if (bHorizon)
					m_scene->AddChild(beach_frame);
				if (bSprayOn)
				{
					for (i = 0; i < NUMSPRAY; i++)
					{
						m_scene->AddChild(spray[i]);
					}
				}
				m_scene->AddChild(barrel);
				m_scene->AddChild(leftbouy);
				m_scene->AddChild(ritebouy);
				m_scene->AddChild(pier);
				m_scene->AddChild(oilrig);
				surfer[current_surfer]->AddChild(sharkhead);
	
				pier->SetPosition(m_scene, D3DVALUE(2000), D3DVALUE(-32), D3DVALUE(-7440));
				pier->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(PIER_SPEED), NULL);
				oilrig->SetPosition(m_scene, D3DVALUE(-2000), D3DVALUE(0), D3DVALUE(-3240));
				oilrig->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(PIER_SPEED), NULL);
				m_scene->AddChild(dolphin);
				m_scene->AddChild(rock);

				m_scene->DeleteChild(intro_scene);
#ifndef NO_SURFERS
				m_scene->DeleteChild(shopguys);
				m_scene->DeleteChild(trophy);
#endif

				m_camera->SetRotation(m_scene, D3DVALUE(0),D3DVALUE(0),D3DVALUE(0),D3DVALUE(0));
				m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
				
				old_dither = m_lpDev->GetDither();
				old_quality = m_lpDev->GetQuality();
				old_shades = m_lpDev->GetShades();

				if (m_view != NULL)
				{
					m_view->Render(m_scene);
					m_view->Release();
					m_view = NULL;
				}
//				m_lpDev->Release();

				if (lpBackBuffer)
				{
					lpBackBuffer->Release();
					lpBackBuffer = NULL;
				}

			    memset(&ddsd,0,sizeof(DDSURFACEDESC));
			    ddsd.dwSize = sizeof( ddsd );

				// back buffer

				if (bFullscreen)
				{
					DDSCAPS ddscaps;
				    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
				    LastError = lpFrontBuffer->GetAttachedSurface(&ddscaps, &lpBackBuffer);
				    if(LastError != DD_OK) 
					{
				        if (bShowErrors) MessageBox(MyErrorToString(LastError), "GetAttachedSurface failed to get back buffer.");
				        return;
				    }
//				    GetDDSurfaceDesc(&ddsd, lpBackBuffer);
//				    if (!(ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY))
//				        bOnlySoftRender;
				}
				else
				{
					ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
					ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
					ddsd.dwHeight = ModeCy;
					ddsd.dwWidth = ModeCx;
					if (bOnlySystemMemory)
					    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
					LastError = lpDD->CreateSurface(&ddsd, &lpBackBuffer, NULL);
					if(LastError != DD_OK) 
					{
					    if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Back buffer failed.");
						return;
					}
				}

				if (lpHalfresBuffer)
				{
					lpHalfresBuffer->Release();
					lpHalfresBuffer = NULL;
				}

				// halfres buffer
				ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
				ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
				ddsd.dwHeight = ModeCy/2;
				ddsd.dwWidth = ModeCx/2;
				if (bOnlySystemMemory)
				    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
				LastError = lpDD->CreateSurface(&ddsd, &lpHalfresBuffer, NULL );
				if(LastError != DD_OK) 
				{
				    if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Halfres buffer failed.");
				    return;
				}

				if (bHalfres)
				{
				    LastError = FindDevice(lpHalfresBuffer);
				    if(LastError != DD_OK ) 
					{
				        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
						return;
					}
				}
				else
				{
				    LastError = FindDevice(lpBackBuffer);
				    if(LastError != DD_OK ) 
					{
						if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
				        return;
					}
				}
				
				m_lpDev->SetDither(old_dither);
				m_lpDev->SetQuality(old_quality);
				m_lpDev->SetShades(old_shades);
				m_lpDev->SetTextureQuality(TextureFiltering);

			    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
					m_lpDev->GetWidth(), 
					m_lpDev->GetHeight(), &m_view);

			    m_view->SetBack(D3DVAL(GAME_BACK));

				lives = 3;
				score = 0;

				ApplyStats();

				dydeltasc = (const float)0;
				dzdeltasc = (const float)0;
				wydeltasc = (const float)1.8;
				wzdeltasc = (const float)1.8;
				game_time = (const float)0;
				curlpos_off = (const float)10000;
				bPitch = FALSE;
				curl_width = (const float)30.32034632;
				surferstartpos_x = (const float)0;
				bDrop = FALSE;
				bCloseOut = FALSE;
				RestartSurfer();
				if (bSoundFx)
				{
					m_pDSBuffer[OCEANSND]->SetVolume(0);
					m_pDSBuffer[STEAMSHIPWAVE]->SetVolume(0);
				}

//				if (bSoundFx)
//			 		m_pDSBuffer[current_surfer]->Play(0, 0, 0);
			}
		}
	}
}

void CsurfView::UpdateWorld()
{
	int i,j,l;
	static BOOL escrepeat = TRUE;
	static int last_collide = NO_COLLIDE;
	static D3DVECTOR last_sbuffer;
	DWORD status;
	static BOOL bLastCollide= FALSE;
//	BOOL bLightChange = FALSE;
//	static BOOL bLastLightChange = FALSE;
	BOOL bNoCollide = !bLastCollide;
	bLastCollide = FALSE;
	BOOL bAutoUsed = FALSE;
	static BOOL	bPlayTubeSound = TRUE;
	// ufo, collision, etc
	D3DVECTOR sbuffer;
	D3DVECTOR ubuffer;
	D3DVECTOR vbuffer;
	BOOL THISXMIN;
	BOOL THISXMAX;
	BOOL THISYMIN;
	BOOL THISYMAX;
	BOOL THISZMIN;
	BOOL THISZMAX;
	float y;
	static BOOL bUfoCollide = TRUE;

	this_tick = timeGetTime();
	fGameSpeed = D3DVAL((float)((this_tick - prev_tick)/100.0));
//	if (fGameSpeed > 2.5)
//		fGameSpeed = (float)2.5;
	prev_tick = this_tick;

	  // this will make smoother gameplay...
	 //  averaging destroys "chunks"
	//	 but for some strange reason it goes weird.
	if (fGameSpeed <= 0.0)
	{
		if (num_ticks > 0.0)
		{
			total_ticks = total_ticks/num_ticks*10;
			num_ticks = 10;
		}
		else
		{
			total_ticks = (const float)10;
			num_ticks = 10;
		}
		return;
	}
	num_ticks++;
	total_ticks += fGameSpeed;
	if (fGameSpeed > (total_ticks/num_ticks*1.5))
		fGameSpeed = total_ticks/num_ticks*(const float)1.5;
	else if (fGameSpeed < (total_ticks/num_ticks*0.75))
		fGameSpeed = total_ticks/num_ticks*(const float)0.75;

	if (bCDMusic)
	{
		MCI_STATUS_PARMS lpStatus;
		lpStatus.dwItem = MCI_STATUS_MODE;

	    if (!mciSendCommand(wCDDeviceID, MCI_STATUS, 
		    MCI_STATUS_ITEM, (DWORD)(LPVOID) &lpStatus))
	    {
			if ((lpStatus.dwReturn & MCI_MODE_OPEN) == MCI_MODE_OPEN)
			{
				OnCdMusic();
			}
			else if ((lpStatus.dwReturn & MCI_MODE_STOP) == MCI_MODE_STOP)
			{
				{
					bSecretTrack = FALSE;
					extraCDsong++;
					if (extraCDsong>16)
						extraCDsong = 10;
					playCDTrack(extraCDsong);
				}
			}
		}
	}

	if ((bAppPaused && !bFullscreen) || !bOkGo)
	{
		ResetFps();
		return;
	}

	numframes++;

	if ((::GetAsyncKeyState(VK_ESCAPE) <0) && !escrepeat && bFullscreen)
	{
		FullscreenFailed(FALSE);
	}
	else
	{
		escrepeat = FALSE;
	}

	if (bSoundFx)
	{
		if (randInt(0,100) > 98)
		{
			m_pDSBuffer[SEAGULL1]->GetStatus(&status);
			if ((status & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
			{
				m_pDSBuffer[SEAGULL1]->SetPan(randInt(-8000,8000));
				m_pDSBuffer[SEAGULL1]->Play(0, 0, 0);
			}
		}
		if (randInt(0,100) > 98)
		{
			m_pDSBuffer[SEAGULL2]->GetStatus(&status);
			if ((status & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
			{
				m_pDSBuffer[SEAGULL2]->SetPan(randInt(-8000,8000));
				m_pDSBuffer[SEAGULL2]->Play(0, 0, 0);
			}
		}
		if (randInt(0,200) > 198)
		{
			m_pDSBuffer[STEAMSHIPWAVE]->GetStatus(&status);
			if ((status & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
			{
				m_pDSBuffer[STEAMSHIPWAVE]->SetPan(randInt(-5000,5000));
//				m_pDSBuffer[STEAMSHIPWAVE]->SetVolume(randInt(-1500,0));
				m_pDSBuffer[STEAMSHIPWAVE]->Play(0, 0, 0);
			}
		}
	}
	if (bNaration || (bCharselect && (bSurferSounds || bSoundFx)))
	{
		AddAnnounce(SOUND_PLAY);
	}
	if (bSurferSounds)
	{
		AddSurferSound(SOUND_PLAY);
	}

	// highscore is handled elsewhere, so if there is one, just do nothing and
	// exit the if/else stuff...

	D3DVECTOR buffer;
	if (bGameOver && !bHiscore)
	{
		gameovert++;
		if (bNaration && (gameovert == 10))
		{
#ifndef SHAREWARE
			if (bContest)
			{
				if (bFirstRun)
					AddAnnounce(randInt(RUNOVERDAVE,RUNOVERDAVE+2));
				else
					AddAnnounce(randInt(HEATOVERDAVE,HEATOVERDAVE+2));
			}
			else
#endif
				AddAnnounce(randInt(GAMEOVERDAVE,GAMEOVERDAVE+3));
		}

		MoveWave();
		if (bSplat)
		{
			if ((splat_time >= 0) && (splat_time < NUMBLOOD))
				blood[splat_time]->SetPosition(surfer[current_surfer], D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
			if ((splat_time >= 1) && (splat_time < NUMBLOOD+1))
				blood[splat_time-1]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			splat_time++;
		}
		if (bSprayOn)
		{
			for (i = NUMSPRAY-2; i >= 0; i--)
			{
				spray[i+1]->SetPosition(spray[i], D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
				spray_used[i+1] = spray_used[i];
				spray_size[i+1] += 5;
				lpSprayMap[i+1]->SetDecalSize(spray_size[i+1], spray_size[i+1]);
			}
			spray[0]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			spray_used[0] = TRUE;
		}
		m_scene->Move(fGameSpeed);
		Render();
		m_camera->GetPosition(m_scene, &buffer);
		if (buffer.y > 200) 
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
		if (Fire(FALSE))
		{
			if (bContest)
			{
				for (i = 0; i < 6; i++)
				{
					if (bInContest[i])
					{
						if (current_surfer != i)
						{
							// ai logic: Simplified to become more fair...

							// odds look like this:

							// surfer score // odds of ai beating you

							// 0				100%
							// 5000				100%
							// 8000				100%
							// 9000				71%
							// 10000			56%
							// 10500			50% * break even at 10500
							// 15000			26%
							// 20000			17%
							// 25000			13%
							// 30000			10%
							// 35000			8%
							// 40000			7%

							if (score > 10000)
								contest_score[i] += randInt(8000,score+3000);
							else
								contest_score[i] += randInt(8000,13000);
						}
						else
						{
							contest_score[i] += score;
						}
					}
				}
				bFirstRun = !bFirstRun;
				if (bFirstRun)
				{
					Heat++;
					for (i = 0; i < 6; i++)
					{
						for (j = i; j < 6; j++)
						{
							if (contest_score[contest_place[j]] > contest_score[contest_place[i]])
							{
								l = contest_place[i];
								contest_place[i] = contest_place[j];
								contest_place[j] = l;
							}
						}
						if (i >= (6-Heat))
						{
							bInContest[contest_place[i]] = FALSE;
						}
					}
				}
			}
			if (lpDDGuid[DDDriverNum[D3DDriver]] != NULL)
				FullscreenFailed(FALSE);
			lives = 0;
			bGameOver = FALSE;
			bHiscore = FALSE;
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			UpdateSpeedometer();
			bCharselect = TRUE;
			escrepeat = TRUE;
		}
	}
	else if ((bHiscore && !bCharselect) || bGameOver)
	{
		gameovert++;
		if (bNaration && (gameovert == 10))
			AddAnnounce(randInt(HISCORE1,HISCORE1+2));
		MoveWave();
		if (bSplat)
		{
			if ((splat_time >= 0) && (splat_time < NUMBLOOD))
				blood[splat_time]->SetPosition(surfer[current_surfer], D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
			if ((splat_time >= 1) && (splat_time < NUMBLOOD+1))
				blood[splat_time-1]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			splat_time++;
		}
		if (bSprayOn)
		{
			for (i = NUMSPRAY-2; i >= 0; i--)
			{
				spray[i+1]->SetPosition(spray[i], D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
				spray_used[i+1] = spray_used[i];
				spray_size[i+1] +=5;
				lpSprayMap[i+1]->SetDecalSize(spray_size[i+1], spray_size[i+1]);
			}
			spray[0]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			spray_used[0] = TRUE;
		}
		m_scene->Move(fGameSpeed);
		Render();
		m_camera->GetPosition(m_scene, &buffer);
		if (buffer.y > 200) 
			m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
		return;
	}

	// character select calls select character on every display loop

	else if (bCharselect)
	{
		SelectCharacter();
		return;
	}

	// otherwise, we are in the game!

	else
	{
		//f12 exits

		if (::GetAsyncKeyState(VK_F12) <0)
		{
			lives = 0;
			bGameOver = FALSE;
			bHiscore = FALSE;
			UpdateSpeedometer();
			bCharselect = TRUE;

			escrepeat = TRUE;
			return;
		}

		if (bNoCollideCheck)
		{
			surfer[current_surfer]->GetPosition(m_scene, &last_sbuffer);
			bNoCollideCheck = FALSE;
		}

#define LASTX		last_sbuffer.x
#define LASTY		last_sbuffer.y
#define LASTZ		last_sbuffer.z
#define THISX		sbuffer.x
#define THISY		sbuffer.y
#define THISZ		sbuffer.z
#define UFOMINX		(ubuffer.x-80)
#define UFOMAXX		(ubuffer.x+80)
#define UFOMINY		(ubuffer.y-10)
#define UFOMAXY		(ubuffer.y+10)
#define UFOMINZ		(ubuffer.z-80)
#define UFOMAXZ		(ubuffer.z+80)
#define PLIDMINX	1889
#define PLIDMAXX	2114
#define PLIDMINY	(ubuffer.y+138)
#define PLIDMAXY	(ubuffer.y+157)
#define PLIDMINZ	(ubuffer.z+211)
#define PLIDMAXZ	(ubuffer.z+1567)

#define RLIDMINX	-2498
#define RLIDMAXX	-1504
#define RLIDMINY	(ubuffer.y+169)
#define RLIDMAXY	(ubuffer.y+189)
#define RLIDMINZ	(ubuffer.z+886)
#define RLIDMAXZ	(ubuffer.z+1657)
#define RPOSTMINX1	-2206
#define RPOSTMAXX1	-2171
#define RPOSTMINX2	-1839
#define RPOSTMAXX2	-1804
#define RPOSTMINX3	-1577
#define RPOSTMAXX3	-1542
#define RPOSTMINX4	-2211
#define RPOSTMAXX4	-2176
#define RPOSTMINX5	-1834
#define RPOSTMAXX5	-1799
#define RPOSTMINX6	-2465
#define RPOSTMAXX6	-2430

#define RPOSTMINZ1	(ubuffer.z+1596)
#define RPOSTMAXZ1	(ubuffer.z+1641)
#define RPOSTMINZ2	(ubuffer.z+1591)
#define RPOSTMAXZ2	(ubuffer.z+1626)
#define RPOSTMINZ3	(ubuffer.z+1251)
#define RPOSTMAXZ3	(ubuffer.z+1286)
#define RPOSTMINZ4	(ubuffer.z+912)
#define RPOSTMAXZ4	(ubuffer.z+947)
#define RPOSTMINZ5	(ubuffer.z+908)
#define RPOSTMAXZ5	(ubuffer.z+943)
#define RPOSTMINZ6	(ubuffer.z+1252)
#define RPOSTMAXZ6	(ubuffer.z+1286)

#define POSTMINX1	1889
#define POSTMAXX1	1923
#define POSTMINX2	2079
#define POSTMAXX2	2114
#define POSTMINZ1	(ubuffer.z+1515)
#define POSTMAXZ1	(ubuffer.z+1549)
#define POSTMINZ2	(ubuffer.z+1251)
#define POSTMAXZ2	(ubuffer.z+1286)
#define POSTMINZ3	(ubuffer.z+1003)
#define POSTMAXZ3	(ubuffer.z+1038)
#define POSTMINZ4	(ubuffer.z+740)
#define POSTMAXZ4	(ubuffer.z+775)
#define POSTMINZ5	(ubuffer.z+500)
#define POSTMAXZ5	(ubuffer.z+535)
#define POSTMINZ6	(ubuffer.z+236)
#define POSTMAXZ6	(ubuffer.z+262)
#define LBOUYMINX	-23-BOUNDARY
#define LBOUYMAXX	23-BOUNDARY
#define RBOUYMINX	-23+BOUNDARY
#define RBOUYMAXX	23+BOUNDARY
#define BOUYMAXY	(ubuffer.y+35)
#define BOUYMINZ	(ubuffer.z-23)
#define BOUYMAXZ	(ubuffer.z+23)
#define BARRELMINX	(ubuffer.x-27)
#define BARRELMAXX	(ubuffer.x+27)
#define BARRELMINY	(ubuffer.y-31)
#define BARRELMAXY	(ubuffer.y+31)
#define BARRELMINZ	(ubuffer.z-27)
#define BARRELMAXZ	(ubuffer.z+27)
#define ROCKMINX	(ubuffer.x-50)
#define ROCKMAXX	(ubuffer.x+49)
#define ROCKMAXY	(ubuffer.y+59)
#define ROCKMINZ	(ubuffer.z-40)
#define ROCKMAXZ	(ubuffer.z+58)
#define DOLPHINMINX (ubuffer.x-25)
#define DOLPHINMAXX (ubuffer.x+25)
#define DOLPHINMINY (ubuffer.y-27)
#define DOLPHINMAXY (ubuffer.y+25)
#define DOLPHINMINZ (ubuffer.z-60)
#define DOLPHINMAXZ (ubuffer.z+63)
#define CURLMINX	curlpos_x-curl_width+curlpos_off
#define CURLMAXX	curlpos_x+curl_width-curlpos_off

		surfer[current_surfer]->GetPosition(m_scene, &sbuffer);
		if (bBreakingWave || bContest)
		{
			if ((THISX != curlpos_x) && !bNotDroppedInYet && !bWipeout)
				curlpos_x += (THISX - curlpos_x)/40*fGameSpeed;
		}

		if (bUfo)
		{
			ufo->GetPosition(m_scene, &ubuffer);
			if (current_frame >= LIP_FRAME)
				bUfoCollide = FALSE;
			if (bUfoCollide)
			{
				if (current_surfer == BUCKY)
				{
					if (ubuffer.x < 0)
						ufo->SetVelocity(m_scene, D3DVALUE(5), D3DVALUE(5), D3DVALUE(10), FALSE);
					else
						ufo->SetVelocity(m_scene, D3DVALUE(-5), D3DVALUE(5), D3DVALUE(10), FALSE);
				}
				else
				{
					if (ubuffer.x < 0)
						ufo->SetVelocity(m_scene, D3DVALUE(10), D3DVALUE(10), D3DVALUE(20), FALSE);
					else
						ufo->SetVelocity(m_scene, D3DVALUE(-10), D3DVALUE(10), D3DVALUE(20), FALSE);
				}
			}
			else if (current_surfer == BUCKY)
			{
				y = (sbuffer.y - ubuffer.y + 130)/2;
				if (ubuffer.y < frame_y[LIP_FRAME] + 90);
					y = (frame_y[LIP_FRAME] - ubuffer.y + 130)/2;
				ufo->SetVelocity(m_scene, (sbuffer.x - ubuffer.x)/10, y, (sbuffer.z - ubuffer.z)/40, FALSE);
			}
			else
			{
				y = (sbuffer.y - ubuffer.y + 170)/2;
				if (ubuffer.y < frame_y[LIP_FRAME] + 130);
					y = (frame_y[LIP_FRAME] - ubuffer.y + 170)/2;
				ufo->SetVelocity(m_scene, (sbuffer.x - ubuffer.x)/20, y, (sbuffer.z - ubuffer.z)/50, FALSE);
			}

			if (!bUfoStop2)
			{
				if (ubuffer.z < 800)
				{
					bUfoStop2 = TRUE;
					if (!bSummoned)
						bUfoStop = TRUE;
					if (bSoundFx)
						AddAnnounce(randInt(UFODAVE,UFODAVE+2));
				}
			}
			if (bSoundFx)
			{
				if (sbuffer.z < ubuffer.z)
					m_pDSBuffer[UFOSTOPWAVE]->SetVolume((long)(sbuffer.z-ubuffer.z));
				else
					m_pDSBuffer[UFOSTOPWAVE]->SetVolume((long)(ubuffer.z-sbuffer.z));
			}

			// ufo collide
			THISXMIN = (THISX >= UFOMINX);
			THISXMAX = (THISX <= UFOMAXX);
			THISYMIN = (THISY >= UFOMINY);
			THISYMAX = (THISY <= UFOMAXY);
			THISZMIN = (THISZ >= UFOMINZ);
			THISZMAX = (THISZ <= UFOMAXZ);
			if (((THISXMIN && THISXMAX)
				|| ((LASTX <= UFOMINX) && THISXMIN)
				|| ((LASTX >= UFOMAXX) && THISXMAX))
				&& ((THISYMIN && THISYMAX)
				|| ((LASTY <= UFOMINY) && THISYMIN)
				|| ((LASTY >= UFOMAXY) && THISYMAX))
				&& ((THISZMIN && THISZMAX)
				|| ((LASTZ <= UFOMINZ) && THISZMIN)
				|| ((LASTZ >= UFOMAXZ) && THISZMAX)))
			{
				bUfoCollide = TRUE;
				if (bNoCollide || (last_collide != UFO))
				{
					surfer[current_surfer]->GetVelocity(ufo, &vbuffer, FALSE);
					if (current_surfer != BUCKY)
					{
						score += 7500;
						if (bNaration)
							AddAnnounce(randInt(ALIEN,ALIEN+2));
						if (!bWipeout)
						{
							animate_time = (const float)146;
							bWipeout = TRUE;
						}
						if (bGore)
						{
							bSplat = TRUE;
							splat_time = 0;
						}
						camera_type = (randInt(0,20) < 15) ? ROCK_VIDEO_CAMERA : MAIN_CAMERA;
						bAutoUsed = TRUE;
						surfer[current_surfer]->SetVelocity(ufo, D3DVALUE(randInt(-40,40)), D3DVALUE(randInt(40,80)), D3DVALUE(randInt(-60,60)), NULL);
						if (bSoundFx)
				 			m_pDSBuffer[UFOCWAVE]->Play(0, 0, 0);
					}
					else
					{
						if (bSurferSounds)
						{
							AddSurferSound(INSANITY_SOUND);
						}
						if (bSoundFx)
					 		m_pDSBuffer[BOUYWAVE2]->Play(0, 0, 0);
						score += (trick == 2) ? 2000 : 1000;
						if ((vbuffer.x<12.0) && (vbuffer.x>-12.0))
						{
							if (vbuffer.x < 0)
								vbuffer.x=(const float)-12;
							else
								vbuffer.x=(const float)12;
						}
						if ((vbuffer.y<0) && (vbuffer.y>-17.0))
						{
							vbuffer.y=(const float)-17;
						}
						surfer[current_surfer]->SetVelocity(ufo, vbuffer.x, -vbuffer.y*(const float)0.7, -vbuffer.z*(const float)0.7, NULL);
					}

					if (bContest)
					{
						board_condition += 5;
						ApplyStats();
					}
				}
				last_collide = UFO;
				bLastCollide = TRUE;
			}
		}

		// shark attack!

		if ((THISX < LBOUYMINX) || (THISX > RBOUYMAXX) || bSharkAttack)
		{
			// increment timer, once it reaches a certain 
			// value, shark eats surfer.  Worry about fin later.
			if ((current_frame >= LIP_FRAME) || bSharkAttack)
				sharktime++;
			if (sharktime == 15)
			{
				if (bNaration && !bWipeout)
					AddAnnounce(randInt(SHARKDAVE,SHARKDAVE+2));
				sharktime++;
			}
			if (sharktime > 30)
			{
				if ((sharktime == 32) && bSurferSounds)
				{
					AddSurferSound(WIPEOUT_SOUND);
					if (bContest)
					{
						board_condition += 25;
						ApplyStats();
					}
				}
				// eat surfer!
				surfer[current_surfer]->GetOrientation(m_scene, &ubuffer, &vbuffer);
				sharkhead->SetOrientation(m_scene, ubuffer.x, D3DVALUE(0), ubuffer.z, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
				sharkhead->SetPosition(surfer[current_surfer], D3DVALUE(0), D3DVALUE(50), D3DVALUE(0));
			}
			else if (sharktime > 20)
			{
				surfer[current_surfer]->GetOrientation(m_scene, &ubuffer, &vbuffer);
				sharkhead->SetOrientation(m_scene, ubuffer.x, D3DVALUE(0), ubuffer.z, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
				sharkhead->SetPosition(surfer[current_surfer], D3DVALUE(0), D3DVALUE(sharktime*5-100), D3DVALUE(0));
				sharkhead_animate->SetTime(sharktime-(const float)20);
				bSharkAttack = TRUE;
				if (bGore)
				{
					bSplat = TRUE;
					splat_time = 0;
				}
			}
		}
		else if (sharktime < 20)
		{
			sharktime = 0;
			sharkhead->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
		}

		// pier lid collide and camera

		pier->GetPosition(m_scene, &ubuffer);

		// at pier?

		if ((THISX >= PLIDMINX) && (THISX <= PLIDMAXX)
			 && (THISZ >= PLIDMINZ) && (THISZ <= PLIDMAXZ))
		{
			if (!bNotDroppedInYet && !bWipeout)
				score += (int)((bUfoStop ? 100.0 : 50.0)*fGameSpeed);
			if (THISY < PLIDMAXY)
			{
			// under pier
				if (bAutoCamera && !bWipeout && (LASTY < PLIDMAXY))
				{
					bAutoUsed = TRUE;
					if	((camera_type == SATELLITE_CAMERA) ||
						(camera_type == HELICOPTER_CAMERA))
					{
						camera_type = BEACH_CAMERA;
					}
				}
			}
			else
			{
			// over pier
				if (bAutoCamera && !bWipeout)
				{
					bAutoUsed = TRUE;
					if ((camera_type != SATELLITE_CAMERA) ||
						(camera_type != ROCK_VIDEO_CAMERA))
					{
						camera_type = SATELLITE_CAMERA;
					}
				}
				bOverPier = TRUE;
			}
			// lid collide
			THISYMIN = (THISY >= PLIDMINY);
			THISYMAX = (THISY <= PLIDMAXY);
			if ((THISYMIN && THISYMAX)
				|| ((LASTY <= PLIDMINY) && THISYMIN)
				|| ((LASTY >= PLIDMAXY) && THISYMAX)
				&& !bNotDroppedInYet)
			{
				if (bNoCollide || (last_collide != PIER))
				{
					if (!bWipeout)
					{
						if (bNaration)
							AddAnnounce(randInt(REEF1,REEF1+12));
						if (bSurferSounds)
							AddSurferSound(WIPEOUT_SOUND);

						animate_time = (const float)146;
						bWipeout = TRUE;
					}
					if (bGore)
					{
						bSplat = TRUE;
						splat_time = 0;
					}
					surfer[current_surfer]->GetVelocity(pier, &vbuffer, NULL);
					if (bContest)
					{
						board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
						ApplyStats();
					}

					if ((vbuffer.x<12.0) && (vbuffer.x>-12.0))
					{
						if (vbuffer.x < 0)
							vbuffer.x=(const float)-12;
						else
							vbuffer.x=(const float)12;
					}
					if ((vbuffer.y<0) && (vbuffer.y>-17.0))
					{
						vbuffer.y=(const float)-17;
					}
					surfer[current_surfer]->SetVelocity(pier, vbuffer.x*(const float)0.7, -vbuffer.y*(const float)0.6, vbuffer.z*(const float)0.6, NULL);
					if (bSoundFx)
				 		m_pDSBuffer[randInt(PLIDWAVE,PLIDWAVE+2)]->Play(0, 0, 0);
				}
				last_collide = PIER;
				bLastCollide = TRUE;
			}
		}
		if (!bNotDroppedInYet)
		{

			// pier post collide

			if ((THISY <= PLIDMINY) || ((LASTY <= PLIDMINY) && (THISY >= PLIDMINY)))
			{
				// x1 or x2
				THISXMIN = (THISX >= POSTMINX1);
				THISXMAX = (THISX <= POSTMAXX1);
				THISZMIN = (THISX >= POSTMINX2);
				THISZMAX = (THISX <= POSTMAXX2);
				if (((THISXMIN && THISXMAX)
					|| ((LASTX <= POSTMINX1) && THISXMIN)
					|| ((LASTX >= POSTMAXX1) && THISXMAX))
					|| ((THISZMIN && THISZMAX)
					|| ((LASTX <= POSTMINX2) && THISZMIN)
					|| ((LASTX >= POSTMAXX2) && THISZMAX)))
				{
					// z1 thru z6
					if   ((((THISZ >= POSTMINZ1) && (THISZ <= POSTMAXZ1))
						|| ((LASTZ <= POSTMINZ1) && (THISZ >= POSTMINZ1))
						|| ((LASTZ >= POSTMAXZ1) && (THISZ <= POSTMAXZ1)))
						||(((THISZ >= POSTMINZ2) && (THISZ <= POSTMAXZ2))
						|| ((LASTZ <= POSTMINZ2) && (THISZ >= POSTMINZ2))
						|| ((LASTZ >= POSTMAXZ2) && (THISZ <= POSTMAXZ2)))
						||(((THISZ >= POSTMINZ3) && (THISZ <= POSTMAXZ3))
						|| ((LASTZ <= POSTMINZ3) && (THISZ >= POSTMINZ3))
						|| ((LASTZ >= POSTMAXZ3) && (THISZ <= POSTMAXZ3)))
						||(((THISZ >= POSTMINZ4) && (THISZ <= POSTMAXZ4))
						|| ((LASTZ <= POSTMINZ4) && (THISZ >= POSTMINZ4))
						|| ((LASTZ >= POSTMAXZ4) && (THISZ <= POSTMAXZ4)))
						||(((THISZ >= POSTMINZ5) && (THISZ <= POSTMAXZ5))
						|| ((LASTZ <= POSTMINZ5) && (THISZ >= POSTMINZ5))
						|| ((LASTZ >= POSTMAXZ5) && (THISZ <= POSTMAXZ5)))
						||(((THISZ >= POSTMINZ6) && (THISZ <= POSTMAXZ6))
						|| ((LASTZ <= POSTMINZ6) && (THISZ >= POSTMINZ6))
						|| ((LASTZ >= POSTMAXZ6) && (THISZ <= POSTMAXZ6))))
					{
						if (bNoCollide || (last_collide != POST))
						{
							if (!bWipeout)
							{
								if (bNaration)
									AddAnnounce(randInt(REEF1,REEF1+12));
								if (bSurferSounds)
									AddSurferSound(WIPEOUT_SOUND);
								animate_time = (const float)146;
								bWipeout = TRUE;
							}
							if (bGore)
							{
								bSplat = TRUE;
								splat_time = 0;
							}
							surfer[current_surfer]->GetVelocity(pier, &vbuffer, NULL);
							if (bContest)
							{
								board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
								ApplyStats();
							}
							surfer[current_surfer]->SetVelocity(pier, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
							if (bSoundFx)
						 		m_pDSBuffer[randInt(POSTWAVE,POSTWAVE+2)]->Play(0, 0, 0);
						}
						last_collide = POST;
						bLastCollide = TRUE;
					}
				}
			}
		}

		// oilrig lid collide and camera

		oilrig->GetPosition(m_scene, &ubuffer);

		// at oilrig?

		if ((THISX >= RLIDMINX) && (THISX <= RLIDMAXX)
			 && (THISZ >= RLIDMINZ) && (THISZ <= RLIDMAXZ))
		{
			if (!bNotDroppedInYet && !bWipeout)
				score += (int)((bUfoStop ? 50.0 : 25.0)*fGameSpeed);
			if (THISY < RLIDMAXY)
			{
			// under oilrig
				if (bAutoCamera && !bWipeout && (LASTY < RLIDMAXY))
				{
					bAutoUsed = TRUE;
					if	((camera_type == SATELLITE_CAMERA) ||
						(camera_type == HELICOPTER_CAMERA))
					{
						camera_type = BEACH_CAMERA;
					}
				}
			}
			else
			{
			// over oilrig
				if (bAutoCamera && !bWipeout)
				{
					bAutoUsed = TRUE;
					if ((camera_type != SATELLITE_CAMERA) ||
						(camera_type != ROCK_VIDEO_CAMERA))
					{
						camera_type = SATELLITE_CAMERA;
					}
				}
				bOverOilRig = TRUE;
			}
			// lid collide
			THISYMIN = (THISY >= RLIDMINY);
			THISYMAX = (THISY <= RLIDMAXY);
			if ((THISYMIN && THISYMAX)
				|| ((LASTY <= RLIDMINY) && THISYMIN)
				|| ((LASTY >= RLIDMAXY) && THISYMAX)
				&& !bNotDroppedInYet)
			{
				if (bNoCollide || (last_collide != OILRIG))
				{
					if (!bWipeout)
					{
						if (bNaration)
							AddAnnounce(randInt(REEF1,REEF1+12));
						if (bSurferSounds)
							AddSurferSound(WIPEOUT_SOUND);

						animate_time = (const float)146;
						bWipeout = TRUE;
					}
					if (bGore)
					{
						bSplat = TRUE;
						splat_time = 0;
					}
					surfer[current_surfer]->GetVelocity(oilrig, &vbuffer, NULL);
					if (bContest)
					{
						board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
						ApplyStats();
					}

					if ((vbuffer.x<12.0) && (vbuffer.x>-12.0))
					{
						if (vbuffer.x < 0)
							vbuffer.x=(const float)-12;
						else
							vbuffer.x=(const float)12;
					}
					if ((vbuffer.y<0) && (vbuffer.y>-17.0))
					{
						vbuffer.y=(const float)-17;
					}
					surfer[current_surfer]->SetVelocity(oilrig, vbuffer.x*(const float)0.7, -vbuffer.y*(const float)0.6, vbuffer.z*(const float)0.6, NULL);
					if (bSoundFx)
				 		m_pDSBuffer[randInt(OILRIGWAVE,OILRIGWAVE+2)]->Play(0, 0, 0);
				}
				last_collide = OILRIG;
				bLastCollide = TRUE;
			}
		}
		if (!bNotDroppedInYet)
		{

			// oilrig post collide

			if (((THISY <= RLIDMINY) || ((LASTY <= RLIDMINY) && (THISY >= RLIDMINY)))

				&& ((((THISX >= RPOSTMINX1) && (THISX <= RPOSTMAXX1))
				|| ((LASTX <= RPOSTMINX1) && (THISX >= RPOSTMINX1))
				|| ((LASTX >= RPOSTMAXX1) && (THISX <= RPOSTMAXX1)))
				&& (((THISZ >= RPOSTMINZ1) && (THISZ <= RPOSTMAXZ1))
				|| ((LASTZ <= RPOSTMINZ1) && (THISZ >= RPOSTMINZ1))
				|| ((LASTZ >= RPOSTMAXZ1) && (THISZ <= RPOSTMAXZ1)))

				|| (((THISX >= RPOSTMINX2) && (THISX <= RPOSTMAXX2))
				|| ((LASTX <= RPOSTMINX2) && (THISX >= RPOSTMINX2))
				|| ((LASTX >= RPOSTMAXX2) && (THISX <= RPOSTMAXX2)))
				&& (((THISZ >= RPOSTMINZ2) && (THISZ <= RPOSTMAXZ2))
				|| ((LASTZ <= RPOSTMINZ2) && (THISZ >= RPOSTMINZ2))
				|| ((LASTZ >= RPOSTMAXZ2) && (THISZ <= RPOSTMAXZ2)))

				|| (((THISX >= RPOSTMINX3) && (THISX <= RPOSTMAXX3))
				|| ((LASTX <= RPOSTMINX3) && (THISX >= RPOSTMINX3))
				|| ((LASTX >= RPOSTMAXX3) && (THISX <= RPOSTMAXX3)))
				&& (((THISZ >= RPOSTMINZ3) && (THISZ <= RPOSTMAXZ3))
				|| ((LASTZ <= RPOSTMINZ3) && (THISZ >= RPOSTMINZ3))
				|| ((LASTZ >= RPOSTMAXZ3) && (THISZ <= RPOSTMAXZ3)))

				|| (((THISX >= RPOSTMINX4) && (THISX <= RPOSTMAXX4))
				|| ((LASTX <= RPOSTMINX4) && (THISX >= RPOSTMINX4))
				|| ((LASTX >= RPOSTMAXX4) && (THISX <= RPOSTMAXX4)))
				&& (((THISZ >= RPOSTMINZ4) && (THISZ <= RPOSTMAXZ4))
				|| ((LASTZ <= RPOSTMINZ4) && (THISZ >= RPOSTMINZ4))
				|| ((LASTZ >= RPOSTMAXZ4) && (THISZ <= RPOSTMAXZ4)))

				|| (((THISX >= RPOSTMINX5) && (THISX <= RPOSTMAXX5))
				|| ((LASTX <= RPOSTMINX5) && (THISX >= RPOSTMINX5))
				|| ((LASTX >= RPOSTMAXX5) && (THISX <= RPOSTMAXX5)))
				&& (((THISZ >= RPOSTMINZ5) && (THISZ <= RPOSTMAXZ5))
				|| ((LASTZ <= RPOSTMINZ5) && (THISZ >= RPOSTMINZ5))
				|| ((LASTZ >= RPOSTMAXZ5) && (THISZ <= RPOSTMAXZ5)))

				|| (((THISX >= RPOSTMINX6) && (THISX <= RPOSTMAXX6))
				|| ((LASTX <= RPOSTMINX6) && (THISX >= RPOSTMINX6))
				|| ((LASTX >= RPOSTMAXX6) && (THISX <= RPOSTMAXX6)))
				&& (((THISZ >= RPOSTMINZ6) && (THISZ <= RPOSTMAXZ6))
				|| ((LASTZ <= RPOSTMINZ6) && (THISZ >= RPOSTMINZ6))
				|| ((LASTZ >= RPOSTMAXZ6) && (THISZ <= RPOSTMAXZ6)))))
			{
				if (bNoCollide || (last_collide != POST))
				{
					if (!bWipeout)
					{
						if (bNaration)
							AddAnnounce(randInt(REEF1,REEF1+12));
						if (bSurferSounds)
							AddSurferSound(WIPEOUT_SOUND);
						animate_time = (const float)146;
						bWipeout = TRUE;
					}
					if (bGore)
					{
						bSplat = TRUE;
						splat_time = 0;
					}
					surfer[current_surfer]->GetVelocity(oilrig, &vbuffer, NULL);
					if (bContest)
					{
						board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
						ApplyStats();
					}

					surfer[current_surfer]->SetVelocity(oilrig, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
					if (bSoundFx)
			 			m_pDSBuffer[randInt(OILLEGWAVE,OILLEGWAVE+2)]->Play(0, 0, 0);
				}
				last_collide = POST;
				bLastCollide = TRUE;
			}
	
			// leftbouy collide
	
			leftbouy->GetPosition(m_scene, &ubuffer);
			THISXMIN = (THISX >= LBOUYMINX);
			THISXMAX = (THISX <= LBOUYMAXX);
			THISZMIN = (THISZ >= BOUYMINZ);
			THISZMAX = (THISZ <= BOUYMAXZ);
			if (((THISXMIN && THISXMAX)
				|| ((LASTX <= LBOUYMINX) && THISXMIN)
				|| ((LASTX >= LBOUYMAXX) && THISXMAX))
				&& ((THISY <= BOUYMAXY)
				|| ((LASTY <= BOUYMAXY) && (THISY >= BOUYMAXY)))
				&& ((THISZMIN && THISZMAX)
				|| ((LASTZ <= BOUYMINZ) && THISZMIN)
				|| ((LASTZ >= BOUYMAXZ) && THISZMAX)))
			{
				if (bNoCollide || (last_collide != LEFTBOUY))
				{
					if (!bWipeout)
					{
						if (bNaration)
							AddAnnounce(randInt(REEF1,REEF1+12));
						if (bSurferSounds)
							AddSurferSound(WIPEOUT_SOUND);
						animate_time = (const float)146;
						bWipeout = TRUE;
					}
					if (bGore)
					{
						bSplat = TRUE;
						splat_time = 0;
					}
					surfer[current_surfer]->GetVelocity(leftbouy, &vbuffer, NULL);
					if (bContest)
					{
						board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
						ApplyStats();
					}

					surfer[current_surfer]->SetVelocity(leftbouy, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
					leftbouy->SetRotation(m_scene, vbuffer.z, vbuffer.y, -vbuffer.x, D3DVALUE(0.2));
					if (bSoundFx)
				 		m_pDSBuffer[randInt(BOUYWAVE,BOUYWAVE+2)]->Play(0, 0, 0);
				}	
				last_collide = LEFTBOUY;
				bLastCollide = TRUE;
			}
	
			// ritebouy collide

			ritebouy->GetPosition(m_scene, &ubuffer);
			THISXMIN = (THISX >= RBOUYMINX);
			THISXMAX = (THISX <= RBOUYMAXX);
			THISZMIN = (THISZ >= BOUYMINZ);
			THISZMAX = (THISZ <= BOUYMAXZ);
			if (((THISXMIN && THISXMAX)
				|| ((LASTX <= RBOUYMINX) && THISXMIN)
				|| ((LASTX >= RBOUYMAXX) && THISXMAX))
				&& ((THISY <= BOUYMAXY)
				|| ((LASTY <= BOUYMAXY) && (THISY >= BOUYMAXY)))
				&& ((THISZMIN && THISZMAX)
				|| ((LASTZ <= BOUYMINZ) && THISZMIN)
				|| ((LASTZ >= BOUYMAXZ) && THISZMAX)))
			{
				if (bNoCollide || (last_collide != RITEBOUY))
				{
					if (!bWipeout)
					{
						if (bNaration)
							AddAnnounce(randInt(REEF1,REEF1+12));
						if (bSurferSounds)
							AddSurferSound(WIPEOUT_SOUND);
						animate_time = (const float)146;
						bWipeout = TRUE;
					}
					if (bGore)
					{
						bSplat = TRUE;
						splat_time = 0;
					}
					surfer[current_surfer]->GetVelocity(ritebouy, &vbuffer, NULL);
					if (bContest)
					{
						board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
						ApplyStats();
					}

					surfer[current_surfer]->SetVelocity(ritebouy, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
					ritebouy->SetRotation(m_scene, vbuffer.z, vbuffer.y, -vbuffer.x, D3DVALUE(0.2));
					if (bSoundFx)
				 		m_pDSBuffer[randInt(BOUYWAVE,BOUYWAVE+2)]->Play(0, 0, 0);
					}
				last_collide = RITEBOUY;
				bLastCollide = TRUE;
			}

			if (!bPractice || bContest)
			{
			// dolphin collide

				dolphin->GetPosition(m_scene, &ubuffer);
				THISXMIN = (THISX >= DOLPHINMINX);
				THISXMAX = (THISX <= DOLPHINMAXX);
				THISYMIN = (THISY >= DOLPHINMINY);
				THISYMAX = (THISY <= DOLPHINMAXY);
				THISZMIN = (THISZ >= DOLPHINMINZ);
				THISZMAX = (THISZ <= DOLPHINMAXZ);
				if (((THISXMIN && THISXMAX)
					|| ((LASTX <= DOLPHINMINX) && THISXMIN)
					|| ((LASTX >= DOLPHINMAXX) && THISXMAX))
					&& ((THISYMIN && THISYMAX)
					|| ((LASTY <= DOLPHINMINY) && THISYMIN)
					|| ((LASTY >= DOLPHINMAXY) && THISYMAX))
					&& ((THISZMIN && THISZMAX)
					|| ((LASTZ <= DOLPHINMINZ) && THISZMIN)
					|| ((LASTZ >= DOLPHINMAXZ) && THISZMAX)))
				{
					if (bNoCollide || (last_collide != DOLPHIN))
					{
						if (!bWipeout)
						{
							animate_time = (const float)146;
							bWipeout = TRUE;
						}
						if (bGore)
						{
							bSplat = TRUE;
							splat_time = 0;
						}
						if (score > 1000)
							score -= 1000;
						else
							score = 0;
						if (bNaration)
							AddAnnounce(DOLPHINDISTURBANCE);
						surfer[current_surfer]->GetVelocity(dolphin, &vbuffer, NULL);
						if (bContest)
						{
							board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
							ApplyStats();
						}

						surfer[current_surfer]->SetVelocity(dolphin, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
						dolphin->SetVelocity(m_scene, vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, vbuffer.z*(const float)0.6, NULL);
						dolphin->SetRotation(m_scene, vbuffer.z, vbuffer.y, -vbuffer.x, D3DVALUE(0.2));
						if (bSoundFx)
					 		m_pDSBuffer[randInt(DOLPHINHITWAVE,DOLPHINHITWAVE+2)]->Play(0, 0, 0);
					}
					last_collide = DOLPHIN;
					bLastCollide = TRUE;
				}

				// barrel collide

				barrel->GetPosition(m_scene, &ubuffer);
				THISXMIN = (THISX >= BARRELMINX);
				THISXMAX = (THISX <= BARRELMAXX);
				THISYMIN = (THISY >= BARRELMINY);
				THISYMAX = (THISY <= BARRELMAXY);
				THISZMIN = (THISZ >= BARRELMINZ);
				THISZMAX = (THISZ <= BARRELMAXZ);
				if (((THISXMIN && THISXMAX)
					|| ((LASTX <= BARRELMINX) && THISXMIN)
					|| ((LASTX >= BARRELMAXX) && THISXMAX))
					&& ((THISYMIN && THISYMAX)
					|| ((LASTY <= BARRELMINY) && THISYMIN)
					|| ((LASTY >= BARRELMAXY) && THISYMAX))
					&& ((THISZMIN && THISZMAX)
					|| ((LASTZ <= BARRELMINZ) && THISZMIN)
					|| ((LASTZ >= BARRELMAXZ) && THISZMAX)))
				{
					if (bNoCollide || (last_collide != BARREL))
					{
						if (!bWipeout)
						{
							if (bNaration)
								AddAnnounce(randInt(BARRELDAVE,BARRELDAVE+2));
							animate_time = (const float)146;
							bWipeout = TRUE;
						}
						if (bGore)
						{
							bSplat = TRUE;
							splat_time = 0;
						}
						surfer[current_surfer]->GetVelocity(barrel, &vbuffer, NULL);
						if (bContest)
						{
							board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
							ApplyStats();
						}

						surfer[current_surfer]->SetVelocity(barrel, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
						barrel->SetVelocity(m_scene, vbuffer.x*(const float)0.8, D3DVALUE(-2), D3DVALUE(OBSTACLE_SPEED), NULL);
						barrel->SetRotation(m_scene, vbuffer.z, vbuffer.y, -vbuffer.x, D3DVALUE(0.2));
						if (bSoundFx)
					 		m_pDSBuffer[randInt(BARRELWAVE,BARRELWAVE+2)]->Play(0, 0, 0);
					}
					last_collide = BARREL;
					bLastCollide = TRUE;
				}	
	
				// rock collide

				rock->GetPosition(m_scene, &ubuffer);
				THISXMIN = (THISX >= ROCKMINX);
				THISXMAX = (THISX <= ROCKMAXX);
				THISZMIN = (THISZ >= ROCKMINZ);
				THISZMAX = (THISZ <= ROCKMAXZ);
				if (((THISXMIN && THISXMAX)
					|| ((LASTX <= ROCKMINX) && THISXMIN)
					|| ((LASTX >= ROCKMAXX) && THISXMAX))
					&& ((THISY <= ROCKMAXY)
					|| ((LASTY <= ROCKMAXY) && (THISY >= ROCKMAXY)))
					&& ((THISZMIN && THISZMAX)
					|| ((LASTZ <= ROCKMINZ) && THISZMIN)
					|| ((LASTZ >= ROCKMAXZ) && THISZMAX)))
				{
					if (bNoCollide || (last_collide != ROCK))
					{
						if (!bWipeout)
						{
							if (bNaration)
								AddAnnounce(randInt(REEF1,REEF1+13));
							if (bSurferSounds)
								AddSurferSound(WIPEOUT_SOUND);
							animate_time = (const float)146;
							bWipeout = TRUE;
						}
						if (bGore)
						{
							bSplat = TRUE;
							splat_time = 0;
						}
						surfer[current_surfer]->GetVelocity(rock, &vbuffer, NULL);
						if (bContest)
						{
							board_condition += (int)(fabs(vbuffer.x)+fabs(vbuffer.y)+fabs(vbuffer.z))/2;
							ApplyStats();
						}

						surfer[current_surfer]->SetVelocity(rock, -vbuffer.x*(const float)0.6, vbuffer.y*(const float)0.6, -vbuffer.z*(const float)0.6, NULL);
						if (bSoundFx)
					 		m_pDSBuffer[randInt(ROCKWAVE,ROCKWAVE+2)]->Play(0, 0, 0);
					}
					last_collide = ROCK;
					bLastCollide = TRUE;
				}
			}
		}

		// tube collide

		if (curl_width > 55)
		{
			THISXMIN = (THISX >= CURLMINX);
			THISXMAX = (THISX <= CURLMAXX);
			if ((THISXMIN && THISXMAX)
//				|| ((LASTX <= curlpos_x-200) && THISXMIN)
//				|| ((LASTX >= curlpos_x+200) && THISXMAX))
				&& (curlpos_off < 50) && (bBreakingWave || bContest)
				&& !bWipeout)
			{

				if (bAutoCamera)
				{
					bAutoUsed = TRUE;
					if ((current_frame >= LIP_FRAME-1) && (current_frame <= MAXWAVEFRAME-4))
					{
						camera_type = TUBE_CAMERA;
//					    light->DeleteLight(light2);
//					    light2->SetColorRGB(D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0));
//					    light->AddLight(light2);
//						bLightChange = TRUE;
					}
					else if (current_frame < LIP_FRAME-1)
					{
						if ((camera_type == TUBE_CAMERA) 
							|| (camera_type == ROCK_VIDEO_CAMERA))
						{
							camera_type = SATELLITE_CAMERA;
						}
					}
					else
					{
						if ((camera_type == TUBE_CAMERA) 
							|| (camera_type == ROCK_VIDEO_CAMERA))
						{
							camera_type = BEACH_CAMERA;
						}
					}
					if ((camera_type == TUBE_CAMERA) || (camera_type == ROCK_VIDEO_CAMERA))
					{
						if (bSoundFx)
				 			m_pDSBuffer[TUBEWAVE]->Play(0, 0, 0);
					}
				}
				if (current_frame < LIP_FRAME-1)
				{
					if ((trick != 1) || ((current_surfer != SANDY) && (current_surfer != VIC)))
						bOverBreak = TRUE;
				}
				if ((curlpos_off > 7) 
					&& (current_frame >= LIP_FRAME-1) 
					&& (current_frame <= MAXWAVEFRAME-4)
					&& (!bNotDroppedInYet))
				{
					if ((trick == 1) && ((current_surfer == SANDY) || (current_surfer == VIC)))
					{
						if (bContest)
						{
							board_condition += 1;
							ApplyStats();
						}
					}
					else
					{
						animate_time = (const float)146;
						bWipeout = TRUE;
						if (bContest)
						{
							board_condition += 10;
							ApplyStats();
						}
						if (bSoundFx)
					 		m_pDSBuffer[randInt(BREAKHITWAVE,BREAKHITWAVE+2)]->Play(0, 0, 0);
						if (bNaration)
							AddAnnounce(randInt(REEF1,REEF1+12));
						if (bSurferSounds)
							AddSurferSound(WIPEOUT_SOUND);
						if (bGore)
						{
							bSplat = TRUE;
							splat_time = 0;
						}
						last_collide = TUBE;
					}
				}
				else if //((bNoCollide || (last_collide != TUBE)) &&
					((curlpos_off == 0) && !bNotDroppedInYet)
				{
					if ((current_frame == LIP_FRAME-1) 
						|| ((current_frame < LIP_FRAME-1) 
						&& (last_frame >= LIP_FRAME-1))
						|| ((current_frame > LIP_FRAME-1) 
						&& (last_frame <= LIP_FRAME-1))

						|| ((curl_width > 230) 
						&& (sbuffer.x < curlpos_x+curl_width-180)
						&& (sbuffer.x > curlpos_x-curl_width+180)
						&& ((current_frame == MAXWAVEFRAME-4) 
						|| ((current_frame < MAXWAVEFRAME-4) 
						&& (last_frame >= MAXWAVEFRAME-4))
						|| ((current_frame > MAXWAVEFRAME-4) 
						&& (last_frame <= MAXWAVEFRAME-4)))))

					{
						if ((trick == 1) && ((current_surfer == SANDY) || (current_surfer == VIC)))
						{
							if (bContest)
							{
								board_condition += 1;
								ApplyStats();
							}
						}
						else
						{
							animate_time = (const float)146;
							if (bSoundFx)
						 		m_pDSBuffer[randInt(BREAKHITWAVE,BREAKHITWAVE+2)]->Play(0, 0, 0);
							if (bNaration)
								AddAnnounce(randInt(REEF1,REEF1+12));
							if (bSurferSounds)
								AddSurferSound(WIPEOUT_SOUND);

							last_collide = TUBE;
							bWipeout = TRUE;
							if (bContest)
							{
								board_condition += 10;
								ApplyStats();
							}
						}
					}
				}
				bLastCollide = TRUE;
				if (!bWipeout && !bNotDroppedInYet)
				{
					intube++;
					if (intube < 10)
						bPlayTubeSound = TRUE;
					else if (bSurferSounds && bPlayTubeSound)
					{
						AddSurferSound(TUBE_SOUND);
						bPlayTubeSound = FALSE;
					}
				}
			}
			else
			{
				if ((intube > 15) && !bWipeout && !bNotDroppedInYet)
				{
					if (bNaration && !bSharkAttack)
						AddAnnounce(randInt(GROOVYTUBE,GROOVYTUBE+2));
					score += (int)((bUfo ?100.0 : 50.0)*intube*fGameSpeed);
				}
				if (bSoundFx)
		 			m_pDSBuffer[TUBEWAVE]->Stop();
				intube = 0;
			}
		}
		else
			intube = 0;
		
		if (!bAutoUsed && !bWipeout)
			camera_type = last_camera;
//		if (!bLightChange && bLastLightChange)
//		{
//			light->DeleteLight(light2);
//		    light2->SetColorRGB(D3DVALUE(0.3), D3DVALUE(0.3), D3DVALUE(0.33));
//		    light->AddLight(light2);
//		}
//		bLastLightChange = bLightChange;

		// shit for figuring out where the curl goes...
		/*
		if (::GetAsyncKeyState(VK_NUMPAD2) <0)
		{
			curl_frame->SetRotation(curl_frame, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0.0), D3DVALUE(0.00));
			D3DVECTOR Zvector, Yvector;
			curl_frame->GetOrientation(m_scene, &Zvector, &Yvector);
			char ss[10];
			sprintf(ss, "%d",(int)((Zvector.y/Zvector.z)*1000));
			WritePrivateProfileString("CurlPos","dz",ss,"wildride.ini");
		}

		if (::GetAsyncKeyState(VK_NUMPAD5) <0)
			curl_frame->SetRotation(curl_frame, D3DVALUE(-1), D3DVALUE(0), D3DVALUE(0.0), D3DVALUE(0.05));

		if (::GetAsyncKeyState(VK_NUMPAD3) <0)
			curl_frame->SetRotation(curl_frame, D3DVALUE(1), D3DVALUE(0), D3DVALUE(0.0), D3DVALUE(0.05));

		if (::GetAsyncKeyState(VK_NUMPAD7) <0)
		{
			curlpos_y -= 1;
			char ss[10];
			sprintf(ss, "%d",(int)curlpos_y);
			WritePrivateProfileString("CurlPos","y",ss,"wildride.ini");
		}
		if (::GetAsyncKeyState(VK_NUMPAD8) <0)
		{
			curlpos_y += 1;
			char ss[10];
			sprintf(ss, "%d",(int)curlpos_y);
			WritePrivateProfileString("CurlPos","y",ss,"wildride.ini");
		}
		if (::GetAsyncKeyState(VK_NUMPAD4) <0)
		{
			curlpos_z += 1;
			char ss[10];
			sprintf(ss, "%d",(int)curlpos_z);
			WritePrivateProfileString("CurlPos","z",ss,"wildride.ini");
		}
		if (::GetAsyncKeyState(VK_NUMPAD6) <0)
		{
			curlpos_z -= 1;
			char ss[10];
			sprintf(ss, "%d",(int)curlpos_z);
			WritePrivateProfileString("CurlPos","z",ss,"wildride.ini");
		}
		*/
/*
		if (lpBackBuffer->IsLost())
			lpBackBuffer->Restore();
		if (lpFrontBuffer->IsLost())
			lpFrontBuffer->Restore();
		if (lpHalfresBuffer->IsLost())
			lpHalfresBuffer->Restore();
		if (lpZBuffer)
		{
			if (lpZBuffer->IsLost())
				lpZBuffer->Restore();
		}
		if (lpSkySource->IsLost())
			lpSkySource->Restore();
		if (lpNavBar->IsLost())
			lpNavBar->Restore();
		if (lpSpeedometer->IsLost())
			lpSpeedometer->Restore();
		if (lpAlphabet->IsLost())
			lpAlphabet->Restore();
		if (lpIntrBkg->IsLost())
			lpIntrBkg->Restore();
*/		
		// this shit is all for testing & playing with the surfer

		if (bCheatKeys)
		{
		   	if (::GetAsyncKeyState(VK_NUMPAD9) <0)
			{
				surfer_velocity += 5*fGameSpeed;
			}

			if (::GetAsyncKeyState(VK_NUMPAD3) <0)
			{
				surfer_velocity -= 5*fGameSpeed;
			}
		}

		UpdateCamera();
	    m_scene->Move(fGameSpeed);
//		surfer[current_surfer]->GetPosition(m_scene, &ubuffer);
//		if (ubuffer.x != sbuffer.x)
//			last_sbuffer.x = sbuffer.x;
//		if (ubuffer.y != sbuffer.y)
//			last_sbuffer.y = sbuffer.y;
//		if (ubuffer.z != sbuffer.z)
//			last_sbuffer.z = sbuffer.z;
		last_sbuffer = sbuffer;
		if (game_time > 1)
			Render();
		MoveSurfer();
	}
//	goto updateloop;
}

// Render the scene into the viewport

void CsurfView::UpdateSpeedometer()
{
//#define SET_DEST_MOVE dest.left = (int)(ModeCx/32);dest.top = 2;dest.right = (int)(ModeCx*15/32);dest.bottom = ModeCy/6;

#define SET_DEST_MOVE destright = destleft = 8.0/32.0;destbottom = desttop = 1.0/12.0;
#define SHRINK_SPINNER destleft += 1.0/32.0;desttop += 1.0/84.0;destright -= 1.0/32.0;destbottom -= 1.0/84.0;
#define GROW_SPINNER destleft -= 1.0/32.0;desttop -= 1.0/84.0;destright += 1.0/32.0;destbottom += 1.0/84.0;
#define SHRINK 5;
#define DONE_SHRINK -115
	static float display_velocity = (const float)0;
	static BOOL bPlay360Sound = TRUE;
	static BOOL bPlayInsanitySound = TRUE;
	BOOL bOver100 = FALSE;
	static int shrink = DONE_SHRINK;
	RECT source2, dest2;
	static RECT source;
	static double destleft = 8.0/32.0;
	static double desttop = 1.0/12.0;
	static double destright = 8.0/32.0;
	static double destbottom = 1.0/12.0;
	static int cursor = 0;
	HRESULT LastError;
	float speedom;
	char ss[80];

	// game over - clear settings for next game

	if (lives < 1)
	{
		if (!bGameOver)
		{
			SET_DEST_MOVE
			source.left = source.right = source.top 
				= source.bottom = 0;
			lastp = 0;
			shrink = DONE_SHRINK;
			display_velocity = (const float)0;
			rotate_sum = (const float)0;
			return;
		}
		if (lpDDGuid[DDDriverNum[D3DDriver]] != NULL)
			return;

		// game over

		// " " or h or g
		dest2.top = ModeCy*3/8;
 		dest2.bottom = ModeCy*5/8;
		if (!(bContest && bFirstRun))
		{
			if (bContest)
				source2 = letter_rect[17];
			else
				source2 = letter_rect[16];
			dest2.left = ModeCx*5/20;
			dest2.right = ModeCx*6/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
			if (LastError != DD_OK) 
			{
				if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
			}
		}
		//r or e or a
		if (bContest)
		{
			if (bFirstRun)
				source2 = letter_rect[27];
			else
				source2 = letter_rect[14];
		}
		else
			source2 = letter_rect[10];
		dest2.left = ModeCx*6/20;
		dest2.right = ModeCx*7/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//u or a or m
		if (bContest)
		{
			if (bFirstRun)
				source2 = letter_rect[30];
			else
				source2 = letter_rect[10];
		}
		else
			source2 = letter_rect[22];
		dest2.left = ModeCx*7/20;
		dest2.right = ModeCx*8/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//n or t or e
		if (bContest)
		{
			if (bFirstRun)
				source2 = letter_rect[23];
			else
				source2 = letter_rect[29];
		}
		else
			source2 = letter_rect[14];
		dest2.left = ModeCx*8/20;
		dest2.right = ModeCx*9/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//o
		source2 = letter_rect[24];
		dest2.left = ModeCx*10/20;
		dest2.right = ModeCx*11/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//v
		source2 = letter_rect[31];
		dest2.left = ModeCx*11/20;
		dest2.right = ModeCx*12/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//e
		source2 = letter_rect[14];
		dest2.left = ModeCx*12/20;
		dest2.right = ModeCx*13/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//r
		source2 = letter_rect[27];
		dest2.left = ModeCx*13/20;
		dest2.right = ModeCx*14/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }
		//!
		source2 = letter_rect[38];
		dest2.left = ModeCx*14/20;
		dest2.right = ModeCx*15/20;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Game Over Blit failed.");
	    }

		// hiscore

		if (bHiscore)
		{
			//#
			source2 = letter_rect[scorenum+1];
			dest2.top = ModeCy/8;
			dest2.bottom = ModeCy/4;
			dest2.left = ModeCx*5/20;
			dest2.right = ModeCx*6/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//s
			if (scorenum == 0)
				source2 = letter_rect[28];
			//n
			else if (scorenum == 1)
				source2 = letter_rect[23];
			//r
			else if (scorenum == 2)
				source2 = letter_rect[27];
			//t
			else
				source2 = letter_rect[29];

			dest2.left = ModeCx*6/20;
			dest2.right = ModeCx*7/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//t
			if (scorenum == 0)
				source2 = letter_rect[29];
			//d
			else if (scorenum == 1)
				source2 = letter_rect[13];
			//d
			else if (scorenum == 2)
				source2 = letter_rect[13];
			//h
			else
				source2 = letter_rect[17];

			dest2.left = ModeCx*7/20;
			dest2.right = ModeCx*8/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }

			//p
			source2 = letter_rect[25];
			dest2.left = ModeCx*9/20;
			dest2.right = ModeCx*10/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//l
			source2 = letter_rect[21];
			dest2.left = ModeCx*10/20;
			dest2.right = ModeCx*11/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//a
			source2 = letter_rect[10];
			dest2.left = ModeCx*11/20;
			dest2.right = ModeCx*12/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//c
			source2 = letter_rect[12];
			dest2.left = ModeCx*12/20;
			dest2.right = ModeCx*13/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//e
			source2 = letter_rect[14];
			dest2.left = ModeCx*13/20;
			dest2.right = ModeCx*14/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }
			//!
			source2 = letter_rect[38];
			dest2.left = ModeCx*14/20;
			dest2.right = ModeCx*15/20;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		    }

			dest2.top = ModeCy * 3/4;
			dest2.bottom = ModeCy - 2 - (ModeCy/12);
			for (int j = 0; j < letnum; j++)
			{
				for (int i = 0; i < NUM_LETTERS; i++)
				{
					if (hiname[scorenum][j] == letters[i])
					{
						source2 = letter_rect[i];
					
						dest2.left = j * ModeCx / 8;
						dest2.right = (j+1) * ModeCx /8;
						
						LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
					    if (LastError != DD_OK) 
						{
						    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Letter Blit failed.");
					    }
						i = 255;
					}
				}
			}
			if (j < 8)
			{
				cursor++;
				if (cursor > 4)
				{
					if (cursor > 8)
						cursor = 0;
					source2 = letter_rect[69];
			
					dest2.left = j * ModeCx / 8;
					dest2.right = (j+1) * ModeCx /8;
						
					LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
				    if (LastError != DD_OK) 
					{
					    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Letter Blit failed.");
					}
				}
			}
		}
	}

	// moves (180s etc) display

	if (lpDDGuid[DDDriverNum[D3DDriver]] != NULL)
		return;
	if (bScoreBlit)
	{
		if (bNotDroppedInYet && (shrink == DONE_SHRINK))
		{
			// surf!
			source.left = 128; 
			source.top = 417;
			source.right = 253;
			source.bottom = 462;
			SET_DEST_MOVE;
			shrink = -3;
		}

		else if ((rotate_sum > 59*PI/8) || (rotate_sum < -59*PI/8)) //rediculous insane!
		{
			if (lastp < 10)
			{
				lastp++;

				source.left = 128; 
				source.top = 334;
				source.right = 256;
				source.bottom = 416;
			}
			shrink = SHRINK;
		}

		else if ((rotate_sum > 51*PI/8) || (rotate_sum < -51*PI/8)) //quadruple insane!
		{
			if (lastp < 9)
			{
				lastp++;
				source.left = 0; 
				source.top = 334;
				source.right = 128;
				source.bottom = 416;
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 43*PI/8) || (rotate_sum < -43*PI/8)) //triple insane!
		{
			if (lastp < 8)
			{
				lastp++;
				source.left = 128; 
				source.top = 250;
				source.right = 256;
				source.bottom = 334;
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 35*PI/8) || (rotate_sum < -35*PI/8)) //double insane!
		{
			if (lastp < 7)
			{
				lastp++;
				source.left = 0; 
				source.top = 250;
				source.right = 128;
				source.bottom = 334;
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 27*PI/8) || (rotate_sum < -27*PI/8)) //insane!
		{
			if (lastp < 6)
			{
				lastp++;
				source.left = 128; 
				source.top = 167;
				source.right = 256;
				source.bottom = 250;
				if (bPlayInsanitySound && bSurferSounds)
				{
					AddSurferSound(INSANITY_SOUND);
					bPlayInsanitySound = FALSE;
				}
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 23*PI/8) || (rotate_sum < -23*PI/8)) //900
		{
			if (lastp < 5)
			{
				lastp++;
				source.left = 0; 
				source.top = 167;
				source.right = 128;
				source.bottom = 250;
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 19*PI/8) || (rotate_sum < -19*PI/8)) //720
		{
			if (lastp < 4)
			{
				lastp++;
				source.left = 128; 
				source.top = 84;
				source.right = 256;
				source.bottom = 167;
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 15*PI/8) || (rotate_sum < -15*PI/8)) //540
		{
			if (lastp < 3)
			{
				lastp++;
				source.left = 0; 
				source.top = 84;
				source.right = 128;
				source.bottom = 167;
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 11*PI/8) || (rotate_sum < -11*PI/8)) //360
		{
			if (lastp < 2)
			{
				lastp++;
				source.left = 128; 
				source.top = 1;
				source.right = 256;
				source.bottom = 84;
				if (bPlay360Sound && bSurferSounds)
				{
					AddSurferSound(S360_SOUND);
					bPlay360Sound = FALSE;
				}
			}
			shrink = SHRINK;
		}
		else if ((rotate_sum > 7*PI/8) || (rotate_sum < -7*PI/8)) //180
		{
			if (lastp < 1)
			{
				lastp++;
				source.left = 0; 
				source.top = 1;
				source.right = 128;
				source.bottom = 84;
				SET_DEST_MOVE;
				bPlay360Sound = TRUE;
				bPlayInsanitySound = TRUE;
			}
			shrink = SHRINK;
		}
		else
		{
			lastp = 0;
		}

		if (shrink > -10)
		{
			GROW_SPINNER
			if (destleft < 1.0/32.0)
				destleft = 1.0/32.0;
			if (destright > 15.0/32.0)
				destright = 15.0/32.0;
			if (desttop < 0)
				desttop = 0.0;
			if (destbottom > 1.0/6.0)
				destbottom = 1.0/6.0;
			shrink--;
		}
		else
		{
			SHRINK_SPINNER
		}

		if (((ModeCy*desttop) <= ((ModeCy*destbottom)-1)) 
			&& ((ModeCx*destleft) <= (ModeCx*destright-1)))
		{ 
			dest2.left = (long)(destleft*ModeCx);
			dest2.top = (long)(desttop*ModeCy)+2;
			dest2.right = (long)(destright*ModeCx);
			dest2.bottom = (long)(destbottom*ModeCy)+2;
			LastError = lpBackBuffer->Blt(&dest2, lpSpeedometer, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
			if (LastError != DD_OK) 
			{
				if (bShowErrors) MessageBox(MyErrorToString(LastError), "Move scale off Blit failed.");
			}
		}
		else 
			shrink = DONE_SHRINK;
	//speedometer_plot:
		// plot scores --
		dest2.top = 2;
		dest2.bottom = ModeCy/10;
		unsigned long int tempscore = score;
		// millions
		source2 = letter_rect[(int(tempscore/1000000))];
		dest2.left = ModeCx*8/16;
		dest2.right = ModeCx*9/16;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
			wsprintf(ss,"Million failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}

		tempscore -= (int(tempscore/1000000))*1000000;

		// hundred thousands

		source2 = letter_rect[(int(tempscore/100000))];

		dest2.left = ModeCx*9/16;
		dest2.right = ModeCx*10/16;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
			wsprintf(ss,"Hunthou failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}

		tempscore -= (int(tempscore/100000))*100000;

		// ten thousands

		source2 = letter_rect[(int(tempscore/10000))];

		dest2.left = ModeCx*10/16;
		dest2.right = ModeCx*11/16;

		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{	
			wsprintf(ss,"TenThou failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}

		tempscore -= (int(tempscore/10000))*10000;

		// thousands

		source2 = letter_rect[(int(tempscore/1000))];

		dest2.left = ModeCx*11/16;
		dest2.right = ModeCx*12/16;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
			wsprintf(ss,"Thou failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}

		tempscore -= (int(tempscore/1000))*1000;

		// hundreds

		source2 = letter_rect[(int(tempscore/100))];
		dest2.left = ModeCx*12/16;
		dest2.right = ModeCx*13/16;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
			wsprintf(ss,"Hund failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}
		tempscore -= (int(tempscore/100))*100;
		// tens
		source2 = letter_rect[(int(tempscore/10))];
		dest2.left = ModeCx*13/16;
		dest2.right = ModeCx*14/16;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
			wsprintf(ss,"Tens failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}
		tempscore -= (int(tempscore/10))*10;
		// ones
		
		source2 = letter_rect[tempscore];
		dest2.left = ModeCx*14/16;
		dest2.right = ModeCx*15/16;
		LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
			wsprintf(ss,"Ones failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
				source2.left, source2.top, source2.right, source2.bottom,
				dest2.left, dest2.top, dest2.right, dest2.bottom);
			if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
		}
	}
	// timer plot

	dest2.top = (long)(ModeCy*0.9);
	dest2.bottom = ModeCy-2;
	if (!bGameOver && bSpeedofish)
	{
		int tempscore2 = (1201-(int)game_time)/10;
		if (tempscore2 > 0)
		{
			//hundreds
			if (tempscore2 > 99)
			{
				bOver100 = TRUE;
				source2 = letter_rect[(int(tempscore2/100))];
				dest2.left = ModeCx*12/16;
				dest2.right = ModeCx*13/16;
				LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
				if (LastError != DD_OK) 
				{
					wsprintf(ss,"Huns2 failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
						source2.left, source2.top, source2.right, source2.bottom,
						dest2.left, dest2.top, dest2.right, dest2.bottom);
				    if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
			    }
				tempscore2 -= (int(tempscore2/100))*100;
			}
			//tens
			if ((tempscore2 > 9) || bOver100)
			{
				source2 = letter_rect[(int(tempscore2/10))];
				dest2.left = ModeCx*13/16;
				dest2.right = ModeCx*14/16;
				LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
				if (LastError != DD_OK) 
				{
					wsprintf(ss,"Tens2 failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
						source2.left, source2.top, source2.right, source2.bottom,
						dest2.left, dest2.top, dest2.right, dest2.bottom);
				    if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
			    }
				tempscore2 -= (int(tempscore2/10))*10;
			}
	
			// ones

			source2 = letter_rect[tempscore2];

			dest2.left = ModeCx*14/16;
			dest2.right = ModeCx*15/16;
			LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
			if (LastError != DD_OK) 
			{
				wsprintf(ss,"ones2 failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
					source2.left, source2.top, source2.right, source2.bottom,
					dest2.left, dest2.top, dest2.right, dest2.bottom);
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
			}
		}
	}
	// speedometer
	speedom = surfer_velocity;
	if (speedom < 0)
		speedom = -speedom;
	display_velocity += (speedom - display_velocity)/8;
	if (bSpeedofish)
	{
		int width = (int)((ModeCx-16)*(display_velocity/surfer_max));
		if (width>(ModeCx*11/16))
			width = ModeCx*11/16;
		if (width > 0)
		{
			source2.left = 0; 
			source2.top = 416;
			source2.right = 128;
			source2.bottom = 437;

			dest2.left = (((ModeCx*12/16)-width)/2);
			dest2.right = (ModeCx*12/16)-dest2.left;

			if (dest2.right > dest2.left)
			{
				LastError = lpBackBuffer->Blt(&dest2, lpSpeedometer, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
			    if (LastError != DD_OK) 
				{
					wsprintf(ss,"Speedofish failed: (%d,%d)-(%d,%d),(%d,%d)-(%d,%d)",
						source2.left, source2.top, source2.right, source2.bottom,
						dest2.left, dest2.top, dest2.right, dest2.bottom);
			        if (bShowErrors) MessageBox(MyErrorToString(LastError), ss);
			    }
			}
		}
	}
	if (bFps)
	{
		char ach[40];

		DWORD elapsed = timeGetTime()-starttime;
		float fps = (float)numframes/elapsed*100000;
		wsprintf(ach, "%d.%02dfps-%d.%03ds-%df-%dx%d-%s-%s",
	        (int)fps / 100,
	        (int)fps % 100,
			(int)elapsed / 1000,
			(int)elapsed % 1000,
			numframes,
			ModeCx, 
			ModeCy,
			bFullscreen ? "f":"w",
			bHalfres ? "h":" ");
		dest2.top = ModeCy*6/8; 
		dest2.bottom = ModeCy*7/8;
		for (int i = 0; i < 40; i++)
		{
			if (ach[i] == (char)0)
				i = 44;
			else for (int j = 0; j < NUM_LETTERS; j++)
			{
				if (ach[i] == letters[j])
				{
					source2 = letter_rect[j];
					dest2.left = ModeCx*i/40;
					dest2.right = ModeCx*(i+1)/40;
					LastError = lpBackBuffer->Blt(&dest2, lpAlphabet, &source2, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
				    if (LastError != DD_OK) 
					{
				        if (bShowErrors) MessageBox(MyErrorToString(LastError), "FPS blit failed");
				    }
				}
			}
		}
	}
}

void CsurfView::Render()
{
	HRESULT LastError;
	RECT source, dest;

    m_view->Clear();

	dest.top = dest.left = 0;

	if (bHalfres)
	{
		dest.right = ModeCx/2;
		dest.bottom = ModeCy/2;
		if (bSky && (lpDDGuid[DDDriverNum[D3DDriver]] == NULL))
		{
			LastError = lpHalfresBuffer->Blt(&dest, lpSkySource, &skysource, DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
			    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Sky to Halfres Blit failed.");
		    }
		}
		else
			m_view->ForceUpdate(0, 0, dest.right, dest.bottom);
		m_view->Render(m_scene);
		source = dest;
		dest.top = 0;
		dest.left = 0;
		dest.right = ModeCx;
		dest.bottom = ModeCy;
		LastError = lpBackBuffer->Blt(&dest, lpHalfresBuffer, &source, DDBLT_WAIT, NULL);

	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Halfres to Backbuffer Blit failed.");
	    }
	}
	else
	{
		if (bSky && (lpDDGuid[DDDriverNum[D3DDriver]] == NULL))
		{
			dest.top = 0;
			dest.left = 0;
			dest.right = ModeCx;
			dest.bottom = ModeCy;

			LastError = lpBackBuffer->Blt(&dest, lpSkySource, &skysource, DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Sky to Backbuffer Blit failed.");
		    }
		}
		else
			m_view->ForceUpdate(0, 0, ModeCx, ModeCy);
		m_view->Render(m_scene);
	}

//    m_lpDev->Update();	
	UpdateSpeedometer();

	if (bFullscreen)
		lpFrontBuffer->Flip(NULL, NULL);
	else 
	{
		source.top = source.left = 0;
		source.right = ModeCx;
		source.bottom = ModeCy;
		dest.top = ModeAy;
		dest.left = ModeAx;
		dest.right = ModeBx;
		dest.bottom = ModeBy;

//		LastError = lpFrontBuffer->BltFast(ModeAx, ModeAy, lpBackBuffer, &source, DDBLTFAST_NOCOLORKEY);
		LastError = lpFrontBuffer->Blt(&dest, lpBackBuffer, &source, DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
//	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "BlitFast back/front flip failed.");
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Blit back/front flip failed.");
	    }
	}
}

void CsurfView::RenderInterface(int navbarframe)
{
	HRESULT LastError;
	RECT source, dest;
	static int cursor = 0;
	int height = INTR_BOTTOM - INTR_TOP;
	int width = INTR_RIGHT - INTR_LEFT;
	int left = INTR_LEFT;
	int top = INTR_TOP;
	int bottom = INTR_BOTTOM;

    m_view->Clear();

	if (bHalfres)
	{
		dest.left = INTR_HLEFT;
		dest.top = INTR_HTOP;
		dest.right = INTR_HRIGHT-1;
		dest.bottom = INTR_HBOTTOM-1;
		if ((dest.bottom - dest.top)/2 != (int)((float)((dest.bottom - dest.top)/2+0.5)))
			dest.bottom--;
		if ((dest.right - dest.left)/2 != (int)((float)((dest.right - dest.left)/2+0.5)))
			dest.right--;
		if (bSky)
		{
			LastError = lpHalfresBuffer->Blt(&dest, lpSkySource, &skysource, DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
			    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Sky to Halfres Blit failed.");
		    }
		}
		else
			m_view->ForceUpdate(INTR_VLEFT, INTR_VTOP,
				INTR_VRIGHT, INTR_VBOTTOM);

		LastError = m_view->Render(m_scene);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Halfres Render failed.");
	    }

		source = dest;

		dest.left = left;
		dest.top = top;
		dest.right = INTR_RIGHT;
		dest.bottom = bottom;
		if ((dest.bottom - dest.top)/2 != (int)((float)((dest.bottom - dest.top)/2+0.5)))
		{
			dest.bottom++;
			source = dest;
		}
		if ((dest.right - dest.left)/2 != (int)((float)((dest.right - dest.left)/2+0.5)))
		{
			dest.bottom++;
			source = dest;
		}
		LastError = lpBackBuffer->Blt(&dest, lpHalfresBuffer, &source, DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Halfres to Backbuffer Blit failed.");
	    }
	}
	else
	{
		dest.left = left;
		dest.top = top;
		dest.right = INTR_RIGHT;
		dest.bottom = bottom;
		if (bSky)
		{
			if ((dest.bottom - dest.top)/2 != (int)((float)((dest.bottom - dest.top)/2+0.5)))
				dest.bottom--;
			if ((dest.right - dest.left)/2 != (int)((float)((dest.right - dest.left)/2+0.5)))
				dest.right--;
			LastError = lpBackBuffer->Blt(&dest, lpSkySource, &skysource, DDBLT_WAIT, NULL);
		    if (LastError != DD_OK) 
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Sky to Backbuffer Blit failed.");
		    }
		}
		else
			m_view->ForceUpdate(INTR_VLEFT, INTR_VTOP,
				INTR_VRIGHT, INTR_VBOTTOM);

		LastError = m_view->Render(m_scene);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Backbuffer Render failed.");
	    }
	}

//    m_lpDev->Update();

	dest.top = bottom - (height/6);
	dest.bottom = bottom - 2;
	switch (current_surfer)
	{
	case ALANA:
		//a
		dest.left = left + (width*8/13);
		dest.right = left + (width*9/13);
		source = letter_rect[10];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//l
		dest.left = dest.right;
		dest.right = left + (width*10/13);
		source = letter_rect[51];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//a
		dest.left = dest.right;
		dest.right = left + (width*11/13);
		source = letter_rect[40];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//n
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[53];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//a
		dest.left = dest.right;
		dest.right = INTR_RIGHT;
		source = letter_rect[40];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		break;
	case BUCKY:
		//B
		dest.left = left + (width*8/13);
		dest.right = left + (width*9/13);
		source = letter_rect[11];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//u
		dest.left = dest.right;
		dest.right = left + (width*10/13);
		source = letter_rect[60];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//c
		dest.left = dest.right;
		dest.right = left + (width*11/13);
		source = letter_rect[42];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//k
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[50];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//y
		dest.left = dest.right;
		dest.right = INTR_RIGHT;
		source = letter_rect[64];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		break;
	case LEE:
		//L
		dest.left = left + (width*10/13);
		dest.right = left + (width*11/13);
		source = letter_rect[21];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//e
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[44];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//e
		dest.left = dest.right;
		dest.right = INTR_RIGHT;
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		break;
	case SANDY:
		//S
		dest.left = left + (width*8/13);
		dest.right = left + (width*9/13);
		source = letter_rect[28];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//a
		dest.left = dest.right;
		dest.right = left + (width*10/13);
		source = letter_rect[40];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//n
		dest.left = dest.right;
		dest.right = left + (width*11/13);
		source = letter_rect[53];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//d
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[43];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//y
		dest.left = dest.right;
		dest.right = INTR_RIGHT;
		source = letter_rect[64];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		break;
	case TODD:
		//T
		dest.left = left + (width*9/13);
		dest.right = left + (width*10/13);
		source = letter_rect[29];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//o
		dest.left = dest.right;
		dest.right = left + (width*11/13);
		source = letter_rect[54];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//d
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[43];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//d
		dest.left = dest.right;
		dest.right = INTR_RIGHT;
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		break;
	case VIC:
		//V
		dest.left = left + (width*10/13);
		dest.right = left + (width*11/13);
		source = letter_rect[31];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//i
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[48];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//c
		dest.left = dest.right;
		dest.right = INTR_RIGHT;
		source = letter_rect[42];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		break;
	}
	if (bHiscore)
	{
		//H
		source = letter_rect[17];
		dest.left = left + (width/13);
		dest.top = top + (height/2);
		dest.right = left + (width*2/13);
		dest.bottom = top + (height*2/3);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
	    }
		//I
		source = letter_rect[18];
		dest.left = left + (width*2/13);
		dest.right = left + (width*3/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
	    }
		//-
		source = letter_rect[69];
		dest.left = dest.right;
		dest.right = left + (width*4/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
	    }
		//S
		source = letter_rect[28];

		dest.left = dest.right;
		dest.right = left + (width*5/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		}

		//C
		source = letter_rect[12];
		dest.left = dest.right;
		dest.right = left + (width*6/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		}
		//O
		source = letter_rect[24];
		dest.left = dest.right;
		dest.right = left + (width*7/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		}
		//R
		source = letter_rect[27];
		dest.left = dest.right;
		dest.right = left + (width*8/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
	    }
		//E
		source = letter_rect[14];
		dest.left = dest.right;
		dest.right = left + (width*9/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		}
		//#
		source = letter_rect[scorenum+1];
		dest.left = left + (width*10/13);
		dest.right = left + (width*11/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
		}
		//!
		source = letter_rect[38];
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Blit failed.");
	    }

		dest.top = top + (height * 3/4);
		dest.bottom = bottom - 2 - (height/12);
		for (int j = 0; j < letnum; j++)
		{
			for (int i = 0; i < NUM_LETTERS; i++)
			{
				if (hinamec[scorenum][j] == letters[i])
				{
					source = letter_rect[i];
				
					dest.left = left + (j * width / 8);
					dest.right = left + ((j+1) * width /8);
						
					LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
				    if (LastError != DD_OK) 
					{
					    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Letter Blit failed.");
					}
					i = 255;
				}
			}
		}
		if (j < 8)
		{
			cursor++;
			if (cursor > 4)
			{
				if (cursor > 8)
					cursor = 0;
				source = letter_rect[69];
			
				dest.left = left + (j * width / 8);
				dest.right = left + ((j+1) * width /8);
						
				LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
			    if (LastError != DD_OK) 
				{
				    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Hiscore Letter Blit failed.");
				}
			}
		}
	}
	else if (bConfirmation)
	{
		dest.top = top + (height/3);
		dest.bottom = top + (height/2);
		//a
		dest.left = left;
		dest.right = left + (width/13);
		source = letter_rect[10];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//r
		dest.left = dest.right;
		dest.right = left + (width*2/13);
		source = letter_rect[57];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//e
		dest.left = dest.right;
		dest.right = left + (width*3/13);
		source = letter_rect[44];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//y
		dest.left = left + (width*4/13);
		dest.right = left + (width*5/13);
		source = letter_rect[64];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//o
		dest.left = dest.right;
		dest.right = left + (width*6/13);
		source = letter_rect[54];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//u
		dest.left = dest.right;
		dest.right = left + (width*7/13);
		source = letter_rect[60];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//s
		dest.left = left + (width*8/13);
		dest.right = left + (width*9/13);
		source = letter_rect[58];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//u
		dest.left = dest.right;
		dest.right = left + (width*10/13);
		source = letter_rect[60];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//r
		dest.left = dest.right;
		dest.right = left + (width*11/13);
		source = letter_rect[57];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//e
		dest.left = dest.right;
		dest.right = left + (width*12/13);
		source = letter_rect[44];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//?
		dest.left = dest.right;
		dest.right = left + (width*13/13);
		source = letter_rect[39];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		dest.top = top + (height/2);
		dest.bottom = top + (height*2/3);
		//-
		dest.left = left + (width*4/13);
		dest.right = left + (width*5/13);
		source = letter_rect[69];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		//y
		dest.left = dest.right;
		dest.right = left + (width*6/13);
		source = letter_rect[34];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		// /
		dest.left = dest.right;
		dest.right = left + (width*7/13);
		source = letter_rect[68];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		// n
		dest.left = dest.right;
		dest.right = left + (width*8/13);
		source = letter_rect[23];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}
		// -
		dest.left = dest.right;
		dest.right = left + (width*9/13);
		source = letter_rect[69];
		LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
		    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
		}

		dest.top = top + (height/6);
		dest.bottom = top + (height/3);
		for (int j = 0; j < 13; j++)
		{
			for (int i = 0; i < NUM_LETTERS; i++)
			{
				if (ConfirmationText[j] == letters[i])
				{
					source = letter_rect[i];
				
					dest.left = left + (j * width/13);
					dest.right = left + ((j+1) * width/13);
						
					LastError = lpBackBuffer->Blt(&dest, lpAlphabet, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
				    if (LastError != DD_OK) 
					{
					    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Confirmation Letter Blit failed.");
					}
					i = 255;
				}
			}
		}
	}

	if (bFullscreen)
	{
		source.left = 0;
		source.top  = navbarframe*86;
		source.right = 194;
		source.bottom = navbarframe*86+85;
		dest.left = ModeCx/32;
		dest.top = ModeCy*25/32;
		dest.right = ModeCx/2;
		dest.bottom = ModeCy*31/32;
		LastError = lpBackBuffer->Blt(&dest, lpNavBar, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Navigation Thingy to Backbuffer Blit failed.");
		}

		lpFrontBuffer->Flip(NULL, NULL);
	}
	else
	{
		source.left = 0;
		source.top  = navbarframe*86;
		source.right = 194;
		source.bottom = navbarframe*86+85;
		dest.left = ModeCx/32+ModeAx;
		dest.top = ModeCy*25/32+ModeAy;
		dest.right = ModeCx/2+ModeAx;
		dest.bottom = ModeCy*31/32+ModeAy;

		LastError = lpFrontBuffer->Blt(&dest, lpNavBar, &source, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Navigation Thingy to Backbuffer Blit failed.");
	    }
		source.left = INTR_LEFT;
		source.top = INTR_TOP;
		source.right = INTR_RIGHT;
		source.bottom = INTR_BOTTOM;
		if ((dest.bottom - dest.top)/2 != (int)((float)((dest.bottom - dest.top)/2+0.5)))
			dest.bottom--;
		if ((dest.right - dest.left)/2 != (int)((float)((dest.right - dest.left)/2+0.5)))
			dest.right--;

// this shit is fucked.

		dest.left = ModeAx + source.left;
		dest.top = ModeAy + source.top;
		dest.right = ModeAx + source.right;
		dest.bottom = ModeAy + source.bottom;

//		LastError = lpFrontBuffer->BltFast(ModeAx, ModeAy, lpBackBuffer, &source, DDBLTFAST_NOCOLORKEY);
		LastError = lpFrontBuffer->Blt(&dest, lpBackBuffer, &source, DDBLT_WAIT, NULL);
	    if (LastError != DD_OK) 
		{
//	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "BlitFast back/front flip failed.");
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Blit back/front flip failed.");
	    }
	}
}

static HRESULT __cdecl loadTextures(char *name, LPVOID lpThat, LPDIRECT3DRMTEXTURE*tex)
{
	CsurfView * view = (CsurfView *)lpThat;
	return view->loadTexturesCallFront(name, tex);
}
HRESULT CsurfView::loadTexturesCallFront(char *name, LPDIRECT3DRMTEXTURE*tex)
{
	static const char* TextureName[NUMTEXTURES] = 
	{
		"alana.bmp",
		"buckfi~1.bmp",
		"leefinal.bmp",
		"sandra.bmp",
		"toadfi~1.bmp",
		"vicfinal.bmp",
		"barrel.bmp",
		"buildall.bmp",
		"hlxwalls.bmp",
		"options.bmp",
		"mountain.bmp",
		"sandma~1.bmp",
		"hlshutr.bmp",
		"surfsign.bmp",
		"thatch.bmp",
		"ufomap.bmp",
		"vanetc.bmp",
		"piermap.bmp",
		"newbea~1.bmp",
		"csguy.bmp",
		"hlguy.bmp",
		"waterm~1.bmp",
		"sflogo.bmp"
	};
	static const int TextureId[NUMTEXTURES] = 
	{
		IDR_ALANAMAP,
		IDR_BUCKYMAP,
		IDR_LEEMAP,
		IDR_SANDYMAP,
		IDR_TODDMAP,
		IDR_VICMAP,
		IDR_BARRELMAP,
		IDR_BUILDALLMAP,
		IDR_HLXWALLMAP,
		IDR_OPTIONMAP,
		IDR_MOUNTAINMAP,
		IDR_SANDMAP,
		IDR_SHUTTERMAP,
		IDR_SURFSIGNMAP,
		IDR_THATCHMAP,
		IDR_UFOMAP,
		IDR_VANMAP,
		IDR_PIERMAP,
		IDR_WRBEACHMAP,
		IDR_CSGUYMAP,
		IDR_HLGUYMAP,
		IDR_WATERMAP,
		IDR_SFLOGOMAP
	};
	static const BOOL TextureTrans[NUMTEXTURES] = 
	{
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		TRUE,
		FALSE,
		FALSE,
		FALSE,
		TRUE,
		TRUE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};
	if (bNoTextures)
		return -1;

	else for (int i = 0; i < NUMTEXTURES; i++)
	{
		if (!lstrcmpi(name, TextureName[i]))
		{
			if (!map[i])
			{
				m_lprm->LoadTextureFromResource(
					FindResource(GetModuleHandle(NULL),
					MAKEINTRESOURCE(TextureId[i]), 
					"PPM"), 
					&map[i]);
				if (TextureTrans[i])
				{
					map[i]->SetDecalTransparency(TRUE);
					map[i]->SetDecalTransparentColor(RGB_MAKE(0,255,0));
				}
			}
			*tex = map[i];
		    return TRUE;
		}
	}
	return -1;
}

// Routine to scale the wave and animate the textures

void CsurfView::MoveWave()
{
	int i;
	static float bouytime = (const float)0;
	static float barreltime = (const float)0;
	static int foamanim1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	static BOOL bDolphinSplash = FALSE;

	D3DVECTOR ubuffer;
	int j;
	float last_time;

	last_time = game_time;
	game_time += fGameSpeed;
	for (j = 0; j < NUMEVENT; j++)
	{
		if ((game_time >= EventTime[j]) && (last_time < EventTime[j]))
		{
			switch (EventNumber[j])
			{
			case E_WAVE100:
				dydeltasc = (const float)-0.001564246;
				dzdeltasc = (const float)-0.001564246;
				break;
			case E_WAVE60:
				dydeltasc = (const float)0.0055;//0.005
				dzdeltasc = (const float)0.0055;//
				break;
			case E_WAVE75:
				dydeltasc = (const float)-0.000432686;//632686
				dzdeltasc = (const float)-0.000432686;
				break;
			case E_WAVE25:
				dydeltasc = (const float)-0.00625;
				dzdeltasc = (const float)-0.00625;
				break;
			case E_WAVE0:
				dydeltasc = (const float)-0.05;
				dzdeltasc = (const float)0;
				bWipeout = TRUE;
				lives = -1;
				break;
			case E_CURLSTART:
				curl_frame->SetOrientation(m_scene, (const float)0, (const float)0, (const float)1, (const float)0, (const float)1, (const float)0);
				curl_frame->SetRotation(curl_frame, D3DVALUE(-1), D3DVALUE(0), D3DVALUE(0.0), D3DVALUE(0.08));
				curl_frame->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
				curlpos_off = (const float)0;
				curlpos_x = (const float)0;
				bPitch = TRUE;
				bDrop = FALSE;
				bCloseOut = FALSE;
				foam_off = (const float)60;
				curl_width = (const float)30.32034632;
				for (i = 0; i < NUMFOAM; i++)
					foam[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
				break;
			case E_CLOSEOUT:
				closeout_off = (const float)60;
				bCloseOut = TRUE;
				break;
			case E_CURLDROP:
				bDrop = TRUE;
				break;
			}
		}
	}
	wydeltasc += dydeltasc*fGameSpeed;
	if (wydeltasc < 0)
		wydeltasc = (const float)0;
	wzdeltasc += dzdeltasc*fGameSpeed;

	AnimateWater();

 	wave_mesh->Scale((const float)1,wydeltasc,wzdeltasc);

	frame_y[1] = DFRAMEY1* wydeltasc;
	frame_y[2] = DFRAMEY2* wydeltasc;
	frame_y[3] = DFRAMEY3* wydeltasc;
	frame_y[4] = DFRAMEY4* wydeltasc;
	frame_y[5] = DFRAMEY5* wydeltasc;
	frame_y[6] = DFRAMEY6* wydeltasc;
	frame_y[7] = DFRAMEY7* wydeltasc;
	frame_y[8] = DFRAMEY8* wydeltasc;
	frame_y[9] = DFRAMEY9* wydeltasc;
	frame_y[10] = DFRAMEY10* wydeltasc;
	frame_y[11] = DFRAMEY11* wydeltasc;

	frame_y[0] = frame_y[1]+1000;

	frame_z[0] = DFRAMEZ0* wzdeltasc;
	frame_z[1] = DFRAMEZ1* wzdeltasc;
	frame_z[2] = DFRAMEZ2* wzdeltasc;
	frame_z[3] = DFRAMEZ3* wzdeltasc;
	frame_z[4] = DFRAMEZ4* wzdeltasc;
	frame_z[5] = DFRAMEZ5* wzdeltasc;
	frame_z[6] = DFRAMEZ6* wzdeltasc;
	frame_z[7] = DFRAMEZ7* wzdeltasc;
	frame_z[8] = DFRAMEZ8* wzdeltasc;
	frame_z[9] = DFRAMEZ9* wzdeltasc;
	frame_z[10] = DFRAMEZ10* wzdeltasc;
	frame_z[11] = DFRAMEZ11* wzdeltasc;

	for (i = 0; i < MAXWAVEFRAME+1; i++)
	{
		frame_orient[i].x = (const float)0;
		frame_orient[i].y = (frame_z[i] - frame_z[i+1]);
		frame_orient[i].z = -(frame_y[i] - frame_y[i+1]);
	}

	// check on curl/tube
	if (bBreakingWave || bContest)
	{
		if (bPitch)
		{
			D3DVECTOR Zvector, Yvector;
			curl_frame->GetOrientation(m_scene, &Zvector, &Yvector);
			curl_width+=(const float)7.107692308*fGameSpeed;
			if (((Zvector.y/Zvector.z) >= -0.3) && ((Zvector.y/Zvector.z) <= -0.1))
			{
				curl_frame->SetRotation(curl_frame, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
				bPitch = FALSE;
			}
		}
		if (bDrop)
		{
			curlpos_off += 3*fGameSpeed;
		}
		if (bFoam && (curl_width > 230))
		{	
			foam[foamanim1[0]]->SetPosition(m_scene, curlpos_x-50, frame_y[MAXWAVEFRAME-3]-curlpos_off-foam_off, frame_z[MAXWAVEFRAME-3]+curlpos_off);
			foam[foamanim1[1]]->SetPosition(m_scene, curlpos_x, frame_y[MAXWAVEFRAME-3]-curlpos_off-foam_off, frame_z[MAXWAVEFRAME-3]+curlpos_off);
			foam[foamanim1[2]]->SetPosition(m_scene, curlpos_x+50, frame_y[MAXWAVEFRAME-3]-curlpos_off-foam_off, frame_z[MAXWAVEFRAME-3]+curlpos_off);
			foam_off -= 6*fGameSpeed;
			if (foam_off < 0)
				foam_off = (const float)0;
			if (bCloseOut)
			{
				foam[foamanim1[3]]->SetPosition(m_scene, curlpos_x-200+(closeout_off*3), frame_y[MAXWAVEFRAME-5]-curlpos_off-closeout_off, frame_z[MAXWAVEFRAME-5]+curlpos_off-closeout_off);
				foam[foamanim1[4]]->SetPosition(m_scene, curlpos_x, frame_y[MAXWAVEFRAME-5]-curlpos_off-closeout_off, frame_z[MAXWAVEFRAME-5]+curlpos_off-closeout_off);
				foam[foamanim1[5]]->SetPosition(m_scene, curlpos_x+200-(closeout_off*3), frame_y[MAXWAVEFRAME-5]-curlpos_off-closeout_off, frame_z[MAXWAVEFRAME-5]+curlpos_off-closeout_off);
				closeout_off -= 3*fGameSpeed;
				if (closeout_off < 0)
					closeout_off = (const float)0;
			}
			else
			{
				foam[foamanim1[3]]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
				foam[foamanim1[4]]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
				foam[foamanim1[5]]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			}
			if (DolphinSplash < 10)
			{
				foam[foamanim1[6]]->SetPosition(dolphin, D3DVALUE(10), D3DVALUE(0), D3DVALUE(0));
				foam[foamanim1[7]]->SetPosition(dolphin, D3DVALUE(-10), D3DVALUE(0), D3DVALUE(0));
				DolphinSplash++;
			}
			else
			{
				if (bCloseOut)
				{
					foam[foamanim1[6]]->SetPosition(m_scene, curlpos_x-100+(closeout_off), frame_y[MAXWAVEFRAME-5]-curlpos_off-closeout_off, frame_z[MAXWAVEFRAME-5]+curlpos_off-closeout_off);
					foam[foamanim1[7]]->SetPosition(m_scene, curlpos_x+100-(closeout_off), frame_y[MAXWAVEFRAME-5]-curlpos_off-closeout_off, frame_z[MAXWAVEFRAME-5]+curlpos_off-closeout_off);
				}
				else
				{
					foam[foamanim1[6]]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
					foam[foamanim1[7]]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
				}
			}

			j = foamanim1[0];
			foamanim1[0] = foamanim1[1];
			foamanim1[1] = foamanim1[2];
			foamanim1[2] = foamanim1[3];
			foamanim1[3] = foamanim1[4];
			foamanim1[4] = foamanim1[5];
			foamanim1[5] = foamanim1[6];
			foamanim1[6] = foamanim1[7];
			foamanim1[7] = j;
		}
 		curlr_mesh->Scale((const float)1,wydeltasc,wzdeltasc);
		curl_frame->SetPosition(m_scene, curlpos_x, curlpos_y*wydeltasc-curlpos_off, curlpos_z*wzdeltasc+curlpos_off);
	}

	// set bouys
	bouytime += fGameSpeed;
	if (bouytime > 10)
		bouytime -= 10;
	leftbouy_animate->SetTime(bouytime);
	ritebouy_animate->SetTime(bouytime);
	leftbouy->SetPosition(m_scene, D3DVALUE(-BOUNDARY), frame_y[6], frame_z[6]);
	ritebouy->SetPosition(m_scene, D3DVALUE(BOUNDARY), frame_y[6], frame_z[6]);
	if (!bPractice || bContest)
	{
		// barrel nonsense
		barreltime+=(const float)0.4*fGameSpeed;
		if (barreltime > 10)
			barreltime -= 10;
		barrel_animate->SetTime(barreltime);
		barrel->GetPosition(m_scene, &ubuffer);
		if ((ubuffer.z > frame_z[0] + 300) && (game_time < 1180))
		{
			// regenerate barrel
			surfer[current_surfer]->GetPosition(m_scene, &ubuffer);
			ubuffer.x+=randInt(-BOUNDARY/5, BOUNDARY/5);
			if (ubuffer.x > BOUNDARY)
				ubuffer.x-=BOUNDARY/5;
			if (ubuffer.x < -BOUNDARY)
				ubuffer.x+=BOUNDARY/5;
			barrel->SetPosition(m_scene, ubuffer.x, frame_y[MAXWAVEFRAME], D3DVALUE(randInt(-400,-200)));
			barrel->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(OBSTACLE_SPEED), NULL);
		}
		else if (ubuffer.z > frame_z[0])
		{
			barrel->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(-4), D3DVALUE(OBSTACLE_SPEED), NULL);
		}
		else if (ubuffer.z < frame_z[MAXWAVEFRAME])
		{
			barrel->SetPosition(m_scene, ubuffer.x, frame_y[MAXWAVEFRAME], ubuffer.z);
		}
		else 
		{
			for (j = LIP_FRAME; j < MAXWAVEFRAME; j++)
			{
				if (ubuffer.z > frame_z[j+1])
				{
					ubuffer.y = frame_y[j] - ((frame_y[j] - frame_y[j+1])*
						(frame_z[j] - ubuffer.z)/
						(frame_z[j] - frame_z[j+1]));
					barrel->SetPosition(m_scene, ubuffer.x, ubuffer.y, ubuffer.z);
					j = MAXWAVEFRAME;
				}
			}
		}
		//dolphin nonsense
		dolphintime+=(const float)0.4*fGameSpeed;
		if ((dolphintime > 50) && (randInt(0,80) < 2))
		{
			// regenerate dolphin
			dolphintime = (const float)-3;
			dolphin_animate->SetTime((const float)1);
			dolphin->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			dolphin->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
			dolphin->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			if (bSoundFx)
			{
				i = randInt(DOLPHINWAVE,DOLPHINWAVE+2);
				m_pDSBuffer[i]->SetPan(((long)ubuffer.x - tempCameraX) * 6);
		 		m_pDSBuffer[i]->Play(0, 0, 0);
			}
		}
		else if ((dolphintime > 1.0) && (dolphintime < 1.5))
		{
			bDolphinSplash = FALSE;
			dolphin_animate->SetTime(dolphintime);
			surfer[current_surfer]->GetPosition(m_scene, &ubuffer);
			ubuffer.x+=randInt(-BOUNDARY/4, BOUNDARY/4);
			if (ubuffer.x > BOUNDARY)
				ubuffer.x-=BOUNDARY/4;
			if (ubuffer.x < -BOUNDARY)
				ubuffer.x+=BOUNDARY/4;
			ubuffer.z+=randInt(-200, 200);
			dolphin->SetPosition(m_scene, ubuffer.x, D3DVALUE(frame_y[MAXWAVEFRAME-1]-40), ubuffer.z);
			dolphin->LookAt(surfer[current_surfer], m_scene, D3DRMCONSTRAIN_Z);
			dolphin->SetVelocity(dolphin, D3DVALUE(0), D3DVALUE(randInt(22,26)), D3DVALUE(randInt(8,11)), FALSE);
		}
		else
		{
			// do dolphin
			if (dolphintime < 10)
				dolphin_animate->SetTime(dolphintime);
			dolphin->GetVelocity(m_scene, &ubuffer, FALSE);
			float t = ubuffer.y - (const float)1.9;
			dolphin->SetVelocity(m_scene, ubuffer.x, t, ubuffer.z, FALSE);
			if (t < 0)
			{
				dolphin->GetPosition(m_scene, &ubuffer);
				if ((ubuffer.y+t < frame_y[MAXWAVEFRAME-4]) && !bDolphinSplash)
				{
					DolphinSplash = 0;
					bDolphinSplash = TRUE;
				}
			}
		}

		// rock nonsense
		rock->GetPosition(m_scene, &ubuffer);
		if ((ubuffer.z > frame_z[0] + 300) && (game_time < 1180))
		{
			// regenerate rock
			surfer[current_surfer]->GetPosition(m_scene, &ubuffer);
			ubuffer.x+=randInt(-BOUNDARY/5, BOUNDARY/5);
			if (ubuffer.x > BOUNDARY)
				ubuffer.x-=BOUNDARY/5;
			if (ubuffer.x < -BOUNDARY)
				ubuffer.x+=BOUNDARY/5;
			rock->SetPosition(m_scene, ubuffer.x, frame_y[MAXWAVEFRAME+1], D3DVALUE(randInt(-400,-200)));
			rock->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(PIER_SPEED), FALSE);
		}
	}

	// stop pier at -174 z

	pier->GetPosition(m_scene, &ubuffer);
	if (ubuffer.z >= -174.0)
	{
		pier->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
		rock->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
		oilrig->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
		beach_frame->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
	}
}

BOOL CsurfView::Fire(BOOL button2)
{
	static BOOL last1 = FALSE;
	static BOOL last2 = FALSE;
	BOOL this1 = FALSE;
	BOOL this2 = FALSE;

	if (::GetAsyncKeyState(VK_SPACE) <0)
	{
		this1 = TRUE;
	}

	if (::GetAsyncKeyState(VK_CONTROL) <0)
	{
		this2 = TRUE;
	}

	else if (::GetAsyncKeyState(VK_RETURN) <0)
	{
		this2 = TRUE;
	}

	// joystick routines

	else if (bJoystickExists)
	{
		JOYINFO joyinfo;

		// if no errors, proceed with joystick routines

		if (joyGetPos(m_uiJoyStick, &joyinfo) == JOYERR_NOERROR)
		{
			// check for joybutton and on wave, if so super-turn!
			if ((joyinfo.wButtons & JOY_BUTTON1) == JOY_BUTTON1)
				this1 = TRUE;
			if ((joyinfo.wButtons & JOY_BUTTON2) == JOY_BUTTON2)
				this2 = TRUE;
		}
	}
	if (!button2)
	{
		if (last1 != this1)
		{
			last1 = this1;
			return this1;
		}
	}
	else
	{
		if (last2 != this2)
		{
			last2 = this2;
			return this2;
		}
	}
	return FALSE;
}

void CsurfView::MoveSurfer()
{
	D3DVECTOR position;
	D3DVECTOR z_vector;
	D3DVECTOR y_vector;
	D3DVECTOR velocity_vector;
	float ratio_from_top;
	int i; 
	static float launch_rotation = (const float)0;

	float speed = (const float)1;
	float rotation = (const float)0;
	BOOL animatedwater = FALSE;
	static BOOL dropin = FALSE;
	static BOOL bFloater = FALSE;
	static BOOL firstspray = TRUE;
	static int tricksound;
	static int ollie_time = 0;
	static int spray_array[NUMSPRAY] = {0,7,6,5,4,3,2,1};
	float animate_add = (const float)0;
	float rotate_coeff = (const float)0.1;
	BOOL trick_button = FALSE;
	static int NarateNum = 0;
	BOOL push_down = FALSE;
	BOOL push_up = FALSE;
	BOOL push_left = FALSE;
	BOOL push_right = FALSE;
	float temp_hold;
	static BOOL trick_param;
	static BOOL narate = TRUE;
	static BOOL playsound = TRUE;
	static D3DVECTOR last_ollie;
	BOOL bDoneOllie = FALSE;
	static const float todd_ollie[10] = 
	{
		(const float) 0,
		(const float) 0.6,
		(const float) 1.5,
		(const float) 2.4,
		(const float) 2.7,
		(const float) 3.0,
		(const float) 2.7,
		(const float) 2.4,
		(const float) 1.5,
		(const float) 0.6
	};
	static const float alana_ollie[13] = 
	{
		(const float) 0,
		(const float) 0,
		(const float) 0,
		(const float) 0.6,
		(const float) 1.5,
		(const float) 2.4,
		(const float) 2.7,
		(const float) 3.0,
		(const float) 2.7,
		(const float) 2.4,
		(const float) 1.5,
		(const float) 0.6,
		(const float) 0
	};

	// check to see if the surfer is in the middle of a wipe-out,
	// if so, apply changes and check to see if done.

	if (bSharkAttack)
	{
		if (sharktime>=30)
		{
			if (bSplat)
			{
				if ((splat_time >= 0) && (splat_time < NUMBLOOD))
					blood[splat_time]->SetPosition(surfer[current_surfer], D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
				if ((splat_time >= 1) && (splat_time < NUMBLOOD+1))
					blood[splat_time-1]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
				splat_time++;
			}
			surfer[current_surfer]->GetVelocity(m_scene, &velocity_vector, FALSE);
			surfer[current_surfer]->SetVelocity(m_scene, D3DVALUE(velocity_vector.x), D3DVALUE(-8), D3DVALUE(velocity_vector.z), FALSE);
			surfer[current_surfer]->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(0.2));
			surfer[current_surfer]->GetPosition(m_scene, &position);
			if (position.y < (frame_y[MAXWAVEFRAME+1]-48))
			{
				WipeOut();
				dropin = FALSE;
			}
			else if (position.y < (frame_y[MAXWAVEFRAME]))
			{
				if (bSprayOn)
				{
					surfer[current_surfer]->GetPosition(m_scene, &position);
 					for (i = 0; i < NUMSPRAY; i++)
					{
						if (spray_used[i] == FALSE)
						{
							spray[spray_array[i]]->SetPosition(m_scene, position.x, position.y+i*10, position.z-i);
						}
					}
				}
			}
			if (bSoundFx)
		 		m_pDSBuffer[randInt(SHARKWAVE,SHARKWAVE+2)]->Play(0, 0, 0);
		}
		goto move_surfer_end;
	}
	else if (bWipeout)
	{
		if (bSplat)
		{
			if ((splat_time >= 0) && (splat_time < NUMBLOOD))
				blood[splat_time]->SetPosition(surfer[current_surfer], D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
			if ((splat_time >= 1) && (splat_time < NUMBLOOD+1))
				blood[splat_time-1]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			splat_time++;
		}
		if (animate_time >= 146.0)
			animate_time += (const float)0.3*fGameSpeed;
		else
			animate_time += (const float)0.4*fGameSpeed;

		if ((animate_time > 142.0) && (animate_time < 143.0))
			animate_time = (const float)142;
		else if ((animate_time > 145.0) && (animate_time < 146.0))
			animate_time = (const float)145;
		else if ((animate_time > 149.0) && (animate_time < 150.0))
			animate_time = (const float)149;

		surfer[current_surfer]->GetVelocity(m_scene, &velocity_vector, FALSE);
		surfer[current_surfer]->SetVelocity(m_scene, D3DVALUE(velocity_vector.x), D3DVALUE(velocity_vector.y-(SINK)), D3DVALUE(velocity_vector.z), FALSE);
		surfer[current_surfer]->GetPosition(m_scene, &position);
		if (position.y < (frame_y[MAXWAVEFRAME+1]-48))
		{
//			if (bSoundFx)
//				m_pDSBuffer[SURFERSND]->Stop();
			bFloater = FALSE;
			dropin = FALSE;
			WipeOut();
 			narate = TRUE;
		}
		else if (position.y < (frame_y[MAXWAVEFRAME]))
		{
			if (bSprayOn)
			{
				surfer[current_surfer]->GetPosition(m_scene, &position);
 				for (i = 0; i < NUMSPRAY; i++)
				{
					if (spray_used[i] == FALSE)
					{
						spray[spray_array[i]]->SetPosition(m_scene, position.x, position.y+i*10, position.z-i);
					}
				}
			}
		}
		surf_animate[current_surfer]->SetTime(D3DVAL(animate_time));
		goto move_surfer_end;
	}
	
	// set the bottom frame distance to be relative to the surfer's speed
	// for example - he can go out farther if he is going faster...

	frame_z[MAXWAVEFRAME+1] = frame_z[MAXWAVEFRAME]-(50+(100*surfer_velocity/surfer_speed));
	frame_orient[MAXWAVEFRAME].y = (frame_z[MAXWAVEFRAME] - frame_z[MAXWAVEFRAME+1]);
	frame_orient[MAXWAVEFRAME].z = -(frame_y[MAXWAVEFRAME] - frame_y[MAXWAVEFRAME+1]);

	// this part sets his orientation according to his y coordinate.

	surfer[current_surfer]->GetPosition(m_scene, &position);
	if (trick == 5)
	{
		position.x -= last_ollie.x;
		position.y -= last_ollie.y;
		position.z -= last_ollie.z;
	}
	surfer[current_surfer]->GetOrientation(m_scene, &z_vector, &y_vector);

	// see what frame he is on

	for (i = 1; i <= MAXWAVEFRAME; i++)
	{
		if (position.y > frame_y[i+1])
		{
			if (position.y < frame_y[i])
			{
				// he is on a "safe" frame..
				// This part ensures that he is locked to the wave...
				
				ratio_from_top = (frame_y[i] - position.y)/(frame_y[i] - frame_y[i+1]);
				
				animatedwater = TRUE;
				MoveWave();

				position.z = frame_z[i] - ((frame_z[i] - frame_z[i+1]) * ratio_from_top);
				position.y = frame_y[i] - ((frame_y[i] - frame_y[i+1]) * ratio_from_top);

				surfer[current_surfer]->SetPosition(m_scene, position.x, position.y, position.z);
				tempSurfX = (long)position.x;

				y_vector.x = frame_orient[i-1].x - ((frame_orient[i-1].x - frame_orient[i].x) * ratio_from_top);
				y_vector.y = frame_orient[i-1].y - ((frame_orient[i-1].y - frame_orient[i].y) * ratio_from_top);
				y_vector.z = frame_orient[i-1].z - ((frame_orient[i-1].z - frame_orient[i].z) * ratio_from_top);

				current_frame = i;

				i = ON_FRAMES;
			}
		}
	}

	// routines for paddle out
	if (bNotDroppedInYet &! bGameOver)
	{
		surf_animate[current_surfer]->SetTime(animate_time);

		surfer[current_surfer]->SetVelocity(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
		if (current_frame > LIP_FRAME+3)
		{
			surfer[current_surfer]->SetVelocity(surfer[current_surfer], D3DVALUE(-15.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
			animate_time -= (const float)0.5*fGameSpeed;
			playsound = TRUE;
		}
		else if (current_frame > LIP_FRAME)
		{
			surfer[current_surfer]->SetVelocity(surfer[current_surfer], D3DVALUE(-8.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
			animate_time -= (const float)0.1*fGameSpeed;
			surfer_velocity = surfer_speed/3;
			if (Fire(FALSE))
			{
				bNotDroppedInYet = FALSE;
				dropin = TRUE;
				surfer_velocity = surfer_speed;
				narate = TRUE;
				playsound = TRUE;
				if (bSurferSounds)
					AddSurferSound(DROPIN_SOUND);
			}
		}
		else if (current_frame == LIP_FRAME)
		{
			if (bNaration && narate && (game_time < 1161))
			{
				AddAnnounce(randInt(SURF1,SURF1+3));
				narate = FALSE;
			}
			surfer_velocity = surfer_speed/2;
			if (Fire(FALSE))
			{
				bNotDroppedInYet = FALSE;
				dropin = TRUE;
				narate = TRUE;
				surfer_velocity = surfer_speed;
				playsound = TRUE;
				if (bSurferSounds)
					AddSurferSound(DROPIN_SOUND);
			}
		}

		animate_time += fGameSpeed;

		if ((animate_time > (const float)19) && !dropin)
			animate_time = (const float)10;

		goto move_surfer_set;
	}

	if (dropin)
	{
		surf_animate[current_surfer]->SetTime(animate_time);

		if (animate_time < 20)
			animate_time += (const float)1.5*fGameSpeed;

		surfer[current_surfer]->SetVelocity(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
		surfer[current_surfer]->SetVelocity(surfer[current_surfer], D3DVALUE(surfer_speed/2), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);

		animate_time += fGameSpeed;

		if (animate_time > (const float)29)
		{
			dropin = FALSE;
			animate_time = (const float)40;
		}
	}

	// taxi cab meter for score

	score += (int)((bUfoStop ? 2 : 1)*fGameSpeed);

	// if he is not on a "safe" frame...

	if (i < ON_FRAMES)
	{
		
		if (position.y > frame_y[1])
		{
			current_frame = ABOVE_WAVE;
		}
		else 
		{
			current_frame = BETWEEN_FRAMES;

			// check for wipeout off of bottom of wave
			
			if (((position.y < frame_y[MAXWAVEFRAME+1]) || (position.z < frame_z[MAXWAVEFRAME+1]))
				&& (trick != 5))
			{
				if (!bWipeout)
				{
					animate_time = (const float)140;
					bWipeout = TRUE;
					if (bContest)
					{
						board_condition += 5;
						ApplyStats();
					}
				}
				if (bSoundFx)
	 				m_pDSBuffer[SINKING]->Play(0, 0, 0);
				if (bNaration && narate)
				{
					AddAnnounce(randInt(REEF1,REEF1+12));
					narate = FALSE;
				}
				if (bSurferSounds && playsound)
				{
					AddSurferSound(WIPEOUT_SOUND);
					playsound = FALSE;
				}

				return;
			}
		}
	}

	// check for spacebar and on wave, if so, super-turn activate!

	if ((::GetAsyncKeyState(VK_SPACE) <0) && (current_frame >= LIP_FRAME))
	{
		speed = (const float) 2;
	}

	// joystick routines

	if (bJoystickExists)
	{
		JOYINFO joyinfo;

		// if no errors, proceed with joystick routines

		if (joyGetPos(m_uiJoyStick, &joyinfo) == JOYERR_NOERROR)
		{
			// check for joybutton and on wave, if so super-turn!
			if ((joyinfo.wButtons & JOY_BUTTON1) && (current_frame >= LIP_FRAME))
			// This method needs to be fixed to work when
			// more than one button is pressed at one time...
			{
				speed = (const float) 2;
			}

			// joystick left turn with gradual response

			if (joyinfo.wXpos < joy_center)
			{
				rotation = (surfer_turn*speed*(joyinfo.wXpos-joy_center)/joy_half);
				if (joyinfo.wXpos < joy_left)
					push_left = TRUE;
			}

			// joystick right turn with gradual response

			else if (joyinfo.wXpos > joy_center)   
			{
  				rotation = -(surfer_turn*speed*(joy_center-joyinfo.wXpos)/joy_half);
				if (joyinfo.wXpos > joy_right)
					push_right = TRUE;
			}

			// keyboard up pressed

		  	if (joyinfo.wYpos < joy_up)
			{
				push_up = TRUE;
			}
			else

			// keyboard down pressed

		  	if (joyinfo.wYpos > joy_down)
			{
				push_down = TRUE;
			}


			// trick button
			if ((joyinfo.wButtons & JOY_BUTTON2) && !dropin)
			{
				trick_button = TRUE;
			}
		}
	}

	// keyboard left turn

  	if (::GetAsyncKeyState(VK_LEFT) <0)
	{
		rotation = -(surfer_turn*speed);
		push_left = TRUE;
	}

	// keyboard right turn

  	if (::GetAsyncKeyState(VK_RIGHT) <0)
	{
  		rotation = (surfer_turn*speed);
		push_right = TRUE;
	}

	// keyboard down pressed

  	if (::GetAsyncKeyState(VK_DOWN) <0)
	{
		push_down = TRUE;
	}

	// keyboard up pressed

  	if (::GetAsyncKeyState(VK_UP) <0)
	{
		push_up = TRUE;
	}

	// trick
	if ((::GetAsyncKeyState(VK_CONTROL) <0) && !dropin)
	{
		trick_button = TRUE;
	}

	bTubeTuck = FALSE;

	// apply animation
	if (!dropin)
	{
		if (trick_button)
		{
			if (trick == 0)
			{
				if (push_up)
				{
					// ollie for alana
					// headstand for bucky
					// hang ten for lee
					// arch for sandy
					// kickflip for todd
					// luge for vic
					if ((current_surfer == ALANA)
						|| (current_surfer == TODD))
					{
						if (current_frame >= LIP_FRAME && intube == 0)
						{
							bOverBreak = FALSE;
							bOverPier = FALSE;
							bOverOilRig = FALSE;
							trick = 5;
							ollie_time = 0;
							tricksound = randInt(TRICKSOUND1,TRICKSOUND1+10);
							if (bSurferSounds)
							{
								if (randInt(0,3)<1)
									AddSurferSound(HOLD_SOUND);
								else
									AddSurferSound(TRICK_SOUND);
							}
						}
					}
					else
					{
						trick = 1;
						if (bSurferSounds)
							AddSurferSound(HOLD_SOUND);
					}
					animate_time = (const float)70;
				}
				else if (push_down)
				{
					// duck for alana
					// scorpion for bucky
					// quasimodo for lee
					// split headstand for sandy
					// noseride for todd
					// duck for vic
					trick = 2; 
					animate_time = (const float)80;
					if (bSurferSounds)
						AddSurferSound(HOLD_SOUND);
				}
				else if (push_right)
				{
					// 360 slide for alana
					// and bucky
					// walkaround from right for lee
					// kick for sandy
					// powerslide for todd
					// 360 slide for vic
					if ((current_surfer != TODD) || (current_frame >= LIP_FRAME))
					{
						trick = 3; 
						animate_time = (const float)120;
						tricksound = randInt(TRICKSOUND1,TRICKSOUND1+10);
						if (bSurferSounds)
							AddSurferSound(TRICK_SOUND);
					}
				}
				else if (push_left)
				{
					// 360 slide for alana
					// and bucky
					// walkaround left for lee
					// kick for sandy
					// powerslide for todd
					// 360 slide for vic
					if ((current_surfer != TODD) || (current_frame >= LIP_FRAME))
					{
						trick = 4; 
						animate_time = (const float)120;
						tricksound = randInt(TRICKSOUND1,TRICKSOUND1+10);
						if (bSurferSounds)
							AddSurferSound(TRICK_SOUND);
					}
				}
//				trick_param = FALSE;
			}
		}
		else if (push_down && (trick == 0))
		{
			// tube tuck
			bTubeTuck = TRUE;
			animate_add = (const float) 60;
		}
		switch (trick)
		{
		case 0: // no trick - standard rotation animation
		
			animate_time -= rotation*10*fGameSpeed;

			if (animate_time < 40)
				animate_time += (40-animate_time)/8*fGameSpeed;
			else if (animate_time > 40)
				animate_time -= (animate_time-40)/8*fGameSpeed;

			if (animate_time > (const float)49)
				animate_time = (const float)49;
			else if (animate_time < (const float)31)
				animate_time = (const float)31;

			if (current_frame < LIP_FRAME)
				animate_add = (const float)20;

			surf_animate[current_surfer]->SetTime(D3DVAL(animate_time+animate_add));
			break;
			
		case 1: // hang ten for lee
	
			if (push_up)
			{
				if (animate_time < 78)
					animate_time += fGameSpeed;
				else
				{
					score += (int)(((bUfoStop ? 10.0 : 5.0) + ((current_frame < LIP_FRAME) ? 10.0 : 5.0))*fGameSpeed);
					if ((current_surfer == BUCKY) && bContest)
					{
						board_condition -= randInt(0,2);
						ApplyStats();
					}
				}
			}
			else if (animate_time > 70)
				animate_time -= fGameSpeed;
			else
			{
				animate_time = (const float)40;
				trick = 0;
				if (bNaration)
					AddAnnounce(randInt(OHH,OHH+2));
			}
			rotation*=(const float)0.5;
			surf_animate[current_surfer]->SetTime(D3DVAL(animate_time));

			break;

		case 2: // quasimodo for lee

			if (push_down)
			{
				if (animate_time < 88)
					animate_time += fGameSpeed;
				else
				{
					score += (int)(((bUfoStop ? 10.0 : 5.0) + ((current_frame < LIP_FRAME) ? 10.0 : 5.0))*fGameSpeed);
					if ((current_surfer != BUCKY) && bContest)
					{
						board_condition -= randInt(0,2);
						ApplyStats();
					}
					else if ((current_surfer == BUCKY) && !bUfo)
					{
						if (current_frame < LIP_FRAME)
						{
							if (randInt(0,25) < 2)
							{
								OnUfo();
								ufo->SetPosition(m_scene, (const float)0, (const float)1500, (const float)1500);
								bSummoned = TRUE;
							}
						}
						else
						{
							if (randInt(0,50) < 2)
							{
								OnUfo();
								ufo->SetPosition(m_scene, (const float)0, (const float)1500, (const float)1500);
								bSummoned = TRUE;
							}
						}
					}
				}
			}
			else if (animate_time > 80)
				animate_time -= fGameSpeed;
			else
			{
				animate_time = (const float)40;
				trick = 0;
				if (bNaration)
					AddAnnounce(randInt(OHH,OHH+2));
			}
			rotation*=(const float)0.5;
			surf_animate[current_surfer]->SetTime(animate_time);

			break;

		case 3: // walkaround from right for lee
				
			if (animate_time > 111)
			{
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Play(0,0,0);
				if (current_surfer == TODD)
				{
					if (animate_time > 117)
					{
						rotation*=(const float)0.5;
						animate_time -= fGameSpeed;
					}
					else if (animate_time > 115)
					{
						if (push_right && (surfer_velocity > (surfer_speed)
							&& (current_frame >= LIP_FRAME)))
						{
							animate_time-=3/(surfer_velocity)*fGameSpeed;
							rotation*=(const float)0.15;
							score += (int)((bUfoStop ? 50 : 25)*fGameSpeed);
						}
						else
						{
							rotation*=(const float)0.5;
							animate_time -= fGameSpeed;
						}
						surfer_velocity*=(const float)0.95;
					}
					else
					{
						if (!push_right)
						{
							rotation*=(const float)0.5;
						}
						animate_time -= fGameSpeed;
					}
				}
				else
				{
					rotation*=(const float)0.5;
					animate_time -= fGameSpeed;
				}
			}
			else
			{
				trick = 0;
				score += (bUfoStop ? 200 : 100) + ((current_frame < LIP_FRAME) ? 200 : 100);
				animate_time = (const float)40;
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Stop();
			}
			surf_animate[current_surfer]->SetTime(animate_time);

			break;

		case 4: // walkaround from left for lee

			if (animate_time < 129)
			{
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Play(0,0,0);
				if (current_surfer == TODD)
				{
					if (animate_time < 123)
					{
						rotation*=(const float)0.5;
						animate_time += fGameSpeed;
					}
					else if (animate_time > 125)
					{
						if (push_left && (surfer_velocity > (surfer_speed)
							&& (current_frame >= LIP_FRAME)))
						{
							animate_time+=3/(surfer_velocity)*fGameSpeed;
							rotation*=(const float)0.15;
							score += (int)((bUfoStop ? 50 : 25)*fGameSpeed);
						}
						else
						{
							rotation*=(const float)0.5;
							animate_time += fGameSpeed;
						}
						surfer_velocity*=(const float)0.95;
					}
					else
					{
						if (!push_left)
						{
							rotation*=(const float)0.5;
						}
						animate_time += fGameSpeed;
					}
				}
				else
				{
					rotation*=(const float)0.5;
					animate_time += fGameSpeed;
				}
			}
			else
			{
				trick = 0;
				score += (bUfoStop ? 200 : 100) + ((current_frame < LIP_FRAME) ? 200 : 100);
				animate_time = (const float)40;
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Stop();
			}
			surf_animate[current_surfer]->SetTime(animate_time);
			break;

		case 5: // kickflip & ollie
	
			if (animate_time < 78)
			{
				surfer[current_surfer]->SetOrientation(m_scene, z_vector.x, z_vector.y, z_vector.z,
					y_vector.x, y_vector.y, y_vector.z);
				surfer[current_surfer]->GetOrientation(m_scene, &z_vector, &y_vector);
				switch (current_surfer)
				{
				case TODD:
					if (surfer_velocity < 10)
						temp_hold = 10 * todd_ollie[ollie_time];
					else if (surfer_velocity > 50)
						temp_hold = 50 * todd_ollie[ollie_time];
					else
						temp_hold = surfer_velocity * todd_ollie[ollie_time];

					last_ollie.x = y_vector.x * temp_hold;
					last_ollie.y = (y_vector.y + (const float)0.6) * temp_hold;
					last_ollie.z = y_vector.z * temp_hold * (const float)0.4;
					ollie_time++;
					animate_time += (const float)0.75*fGameSpeed;
					break;
				case ALANA:
					if (surfer_velocity < 10)
						temp_hold = 10 * alana_ollie[ollie_time];
					else if (surfer_velocity > 50)
						temp_hold = 50 * alana_ollie[ollie_time];
					else
						temp_hold = surfer_velocity * alana_ollie[ollie_time];

					last_ollie.x = y_vector.x * temp_hold;
					last_ollie.y = (y_vector.y + (const float)0.6) * temp_hold;
					last_ollie.z = y_vector.z * temp_hold * (const float)0.4;
					if (animate_time < 73)
					{
						animate_time += fGameSpeed;
					}
					else
					{
						animate_time += (const float)0.5*fGameSpeed;
					}
					ollie_time++;
					break;
				}
				surfer[current_surfer]->SetPosition(m_scene, 
					last_ollie.x + position.x,
					last_ollie.y + position.y,
					last_ollie.z + position.z);
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Play(0,0,0);
			}
			else
			{
				trick = 0;
				animate_time = (const float)40;
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Stop();
				bDoneOllie = TRUE;
				Whooshed = FALSE;
				surfer[current_surfer]->GetVelocity(m_scene, &velocity_vector, FALSE);
				surfer[current_surfer]->SetVelocity(m_scene, velocity_vector.x, D3DVALUE(velocity_vector.y-10), velocity_vector.z, FALSE);
				score += (bUfoStop ? 200 : 100) + ((current_frame < LIP_FRAME) ? 200 : 100);
				if ((z_vector.x <= 0.4) && ((current_frame == LIP_FRAME) || (current_frame == LIP_FRAME-1)))
				{
					bFloater = TRUE;
					score += bUfoStop ? 300 : 150;
					if (bNaration)
						AddAnnounce(randInt(OHH,OHH+2));
					if (bSurferSounds)
						AddSurferSound(INSANITY_SOUND);
					tricksound = randInt(TRICKSOUND1,TRICKSOUND1+10);
					if (bSoundFx)
						m_pDSBuffer[tricksound]->Play(0,0,0);
				}
			}
			if (current_frame >= LIP_FRAME)
				launch_rotation*=(const float)0.75;
			rotation*=(const float)0.5;
			surf_animate[current_surfer]->SetTime(animate_time);
			break;
		}
	}
	else 
		rotation /= speed;

	// in air routines for velocity

	if ((current_frame < LIP_FRAME) || trick == 5)
	{
		num_change = 0;

		// sum of rotation for scoring 360s and whatnot...

		rotate_sum += (rotation + launch_rotation)*fGameSpeed;
	}
	if (current_frame < LIP_FRAME)
	{
		if (trick != 5)
		{
			score += (int)((bUfoStop ? 10 : 5)*fGameSpeed);
			if (Whooshed) // play only once during air
			{
				// put a launch sound here!
				bOverBreak = FALSE;
				bOverPier = FALSE;
				bOverOilRig = FALSE;
				if (bSoundFx)
		 			m_pDSBuffer[WHOOSH]->Play(0, 0, 0);
				Whooshed = FALSE;
			}
		}
		surfer[current_surfer]->GetVelocity(m_scene, &velocity_vector, FALSE);
		if((current_surfer == LEE) && (trick == 1))
			surfer[current_surfer]->SetVelocity(m_scene, velocity_vector.x, D3DVALUE(velocity_vector.y-(GRAVITY*0.60*fGameSpeed)), velocity_vector.z, FALSE);
		else
			surfer[current_surfer]->SetVelocity(m_scene, velocity_vector.x, D3DVALUE(velocity_vector.y-(GRAVITY*fGameSpeed)), velocity_vector.z, FALSE);
	}

	// on wave routines

	else if (trick != 5)
	{
		if (((current_frame >= LIP_FRAME) && (last_frame < LIP_FRAME))
			|| bDoneOllie)
		{
			// splash routine
			if (current_frame >= LIP_FRAME)
			{
				if (bSprayOn)
				{
					for (i = 0; i < NUMSPRAY; i++)
					{
						if (spray_used[i] == FALSE)
						{
							spray[spray_array[i]]->SetPosition(m_scene, position.x, position.y+i*10, position.z-i);
						}
					}
				}
				// landing an air routine
				Whooshed = TRUE;	// need to only set this once from having landed air
				rotate_sum = (const float)0;   // no sum if not in air

				// convert in air velocity to on wave velocity
				child_of_the_wave->SetVelocity(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
				surfer[current_surfer]->GetVelocity(child_of_the_wave, &velocity_vector, TRUE);
				child_of_the_wave->SetVelocity(surfer[current_surfer], D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
				surfer_velocity = velocity_vector.x;
	
				// if velocity < 0 then wipe out

				if ((surfer_velocity <= 0) || (!bDoneOllie && (z_vector.x <= 0)))
				{
					if (bSoundFx)
					{
						m_pDSBuffer[SPLASH]->SetPan((tempSurfX - tempCameraX) * 6);
						m_pDSBuffer[SPLASH]->Play(0, 0, 0);
//						m_pDSBuffer[SURFERSND]->Stop();
					}
					if (bNaration && narate)
					{
						AddAnnounce(randInt(REEF1,REEF1+12));
						narate = FALSE;
					}
					if (bSurferSounds && playsound)
					{
						AddSurferSound(WIPEOUT_SOUND);
						playsound = FALSE;
					}
	
					if (!bWipeout)
					{
						animate_time = (const float)143;
						bWipeout = TRUE;
						bFloater = FALSE;
						if (bContest)
						{
							board_condition += 5;
							ApplyStats();
						}
					}
					return;
				}
			}

			if (bOverPier)
			{
				score+=10000;
				if (bSoundFx)
			 		m_pDSBuffer[UFOCWAVE]->Play(0, 0, 0);
				if (bNaration)
					AddAnnounce(PIERACTION);
				if (bSurferSounds)
					AddSurferSound(INSANITY_SOUND);
			}
			if (bOverBreak && ((trick != 1) || ((current_surfer != SANDY) && (current_surfer != VIC))))
			{
				score+=10000;
				if (bSoundFx)
			 		m_pDSBuffer[UFOCWAVE]->Play(0, 0, 0);
				if (bNaration)
					AddAnnounce(ORBIT);
				if (bSurferSounds)
					AddSurferSound(INSANITY_SOUND);
			}
			if (bOverOilRig)
			{
				score+=20000;
				if (bSoundFx)
			 		m_pDSBuffer[UFOCWAVE]->Play(0, 0, 0);
				if (bNaration)
					AddAnnounce(ORBIT);
				if (bSurferSounds)
					AddSurferSound(INSANITY_SOUND);
			}
			if (bSoundFx && (current_frame >= LIP_FRAME))
			{
				m_pDSBuffer[LANDINGWAVE]->SetPan((tempSurfX - tempCameraX) * 6);
				m_pDSBuffer[LANDINGWAVE]->Play(0, 0, 0);
			}

			if (lastp > 0)
			{
				if (lastp>10)
					lastp = 10;
				if (lastp>5)
					score += (bUfoStop ? 360 : 180) * lastp * 2;//*stat_score[current_surfer];
				else
					score += (bUfoStop ? 360 : 180) * lastp;//*stat_score[current_surfer];

				if (bNaration)
				{
					NarateNum++;
					if (NarateNum > 1)
						NarateNum = 0;
					AddAnnounce(S180SOUND1-2+(lastp*2)+NarateNum);
				}
				lastp = 0;
			}

			// if surfer is going slower than his min. velocity, speed him up

			else if ((surfer_velocity < surfer_speed) && (surfer_velocity > 0))
				surfer_velocity = surfer_speed;
		}
	
		// if surfer is NOT landing an air apply changes to velocity
		// from carving

		else
		{
			if (bFloater && (z_vector.x <= 0.5) && ((current_frame == LIP_FRAME) || (current_frame == LIP_FRAME-1)))
			{
				score += bUfoStop ? 200 : 100;
				if (bSoundFx)
					m_pDSBuffer[tricksound]->Play(0,0,0);
			}
			else
			{
				bFloater = FALSE;
			}
			// surfer must be moving to get speed from carving

			if (surfer_velocity > 0)
			{
				// gravity has some effect

				surfer[current_surfer]->GetVelocity(m_scene, &velocity_vector, FALSE);
				if (velocity_vector.y < 0)
					surfer_velocity += (-velocity_vector.y/surfer_velocity)*fGameSpeed;
				else
					surfer_velocity += (const float)0.5*(-velocity_vector.y/surfer_velocity)*fGameSpeed;
				
				// water resistance causes constant deceleration

				surfer_velocity -= (const float)0.06*fGameSpeed;

				// change in stick's position has some effect
				// (wiggling it madly)

				if (launch_rotation > rotation)
				{
					surfer_velocity += (launch_rotation - rotation)/speed*(MAXWAVEFRAME - current_frame)/MAXWAVEFRAME;
					if (rotation < 0)
					{
						if (bSoundFx)
						{
							m_pDSBuffer[SLALOM]->SetPan((tempSurfX - tempCameraX) * 6);
							m_pDSBuffer[SLALOM]->SetVolume((long)(-1000 + 500*surfer_velocity/surfer_max));
							m_pDSBuffer[SLALOM]->Play(0, 0, 0);
						}
					}
				}
				else
					surfer_velocity += (rotation - launch_rotation)/speed*(MAXWAVEFRAME - current_frame)/MAXWAVEFRAME;
				if (rotation > 0)
				{
					if (bSoundFx)
					{
						m_pDSBuffer[SLALOM]->SetPan((tempSurfX - tempCameraX) * 6);
						m_pDSBuffer[SLALOM]->SetVolume((long)(-3000 + 1000*surfer_velocity/surfer_max));
						m_pDSBuffer[SLALOM]->Play(0, 0, 0);
					}
				}

				// totally carving it up has more of an effect

				// check to see if his frame has changed
				// I do this here because why not? air will not
				// come into play, because it already has in the
				// landing routine.

				if ((current_frame != BETWEEN_FRAMES) && (current_frame != last_frame))
				{
					if ((current_frame > change_frame[0]) && (change_frame[0] < change_frame[1]))
					{
						surfer_velocity += (float)num_change*2*(surfer_max-surfer_velocity)/surfer_max;
						num_change = 0;		
					}
					if ((current_frame < change_frame[0]) && (change_frame[0] > change_frame[1]))
					{
						surfer_velocity += (float)num_change*2*(surfer_max-surfer_velocity)/surfer_max;
						num_change = 0;		
					}
					change_frame[1] = change_frame[0];
					change_frame[0] = current_frame;
					num_change++;
				}
			}
		}
		
		// since he is not in air, overwrite the launch rotation with
		// his current rotation, zero the current rotation, and apply
		// velocities
		launch_rotation = rotation;
		rotation = (const float)0;
		child_of_the_wave->SetVelocity(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
		surfer[current_surfer]->GetVelocity(child_of_the_wave, &velocity_vector, FALSE);
		child_of_the_wave->SetVelocity(surfer[current_surfer], D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
		surfer[current_surfer]->SetVelocity(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
		surfer[current_surfer]->SetVelocity(surfer[current_surfer], surfer_velocity, velocity_vector.y*surfer_slide, velocity_vector.z*surfer_slide, FALSE);
	}

	// apply the surfer's rotations (for on/off wave)

	if (surfer_velocity != 0)
		surfer[current_surfer]->SetRotation(surfer[current_surfer], D3DVALUE(-0.2), D3DVALUE(1.0), D3DVALUE(0.0), rotation+launch_rotation);

	// if the surfer is stopped (for any reason) then wipe him out

	if (surfer_velocity < 1)
	{
		if (bSoundFx)
		{
			m_pDSBuffer[SPLASH]->SetPan((tempSurfX - tempCameraX) * 6);
			m_pDSBuffer[SPLASH]->Play(0, 0, 0);
//			m_pDSBuffer[SURFERSND]->Stop();
		}
		if (!bWipeout)
		{
			animate_time = (const float)140;
			bWipeout = TRUE;
		}
	}

move_surfer_set:

	// set the surfer's orientation

	surfer[current_surfer]->SetOrientation(m_scene, z_vector.x, z_vector.y, z_vector.z,
		y_vector.x, y_vector.y, y_vector.z);

move_surfer_end:

	if(!animatedwater)
		MoveWave();
	if (bCheatKeys)
	{
		if (::GetAsyncKeyState(VK_NUMPAD1) <0)
		{
			if (!bWipeout)
			{
				animate_time = (const float)140;
				bWipeout = TRUE;
			}
		}
		if (::GetAsyncKeyState(VK_NUMPAD2) <0)
		{
			if (!bWipeout)
			{
				animate_time = (const float)140;
				bWipeout = TRUE;
				lives =- 1;
			}
		}
	}

	// spray shit

	if (bSprayOn && !bNotDroppedInYet)
	{
		if (firstspray)
		{
			for (i = 0; i < NUMSPRAY; i++)
			{
				spray_used[i] = FALSE;
			}
			firstspray = FALSE;
		}
		for (i = NUMSPRAY-2; i >= 0; i--)
		{
			spray_used[i+1] = spray_used[i];
			if (spray_used[i+1] == FALSE)
				spray_size[i+1] = spray_size[i+1] + 2;
			else
				spray_size[i+1] = spray_size[i] + 20;
			lpSprayMap[spray_array[i+1]]->SetDecalSize(spray_size[i+1], spray_size[i+1]);
			spray_array[i+1]++;
			if (spray_array[i+1] == NUMSPRAY)
				spray_array[i+1] = 0;
		}
		if ((current_frame < LIP_FRAME) || (trick == 5) || bWipeout)
		{
			spray_used[0] = FALSE;
			spray[spray_array[0]]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-10000), D3DVALUE(0));
			spray_size[0] += D3DVALUE(5);
		}
 		else
		{
			spray_used[0] = TRUE;
			spray[spray_array[0]]->SetPosition(surfer[current_surfer], D3DVALUE(surfer_speed-5), D3DVALUE(8), D3DVALUE(0));
			spray_size[0] = D3DVALUE(20);
		}
		lpSprayMap[spray_array[0]]->SetDecalSize(spray_size[0], spray_size[0]);
		spray_array[0]++;
		if (spray_array[0] == NUMSPRAY)
			spray_array[0] = 0;
	}

	// all of the main network stuff will be here
/*
	if (bNetworked)
	{
		BYTE                CommBuff[256];
	    DPID                fromID, dcoReceiveID;
	    DWORD               nBytes;
//		MSGNEWPLAYER		msgNewPlayer;
//		MSGUSEDCHARS		msgUsedChars;
//		MSGPLAYERINUSE		msgPlayerInUse;
//		MSGCHARSELECT		msgCharselect;
//		MSGUPDATEWAVE		msgUpdateWave;
		MSGONWAVEPOS		msgOnWavePos;
//		MSGWIPEOUT			msgWipeOut;
//		MSGHANGINGOUT		msgHangingOut;
	    HRESULT				LastError;
		LPMSGONWAVEPOS		msg;
	    if ( lpDP )
	    {
			// send messages
			msgOnWavePos.MsgType = MSG_ON_WAVE_POS;
			msgOnWavePos.Surfer = ALANA;
			msgOnWavePos.AnimateTime = animate_time; // not quite right
			msgOnWavePos.WaveFrame = current_frame;
			msgOnWavePos.WaveFrameRatio = ratio_from_top;
			msgOnWavePos.SurferPosX = position.x;
			msgOnWavePos.SurferOrientZ = z_vector;
			msgOnWavePos.SurferOrientZ = y_vector;
			DPID from = PlayerId[ThisPlayer];
			LastError = lpDP->Send(from, 0, NULL, &msgOnWavePos, sizeof (MSGONWAVEPOS));
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "DP New Player Message Failed.");
		    }

		    // read all messages in queue
	        while(1)
		    {
	            nBytes = 256;
	            LastError = lpDP->Receive(
	                        &fromID,
	                        &dcoReceiveID,
	                        DPRECEIVE_ALL,
	                        CommBuff,
	                        &nBytes);
				if (LastError == DP_OK)
                {
					switch (CommBuff[0])
					{
					case MSG_NEW_PLAYER:
//						MessageBox("Msg New Player","Network!");
						m_scene->AddChild(surfer[ALANA]);
						break;
					case MSG_USED_CHARS:
						MessageBox("Msg Used Chars","Network!");
						break;
					case MSG_PLAYER_IN_USE:
						MessageBox("Player In Use","Network!");
						break;
					case MSG_CHAR_SELECT:
						MessageBox("Char Select","Network!");
						break;
					case MSG_UPDATE_WAVE:
						MessageBox("Update Wave","Network!");
						break;
					case MSG_ON_WAVE_POS:
//						MessageBox("On Wave Pos","Network!");
						msg = (LPMSGONWAVEPOS)CommBuff;
						surf_animate[msg->Surfer]->SetTime(msg->AnimateTime);
						surfer[msg->Surfer]->SetOrientation(m_scene, msg->SurferOrientZ.x,
							msg->SurferOrientZ.y, msg->SurferOrientZ.z,
							msg->SurferOrientY.x,msg->SurferOrientY.y, msg->SurferOrientY.z);
						surfer[msg->Surfer]->SetPosition(m_scene, 
							msg->SurferPosX,
							top_frame_y[msg->WaveFrame] - ((top_frame_y[msg->WaveFrame] - bottom_frame_y[msg->WaveFrame]) * msg->WaveFrameRatio),
							top_frame_z[msg->WaveFrame] - ((top_frame_z[msg->WaveFrame] - bottom_frame_z[msg->WaveFrame]) * msg->WaveFrameRatio));
	
						break;
					case MSG_WIPE_OUT:
						MessageBox("Wipe Out","Network!");
						break;
					case MSG_HANGING_OUT:
						MessageBox("Hanging Out","Network!");
						break;
//					default:
//						MessageBox("Weird Message","Network!");
					}
                }
				else
				{

                // Error condition of some kind - we just stop
                // checking for now
					if (LastError != DPERR_NOMESSAGES)
					    if (bShowErrors) MessageBox(MyErrorToString(LastError), "Network receive error.");
					last_frame = current_frame;
	                return;
		        }
			}
	    }
	}
	*/
	last_frame = current_frame;
}

// Routine to update the surfer with a position buffer...

void CsurfView::UpdateCamera()
{
#define CAMAX_X_BUF 500
#define CAMAX_Y_BUF 100
#define CAMAX_Z_BUF 350
#define CAMIN_X_BUF -350
#define CAMIN_Y_BUF -200
#define CAMIN_Z_BUF 50
	int i;
	static D3DVECTOR last_camera;

//	HRESULT LastError;

	//re-centre the camera after drop in.

	if ((cam_min_x < 0) && (surfer_velocity >= surfer_speed))
	{
		cam_min_x += 5;
		if (cam_min_x > 0)
			cam_min_x = 0;
	}

	if ((cam_min_x > 0) && (surfer_velocity >= surfer_speed))
	{
		cam_min_x -= 5;
		if (cam_min_x < 0)
			cam_min_x = 0;
	}

	D3DVECTOR buffer;
	// scroll the buffer

	for (i = 0; i <= MAXCAMBUFFER-1; i++)
		camera_buffer[i] = camera_buffer[i+1];

	// set up the frame-delay for each axis dependant on the
	// surfer's speed

	int xbuf = (int)(surfer_velocity/5);
	if (xbuf < 0)
		xbuf = 0;
	if (xbuf > MAXCAMBUFFER)
		xbuf = MAXCAMBUFFER;

	int ybuf = (int)(surfer_velocity/2);
	if (ybuf < 0)
		ybuf = 0;
	if (ybuf > MAXCAMBUFFER)
		ybuf = MAXCAMBUFFER;

	int zbuf = (int)(surfer_velocity/3);
	if (zbuf < 0)
		zbuf = 0;
	if (zbuf > MAXCAMBUFFER)
		zbuf = MAXCAMBUFFER;
	
	// get the most recent frame into the buffer

	surfer[current_surfer]->GetPosition(m_scene, &camera_buffer[MAXCAMBUFFER]);

	// now for the real fun stuff
	
	// ensure that the camera does not get too crazy

	buffer.x = camera_buffer[xbuf].x + cam_min_x;
	buffer.y = camera_buffer[ybuf].y + cam_min_y;
	buffer.z = camera_buffer[zbuf].z - cam_min_z;// this will change
													// when the tube is 
													// implemented.
	// check for camera lunacy

	if (buffer.y > frame_y[1])
	{
//		MessageBox("y buffer ++ oveDirect3DRMoad","camera freakout");
		buffer.y = frame_y[1];
	}
	else if ((camera_buffer[MAXCAMBUFFER].y - buffer.y) > CAMAX_Y_BUF)
	{
//		MessageBox("y buffer + oveDirect3DRMoad","camera freakout");
		buffer.y = camera_buffer[MAXCAMBUFFER].y - CAMAX_Y_BUF;
	}
	else if ((camera_buffer[MAXCAMBUFFER].y - buffer.y) < CAMIN_Y_BUF)
	{
//		MessageBox("y buffer - oveDirect3DRMoad","camera freakout");
		buffer.y = camera_buffer[MAXCAMBUFFER].y - CAMIN_Y_BUF;
	}

	if ((camera_buffer[MAXCAMBUFFER].z - buffer.z) > CAMAX_Z_BUF)
	{
//		MessageBox("z buffer + oveDirect3DRMoad","camera freakout");
		buffer.z = camera_buffer[MAXCAMBUFFER].z - CAMAX_Z_BUF;
	}
	else if ((camera_buffer[MAXCAMBUFFER].z - buffer.z) < CAMIN_Z_BUF)
	{
//		MessageBox("z buffer - oveDirect3DRMoad","camera freakout");
		buffer.z = camera_buffer[MAXCAMBUFFER].z - CAMIN_Z_BUF;
	}
	// update the camera's position and angle
	if (camera_type == HELICOPTER_CAMERA)
		buffer.y += 200;
	else if (camera_type == TUBE_CAMERA)
	{
		buffer.y = frame_y[LIP_FRAME+1];
		buffer.z = frame_z[LIP_FRAME+3];
	}
	else if (camera_type == BEACH_CAMERA)
	{
		buffer.y = frame_y[LIP_FRAME];
		buffer.z = frame_z[LIP_FRAME]-300;
	}
	else if (camera_type == BEACH_CAMERA2)
	{
		buffer.y = frame_y[LIP_FRAME];
		buffer.z = frame_z[LIP_FRAME]-700;
	}
	else if (camera_type == SATELLITE_CAMERA)
	{
		buffer.y = (const float)500;
		buffer.z = (const float)0;
	}
	else if (camera_type == ROCK_VIDEO_CAMERA)
	{
		buffer.y = camera_buffer[ybuf].y + 20;
		buffer.z = camera_buffer[MAXCAMBUFFER].z - 60;
	}
	for (i = LIP_FRAME-1; i < MAXWAVEFRAME+1; i++)
	{
		if ((buffer.y <= frame_y[i+1]) && 
			(buffer.z >= frame_z[i+1]))
		{
			buffer.z = last_camera.z;
			buffer.y = last_camera.y;
			i = MAXWAVEFRAME+1;
		}
		while ((buffer.y <= frame_y[i+1]) && 
			(buffer.z >= frame_z[i+1]))
		{
			buffer.z--;
			buffer.y++;
		}
	}
	if (buffer.y < frame_y[MAXWAVEFRAME-2]+1)
		buffer.y = frame_y[MAXWAVEFRAME-2]+1;
	if (game_time > 1200)
	{
		buffer.y += 160;
	}
	else if (game_time > 1160)
	{
		buffer.y += 4*(game_time - 1160);
	}
	tempCameraX = (long)buffer.x;

	m_camera->SetPosition(m_scene, buffer.x, buffer.y, buffer.z);
	m_camera->LookAt(surfer[current_surfer], m_scene, D3DRMCONSTRAIN_Z);
	last_camera = buffer;
	
	// adjust sky proper
	if (bSky)
	{
		D3DVECTOR garbage;
		m_camera->GetOrientation(m_scene, &buffer, &garbage);
		skysource.top = (long)((-buffer.y*128)+128);
		if (skysource.top < 0)
			skysource.top = 0;
		else if (skysource.top > 256)
			skysource.top = 256;
		skysource.left = (long)(buffer.x*80+80);
		if (skysource.left < 0)
			skysource.left = 0;
		else if (skysource.left > 160)
			skysource.left = 160;
		skysource.bottom = skysource.top+255;
		skysource.right = skysource.left+160;
	}
}

void CsurfView::RestartSurfer()
{
	D3DVECTOR buffer;	
	int i;
	// reset velocity, rotation, wipeout flag, last_frame, rotation,
	// orientation, position, and whatnot
	DolphinSplash = 11;
	bOverPier = FALSE;
	bOverBreak = FALSE;
	bOverOilRig = FALSE;
	num_change = 0;		
	bNoCollideCheck = TRUE;
	gameovert = 0;
	change_frame[0] = MAXWAVEFRAME-1;
	change_frame[1] = MAXWAVEFRAME-1;
	surfer_velocity = (const float)0;
	bWipeout = FALSE;
	bSplat = FALSE;
	splat_time = 0;
	last_frame = MAXWAVEFRAME-1;
	current_frame = MAXWAVEFRAME-1;
	cam_min_x = randInt(-300,300);
	bNotDroppedInYet = TRUE;
	bSharkAttack = FALSE;
	sharktime = 0;
	animate_time = (const float)0;
	surf_animate[current_surfer]->SetTime(animate_time);
	ritebouy->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
	leftbouy->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), D3DVALUE(0));
	ritebouy->SetOrientation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
	leftbouy->SetOrientation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
	if (!bPractice || bContest)
	{
		barrel->SetPosition(m_scene, D3DVALUE(randInt(-BOUNDARY/5, BOUNDARY/5)), frame_y[MAXWAVEFRAME+1], D3DVALUE(randInt(-800,-200)));
		barrel->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(OBSTACLE_SPEED), NULL);
		barrel->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(0.1));
		barrel->SetOrientation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
		rock->SetPosition(m_scene, D3DVALUE(randInt(-BOUNDARY/5, BOUNDARY/5)), frame_y[MAXWAVEFRAME+1], D3DVALUE(randInt(-800,-200)));
		rock->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(PIER_SPEED), NULL);
		dolphintime = (const float)11;
	}
	else
	{
		rock->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
		rock->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), NULL);
		dolphin->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
		dolphin->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), NULL);
		barrel->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
		barrel->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), NULL);
		dolphintime = (const float)0;
	}

	sharkhead->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));

	if (bGore)
	{
		for (i = 0; i < NUMBLOOD; i++)
			blood[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
	}
	lastp = 0;
	rotate_sum = (const float)0;
	trick = 0;
	if (bHorizon)
	{
		beach_frame->SetPosition(m_scene, D3DVALUE(0),D3DVALUE(0),D3DVALUE(0));
		beach_frame->SetVelocity(m_scene, D3DVALUE(0),D3DVALUE(0),D3DVALUE(PIER_SPEED), FALSE);
	}
	if (bSprayOn)
	{
		for (i = 0; i < NUMSPRAY; i++)
		{
			spray[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-10000), D3DVALUE(0));
			spray_used[i] = FALSE;
		}
	}

	// ufo nonsense

	if (randInt(0,20) > 18)//18
	{
		bUfo = FALSE;
		OnUfo();
	}
	else if (bUfo)
	{
		OnUfo();
	}

	surfer[current_surfer]->SetRotation(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0));
	surfer[current_surfer]->SetVelocity(m_scene, D3DVALUE(0.0), D3DVALUE(0.0), D3DVALUE(0.0), FALSE);
	surfer[current_surfer]->SetOrientation(m_scene, D3DVALUE(1.0), D3DVALUE(0.0), D3DVALUE(0.0), frame_orient[MAXWAVEFRAME-1].x, frame_orient[MAXWAVEFRAME-1].y, frame_orient[MAXWAVEFRAME-1].z);
	surfer[current_surfer]->SetPosition(m_scene, surferstartpos_x, frame_y[MAXWAVEFRAME-1], frame_z[MAXWAVEFRAME-1]);
	surfer[current_surfer]->GetPosition(m_scene, &buffer);

	// reset camera buffer

	int dx = randInt(-30,30);
	int dy = randInt(2,62);
	int dz = randInt(20,100);

	for (i = 0; i <= MAXCAMBUFFER; i++)
	{
		camera_buffer[i].x = buffer.x + ((MAXCAMBUFFER-i)*dx);
		camera_buffer[i].y = buffer.y + ((MAXCAMBUFFER-i)*dy);
		camera_buffer[i].z = buffer.z - ((MAXCAMBUFFER-i)*dz);
	}
}


void CsurfView::WipeOut()
{
	surfer_velocity = (const float)0;
	D3DVECTOR sbuffer;
	surfer[current_surfer]->GetPosition(m_scene, &sbuffer);
	if ((sbuffer.x > curlpos_x-400) && (sbuffer.x < curlpos_x+400))
	{
		if (curlpos_x < -BOUNDARY+800)
			sbuffer.x = curlpos_x+400;
		else if (curlpos_x > BOUNDARY-800)
			sbuffer.x = curlpos_x-400;
		else if (sbuffer.x > curlpos_x)
			sbuffer.x = curlpos_x+400;
		else
			sbuffer.x = curlpos_x-400;
	}
	if (sbuffer.x < -BOUNDARY+400)
		surferstartpos_x = (const float)-BOUNDARY+400;
	else if (sbuffer.x > BOUNDARY-400)
		surferstartpos_x = (const float)BOUNDARY-400;
	else
		surferstartpos_x = sbuffer.x;

	if (!bContest)
		lives--;
	else if (lives > 0)
	{
		if (score > 250)
			score -= 250;
		else
			score = 0;
	}
	if (lives < 1)
	{
		if (bSoundFx && !bNaration)
			m_pDSBuffer[GAMEOVERS]->Play(0, 0, 0);

		m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(-2), FALSE);

		// get rid of rotation output

		UpdateSpeedometer();

		bGameOver = TRUE;

		// check for hi score

		BOOL hisc = FALSE;
		int i,j;

		if (!bContest)
		{
			for (i = 5; i >= 0; i--)
			{
				if (score > hiscore[i])
				{
					scorenum = i;
					hisc = TRUE;
	
					if (i < 5)
					{
						hiscore[i+1] = hiscore[i];
						hisurfer[i+1] = hisurfer[i];
						for (j = 0; j < 8; j++)
						{
							hiname[i+1][j] = hiname[i][j];
						}
					}
				}
			}
			if (hisc)
			{
				hiscore[scorenum] = score;
				hisurfer[scorenum] = current_surfer;
	
				letnum = 0;
				bHiscore = TRUE;
			}
		}

		if (bMIDIMusic)
		{
			bMIDIMusic = FALSE;
			OnMidiMusic();
		}
		if (bCDMusic)
		{
			playCDTrack(10);
		}
	}
	else
	{
		RestartSurfer();
	}
}

void CsurfView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	static char buffer_text[10] = "HolYhEck!";
	static int secret_track = 22;

	if (bHiscore)
	{
		if (nChar == 0x08) // backspace
		{
			if (letnum > 0)
			{
				letnum--;
			}
		}
		else if (bCharselect)
		{
			if (nChar == 0x0d) // enter
			{
				if (letnum < 8)
				{
					for(letnum; letnum < 8; letnum++)
					{
						hinamec[scorenum][letnum] = (const char)0x00;//(const char)0x20;//space
					}
				}
				hinamec[scorenum][letnum] = (const char)0x00; //eostring

 				bHiscore = FALSE;
				bGameOver = FALSE;
				m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			}
			else if (letnum < 8)
			{
				for (int i = 0; i < NUM_LETTERS; i++)
				{
					if ((char)nChar == letters[i])
					{
						hinamec[scorenum][letnum] = letters[i];	

						i = 255;
						letnum++;
					}
				}
			}
		}
		else
		{
			if (nChar == 0x0d) // enter
			{
				if (letnum < 8)
				{
					for(letnum; letnum < 8; letnum++)
					{
						hiname[scorenum][letnum] = (const char)0x00;//(const char)0x20;//space
					}
				}
				hiname[scorenum][letnum] = (const char)0x00; //eostring

 				bHiscore = FALSE;
				bGameOver = FALSE;
				m_camera->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
				UpdateSpeedometer();
				bCharselect = TRUE;
			}
			else if (letnum < 8)
			{
				for (int i = 0; i < NUM_LETTERS; i++)
				{
					if ((char)nChar == letters[i])
					{
						hiname[scorenum][letnum] = letters[i];	

						i = 255;
						letnum++;
					}
				}
			}
		}
	}
	else if (bConfirmation)
	{
		if (((char)nChar == letters[34]) || 
			((char)nChar == letters[64]))
		{
			ConfirmationResponse = YES_RESPONSE;
		}
		else if (((char)nChar == letters[23]) || 
			((char)nChar == letters[53]))
		{
			ConfirmationResponse = NO_RESPONSE;
		}
	}
	else
	{
		for (int i = 0; i < NUM_LETTERS; i++)
		{
			if ((char)nChar == letters[i])
			{
				for (int j = 0; j < 8; j++)
				{
					buffer_text[j] = buffer_text[j+1];
				}
				buffer_text[8] = letters[i];	
				i = 255;
				if (!lstrcmpi(buffer_text, "holyheck!") && !bFullscreen)
				{
					if (bCDMusic && !bSecretTrack)
					{
						secret_track++;
						if (secret_track > 22)
							secret_track = 17;
						playCDTrack(secret_track);
						bSecretTrack = TRUE;
					}
					CLeroy Leroy;
					if (bCDMusic)
						Leroy.current_track = lastCDtrack;
					else
						Leroy.current_track = secret_track;

					Leroy.bNavigation = !bNormalNavigation;
					Leroy.bCheatKeys = bCheatKeys;
					Leroy.bTron = bTron;
					Leroy.bUfo = bUfo;
					Leroy.DoModal();
					if (Leroy.bOk)
					{
						if (bNormalNavigation = !Leroy.bNavigation)
							bFirstSelect = TRUE;
						bCheatKeys = Leroy.bCheatKeys;
						if (bUfo != Leroy.bUfo)
							OnUfo();
						if (bTron != Leroy.bTron)
							OnTronmode();
						if (Leroy.bLives)
							lives++;
						if (Leroy.bTime && (current_surfer != NO_ONE))
							bInContest[current_surfer] = TRUE;
						if (Leroy.bScore)
							score+=10000;
					}
					if (Leroy.bTrackChange && bCDMusic)
					{
						bSecretTrack = FALSE;
						bMusicRedundancyCheck = FALSE;
						playCDTrack(Leroy.current_track);
						bMusicRedundancyCheck = TRUE;
						bSecretTrack = TRUE;
					}

					delete Leroy;
				}
			}
		}
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CsurfView diagnostics

#ifdef _DEBUG
void CsurfView::AssertValid() const
{
	CView::AssertValid();
}

void CsurfView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsurfDoc* CsurfView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsurfDoc)));
	return (CsurfDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CsurfView message handlers


char* LSTRRCHR( const char* lpString, int bChar )
{
    if( lpString  )
    {
        const char*     lpBegin;

        lpBegin = lpString;

        while( *lpString != 0 )
        {
            lpString++;
        }

        while( 1 )
        {
            if( *lpString == bChar )
            {
                return (char*)lpString;
            }
            
            if( lpString == lpBegin )
            {
                break;
            }

            lpString--;
        }
    }
    return NULL;
} 

BOOL WINAPI EnumDirectDraw(GUID FAR * lpGUID,
    LPSTR lpDriverDescription, LPSTR lpDriverName,
    LPVOID lpContext)
{
	CsurfView * view = (CsurfView *)lpContext;
	return view->EnumDDCallFront(lpGUID, lpDriverName);
}

HRESULT CsurfView::EnumDDCallFront(LPGUID lpGuid, LPSTR lpDeviceName)
{
	int i;
#ifdef NO_VOODOO
	if (lpGuid != NULL)
	{
		return DDENUMRET_OK;
	}
#else
	if (DirectDrawCreate(lpGuid, &lpDD, NULL) != DD_OK)
	{
		// failed, so ignore this device
		return DDENUMRET_OK;
	}
#endif
	for (i = 0; i < 32; i++)
	{
		lpDDDeviceName[NumDDDrivers][i] = lpDeviceName[i];
	}
	lpDDDeviceName[NumDDDrivers][31] = 0x00;
	lpDDGuid[NumDDDrivers] = 0;
	if (lpGuid != NULL)
	{
		lpDDGuid[NumDDDrivers] = &DDGuid[NumDDDrivers];
		memcpy(&DDGuid[NumDDDrivers], lpGuid, sizeof(GUID));
	}

//	DDGuid[NumDDDrivers] = *lpGuid;
	NumDDDrivers++;
	if (NumDDDrivers >= MAX_DD_DRIVERS)
	{
	    return D3DENUMRET_CANCEL;
	}
    return D3DENUMRET_OK;
}

/*
 * FindDevice
 * Find a texturing device, preferably hardware, for a particular color model.
 * Also, create the Z-buffer and disable texture maps if not supported.
 */

BOOL CsurfView::SetUpDrivers()
{
#ifndef NO_VOODOO
	BOOL LastError;
#endif
    LPDIRECT3D lpD3D;
	for (int i = 0; i < NumDDDrivers; i++)
	{
		CurrentDDDriver = i;
//		lpDD->Release();
#ifndef NO_VOODOO
	    LastError = DirectDrawCreate(lpDDGuid[CurrentDDDriver], &lpDD, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "DirectDrawCreate failed.");
	        return FALSE;
	    }
#endif
		if (lpDD->QueryInterface(IID_IDirect3D, (void**) &lpD3D)) 
		{
//		    lpDD->Release();
			return FALSE;
	    }
		lpD3D->EnumDevices(Enum3DDrivers, this);
	}
	if ((D3DDriver >= NumD3DDrivers) || (lpDDGuid[DDDriverNum[D3DDriver]] != NULL))
		D3DDriver = 0;
	LastD3DDriver = D3DDriver;
//	lpDD->Release();
	CurrentDDDriver = DDDriverNum[D3DDriver];
	LastDDDriver = CurrentDDDriver;
#ifndef NO_VOODOO
    LastError = DirectDrawCreate(lpDDGuid[CurrentDDDriver], &lpDD, NULL);
    if (LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "DirectDrawCreate failed.");
        return FALSE;
    }
#endif
	return TRUE;
}

HRESULT CsurfView::FindDevice(LPDIRECTDRAWSURFACE lpSurface)
{
	int i;
    HRESULT LastError = m_lprm->CreateDeviceFromSurface(lpD3DGuid[D3DDriver], lpDD, lpSurface, &m_lpDev);
	if (LastError != DD_OK)
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Init Driver failed, reverting to other.");

		i = 0;
loop_here:
		D3DDriver++;
		if (D3DDriver >= NumD3DDrivers)
			D3DDriver = 0;
	    LastError = m_lprm->CreateDeviceFromSurface(lpD3DGuid[D3DDriver], lpDD, lpSurface, &m_lpDev);
		if (LastError != DD_OK)
		{
			i++;
			if (i < NumD3DDrivers)
				goto loop_here;
		}
		for (i = 0; i < NumD3DDrivers; i++)
		{
			::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_DRIVERS), ID_DRIVER0+i, MF_BYCOMMAND | MF_UNCHECKED);
		}
		::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_DRIVERS), ID_DRIVER0+D3DDriver, MF_BYCOMMAND | MF_CHECKED);
	}
	return LastError;
}

static HRESULT CALLBACK Enum3DDrivers (LPGUID lpGuid, LPSTR lpDeviceDescription,
			LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc,
			LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpUserArg)
{
    LPD3DDEVICEDESC lpDesc;
	BOOL Hardware;
    /*
     * Decide which device description we should consult
     */
	if (lpD3DHWDeviceDesc->dcmColorModel)
	{
	    lpDesc = lpD3DHWDeviceDesc;
		Hardware = TRUE;
	}
	else
	{
	    lpDesc = lpD3DHELDeviceDesc;
		Hardware = FALSE;
	}

    if ((lpDesc->dwDeviceRenderBitDepth & DDBD_16) != DDBD_16)
	{
	    return D3DENUMRET_OK;
	}
	CsurfView * view = (CsurfView *)lpUserArg;
	return view->Enum3DCallFront(lpGuid, lpDeviceName, lpDesc, Hardware);
}

HRESULT CsurfView::Enum3DCallFront(LPGUID lpGuid, LPSTR lpDeviceName, LPD3DDEVICEDESC lpDesc, BOOL Hardware)
{
	char ach[66];
	int i;
	if ((lpDDGuid[CurrentDDDriver] != NULL) && (!Hardware))
	    return D3DENUMRET_OK;

	for (i = 0; i < 32; i++)
	{
		lpD3DDeviceName[NumD3DDrivers][i] = lpDeviceName[i];
	}
	lpD3DDeviceName[NumD3DDrivers][31] = 0x00;
	lpD3DGuid[NumD3DDrivers] = 0;
	if (lpGuid != NULL)
	{
		lpD3DGuid[NumD3DDrivers] = &D3DGuid[NumD3DDrivers];
		memcpy(lpD3DGuid[NumD3DDrivers], lpGuid, sizeof(GUID));
	}
	lpD3DDesc[NumD3DDrivers] = 0;
	if (lpDesc != NULL)
	{
		lpD3DDesc[NumD3DDrivers] = &D3DDesc[NumD3DDrivers];
		memcpy(lpD3DDesc[NumD3DDrivers], lpDesc, sizeof(D3DDEVICEDESC));
	}
//	D3DGuid[NumD3DDrivers] = *lpGuid;
//	D3DDesc[NumD3DDrivers] = *lpDesc;
	bHardwareAccel[NumD3DDrivers] = Hardware;
	DDDriverNum[NumD3DDrivers] = CurrentDDDriver;
	wsprintf(ach,"%s-%s", lpDDDeviceName[CurrentDDDriver], lpD3DDeviceName[NumD3DDrivers]);
	::AppendMenu(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), MENU_DRIVERS),MF_STRING, ID_DRIVER0+NumD3DDrivers, ach);
	NumD3DDrivers++;
	if (NumD3DDrivers >= MAX_3D_DRIVERS)
	{
	    return D3DENUMRET_CANCEL;
	}
    return D3DENUMRET_OK;
}

BOOL CsurfView::CreateDevice()
{
    int bpp, i;
    HDC hdc;
	HRESULT LastError;
    DDSURFACEDESC ddsd;
	ModeAx = GetPrivateProfileInt("ScreenMode","ClientX1",120,"wildride.ini");
	ModeAy = GetPrivateProfileInt("ScreenMode","ClientY1",104,"wildride.ini");
	ModeBx = GetPrivateProfileInt("ScreenMode","ClientX2",520,"wildride.ini");
	ModeBy = GetPrivateProfileInt("ScreenMode","ClientY2",360,"wildride.ini");
	ModeCx = ModeBx - ModeAx;
	ModeCy = ModeBy - ModeAy;
	if (ModeCx/2 != (int)((float)ModeCx/2+0.5))
	{
		ModeBx--;
		ModeCx--;
	}
	if (ModeCy/2 != (int)((float)ModeCy/2+0.5))
	{
		ModeBy--;
		ModeCy--;
	}
    
    LastError = lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
    if( LastError != DD_OK )
    {
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Set Cooperation Level failed.");
        return FALSE;
    }

	::SetWindowLong(m_hWnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
	::SetForegroundWindow(m_hWnd);
	::SetWindowPos(::GetParent(m_hWnd), 
		HWND_TOP, 
		GetPrivateProfileInt("ScreenMode","WindowXPos",114,"wildride.ini"), 
		GetPrivateProfileInt("ScreenMode","WindowYPos",56,"wildride.ini"), 
		GetPrivateProfileInt("ScreenMode","WindowWidth",414,"wildride.ini"), 
		GetPrivateProfileInt("ScreenMode","WindowHeight",310,"wildride.ini"), 
		NULL);

	if (!bFullscreen)
		while (ShowCursor(TRUE) < 0);

	// set up the menu

	for (i = 0; i < NumModes; i++)
	{
		::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_FULLSCREEN), ID_FULLSCREEN0+i, MF_BYCOMMAND | MF_UNCHECKED);
	}
	for (i = 0; i < NumD3DDrivers; i++)
	{
		::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_DRIVERS), ID_DRIVER0+i, MF_BYCOMMAND | MF_UNCHECKED);
	}
	::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_FULLSCREEN), ID_FULLSCREEN0+ModeNumber, MF_BYCOMMAND | MF_CHECKED);
	::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_DRIVERS), ID_DRIVER0+D3DDriver, MF_BYCOMMAND | MF_CHECKED);
	if (TextureFiltering == D3DRMTEXTURE_LINEAR)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_TEXTURE_FILTER, MF_BYCOMMAND | MF_CHECKED);
	else
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_TEXTURE_FILTER, MF_BYCOMMAND | MF_UNCHECKED);
	if (bSprayOn)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SPRAY, MF_BYCOMMAND | MF_CHECKED);
	if (bPractice)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_PRACTICE, MF_BYCOMMAND | MF_CHECKED);
	if (bWaveTextures)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_WAVE_TEXTURES, MF_BYCOMMAND | MF_CHECKED);
	if (bBreakingWave)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_BREAKINGWAVE, MF_BYCOMMAND | MF_CHECKED);
	if (bFoam)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_FOAM, MF_BYCOMMAND | MF_CHECKED);
	if (bGore)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_GORE, MF_BYCOMMAND | MF_CHECKED);
	if (bHalfres)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_HALFRES, MF_BYCOMMAND | MF_CHECKED);
	if (bSky)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SKYMAP, MF_BYCOMMAND | MF_CHECKED);
	if (bHorizon)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_HORIZON, MF_BYCOMMAND | MF_CHECKED);
	if (bSpeedofish)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SPEEDOMETER_TOGGLE, MF_BYCOMMAND | MF_CHECKED);
	if (bScoreBlit)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SCORETOGGLE, MF_BYCOMMAND | MF_CHECKED);
	if (bMIDIMusic)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_MIDI_MUSIC, MF_BYCOMMAND | MF_CHECKED);
	if (bShowErrors)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_FILE), ID_SHOW_ERRORS, MF_BYCOMMAND | MF_CHECKED);
	if (bCDMusic)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_CD_MUSIC, MF_BYCOMMAND | MF_CHECKED);
	if (bSoundFx)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_SOUND_FX, MF_BYCOMMAND | MF_CHECKED);
	if (bNaration)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_NARATION, MF_BYCOMMAND | MF_CHECKED);
	if (bSurferSounds)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_SURFER_SOUNDS, MF_BYCOMMAND | MF_CHECKED);
	if (bFps)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_FPS, MF_BYCOMMAND | MF_CHECKED);
	if (bAutoCamera)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_AUTO_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	switch (camera_type)
	{
	case MAIN_CAMERA:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_MAIN_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		break;
	case HELICOPTER_CAMERA:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_HELICOPTER_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		break;
	case TUBE_CAMERA:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_TUBE_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		break;
	case BEACH_CAMERA:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_BEACH_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		break;
	case BEACH_CAMERA2:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_BEACH_CAMERA2, MF_BYCOMMAND | MF_CHECKED);
		break;
	case SATELLITE_CAMERA:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_SATELLITE_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		break;
	case ROCK_VIDEO_CAMERA:
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_ROCK_VIDEO_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		break;
	}

//	if (!CreateZBuffer(16, DDSCAPS_SYSTEMMEMORY))
//		CleanUpAndExit();

//	Create the primary surface
    ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

    LastError = lpDD->CreateSurface(&ddsd, &lpFrontBuffer, NULL);
    if( LastError != DD_OK )
    {
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Front buffer failed.");
        return FALSE;
    }

	// back buffer
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
	ddsd.dwHeight = ModeCy;
	ddsd.dwWidth = ModeCx;
    if (bOnlySystemMemory)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    LastError = lpDD->CreateSurface(&ddsd, &lpBackBuffer, NULL );
    if(LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Back buffer failed.");
        return FALSE;
    }

	// halfres buffer
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
	ddsd.dwHeight = ModeCy/2;
	ddsd.dwWidth = ModeCx/2;
    if (bOnlySystemMemory)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    LastError = lpDD->CreateSurface(&ddsd, &lpHalfresBuffer, NULL );
    if(LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Halfres buffer failed.");
        return FALSE;
    }

    // create a clipper for the primary surface
    LastError = lpDD->CreateClipper( 0, &lpClipper, NULL );
    if( LastError != DD_OK )
    {
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateClipper for front buffer failed.");
        return FALSE;
    }
    
    LastError = lpClipper->SetHWnd( 0, m_hWnd );
    if( LastError != DD_OK )
    {
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Set hwnd for Clipper failed.");
        return FALSE;
    }

    LastError = lpFrontBuffer->SetClipper( lpClipper );
    if( LastError != DD_OK )
    {
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Set Clipper for front buffer failed.");
        return FALSE;
    }

	if (bHalfres)
	{
	    LastError = FindDevice(lpHalfresBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return FALSE;
		}
	}
	else
	{
	    LastError = FindDevice(lpBackBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return FALSE;
		}
//	    m_lprm->CreateDeviceFromClipper(lpClipper, FindDevice(D3DCOLOR_MONO), r.right, r.bottom, &m_lpDev);
	}

    hdc = ::GetDC(m_hWnd);
    bpp = ::GetDeviceCaps(hdc, BITSPIXEL);
    ::ReleaseDC(m_hWnd, hdc);
    m_lpDev->SetDither(FALSE);
	m_lpDev->SetTextureQuality(TextureFiltering);
	bWrongDisplayMode = FALSE;
    switch (bpp)
    {
    case 16:
        m_lpDev->SetShades(32);
        m_lprm->SetDefaultTextureColors(64);
        m_lprm->SetDefaultTextureShades(32);
        break;
    default:
		bWrongDisplayMode = TRUE;
		return FALSE;
    }
	if (bTron)
	{
		m_lpDev->SetQuality(D3DRMRENDER_WIREFRAME);
	}
	else
	{
		m_lpDev->SetQuality(D3DRMRENDER_GOURAUD);
	}

	if (bCharselect)
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
			INTR_VRIGHT, INTR_VBOTTOM, &m_view);
		m_view->SetBack(D3DVAL(INTR_BACK));
	}
	else
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
			m_lpDev->GetWidth(),
			m_lpDev->GetHeight(), &m_view);
		m_view->SetBack(D3DVAL(GAME_BACK));
	}
	return TRUE;
}

void CsurfView::RestoreSurfaces()
{
	DDCOLORKEY DDColorKey;

    memset(&DDColorKey,0,sizeof(DDCOLORKEY));

	if (lpSkySource)
	{
		if (lpSkySource->IsLost())
		{
			lpSkySource->Release();
			lpSkySource = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_SURFSKY), 0, 0);
		}
	}
	else 
	{
		lpSkySource = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_SURFSKY), 0, 0);
	}

	if (lpSpeedometer)
	{
		if (lpSpeedometer->IsLost())
		{
			lpSpeedometer->Release();
			lpSpeedometer = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_SPINSPEED), 0, 0);
		    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpSpeedometer, RGB(0,0,255));
		    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
			lpSpeedometer->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
		}
	}
	else
	{
		lpSpeedometer = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_SPINSPEED), 0, 0);
	    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpSpeedometer, RGB(0,0,255));
	    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
		lpSpeedometer->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
	}
	if (lpAlphabet)
	{
		if (lpAlphabet->IsLost())
		{
			lpAlphabet->Release();
			lpAlphabet = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_ALPHABET), 0, 0);
		    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpAlphabet, RGB(0,0,255));
		    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
			lpAlphabet->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
		}
	}
	else
	{
		lpAlphabet = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_ALPHABET), 0, 0);
	    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpAlphabet, RGB(0,0,255));
	    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
		lpAlphabet->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
	}

	if (lpNavBar)
	{
		if (lpNavBar->IsLost())
		{
			lpNavBar->Release();
			lpNavBar = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_NAV), 0, 0);
		    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpNavBar, RGB(0,255,0));
		    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
			lpNavBar->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
		}
	}
	else 
	{
		lpNavBar = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_NAV), 0, 0);
	    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpNavBar, RGB(0,255,0));
	    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
		lpNavBar->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
	}

	if (lpLogo)
	{
		if (lpLogo->IsLost())
		{
			lpLogo->Release();
			lpLogo = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_LOGO), 0, 0);
		    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpLogo, RGB(0,255,0));
		    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
			lpLogo->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
		}
	}
	else 
	{
		lpLogo = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_LOGO), 0, 0);
	    DDColorKey.dwColorSpaceLowValue  = DDColorMatch(lpLogo, RGB(0,255,0));
	    DDColorKey.dwColorSpaceHighValue = DDColorKey.dwColorSpaceLowValue;
		lpLogo->SetColorKey(DDCKEY_SRCBLT,&DDColorKey);
	}
	if (lpIntrBkg)
	{
		if (lpIntrBkg->IsLost())
		{
			lpIntrBkg->Release();
			lpIntrBkg = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_INTERFACE), 0, 0);
		}
	}
	else
	{
		lpIntrBkg = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_INTERFACE), 0, 0);
	}

}
void CsurfView::ReleaseSomeStuff()
{
	if (m_view)
	{
		m_view->Release();
		m_view = NULL;
	}
	if ((m_lpDev) && (lpDDGuid[DDDriverNum[D3DDriver]] == NULL))
	{
		m_lpDev->Release();
		m_lpDev=NULL;
	}
	if (lpClipper)
	{
	    lpClipper->Release();
		lpClipper=NULL;
	}
	if (lpHalfresBuffer)
	{
		lpHalfresBuffer->Release();
		lpHalfresBuffer=NULL;
	}
	if (lpZBuffer)
	{
		lpZBuffer->Release();
		lpZBuffer=NULL;
	}
	if (lpBackBuffer)
	{
		lpBackBuffer->Release();
		lpBackBuffer=NULL;
	}
	if (lpFrontBuffer)
	{
		lpFrontBuffer->Release();
		lpFrontBuffer=NULL;
	}
}

BOOL CsurfView::InitAll()
{
	HRESULT LastError;
	static int loading_number = 0;
	int	i;
    LPDIRECT3DRMMESHBUILDER	builder;
	LPDIRECT3DRMTEXTURE		map;
	D3DRMLOADRESOURCE		resourcedata;

	bWrongDisplayMode = FALSE;

	switch (loading_number)
	{
	case 0:
		// seed the random number generator
		srand((unsigned)time(NULL));
		DirectDrawEnumerate(EnumDirectDraw, this);
	    LastError = DirectDrawCreate(NULL, &lpDD, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "DirectDrawCreate failed.");
	        return FALSE;
	    }
        LoadProgress.Text =  "Creating Direct 3d...";
		break;
	case 1:
	    if (FAILED(Direct3DRMCreate(&m_lprm)))
		{
			if (bShowErrors) AfxMessageBox("Create3DRM Failed");
			return FALSE;
		}
		if (!SetUpDrivers())
		{
			if (bShowErrors) MessageBox("Enum D3D Drivers Failed","Bad Things...");
			return FALSE;
		}
		LoadProgress.Text = "Initializing Direct Draw...";
		break;
	case 2:
		if (!DDInit())
		{
			if (bShowErrors) MessageBox("DDInit Failed","Bad Things...");
			return FALSE;
		}
        LoadProgress.Text = "Setting Direct Draw Mode...";
		break;
	case 3:
	    if (!DDSetMode())
		{
			if (bShowErrors) MessageBox("DDSetMode Failed","Bad Things...");
			return FALSE;
		}
        LoadProgress.Text = "Setting Direct 3d Mode...";
		break;
	case 4:
	    if (!D3DRMSetMode())
		{
			if (bShowErrors) MessageBox("D3DRM Set Mode Failed","Bad Things...");
			return FALSE;
		}
        LoadProgress.Text = "Starting Music...";
		break;
	case 5:
		// start playing some muzak
		extraCDsong = 10;
		MidiNum = 0;

		setUpCD();

		if (bCDMusic)
			playCDTrack(0);
		else 
		if (bMIDIMusic)
			MidiMusic[0]->Play(m_hWnd, FALSE);//0
        LoadProgress.Text = "Creating Scene...";
		break;
	case 6:
		// create the scene frame
		RestoreSurfaces();
	    m_lprm->CreateFrame(NULL, &m_scene);
//		m_scene->SetSortMode(D3DRMSORT_BACKTOFRONT);
//		m_scene->SetZbufferMode(D3DRMZBUFFER_ENABLE);
		// set the background colour
		m_scene->SetSceneBackgroundRGB(D3DVALUE(0.539), D3DVALUE(0.434), D3DVALUE(0.966));
		// create the lights
	    m_lprm->CreateFrame(m_scene, &light);
		light->SetPosition(m_scene, D3DVALUE(-50.0), D3DVALUE(-100.0), D3DVALUE(600.0));
		light->SetOrientation(m_scene, D3DVALUE(-0.005), D3DVALUE(-0.8), D3DVALUE(1), D3DVALUE(0.0), D3DVALUE(1.0), D3DVALUE(0.0));
	    m_lprm->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, D3DVALUE(0.7), D3DVALUE(0.7), D3DVALUE(0.7), &light1);
		m_lprm->CreateLightRGB(D3DRMLIGHT_AMBIENT, D3DVALUE(0.3), D3DVALUE(0.3), D3DVALUE(0.33), &light2);
	    light->AddLight(light1);
		light->AddLight(light2);
        LoadProgress.Text = "Building Wave...";
		break;
	case 7:
		// create the wave frame
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";

	    m_lprm->CreateFrame(m_scene, &wave);
	    m_lprm->CreateMeshBuilder(&wave_builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_WAVEX);
		wave_builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE,NULL,NULL);
	    wave_builder->SetPerspective(TRUE);
		wave_builder->CreateMesh(&wave_mesh);
		// load wave textures
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP0), 
			"PPM"), 
			&wave_map[0]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP1), 
			"PPM"), 
			&wave_map[1]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP2), 
			"PPM"), 
			&wave_map[2]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP3), 
			"PPM"), 
			&wave_map[3]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP4), 
			"PPM"), 
			&wave_map[4]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP5), 
			"PPM"), 
			&wave_map[5]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP6), 
			"PPM"), 
			&wave_map[6]);	
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_WAVEMAP7), 
			"PPM"), 
			&wave_map[7]);	
		if (bWaveTextures)
		{
			wave_mesh->SetGroupTexture(D3DRMGROUP_ALLGROUPS, wave_map[0]);
			wave_mesh->SetGroupMapping(D3DRMGROUP_ALLGROUPS, D3DRMMAP_PERSPCORRECT);
		}
		else
			wave_builder->SetColorRGB(D3DVALUE(0.2), D3DVALUE(0.2), D3DVALUE(0.8));

		wave->AddVisual((LPDIRECT3DRMVISUAL) wave_mesh);

		// These are a bunch of frames for orienting the surfer...
		frame_y[0] = DFRAMEY0;
		frame_y[1] = DFRAMEY1;
		frame_y[2] = DFRAMEY2;
		frame_y[3] = DFRAMEY3;
		frame_y[4] = DFRAMEY4;
		frame_y[5] = DFRAMEY5;
		frame_y[6] = DFRAMEY6;
		frame_y[7] = DFRAMEY7;
		frame_y[8] = DFRAMEY8;
		frame_y[9] = DFRAMEY9;
		frame_y[10] = DFRAMEY10;
		frame_y[11] = DFRAMEY11;

		frame_z[0] = DFRAMEZ0;
		frame_z[1] = DFRAMEZ1;
		frame_z[2] = DFRAMEZ2;
		frame_z[3] = DFRAMEZ3;
		frame_z[4] = DFRAMEZ4;
		frame_z[5] = DFRAMEZ5;
		frame_z[6] = DFRAMEZ6;
		frame_z[7] = DFRAMEZ7;
		frame_z[8] = DFRAMEZ8;
		frame_z[9] = DFRAMEZ9;
		frame_z[10] = DFRAMEZ10;
		frame_z[11] = DFRAMEZ11;

		for (i = 0; i < MAXWAVEFRAME+1; i++)
		{
			frame_orient[i].x = (const float)0;
			frame_orient[i].y = (frame_z[i] - frame_z[i+1]);
			frame_orient[i].z = -(frame_y[i] - frame_y[i+1]);
		}

		// set some of the global variables for the characters.  
		// their attributes were determined using the following rules:
		// 30 points to distribute, 5 is average.  specialties cost
		// 1 point.

		stat_turn[ALANA] = 6;
		stat_speed[ALANA] = 6;
		stat_max[ALANA] = 7;
		stat_land[ALANA] = 5;

		stat_turn[BUCKY] = 7;
		stat_speed[BUCKY] = 7;
		stat_max[BUCKY] = 7;
		stat_land[BUCKY] = 6;
		
		stat_turn[LEE] = 5;
		stat_speed[LEE] = 5;
		stat_max[LEE] = 9;
		stat_land[LEE] = 3;

		stat_turn[SANDY] = 7;
		stat_speed[SANDY] = 5;
		stat_max[SANDY] = 6;
		stat_land[SANDY] = 6;

		stat_turn[TODD] = 5;
		stat_speed[TODD] = 6;//4 e3 cheat
		stat_max[TODD] = 7;//5
		stat_land[TODD] = 9;

		stat_turn[VIC] = 6;
		stat_speed[VIC] = 6;//5
		stat_max[VIC] = 7;
		stat_land[VIC] = 6;

        LoadProgress.Text = "Building Alana...";
		break;
	case 8:
	// load alana
#ifndef NO_SURFERS
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &surfer[ALANA]);
		m_lprm->CreateAnimationSet(&surf_animate[ALANA]);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_ALANAX);
		surf_animate[ALANA]->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, surfer[ALANA]);
		surf_animate[ALANA]->SetTime((const float)50);
#endif
        LoadProgress.Text = "Building Bucky...";
		break;
	case 9:
	// load bucky
#ifndef SHAREWARE
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &surfer[BUCKY]);
		m_lprm->CreateAnimationSet(&surf_animate[BUCKY]);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_BUCKYX);
		surf_animate[BUCKY]->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, surfer[BUCKY]);
		surf_animate[BUCKY]->SetTime((const float)50);
#endif
        LoadProgress.Text = "Building Lee...";
		break;
	case 10:
	// load lee
#ifndef NO_SURFERS
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &surfer[LEE]);
		m_lprm->CreateAnimationSet(&surf_animate[LEE]);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_LEEX);
		surf_animate[LEE]->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, surfer[LEE]);
		surf_animate[LEE]->SetTime((const float)50);
#endif
        LoadProgress.Text = "Building Sandy...";
		break;
	case 11:
	// load sandy
#ifndef NO_SURFERS
#ifndef SHAREWARE
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &surfer[SANDY]);
		m_lprm->CreateAnimationSet(&surf_animate[SANDY]);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_SANDYX);
		surf_animate[SANDY]->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, surfer[SANDY]);
		surf_animate[SANDY]->SetTime((const float)50);
#endif
#endif
        LoadProgress.Text = "Building Todd...";
		break;
	case 12:
	// load todd
#ifndef NO_SURFERS
#ifndef SHAREWARE
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &surfer[TODD]);
		m_lprm->CreateAnimationSet(&surf_animate[TODD]);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_TODDX);
		surf_animate[TODD]->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, surfer[TODD]);
		surf_animate[TODD]->SetTime((const float)50);
#endif
#endif
        LoadProgress.Text = "Building Vic...";
		break;
	case 13:
	// load vic
#ifndef NO_SURFERS
#ifndef SHAREWARE
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &surfer[VIC]);
		m_lprm->CreateAnimationSet(&surf_animate[VIC]);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_VICX);
		surf_animate[VIC]->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, surfer[VIC]);
		surf_animate[VIC]->SetTime((const float)50);
#endif
#endif
        LoadProgress.Text = "Building Wave Break...";
		break;
	case 14:
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &child_of_the_wave);
		m_scene->DeleteChild(child_of_the_wave);
		// load in the curl
		m_lprm->CreateFrame(m_scene, &curl_frame);
		m_lprm->CreateMeshBuilder(&curlr_builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_CURLX);
		curlr_builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, NULL, NULL);
		curlr_builder->SetPerspective(TRUE);
		curlr_builder->CreateMesh(&curlr_mesh);
		if (bWaveTextures)
		{
			curlr_mesh->SetGroupTexture(D3DRMGROUP_ALLGROUPS, wave_map[0]);
			curlr_mesh->SetGroupMapping(D3DRMGROUP_ALLGROUPS, D3DRMMAP_PERSPCORRECT);
		}
		else
		{
			curlr_builder->SetColorRGB(D3DVALUE(0.2), D3DVALUE(0.2), D3DVALUE(0.8));
		}
		curl_frame->AddVisual((LPDIRECT3DRMVISUAL) curlr_mesh);
        LoadProgress.Text = "Loading Spray...";
		break;
	case 15:
		// load in the spray
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP0), 
			"PPM"), 
			&lpSprayMap[0]);
		m_lprm->CreateFrame(m_scene, &spray[0]);
		lpSprayMap[0]->SetDecalOrigin(32,32);
		spray_size[0] = D3DVALUE(20);
		lpSprayMap[0]->SetDecalSize(D3DVALUE(20),D3DVALUE(20));
		lpSprayMap[0]->SetDecalTransparency(TRUE);
		lpSprayMap[0]->SetDecalTransparentColor(0);
		spray[0]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[0]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP1), 
			"PPM"), 
			&lpSprayMap[1]);
		m_lprm->CreateFrame(m_scene, &spray[1]);
		lpSprayMap[1]->SetDecalOrigin(32,32);
		spray_size[1] = D3DVALUE(30);
		lpSprayMap[1]->SetDecalSize(D3DVALUE(30),D3DVALUE(30));
		lpSprayMap[1]->SetDecalTransparency(TRUE);
		lpSprayMap[1]->SetDecalTransparentColor(0);
		spray[1]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[1]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP2), 
			"PPM"), 
			&lpSprayMap[2]);
		m_lprm->CreateFrame(m_scene, &spray[2]);
		lpSprayMap[2]->SetDecalOrigin(32,32);
		spray_size[2] = D3DVALUE(40);
		lpSprayMap[2]->SetDecalSize(D3DVALUE(40),D3DVALUE(40));
		lpSprayMap[2]->SetDecalTransparency(TRUE);
		lpSprayMap[2]->SetDecalTransparentColor(0);
		spray[2]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[2]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP3), 
			"PPM"), 
			&lpSprayMap[3]);
		m_lprm->CreateFrame(m_scene, &spray[3]);
		lpSprayMap[3]->SetDecalOrigin(32,32);
		spray_size[3] = D3DVALUE(60);
		lpSprayMap[3]->SetDecalSize(D3DVALUE(60),D3DVALUE(60));
		lpSprayMap[3]->SetDecalTransparency(TRUE);
		lpSprayMap[3]->SetDecalTransparentColor(0);
		spray[3]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[3]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP4), 
			"PPM"), 
			&lpSprayMap[4]);
		m_lprm->CreateFrame(m_scene, &spray[4]);
		lpSprayMap[4]->SetDecalOrigin(32,32);
		spray_size[4] = D3DVALUE(80);
		lpSprayMap[4]->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		lpSprayMap[4]->SetDecalTransparency(TRUE);
		lpSprayMap[4]->SetDecalTransparentColor(0);
		spray[4]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[4]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP5), 
			"PPM"), 
			&lpSprayMap[5]);
		m_lprm->CreateFrame(m_scene, &spray[5]);
		lpSprayMap[5]->SetDecalOrigin(32,32);
		spray_size[5] = D3DVALUE(100);
		lpSprayMap[5]->SetDecalSize(D3DVALUE(100),D3DVALUE(100));
		lpSprayMap[5]->SetDecalTransparency(TRUE);
		lpSprayMap[5]->SetDecalTransparentColor(0);
		spray[5]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[5]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP6), 
			"PPM"), 
			&lpSprayMap[6]);
		m_lprm->CreateFrame(m_scene, &spray[6]);
		lpSprayMap[6]->SetDecalOrigin(32,32);
		spray_size[6] = D3DVALUE(120);
		lpSprayMap[6]->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		lpSprayMap[6]->SetDecalTransparency(TRUE);
		lpSprayMap[6]->SetDecalTransparentColor(0);
		spray[6]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[6]);

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_SPRAYMAP7), 
			"PPM"), 
			&lpSprayMap[7]);
		m_lprm->CreateFrame(m_scene, &spray[7]);
		lpSprayMap[7]->SetDecalOrigin(32,32);
		spray_size[7] = D3DVALUE(140);
		lpSprayMap[7]->SetDecalSize(D3DVALUE(140),D3DVALUE(140));
		lpSprayMap[7]->SetDecalTransparency(TRUE);
		lpSprayMap[7]->SetDecalTransparentColor(0);
		spray[7]->AddVisual((LPDIRECT3DRMVISUAL) lpSprayMap[7]);
        LoadProgress.Text = "Loading Gore...";
		break;
	case 16:
		// load the blood
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_BLOODMAP0), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &blood[0]);
		map->SetDecalOrigin(32,63);
		map->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		blood[0]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_BLOODMAP1), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &blood[1]);
		map->SetDecalOrigin(32,63);
		map->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		blood[1]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_BLOODMAP2), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &blood[2]);
		map->SetDecalOrigin(32,63);
		map->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		blood[2]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_BLOODMAP3), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &blood[3]);
		map->SetDecalOrigin(32,63);
		map->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		blood[3]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_BLOODMAP4), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &blood[4]);
		map->SetDecalOrigin(32,63);
		map->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		blood[4]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_BLOODMAP5), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &blood[5]);
		map->SetDecalOrigin(32,63);
		map->SetDecalSize(D3DVALUE(80),D3DVALUE(80));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		blood[5]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();
        LoadProgress.Text = "Loading Foam...";
		break;
	case 17:
		// load in the foam
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP0), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[0]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[0]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP1), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[1]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[1]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP2), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[2]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[2]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP3), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[3]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[3]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP4), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[4]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[4]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP5), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[5]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[5]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP6), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[6]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[6]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();

		m_lprm->LoadTextureFromResource(
			FindResource(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_FOAMMAP7), 
			"PPM"), 
			&map);
		m_lprm->CreateFrame(m_scene, &foam[7]);
		map->SetDecalOrigin(32,42);
		map->SetDecalSize(D3DVALUE(120),D3DVALUE(120));
		map->SetDecalTransparency(TRUE);
		map->SetDecalTransparentColor(0);
		foam[7]->AddVisual((LPDIRECT3DRMVISUAL) map);
		map->Release();
        LoadProgress.Text = "Building Medical Waste...";
		break;
	case 18:
  		// load the barrel
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &barrel);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_BARRELX);
		m_lprm->CreateAnimationSet(&barrel_animate);
		barrel_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, barrel);
        LoadProgress.Text = "Building Dolphin...";
		break;
	case 19:
		// load the dolphin
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &dolphin);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_DOLPHINX);
		m_lprm->CreateAnimationSet(&dolphin_animate);
		dolphin_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, dolphin);
        LoadProgress.Text = "Building Pier...";
		break;
	case 20:
		// load the pier
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &pier);
		m_lprm->CreateMeshBuilder(&builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_PIERX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetPerspective(TRUE);
		pier->AddVisual((LPDIRECT3DRMVISUAL) builder);
		builder->Release();
        LoadProgress.Text = "Building Oil Rig...";
		break;
	case 21:
		// load the oilrig
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &oilrig);
		m_lprm->CreateMeshBuilder(&builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_OILRIGX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetPerspective(TRUE);
		oilrig->AddVisual((LPDIRECT3DRMVISUAL) builder);
		builder->Release();
        LoadProgress.Text = "Building Rock...";
		break;
	case 22:
		// load the rock
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &rock);
		m_lprm->CreateMeshBuilder(&builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_ROCKX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetPerspective(TRUE);
		rock->AddVisual((LPDIRECT3DRMVISUAL) builder);
		builder->Release();
        LoadProgress.Text = "Building Left Bouy...";
		break;
	case 23:
  		// load the left bouy
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &leftbouy);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_LEFTBOUYX);
		m_lprm->CreateAnimationSet(&leftbouy_animate);
		leftbouy_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, leftbouy);
        LoadProgress.Text = "Building Right Bouy...";
		break;
	case 24:
  		// load the rite bouy
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &ritebouy);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_RITEBOUYX);
		m_lprm->CreateAnimationSet(&ritebouy_animate);
		ritebouy_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, ritebouy);
        LoadProgress.Text = "Building Shark...";
		break;
	case 25:
  		// load the shark head
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &sharkhead);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_SHARKHEADX);
		m_lprm->CreateAnimationSet(&sharkhead_animate);
		sharkhead_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, sharkhead);
		m_scene->DeleteChild(sharkhead);
        LoadProgress.Text = "Building Semjase...";
		break;
	case 26:
		// create the ufo frame
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &ufo);
		m_lprm->CreateMeshBuilder(&builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_UFOX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetQuality(D3DRMFILL_SOLID | D3DRMLIGHT_OFF | D3DRMSHADE_FLAT);
		builder->SetPerspective(TRUE);
		ufo->AddVisual(builder);
		builder->Release();
        LoadProgress.Text = "Building Horizon...";
		break;
	case 27:
		// load up horizon
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &beach_frame);
		m_lprm->CreateMeshBuilder(&builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_LEFTWALLX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetQuality(D3DRMFILL_SOLID | D3DRMLIGHT_OFF | D3DRMSHADE_FLAT);
		builder->SetPerspective(TRUE);
		beach_frame->AddVisual(builder);
		builder->Release();

		m_lprm->CreateMeshBuilder(&builder);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_RITEWALLX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetQuality(D3DRMFILL_SOLID | D3DRMLIGHT_OFF | D3DRMSHADE_FLAT);
		builder->SetPerspective(TRUE);
		beach_frame->AddVisual(builder);
		builder->Release();
        LoadProgress.Text = "Building Beach Scene...";
		break;
	case 28:
		// load in the intro sequence scene
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateMeshBuilder(&builder);
		m_lprm->CreateFrame(m_scene, &intro_scene);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_THEBEACHX);
		builder->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this);
		builder->SetPerspective(TRUE);
		intro_scene->AddVisual(builder);
		builder->Release();
        LoadProgress.Text = "Building Shop Proprietors...";
		break;
	case 29:
		// load in the shop guys
#ifndef NO_SURFERS
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &shopguys);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_SHOPGUYSX);
		m_lprm->CreateAnimationSet(&shopguys_animate);
		shopguys_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, shopguys);
		shopguys_animate->SetTime(D3DVALUE(1.0));
#endif
        LoadProgress.Text = "Building Trophy...";
		break;
	case 30:
		// load the trophy
#ifndef NO_SURFERS
		resourcedata.hModule = GetModuleHandle(NULL);
		resourcedata.lpType = "X";
		m_lprm->CreateFrame(m_scene, &trophy);
		resourcedata.lpName = MAKEINTRESOURCE(IDR_TROPHYX);
		m_lprm->CreateAnimationSet(&trophy_animate);
		trophy_animate->Load(&resourcedata,NULL,D3DRMLOAD_FROMRESOURCE, loadTextures, this, trophy);
#endif
        LoadProgress.Text = "Initializing Direct Sound + Loading Sound Effects...";
		break;
	case 31:
		// init Direct Sound
		if (bSoundFxAllowed)
		{
			if (!InitDirectSound())
			{
				if (bShowErrors) MessageBox("Could not create Direct Sound!","Darn.");
				bSurferSounds = FALSE;
				bNaration = FALSE;
				bSoundFx = FALSE;
				bSoundFxAllowed = FALSE;
			}
	// set volumes 
			m_pDSBuffer[SPLASH]->SetVolume(-500);
			m_pDSBuffer[SEAGULL1]->SetVolume(-1500);
			m_pDSBuffer[SEAGULL2]->SetVolume(-1000);
		}
        LoadProgress.Text = "Creating Cameras...";
		break;
	case 32:
		// create the camera frame
		m_lprm->CreateFrame(m_scene, &m_camera);
		if (bCharselect)
		{
		    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
				INTR_VRIGHT, INTR_VBOTTOM, &m_view);
			m_view->SetBack(D3DVAL(INTR_BACK));
		}
		else
		{
		    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
				m_lpDev->GetWidth(),
				m_lpDev->GetHeight(), &m_view);
			m_view->SetBack(D3DVAL(GAME_BACK));
		}
        LoadProgress.Text = "Clearing Surfaces...";
		break;
	case 33:
		ReleaseSomeStuff();
        LoadProgress.Text = "Creating Devices...";
		break;
	case 34:
		if (!CreateDevice())
		{
			if (bShowErrors) MessageBox("CreateDevice Failed","Bad Things...");
			return FALSE;
		}
        LoadProgress.Text = "Loading Surfaces...";
		break;
	case 35:
		RestoreSurfaces();
        LoadProgress.Text = "Final Setup!!!";
		break;

	case 36:
		bOkGo = TRUE;
		loading_number++;
		LoadProgress.OnCancel();
		if (bSoundFx)
			m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);
		ResetFps();
	    return TRUE;
		break;
	}
	loading_number++;
	::SendMessage(LoadProgress.m_hWnd, LOAD_MESSAGE, 0, 0);
//	::SendMessage(LoadProgress.m_hWnd, WM_PAINT, 0, 0);
	::SendMessage(m_hWnd, LOADING, 0, 0);
    return TRUE;
//	SetUpDirectPlay();
}

BOOL CsurfView::DDInit()
{
	static BOOL bFirstFullscreen = TRUE;
//    static DWORD dwStyle;
	
    /*
     * The first time the application is put in fullscreen mode, enumerate
     * the display modes and pick one to use.
     */
//	dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	if (bFirstFullscreen) 
	{
		ModeCx = GetPrivateProfileInt("ScreenMode","Width",0,"wildride.ini");
		ModeCy = GetPrivateProfileInt("ScreenMode","Height",0,"wildride.ini");

        if (!EnumerateDisplayModes())
            return FALSE;
		ModeNumber = 0;
		for (int i = 0; i < NumModes; i++)
		{
			if ((ModeCx == ModeListW[i]) 
				&& (ModeCy == ModeListH[i]))
			{
  				ModeNumber = i;
				i = NumModes;
			}
		}
		if (ModeNumber == 0)
		{
			ModeCx = ModeListW[0];
			ModeCy = ModeListH[0];
		}
        bFirstFullscreen = FALSE;
	}

	if (bFullscreen)
	{
		while (ShowCursor(FALSE) >= 0);
		::SetWindowPos(::GetParent(m_hWnd), 
						HWND_TOP,
						0, 
						0,
						GetSystemMetrics(SM_CXSCREEN),
						GetSystemMetrics(SM_CYSCREEN),
						NULL);
		::SetWindowLong(m_hWnd, GWL_STYLE, (DWORD) WS_POPUP);
	}
	else
	{
		::SetWindowLong(m_hWnd, GWL_STYLE, (DWORD) WS_POPUP);
		while (ShowCursor(TRUE) < 0);
	}

    HRESULT LastError = lpDD->SetCooperativeLevel(m_hWnd,
		DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);

    if (LastError != DD_OK)
	{
		bFullscreen = FALSE;
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "SetCooperativeLevel failed.");
        return FALSE;
    }

    GetHardwareCaps();
    return TRUE;
}

BOOL CsurfView::DDSetMode()
{
	HRESULT LastError;
//    DWORD dwStyle;
	ModeAx = 0;
	ModeAy = 0;
	ModeBx = ModeCx;
	ModeBy = ModeCy;

	// For fullscreen, set the actual display mode.

	if (bFullscreen)
	{
		if (lpDDGuid[CurrentDDDriver] != NULL)
		{
			ModeBx = ModeCx = 640;
			ModeBy = ModeCy = 480;
		}
	    LastError = lpDD->SetDisplayMode(ModeCx, ModeCy, 16);
	    if (LastError != DD_OK) 
		{
	        bFullscreen = FALSE;
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "SetDisplayMode failed");
	        return FALSE;
	    }
	}
    return DDCreateSurfaces();
}


BOOL CsurfView::D3DRMSetMode()
{
    /*
     * Create the viewport and device objects.
     */
// fullscreen
	BOOL LastError;
	if (bHalfres)
	{
	    LastError = FindDevice(lpHalfresBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return FALSE;
	    }
	}
	else
	{
	    LastError = FindDevice(lpBackBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return FALSE;
	    }
	}

    HDC hdc = ::GetDC(m_hWnd);
    int bpp = ::GetDeviceCaps(hdc, BITSPIXEL);
    ::ReleaseDC(m_hWnd, hdc);
    m_lpDev->SetDither(FALSE);
	m_lpDev->SetTextureQuality(TextureFiltering);
	bWrongDisplayMode = FALSE;
    switch (bpp)
    {
    case 16:
        m_lpDev->SetShades(32);
        m_lprm->SetDefaultTextureColors(64);
        m_lprm->SetDefaultTextureShades(32);
        break;
    default:
		bWrongDisplayMode = TRUE;
		return FALSE;
    }
	if (bTron)
	{
		m_lpDev->SetQuality(D3DRMRENDER_WIREFRAME);
	}
	else
	{
		m_lpDev->SetQuality(D3DRMRENDER_GOURAUD);
	}
	m_lpDev->SetTextureQuality(TextureFiltering);

//	if (firstd3dmode)
//	{
//		CreateScene();
//		firstd3dmode = FALSE;
//	}
	return TRUE;
}


/*
 * DDCreateSurfaces
 * Create front and back buffers as DirectDraw surfaces.
 */
BOOL CsurfView::DDCreateSurfaces()
{
    DDSURFACEDESC ddsd;
    DDSCAPS ddscaps;
	HRESULT LastError;

	// fullscreen
        /*
         * Create a complex flipping surface for fullscreen mode.
         */
    memset(&ddsd,0,sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
        DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
    if (bOnlySystemMemory)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    ddsd.dwBackBufferCount = 1;
    LastError = lpDD->CreateSurface(&ddsd, &lpFrontBuffer, NULL );
    if(LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for front fullscreen buffer failed.");
        return FALSE;
    }
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    LastError = lpFrontBuffer->GetAttachedSurface(&ddscaps, &lpBackBuffer);
    if(LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "GetAttachedSurface failed to get back buffer.");
        return FALSE;
    }
//    GetDDSurfaceDesc(&ddsd, lpBackBuffer);
//    if (!(ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY))
//        bOnlySoftRender;
	// halfres buffer
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
	ddsd.dwHeight = ModeCy/2;
	ddsd.dwWidth = ModeCx/2;
    if (bOnlySystemMemory)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    LastError = lpDD->CreateSurface(&ddsd, &lpHalfresBuffer, NULL );
    if(LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Halfres buffer failed.");
        return FALSE;
    }
    return TRUE;
}

/*
 * GetDDSurfaceDesc
 * Gets a surface description.
 */
void CsurfView::GetDDSurfaceDesc(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE lpDDSurf)
{
    memset(lpDDSurfDesc, 0, sizeof(DDSURFACEDESC));
    lpDDSurfDesc->dwSize = sizeof(DDSURFACEDESC);
    HRESULT LastError = lpDDSurf->GetSurfaceDesc(lpDDSurfDesc);
    if (LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Error getting a surface description.");
        CleanUpAndExit();
    }
}

/*
 * EnumerateDisplayModes
 * Generates the list of available display modes.
 */
BOOL CsurfView::EnumerateDisplayModes()
{
    DDCAPS ddcaps;
    int i,j,q;
    char ach[80];

    memset(&ddcaps, 0, sizeof(ddcaps));
    ddcaps.dwSize = sizeof( ddcaps );
    HRESULT LastError = lpDD->GetCaps(&ddcaps, NULL );
    if(LastError != DD_OK )
	{
         bFullscreen = FALSE;
         if (bShowErrors) MessageBox(MyErrorToString(LastError), "GetCaps failed while enumerating display modes.");
         return FALSE;
    }
    TotalVideoMemory = (long)(ddcaps.dwVidMemTotal);
    NumModes = 0;
    LastError = lpDD->EnumDisplayModes(0, NULL, this, EnumDisplayModesCallback);
    if(LastError != DD_OK ) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "EnumDisplayModes failed.");
        return FALSE;
    }
	
// sort display modes

	for (i = 0; i < NumModes; i++)
	{
		for (j = i+1; j < NumModes; j++)
		{
			if ((ModeListW[i] >= ModeListW[j]) && (ModeListH[i] >= ModeListH[j]))
			{
				q = ModeListW[i];
				ModeListW[i] = ModeListW[j];
				ModeListW[j] = q;
				q = ModeListH[i];
				ModeListH[i] = ModeListH[j];
				ModeListH[j] = q;
			}
		}
        wsprintf(ach,"%dx%dx%d", ModeListW[i], ModeListH[i], 16);
		::AppendMenu(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), MENU_FULLSCREEN),MF_STRING, ID_FULLSCREEN0+i, ach);
	}
    return TRUE;
}

HRESULT CsurfView::EnumDisplayModesCallFront(int ModeLW, int ModeLH)
{
	ModeListW[NumModes] = ModeLW;
	ModeListH[NumModes] = ModeLH;
	NumModes++;
	if (NumModes == D3DAPP_MAXMODES)
        return DDENUMRET_CANCEL;
    else
    return DDENUMRET_OK;
}


/*
 * EnumDisplayModesCallback
 * Callback to save the display mode information.
 */
static HRESULT CALLBACK EnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID lpThat)
{
    /*
     * Very large resolutions cause problems on some hardware.  They are also
     * not very useful for real-time rendering.  We have chosen to disable
     * them by not reporting them as available.
     */
	CsurfView * view = (CsurfView *)lpThat;

	if (!pddsd)
	{
//		if (bShowErrors) MessageBox(NULL, "what the poop?!","surfacedesc is invalid", 0);
		return DDENUMRET_OK;
	}
    if (pddsd->dwWidth > 1024 || pddsd->dwHeight > 768 || pddsd->ddpfPixelFormat.dwRGBBitCount != 16 || pddsd->dwWidth < 320)
        return DDENUMRET_OK;
    /*
     * Save this mode at the end of the mode array and increment mode count
     */
	HRESULT ret = view->EnumDisplayModesCallFront(pddsd->dwWidth, pddsd->dwHeight);
	return ret;
}

BOOL CsurfView::CreateZBuffer(DWORD depth, DWORD memorytype)
{
    DDSURFACEDESC ddsd;
	HRESULT LastError;

    /*
     * Create a Z-Buffer and attach it to the back buffer.
     */
	{
        memset(&ddsd,0,sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof( ddsd );
        ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;
        ddsd.dwHeight = ModeCy;
        ddsd.dwWidth = ModeCx;
        ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | memorytype;
        ddsd.dwZBufferBitDepth = depth;
        LastError = lpDD->CreateSurface(&ddsd, &lpZBuffer, NULL );
        if(LastError != DD_OK) 
		{
            if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for fullscreen Z-buffer failed.");
            return FALSE;
        }
        LastError = lpBackBuffer->AddAttachedSurface(lpZBuffer);
        if(LastError != DD_OK) 
		{
            if (bShowErrors) MessageBox(MyErrorToString(LastError), "AddAttachedBuffer failed for Z-Buffer.");
            return FALSE;
        }
    } 
    return TRUE;
}
 
/*
 * GetHardwareCaps
 * Determines Z buffer depth.
 */
void CsurfView::GetHardwareCaps()
{
    DDCAPS DriverCaps, HELCaps;

    memset(&DriverCaps, 0, sizeof(DriverCaps));
    DriverCaps.dwSize = sizeof(DDCAPS);
    memset(&HELCaps, 0, sizeof(HELCaps));
    HELCaps.dwSize = sizeof(DDCAPS);
	HRESULT LastError = lpDD->GetCaps(&DriverCaps, &HELCaps);
    if (LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "GetCaps failed in while checking driver capabilities.");
        CleanUpAndExit();
    }
    /*
     * Pick the most accurate Z-Buffer depth from hardware or the HEL if hardware
     * doesn't support them.
     */
    if (DriverCaps.dwZBufferBitDepths) 
	{
        if (DriverCaps.dwZBufferBitDepths & DDBD_32)
            dwZBufferBitDepth = 32;
        else if (DriverCaps.dwZBufferBitDepths & DDBD_24)
            dwZBufferBitDepth = 24;
        else if (DriverCaps.dwZBufferBitDepths & DDBD_16)
            dwZBufferBitDepth = 16;
        else if (DriverCaps.dwZBufferBitDepths & DDBD_8)
            dwZBufferBitDepth = 8;
        else 
		{
            if (bShowErrors) MessageBox("No valid Z-Buffer depths available.");
            CleanUpAndExit();
        }
    } 
	else 
	{
        /*
         * At the moment, software requires a 16-bit z-buffer, but doesn't tell
         * you that.  Improvements are scheduled for the D3D caps to remedy this.
         */
        dwZBufferBitDepth = 16;
    }
}

/*
 * CleanUpAndExit
 * Release everything and posts a quit message.  Used for program termination.
 */

void CsurfView::SaveStats()
{
	char ss[10];

	if (!bFullscreen)
	{
		SaveScreenDimensions();
	}

	if (bAutoCamera)
	{
		WritePrivateProfileString("Cameras","Auto","1","wildride.ini");
		camera_type = last_camera;
	}
	else
		WritePrivateProfileString("Cameras","Auto","0","wildride.ini");

	sprintf(ss, "%d",camera_type);
	WritePrivateProfileString("Cameras","Type",ss,"wildride.ini");

	if (bAutoCamera)
		WritePrivateProfileString("Cameras","Auto","1","wildride.ini");
	else
		WritePrivateProfileString("Cameras","Auto","0","wildride.ini");

	sprintf(ss, "%d",hiscore[0]);
	WritePrivateProfileString("HiScores","score0",ss,"wildride.ini");
	sprintf(ss, "%d",hiscore[1]);
	WritePrivateProfileString("HiScores","score1",ss,"wildride.ini");
	sprintf(ss, "%d",hiscore[2]);
	WritePrivateProfileString("HiScores","score2",ss,"wildride.ini");
	sprintf(ss, "%d",hiscore[3]);
	WritePrivateProfileString("HiScores","score3",ss,"wildride.ini");
	sprintf(ss, "%d",hiscore[4]);
	WritePrivateProfileString("HiScores","score4",ss,"wildride.ini");
	sprintf(ss, "%d",hiscore[5]);
	WritePrivateProfileString("HiScores","score5",ss,"wildride.ini");

	WritePrivateProfileString("HiScores","name0",hiname[0],"wildride.ini");
	WritePrivateProfileString("HiScores","name1",hiname[1],"wildride.ini");
	WritePrivateProfileString("HiScores","name2",hiname[2],"wildride.ini");
	WritePrivateProfileString("HiScores","name3",hiname[3],"wildride.ini");
	WritePrivateProfileString("HiScores","name4",hiname[4],"wildride.ini");
	WritePrivateProfileString("HiScores","name5",hiname[5],"wildride.ini");

	sprintf(ss, "%d",hisurfer[0]);
	WritePrivateProfileString("HiScores","surfer0",ss,"wildride.ini");
	sprintf(ss, "%d",hisurfer[1]);
	WritePrivateProfileString("HiScores","surfer1",ss,"wildride.ini");
	sprintf(ss, "%d",hisurfer[2]);
	WritePrivateProfileString("HiScores","surfer2",ss,"wildride.ini");
	sprintf(ss, "%d",hisurfer[3]);
	WritePrivateProfileString("HiScores","surfer3",ss,"wildride.ini");
	sprintf(ss, "%d",hisurfer[4]);
	WritePrivateProfileString("HiScores","surfer4",ss,"wildride.ini");
	sprintf(ss, "%d",hisurfer[5]);
	WritePrivateProfileString("HiScores","surfer5",ss,"wildride.ini");

#ifndef SHAREWARE
	sprintf(ss, "%d",hiscorec[0]);
	WritePrivateProfileString("ContestHiScore","score0",ss,"wildride.ini");
	sprintf(ss, "%d",hiscorec[1]);
	WritePrivateProfileString("ContestHiScore","score1",ss,"wildride.ini");
	sprintf(ss, "%d",hiscorec[2]);
	WritePrivateProfileString("ContestHiScore","score2",ss,"wildride.ini");
	sprintf(ss, "%d",hiscorec[3]);
	WritePrivateProfileString("ContestHiScore","score3",ss,"wildride.ini");
	sprintf(ss, "%d",hiscorec[4]);
	WritePrivateProfileString("ContestHiScore","score4",ss,"wildride.ini");
	sprintf(ss, "%d",hiscorec[5]);
	WritePrivateProfileString("ContestHiScore","score5",ss,"wildride.ini");

	WritePrivateProfileString("ContestHiScore","name0",hinamec[0],"wildride.ini");
	WritePrivateProfileString("ContestHiScore","name1",hinamec[1],"wildride.ini");
	WritePrivateProfileString("ContestHiScore","name2",hinamec[2],"wildride.ini");
	WritePrivateProfileString("ContestHiScore","name3",hinamec[3],"wildride.ini");
	WritePrivateProfileString("ContestHiScore","name4",hinamec[4],"wildride.ini");
	WritePrivateProfileString("ContestHiScore","name5",hinamec[5],"wildride.ini");

	sprintf(ss, "%d",hisurferc[0]);
	WritePrivateProfileString("ContestHiScore","surfer0",ss,"wildride.ini");
	sprintf(ss, "%d",hisurferc[1]);
	WritePrivateProfileString("ContestHiScore","surfer1",ss,"wildride.ini");
	sprintf(ss, "%d",hisurferc[2]);
	WritePrivateProfileString("ContestHiScore","surfer2",ss,"wildride.ini");
	sprintf(ss, "%d",hisurferc[3]);
	WritePrivateProfileString("ContestHiScore","surfer3",ss,"wildride.ini");
	sprintf(ss, "%d",hisurferc[4]);
	WritePrivateProfileString("ContestHiScore","surfer4",ss,"wildride.ini");
	sprintf(ss, "%d",hisurferc[5]);
	WritePrivateProfileString("ContestHiScore","surfer5",ss,"wildride.ini");
#endif

	sprintf(ss, "%d",D3DDriver);
	WritePrivateProfileString("Details","D3DDriver",ss,"wildride.ini");

	if (TextureFiltering == D3DRMTEXTURE_LINEAR)
		WritePrivateProfileString("Details","TextureFiltering","1","wildride.ini");
	else
		WritePrivateProfileString("Details","TextureFiltering","0","wildride.ini");

	if (bSprayOn)
		WritePrivateProfileString("Details","Spray","1","wildride.ini");
	else
		WritePrivateProfileString("Details","Spray","0","wildride.ini");
	if (bPractice)
		WritePrivateProfileString("Details","PracticeMode","1","wildride.ini");
	else
		WritePrivateProfileString("Details","PracticeMode","0","wildride.ini");
	if (!bNoTextures)
		WritePrivateProfileString("Details","Textures","1","wildride.ini");
	else
		WritePrivateProfileString("Details","Textures","0","wildride.ini");
	if (bShowErrors)
		WritePrivateProfileString("Details","ShowErrors","1","wildride.ini");
	else
		WritePrivateProfileString("Details","ShowErrors","0","wildride.ini");
	if (bMIDIMusic)
		WritePrivateProfileString("Audio","MIDIMusic","1","wildride.ini");
	else
		WritePrivateProfileString("Audio","MIDIMusic","0","wildride.ini");
	if (bCDMusic)
		WritePrivateProfileString("Audio","CDMusic","1","wildride.ini");
	else
		WritePrivateProfileString("Audio","CDMusic","0","wildride.ini");
	if (bSoundFx)
		WritePrivateProfileString("Audio","SoundFx","1","wildride.ini");
	else
		WritePrivateProfileString("Audio","SoundFx","0","wildride.ini");
	if (bSoundFxAllowed)
		WritePrivateProfileString("Audio","SoundFxAllowed","1","wildride.ini");
	if (bNaration)
		WritePrivateProfileString("Audio","Naration","1","wildride.ini");
	else
		WritePrivateProfileString("Audio","Naration","0","wildride.ini");
	if (bSurferSounds)
		WritePrivateProfileString("Audio","SurferSounds","1","wildride.ini");
	else
		WritePrivateProfileString("Audio","SurferSounds","0","wildride.ini");
	if (bHalfres)
		WritePrivateProfileString("Details","HalfResolution","1","wildride.ini");
	else
		WritePrivateProfileString("Details","HalfResolution","0","wildride.ini");
	if (bWaveTextures)
		WritePrivateProfileString("Details","WaveMaps","1","wildride.ini");
	else
		WritePrivateProfileString("Details","WaveMaps","0","wildride.ini");
	if (bSky)
		WritePrivateProfileString("Details","SkyMap","1","wildride.ini");
	else
		WritePrivateProfileString("Details","SkyMap","0","wildride.ini");
	if (bHorizon)
		WritePrivateProfileString("Details","Horizon","1","wildride.ini");
	else
		WritePrivateProfileString("Details","Horizon","0","wildride.ini");
	if (bSpeedofish)
		WritePrivateProfileString("Details","Speed-O-Fish","1","wildride.ini");
	else
		WritePrivateProfileString("Details","Speed-O-Fish","0","wildride.ini");
	if (bScoreBlit)
		WritePrivateProfileString("Details","ScoreDisplay","1","wildride.ini");
	else
		WritePrivateProfileString("Details","ScoreDisplay","0","wildride.ini");
	if (bBreakingWave)
		WritePrivateProfileString("Details","BreakingWave","1","wildride.ini");
	else
		WritePrivateProfileString("Details","BreakingWave","0","wildride.ini");
	if (bFoam)
		WritePrivateProfileString("Details","Foam","1","wildride.ini");
	else
		WritePrivateProfileString("Details","Foam","0","wildride.ini");
	if (bGore)
		WritePrivateProfileString("Details","Gore","1","wildride.ini");
	else
		WritePrivateProfileString("Details","Gore","0","wildride.ini");
	WritePrivateProfileString("Details","FrontYard","1978 Oldsmobile Cutlass Supreme w/mag wheels, rust stains & no muffler","wildride.ini");
	WritePrivateProfileString("Details","BackYard","1979 Chevrolet Caprice w/tinted windows, bullet holes & no muffler","wildride.ini");
}

void CsurfView::CleanUpAndExit()
{
    PostQuitMessage( 0 );
}

void CsurfView::OnPaint() 
{
	RECT r;
	PAINTSTRUCT ps;
	static BOOL bFirst = TRUE;

	if (bFirst)	
	{
		bFirst = FALSE;
		LoadProgress.Create(LoadProgress.IDD, this);
        LoadProgress.Text = "Creating Direct Draw...";
		::SendMessage(LoadProgress.m_hWnd, LOAD_MESSAGE, 0, 0);
		::SendMessage(m_hWnd, LOADING, 0, 0);
	}
  
	else if (m_lpDev) 
	{
		LPDIRECT3DRMWINDEVICE windev;
        if (GetUpdateRect(&r, FALSE))
		{
			BeginPaint(&ps);
			if (SUCCEEDED(m_lpDev->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &windev)))
			{   
				if (FAILED(windev->HandlePaint(ps.hdc))) 
				{
					if (bShowErrors) MessageBox("Failed to handle WM_PAINT","D'OH!");
				}
				windev->Release();
			}
			else 
			{
				if (bShowErrors) MessageBox("Failed to create Windows device to handle WM_PAINT","D'OH!");
			}
			EndPaint(&ps);
		}
	}
}

void CsurfView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (m_lpDev) 
	{
		bAppPaused = !bActivate;
		if (bActivate && bCharselect)
			bResizedSelect = TRUE;
	}
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CsurfView::OnSize(UINT nType, int cx, int cy) 
{
	if ((nType == SIZE_MAXIMIZED) || bFullscreen)
	{
		bMinimized = FALSE;
		bMaximized = TRUE;
	}
	else if (nType == SIZE_MINIMIZED)
	{
		bMinimized = TRUE;
		bMaximized = FALSE;
	}
	else if (nType == SIZE_RESTORED)
	{
		bMinimized = FALSE;
		bMaximized = FALSE;
	}
//	CView::OnSize(nType, cx, cy);
	if (m_lpDev)
    {
		if (!bFullscreen)
		{
			ReSizeWindow();
			SaveScreenDimensions();
		}
		ResetFps();
	}
}

void CsurfView::ReSizeWindow()
{
    RECT r;
	HRESULT LastError;
    DDSURFACEDESC ddsd;

	int old_dither = m_lpDev->GetDither();
	D3DRMRENDERQUALITY old_quality = m_lpDev->GetQuality();
	int old_shades = m_lpDev->GetShades();

	if (m_view != NULL)
	{
		m_view->Release();
		m_view = NULL;
	}
//	m_lpDev->Release();

	::GetWindowRect(m_hWnd, &r);

	ModeAx = r.left+2;
	ModeAy = r.top+2;
	ModeBx = r.right-2;
	ModeCx = ModeBx - ModeAx;
	ModeBy = r.bottom-2;
	ModeCy = ModeBy - ModeAy;

	if (ModeCy < 32)
	{
		ModeCy = 32;
		ModeBy = ModeAy + 32;
	}

	if (ModeCx/2 != (int)((float)ModeCx/2+0.5))
	{
		ModeBx--;
		ModeCx--;
	}
	if (ModeCy/2 != (int)((float)ModeCy/2+0.5))
	{
		ModeBy--;
		ModeCy--;
	}

	if (lpBackBuffer)
	{
		lpBackBuffer->Release();
		lpBackBuffer = NULL;
	}

	// back buffer
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
	ddsd.dwHeight = ModeCy;
	ddsd.dwWidth = ModeCx;
	if (bOnlySystemMemory)
	    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	LastError = lpDD->CreateSurface(&ddsd, &lpBackBuffer, NULL);
	if(LastError != DD_OK) 
	{
	    if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Back buffer failed.");
		return;
	}

	if (lpHalfresBuffer)
	{
		lpHalfresBuffer->Release();
		lpHalfresBuffer = NULL;
	}

	// halfres buffer
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
	ddsd.dwHeight = ModeCy/2;
	ddsd.dwWidth = ModeCx/2;
	if (bOnlySystemMemory)
	    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	LastError = lpDD->CreateSurface(&ddsd, &lpHalfresBuffer, NULL );
	if(LastError != DD_OK) 
	{
	    if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateSurface for Halfres buffer failed.");
	    return;
	}

	if (bHalfres)
	{
	    LastError = FindDevice(lpHalfresBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return;
	    }
	}
	else
	{
	    LastError = FindDevice(lpBackBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return;
	    }
	}
				
	m_lpDev->SetDither(old_dither);
	m_lpDev->SetQuality(old_quality);
	m_lpDev->SetShades(old_shades);
	m_lpDev->SetTextureQuality(TextureFiltering);
//    m_lprm->SetDefaultTextureColors(128);
  //  m_lprm->SetDefaultTextureShades(128);

	if (bCharselect)
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
			INTR_VRIGHT, INTR_VBOTTOM, &m_view);

	    m_view->SetBack(D3DVAL(INTR_BACK));

		bResizedSelect = TRUE;
	}
	else
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
			m_lpDev->GetWidth(),
			m_lpDev->GetHeight(), &m_view);
	    m_view->SetBack(D3DVAL(GAME_BACK));
	}

	if (bSoundFx)
		m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);
}

BOOL CsurfView::InitJoystick()
{
  JOYINFO jiInfo;
  BOOL    bDev1Attached, bDev2Attached;

  // See if joystick(s) are attached
  bDev1Attached = (::joyGetPos(JOYSTICKID1, &jiInfo) ==
    JOYERR_NOERROR) && (::joyGetDevCaps(JOYSTICKID1, &jcCaps, 
	sizeof(JOYCAPS)) == JOYERR_NOERROR);

  bDev2Attached = (::joyGetPos(JOYSTICKID2, &jiInfo) ==
    JOYERR_NOERROR) && (::joyGetDevCaps(JOYSTICKID2, &jcCaps, 
	sizeof(JOYCAPS)) == JOYERR_NOERROR);

  // Decide which joystick to use
  if (bDev1Attached || bDev2Attached)
    m_uiJoyStick = bDev1Attached ? JOYSTICKID1 : JOYSTICKID2;
  else
  {
    if (bShowErrors) MessageBox("Your Joystick isn't plugged in, or you don't\nhave it set up under the Control Panel.\nUse the cursor keys and the space bar.",
		"Joystick Difficulties");
    return FALSE;
  }
  // Set up the capabilities of the JoyStick
  if (::joyGetDevCaps(m_uiJoyStick, &jcCaps, 
	  sizeof(JOYCAPS)) != JOYERR_NOERROR)
	return FALSE;

  joy_center = (float)((jcCaps.wXmax - jcCaps.wXmin) /2 ) + jcCaps.wXmin;
  joy_half = ((float)jcCaps.wXmax - joy_center);
  joy_left = ((float)jcCaps.wXmin + (joy_half * (const float)0.25));
  joy_right = ((float)jcCaps.wXmax - (joy_half * (const float)0.25));

  joy_y_center = (float)((jcCaps.wYmax - jcCaps.wYmin) /2 ) + jcCaps.wYmin;
  joy_y_half = ((float)jcCaps.wYmax - joy_y_center);
  joy_up = ((float)jcCaps.wYmin + (joy_y_half * (const float)0.25));
  joy_down = ((float)jcCaps.wYmax - (joy_y_half * (const float)0.25));

  return TRUE;
}

BOOL CsurfView::InitDirectSound()
{
	// Create the DS object
	if (::DirectSoundCreate(NULL, &m_pDirectSound, NULL) != DS_OK)
	{
		if (bShowErrors) MessageBox("Could not create DirectSound object!",
			"DirectSound Error");
	    CleanupDirectSound();
	    return FALSE;
	}

  // Set the cooperation level for the DS object
  if (m_pDirectSound->SetCooperativeLevel(m_hWnd,
    DSSCL_NORMAL) != DS_OK)
  {
    if (bShowErrors) MessageBox("Could not set cooperative level!",
      "DirectSound Error");
    CleanupDirectSound();
    return FALSE;
  }

  // Initialize the DS buffers
  if (!InitDSBuffers())
  {
    if (bShowErrors) MessageBox("Could not initialize DirectSound buffers!",
      "DirectSound Error");
    CleanupDirectSound();
    return FALSE;
  }

  return TRUE;
}

void CsurfView::CleanupDirectSound()
{
	bSoundFx = FALSE;
	bNaration = FALSE;
	bSurferSounds = FALSE;
	bSoundFxAllowed = FALSE;
	// Cleanup the sound buffers
	for (int i = 0; i < NUMSOUNDS; i++)
	{
		if (m_pDSBuffer[i])
		{
			m_pDSBuffer[i]->Release();
			m_pDSBuffer[i] = NULL;
		}
	}

	// Cleanup the DS object
	if (m_pDirectSound)
	{
		m_pDirectSound->Release();
		m_pDirectSound = NULL;
	}
}

BOOL CsurfView::InitDSBuffers()
{
	if (!bSoundFxAllowed)
		return FALSE;
	// Initialize waves
	UINT wave_resource[NUMSOUNDS] =
	{
		IDR_OCEANWAVE,
		IDR_UFOWAVE,
		IDR_SPLASHWAVE,
		IDR_WHOOSHWAVE,
		IDR_SEAGULLWAVE1,
		IDR_SEAGULLWAVE2,
		IDR_SINKWAVE,
		IDR_GAMEOVERWAVE,
		IDR_SLALOMWAVE,
		IDR_STEAMSHIPWAVE,
		IDR_ROCKWAVE,
		IDR_ROCKWAVE2,
		IDR_PLIDWAVE,
		IDR_PLIDWAVE2,
		IDR_POSTWAVE,
		IDR_POSTWAVE2,
		IDR_BARRELWAVE,
		IDR_BARRELWAVE2,
		IDR_BOUYWAVE,
		IDR_BOUYWAVE2,
		IDR_DOLPHINWAVE,
		IDR_DOLPHINWAVE2,
		IDR_DOLPHINHITWAVE1,
		IDR_DOLPHINHITWAVE2,
		IDR_BREAKHITWAVE1,
		IDR_BREAKHITWAVE2,
		IDR_OILLEGWAVE1,
		IDR_OILLEGWAVE2,
		IDR_OILRIGWAVE1,
		IDR_OILRIGWAVE2,
		IDR_TUBEWAVE,
		IDR_LANDINGWAVE,
		IDR_SHARKWAVE,
		IDR_SHARKWAVE2,
		IDR_UFOSTOPWAVE,
		IDR_UFOCWAVE,
		IDR_180WAVE1,
		IDR_180WAVE2,
		IDR_360WAVE1,
		IDR_360WAVE2,
		IDR_540WAVE1,
		IDR_540WAVE2,
		IDR_720WAVE1,
		IDR_720WAVE2,
		IDR_900WAVE1,
		IDR_900WAVE2,
		IDR_INSANEWAVE1,
		IDR_INSANEWAVE2,
		IDR_DOUBLEINSANEWAVE1,
		IDR_DOUBLEINSANEWAVE2,
		IDR_TRIPLEINSANEWAVE1,
		IDR_TRIPLEINSANEWAVE2,
		IDR_QUADRUPLEINSANEWAVE1,
		IDR_QUADRUPLEINSANEWAVE2,
		IDR_RIDICULOUSINSANEWAVE1,
		IDR_RIDICULOUSINSANEWAVE2,
		IDR_SURFWAVE1,
		IDR_SURFWAVE2,
		IDR_SURFWAVE3,
		IDR_REEFWAVE1,
		IDR_WAGONWAVE,
		IDR_WIPEOUTWAVE1,
		IDR_WIPEOUTWAVE2,
		IDR_WIPEOUTWAVE3,
		IDR_WIPEOUTWAVE4,
		IDR_WUSSYWAVE,
		IDR_MUSTHURTWAVE,
		IDR_OUCHWAVE,
		IDR_MANGLEDWAVE,
		IDR_AMBULANCEWAVE,
		IDR_SURFSCHOOLWAVE,
		IDR_ROCKDAVEWAVE,
		IDR_SHARKDAVEWAVE1,
		IDR_SHARKDAVEWAVE2,
		IDR_BARRELDAVEWAVE1,
		IDR_BARRELDAVEWAVE2,
		IDR_DOLPHINDISTURBWAVE,
		IDR_ALIENWAVE,
		IDR_ORBITWAVE,
		IDR_OHHWAVE1,
		IDR_OHHWAVE2,
		IDR_HISCOREWAVE1,
		IDR_HISCOREWAVE2,
		IDR_GAMEOVERDAVEWAVE1,
		IDR_GAMEOVERDAVEWAVE2,
		IDR_GAMEOVERDAVEWAVE3,
		IDR_GROOVYTUBEWAVE1,
		IDR_GROOVYTUBEWAVE2,
		IDR_PIERACTIONWAVE,
		IDR_UFODAVEWAVE1,
		IDR_UFODAVEWAVE2,
		IDR_TRICKWAVE1,
		IDR_TRICKWAVE2,
		IDR_TRICKWAVE3,
		IDR_TRICKWAVE4,
		IDR_TRICKWAVE5,
		IDR_TRICKWAVE6,
		IDR_TRICKWAVE7,
		IDR_TRICKWAVE8,
		IDR_TRICKWAVE9,
		IDR_TRICKWAVE10,
#ifndef SHAREWARE
		IDR_RUNOVERWAVE1,
		IDR_RUNOVERWAVE2,
		IDR_HEATOVERWAVE1,
		IDR_HEATOVERWAVE2,
		IDR_DISQUALIFYWAVE1,
		IDR_DISQUALIFYWAVE2,
		IDR_DISQUALIFYWAVE3,
		IDR_USUREWAVE1,
		IDR_USUREWAVE2,
		IDR_ANALANAWAVE,
		IDR_ANBUCKYWAVE,
		IDR_ANLEEWAVE,
		IDR_ANSANDYWAVE,
		IDR_ANTODDWAVE,
		IDR_ANVICWAVE,
		IDR_WIPEOUTWAVEA1,
		IDR_WIPEOUTWAVEA2,
		IDR_WIPEOUTWAVEA3,
		IDR_WIPEOUTWAVEA4,
		IDR_WIPEOUTWAVEB1,
		IDR_WIPEOUTWAVEB2,
		IDR_WIPEOUTWAVEB3,
		IDR_WIPEOUTWAVEB4,
		IDR_WIPEOUTWAVEL1,
		IDR_WIPEOUTWAVEL2,
		IDR_WIPEOUTWAVEL3,
		IDR_WIPEOUTWAVEL4,
		IDR_WIPEOUTWAVES1,
		IDR_WIPEOUTWAVES2,
		IDR_WIPEOUTWAVES3,
		IDR_WIPEOUTWAVET1,
		IDR_WIPEOUTWAVET2,
		IDR_WIPEOUTWAVEV1,
		IDR_WIPEOUTWAVEV2,
		IDR_WIPEOUTWAVEV3,
		IDR_WIPEOUTWAVEV4,
		IDR_TRICKWAVEA1,
		IDR_TRICKWAVEA2,
		IDR_TRICKWAVEA3,
		IDR_TRICKWAVEB1,
		IDR_TRICKWAVEB2,
		IDR_TRICKWAVEB3,
		IDR_TRICKWAVEL1,
		IDR_TRICKWAVEL2,
		IDR_TRICKWAVEL3,
		IDR_TRICKWAVEL4,
		IDR_TRICKWAVES1,
		IDR_TRICKWAVES2,
		IDR_TRICKWAVES3,
		IDR_TRICKWAVES4,
		IDR_TRICKWAVET1,
		IDR_TRICKWAVET2,
		IDR_TRICKWAVEV1,
		IDR_TRICKWAVEV2,
		IDR_TRICKWAVEV3,
		IDR_HOLDWAVEA1,
		IDR_HOLDWAVEB1,
		IDR_HOLDWAVEB2,
		IDR_HOLDWAVEL1,
		IDR_HOLDWAVEL2,
		IDR_HOLDWAVES1,
		IDR_HOLDWAVES2,
		IDR_HOLDWAVET1,
		IDR_HOLDWAVET2,
		IDR_HOLDWAVEV1,
		IDR_HOLDWAVEV2,
		IDR_360WAVEA1,
		IDR_360WAVEA2,
		IDR_360WAVEB1,
		IDR_360WAVEB2,
		IDR_360WAVEL1,
		IDR_360WAVEL2,
		IDR_360WAVES1,
		IDR_360WAVES2,
		IDR_360WAVET1,
		IDR_360WAVET2,
		IDR_360WAVEV1,
		IDR_360WAVEV2,
		IDR_TUBEWAVEA1,
		IDR_TUBEWAVEA2,
		IDR_TUBEWAVEB1,
		IDR_TUBEWAVEB2,
		IDR_TUBEWAVEL1,
		IDR_TUBEWAVEL2,
		IDR_TUBEWAVES1,
		IDR_TUBEWAVET1,
		IDR_TUBEWAVET2,
		IDR_TUBEWAVEV1,
		IDR_TUBEWAVEV2,
		IDR_DROPINWAVEA1,
		IDR_DROPINWAVEA2,
		IDR_DROPINWAVEA3,
		IDR_DROPINWAVEB1,
		IDR_DROPINWAVEB2,
		IDR_DROPINWAVEL1,
		IDR_DROPINWAVEL2,
		IDR_DROPINWAVEL3,
		IDR_DROPINWAVES1,
		IDR_DROPINWAVES2,
		IDR_DROPINWAVES3,
		IDR_DROPINWAVET1,
		IDR_DROPINWAVET2,
		IDR_DROPINWAVEV1,
		IDR_DROPINWAVEV2,
		IDR_DROPINWAVEV3,
		IDR_INSANITYWAVEA1,
		IDR_INSANITYWAVEB1,
		IDR_INSANITYWAVEL1,
		IDR_INSANITYWAVEL2,
		IDR_INSANITYWAVES1,
		IDR_INSANITYWAVET1,
		IDR_INSANITYWAVEV1,
		IDR_UWONWAVE
#else
		IDR_ANALANAWAVE,
		IDR_ANLEEWAVE,
		IDR_WIPEOUTWAVEA1,
		IDR_WIPEOUTWAVEA2,
		IDR_WIPEOUTWAVEA3,
		IDR_WIPEOUTWAVEA4,
		IDR_WIPEOUTWAVEL1,
		IDR_WIPEOUTWAVEL2,
		IDR_WIPEOUTWAVEL3,
		IDR_WIPEOUTWAVEL4,
		IDR_TRICKWAVEA1,
		IDR_TRICKWAVEA2,
		IDR_TRICKWAVEA3,
		IDR_TRICKWAVEL1,
		IDR_TRICKWAVEL2,
		IDR_TRICKWAVEL3,
		IDR_TRICKWAVEL4,
		IDR_HOLDWAVEA1,
		IDR_HOLDWAVEL1,
		IDR_HOLDWAVEL2,
		IDR_360WAVEA1,
		IDR_360WAVEA2,
		IDR_360WAVEL1,
		IDR_360WAVEL2,
		IDR_TUBEWAVEA1,
		IDR_TUBEWAVEA2,
		IDR_TUBEWAVEL1,
		IDR_TUBEWAVEL2,
		IDR_DROPINWAVEA1,
		IDR_DROPINWAVEA2,
		IDR_DROPINWAVEA3,
		IDR_DROPINWAVEL1,
		IDR_DROPINWAVEL2,
		IDR_DROPINWAVEL3,
		IDR_INSANITYWAVEA1,
		IDR_INSANITYWAVEL1,
		IDR_INSANITYWAVEL2
#endif
	};

	CWave wavebuffer;

	// Initialize DS buffers
	for (int i = 0; i < NUMSOUNDS; i++)
	{
		wavebuffer.Create(wave_resource[i], GetModuleHandle(NULL));
		// Get the wave information
		DWORD         dwDataLen = wavebuffer.GetDataLen();
	    WAVEFORMATEX  wfFormat;
	    wavebuffer.GetFormat(wfFormat);

		// Setup the DS buffer description
	    DSBUFFERDESC  dsbdDesc;
		ZeroMemory(&dsbdDesc, sizeof(DSBUFFERDESC));
	    dsbdDesc.dwSize = sizeof(DSBUFFERDESC);
		dsbdDesc.dwFlags = DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC;
	    dsbdDesc.dwBufferBytes = dwDataLen;
		dsbdDesc.lpwfxFormat = &wfFormat;

	    // Create the DS buffer
		if (m_pDirectSound->CreateSoundBuffer(&dsbdDesc,
	      &m_pDSBuffer[i], NULL) != DS_OK)
		  return FALSE;

	    // Lock the DS buffer
		BYTE* pDSBuffData;
	    if (m_pDSBuffer[i]->Lock(0, dwDataLen, (LPLPVOID)&pDSBuffData,
		  &dwDataLen, NULL, 0, 0) != DS_OK)
	      return FALSE;

		// Write wave data to the DS buffer
	    dwDataLen = wavebuffer.GetData(pDSBuffData, dwDataLen);

		// Unlock the DS buffer
	    if (m_pDSBuffer[i]->Unlock(pDSBuffData, dwDataLen, NULL, 0) !=
		  DS_OK)
	      return FALSE;

		wavebuffer.FreeEmUp();
	}
  return TRUE;
}


BOOL CsurfView::RestoreDSBuffers()
{
	if (!bSoundFxAllowed)
		return FALSE;
  // Restore the buffers
  for (int i = 0; i < NUMSOUNDS; i++)
    if (m_pDSBuffer[i]->Restore() != DS_OK)
      return FALSE;

  // Re-initialize the buffers
  return InitDSBuffers();
}

// CD routines

DWORD CsurfView::setUpCD()
{
    DWORD dwReturn;
    MCI_OPEN_PARMS mciOpenParms;
    MCI_SET_PARMS mciSetParms;

    // Open the CD audio device by specifying the device name.
    mciOpenParms.lpstrDeviceType = "cdaudio";
//	mciOpenParms.dwCallback = MAKELONG(m_hWnd, 0);

    if (dwReturn = mciSendCommand(NULL, MCI_OPEN,
        MCI_OPEN_TYPE , (DWORD)(LPVOID) &mciOpenParms))//| MCI_NOTIFY
    {
        // Failed to open device. Don't close it; just return error.
        return (dwReturn);
    }

    // The device opened successfully; get the device ID.
    wCDDeviceID = mciOpenParms.wDeviceID;
	
    // Set the time format to track/minute/second/frame (TMSF).
    mciSetParms.dwTimeFormat = MCI_FORMAT_TMSF;
    if (dwReturn = mciSendCommand(wCDDeviceID, MCI_SET, 
        MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &mciSetParms))
    {
        mciSendCommand(wCDDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    } 

	return TRUE;
}
void CsurfView::stopCD()
{
	mciSendCommand(wCDDeviceID, MCI_STOP, 0, NULL);
}

DWORD CsurfView::playCDTrack(BYTE bTrack)
{
//	static BYTE lastCDtrack = 125;
	static BYTE lasttrack2 = 121;
	static BYTE lasttrack3 = 122;
	static BYTE lasttrack4 = 124;
	static BYTE lasttrack5 = 125;
	int i;
	if (!bSecretTrack)
	{
		if (bMusicRedundancyCheck)
		{
			while ((bTrack == lastCDtrack) ||
				(bTrack == lasttrack2) ||
				(bTrack == lasttrack3) ||
				(bTrack == lasttrack4) ||
				(bTrack == lasttrack5))
			{
				extraCDsong++;
				if (extraCDsong>16)
					extraCDsong = 10;
				bTrack = extraCDsong;
				i = randInt(0,30);
				if ((bTrack == lastCDtrack) ||
				(bTrack == lasttrack2) ||
				(bTrack == lasttrack3) ||
				(bTrack == lasttrack4) ||
				(bTrack == lasttrack5) ||
				(i < 2))
				{
					if (i == 0)
						bTrack = randInt(2,23);
					else
						bTrack = randInt(2,17);
				}
			}
		}
		lasttrack5 = lasttrack4;
		lasttrack4 = lasttrack3;
		lasttrack3 = lasttrack2;
		lasttrack2 = lastCDtrack;
		lastCDtrack = bTrack;

	    DWORD dwReturn;
		MCI_PLAY_PARMS mciPlayParms;
//		char buffer[256];

	//  Stop the CD Player
		mciSendCommand(wCDDeviceID, MCI_STOP, 0, NULL);
		mciSendCommand(wCDDeviceID, MCI_CLOSE, 0, NULL);
		setUpCD();

    //  Begin playback from the given track and play until the beginning 
    //  of the next track. The window procedure function for the parent 
    //  window will be notified with an MM_MCINOTIFY message when 
    //  playback is complete. Unless the play command fails, the window 
    //  procedure closes the device.

		if (bTrack != 0)
		{
		    mciPlayParms.dwFrom = 0L;
		    mciPlayParms.dwTo = 0L;
		    mciPlayParms.dwFrom = MCI_MAKE_TMSF(bTrack, 0, 0, 0);
		    mciPlayParms.dwTo = MCI_MAKE_TMSF(bTrack + (BYTE)1, 0, 0, 0);

		    if (dwReturn = mciSendCommand(wCDDeviceID, 
				MCI_PLAY,
			    MCI_FROM | 
				MCI_TO,
				(DWORD)(LPVOID) &mciPlayParms))
		    {
				if ((WORD)dwReturn != MCIERR_OUTOFRANGE)
				{
					OnCdMusic();
					return (dwReturn);
				}
				else while ((WORD)dwReturn == MCIERR_OUTOFRANGE)
				{
					if (bTrack == 0)
					{
						OnCdMusic();
						return (dwReturn);
					}

					bTrack = randInt(0,bTrack);
				    mciPlayParms.dwFrom = 0L;
				    mciPlayParms.dwTo = 0L;
				    mciPlayParms.dwFrom = MCI_MAKE_TMSF(bTrack, 0, 0, 0);
				    mciPlayParms.dwTo = MCI_MAKE_TMSF(bTrack + (BYTE)1, 0, 0, 0);

				    if (dwReturn = mciSendCommand(wCDDeviceID, 
						MCI_PLAY,
					    MCI_FROM | 
						MCI_TO,
						(DWORD)(LPVOID) &mciPlayParms))
					{
						if ((WORD)dwReturn != MCIERR_OUTOFRANGE)
						{
							OnCdMusic();
							return (dwReturn);
						}
					}
				}
				lastCDtrack = bTrack;
			}
		}
		else
		{
			mciPlayParms.dwFrom = 0L;
		    mciPlayParms.dwFrom = MCI_MAKE_TMSF(2, 0, 0, 0);

		    if (dwReturn = mciSendCommand(wCDDeviceID, 
				MCI_PLAY,
			    MCI_FROM, 
				(DWORD)(LPVOID) &mciPlayParms))
			{
//				mciGetErrorString(dwReturn, buffer, sizeof(buffer));
//				if (bShowErrors) MessageBox(buffer, "CD Error!");
				return (dwReturn);
			}
		}
	}
    return (0L);
}


//-----------------------------------------------------------------
// CMainFrame Message Handler Methods
//-----------------------------------------------------------------


/*************************************************************************
    Error reporting functions
 *************************************************************************/

/*
 * MyErrorToString
 * Returns a pointer to a string describing the given error code.
 */
char* CsurfView::MyErrorToString(HRESULT error)
{
    switch(error) {
        case DD_OK:
            return "No error.\0";
        case DDERR_ALREADYINITIALIZED:
            return "DDERR_ALREADYINITIALIZED: This object is already initialized.\0";
        case DDERR_BLTFASTCANTCLIP:
            return "DDERR_BLTFASTCANTCLIP: Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
        case DDERR_CANNOTATTACHSURFACE:
            return "DDERR_CANNOTATTACHSURFACE: This surface can not be attached to the requested surface.\0";
        case DDERR_CANNOTDETACHSURFACE:
            return "DDERR_CANNOTDETACHSURFACE: This surface can not be detached from the requested surface.\0";
        case DDERR_CANTCREATEDC:
            return "DDERR_CANTCREATEDC: Windows can not create any more DCs.\0";
        case DDERR_CANTDUPLICATE:
            return "DDERR_CANTDUPLICATE: Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
        case DDERR_CLIPPERISUSINGHWND:
            return "DDERR_CLIPPERISUSINGHWND: An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
        case DDERR_COLORKEYNOTSET:
            return "DDERR_COLORKEYNOTSET: No src color key specified for this operation.\0";
        case DDERR_CURRENTLYNOTAVAIL:
            return "DDERR_CURRENTLYNOTAVAIL: Support is currently not available.\0";
        case DDERR_DIRECTDRAWALREADYCREATED:
            return "DDERR_DIRECTDRAWALREADYCREATED: A DirectDraw object representing this driver has already been created for this process.\0";
        case DDERR_EXCEPTION:
            return "DDERR_EXCEPTION: An exception was encountered while performing the requested operation.\0";
        case DDERR_EXCLUSIVEMODEALREADYSET:
            return "DDERR_EXCLUSIVEMODEALREADYSET: An attempt was made to set the cooperative level when it was already set to exclusive.\0";
        case DDERR_GENERIC:
            return "DDERR_GENERIC: Generic failure.\0";
        case DDERR_HEIGHTALIGN:
            return "DDERR_HEIGHTALIGN: Height of rectangle provided is not a multiple of reqd alignment.\0";
        case DDERR_HWNDALREADYSET:
            return "DDERR_HWNDALREADYSET: The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
        case DDERR_HWNDSUBCLASSED:
            return "DDERR_HWNDSUBCLASSED: HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
        case DDERR_IMPLICITLYCREATED:
            return "DDERR_IMPLICITLYCREATED: This surface can not be restored because it is an implicitly created surface.\0";
        case DDERR_INCOMPATIBLEPRIMARY:
            return "DDERR_INCOMPATIBLEPRIMARY: Unable to match primary surface creation request with existing primary surface.\0";
        case DDERR_INVALIDCAPS:
            return "DDERR_INVALIDCAPS: One or more of the caps bits passed to the callback are incorrect.\0";
        case DDERR_INVALIDCLIPLIST:
            return "DDERR_INVALIDCLIPLIST: DirectDraw does not support the provided cliplist.\0";
        case DDERR_INVALIDDIRECTDRAWGUID:
            return "DDERR_INVALIDDIRECTDRAWGUID: The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
        case DDERR_INVALIDMODE:
            return "DDERR_INVALIDMODE: DirectDraw does not support the requested mode.\0";
        case DDERR_INVALIDOBJECT:
            return "DDERR_INVALIDOBJECT: DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
        case DDERR_INVALIDPARAMS:
            return "DDERR_INVALIDPARAMS: One or more of the parameters passed to the function are incorrect.\0";
        case DDERR_INVALIDPIXELFORMAT:
            return "DDERR_INVALIDPIXELFORMAT: The pixel format was invalid as specified.\0";
        case DDERR_INVALIDPOSITION:
            return "DDERR_INVALIDPOSITION: Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
        case DDERR_INVALIDRECT:
            return "DDERR_INVALIDRECT: Rectangle provided was invalid.\0";
        case DDERR_LOCKEDSURFACES:
            return "DDERR_LOCKEDSURFACES: Operation could not be carried out because one or more surfaces are locked.\0";
        case DDERR_NO3D:
            return "DDERR_NO3D: There is no 3D present.\0";
        case DDERR_NOALPHAHW:
            return "DDERR_NOALPHAHW: Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
        case DDERR_NOBLTHW:
            return "DDERR_NOBLTHW: No blitter hardware present.\0";
        case DDERR_NOCLIPLIST:
            return "DDERR_NOCLIPLIST: No cliplist available.\0";
        case DDERR_NOCLIPPERATTACHED:
            return "DDERR_NOCLIPPERATTACHED: No clipper object attached to surface object.\0";
        case DDERR_NOCOLORCONVHW:
            return "DDERR_NOCOLORCONVHW: Operation could not be carried out because there is no color conversion hardware present or available.\0";
        case DDERR_NOCOLORKEY:
            return "DDERR_NOCOLORKEY: Surface doesn't currently have a color key\0";
        case DDERR_NOCOLORKEYHW:
            return "DDERR_NOCOLORKEYHW: Operation could not be carried out because there is no hardware support of the destination color key.\0";
        case DDERR_NOCOOPERATIVELEVELSET:
            return "DDERR_NOCOOPERATIVELEVELSET: Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
        case DDERR_NODC:
            return "DDERR_NODC: No DC was ever created for this surface.\0";
        case DDERR_NODDROPSHW:
            return "DDERR_NODDROPSHW: No DirectDraw ROP hardware.\0";
        case DDERR_NODIRECTDRAWHW:
            return "DDERR_NODIRECTDRAWHW: A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
        case DDERR_NOEMULATION:
            return "DDERR_NOEMULATION: Software emulation not available.\0";
        case DDERR_NOEXCLUSIVEMODE:
            return "DDERR_NOEXCLUSIVEMODE: Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
        case DDERR_NOFLIPHW:
            return "DDERR_NOFLIPHW: Flipping visible surfaces is not supported.\0";
        case DDERR_NOGDI:
            return "DDERR_NOGDI: There is no GDI present.\0";
        case DDERR_NOHWND:
            return "DDERR_NOHWND: Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
        case DDERR_NOMIRRORHW:
            return "DDERR_NOMIRRORHW: Operation could not be carried out because there is no hardware present or available.\0";
        case DDERR_NOOVERLAYDEST:
            return "DDERR_NOOVERLAYDEST: Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
        case DDERR_NOOVERLAYHW:
            return "DDERR_NOOVERLAYHW: Operation could not be carried out because there is no overlay hardware present or available.\0";
        case DDERR_NOPALETTEATTACHED:
            return "DDERR_NOPALETTEATTACHED: No palette object attached to this surface.\0";
        case DDERR_NOPALETTEHW:
            return "DDERR_NOPALETTEHW: No hardware support for 16 or 256 color palettes.\0";
        case DDERR_NORASTEROPHW:
            return "DDERR_NORASTEROPHW: Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
        case DDERR_NOROTATIONHW:
            return "DDERR_NOROTATIONHW: Operation could not be carried out because there is no rotation hardware present or available.\0";
        case DDERR_NOSTRETCHHW:
            return "DDERR_NOSTRETCHHW: Operation could not be carried out because there is no hardware support for stretching.\0";
        case DDERR_NOT4BITCOLOR:
            return "DDERR_NOT4BITCOLOR: DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
        case DDERR_NOT4BITCOLORINDEX:
            return "DDERR_NOT4BITCOLORINDEX: DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
        case DDERR_NOT8BITCOLOR:
            return "DDERR_NOT8BITCOLOR: DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
        case DDERR_NOTAOVERLAYSURFACE:
            return "DDERR_NOTAOVERLAYSURFACE: Returned when an overlay member is called for a non-overlay surface.\0";
        case DDERR_NOTEXTUREHW:
            return "DDERR_NOTEXTUREHW: Operation could not be carried out because there is no texture mapping hardware present or available.\0";
        case DDERR_NOTFLIPPABLE:
            return "DDERR_NOTFLIPPABLE: An attempt has been made to flip a surface that is not flippable.\0";
        case DDERR_NOTFOUND:
            return "DDERR_NOTFOUND: Requested item was not found.\0";
        case DDERR_NOTLOCKED:
            return "DDERR_NOTLOCKED: Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
        case DDERR_NOTPALETTIZED:
            return "DDERR_NOTPALETTIZED: The surface being used is not a palette-based surface.\0";
        case DDERR_NOVSYNCHW:
            return "DDERR_NOVSYNCHW: Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
        case DDERR_NOZBUFFERHW:
            return "DDERR_NOZBUFFERHW: Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
        case DDERR_NOZOVERLAYHW:
            return "DDERR_NOZOVERLAYHW: Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
        case DDERR_OUTOFCAPS:
            return "DDERR_OUTOFCAPS: The hardware needed for the requested operation has already been allocated.\0";
        case DDERR_OUTOFMEMORY:
            return "DDERR_OUTOFMEMORY: DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OUTOFVIDEOMEMORY:
            return "DDERR_OUTOFVIDEOMEMORY: DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OVERLAYCANTCLIP:
            return "DDERR_OVERLAYCANTCLIP: The hardware does not support clipped overlays.\0";
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
            return "DDERR_OVERLAYCOLORKEYONLYONEACTIVE: Can only have ony color key active at one time for overlays.\0";
        case DDERR_OVERLAYNOTVISIBLE:
            return "DDERR_OVERLAYNOTVISIBLE: Returned when GetOverlayPosition is called on a hidden overlay.\0";
        case DDERR_PALETTEBUSY:
            return "DDERR_PALETTEBUSY: Access to this palette is being refused because the palette is already locked by another thread.\0";
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return "DDERR_PRIMARYSURFACEALREADYEXISTS: This process already has created a primary surface.\0";
        case DDERR_REGIONTOOSMALL:
            return "DDERR_REGIONTOOSMALL: Region passed to Clipper::GetClipList is too small.\0";
        case DDERR_SURFACEALREADYATTACHED:
            return "DDERR_SURFACEALREADYATTACHED: This surface is already attached to the surface it is being attached to.\0";
        case DDERR_SURFACEALREADYDEPENDENT:
            return "DDERR_SURFACEALREADYDEPENDENT: This surface is already a dependency of the surface it is being made a dependency of.\0";
        case DDERR_SURFACEBUSY:
            return "DDERR_SURFACEBUSY: Access to this surface is being refused because the surface is already locked by another thread.\0";
        case DDERR_SURFACEISOBSCURED:
            return "DDERR_SURFACEISOBSCURED: Access to surface refused because the surface is obscured.\0";
        case DDERR_SURFACELOST:
            return "DDERR_SURFACELOST: Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
        case DDERR_SURFACENOTATTACHED:
            return "DDERR_SURFACENOTATTACHED: The requested surface is not attached.\0";
        case DDERR_TOOBIGHEIGHT:
            return "DDERR_TOOBIGHEIGHT: Height requested by DirectDraw is too large.\0";
        case DDERR_TOOBIGSIZE:
            return "DDERR_TOOBIGSIZE: Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
        case DDERR_TOOBIGWIDTH:
            return "DDERR_TOOBIGWIDTH: Width requested by DirectDraw is too large.\0";
        case DDERR_UNSUPPORTED:
            return "DDERR_UNSUPPORTED: Action not supported.\0";
        case DDERR_UNSUPPORTEDFORMAT:
            return "DDERR_UNSUPPORTEDFORMAT: FOURCC format requested is unsupported by DirectDraw.\0";
        case DDERR_UNSUPPORTEDMASK:
            return "DDERR_UNSUPPORTEDMASK: Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
        case DDERR_VERTICALBLANKINPROGRESS:
            return "DDERR_VERTICALBLANKINPROGRESS: Vertical blank is in progress.\0";
        case DDERR_WASSTILLDRAWING:
            return "DDERR_WASSTILLDRAWING: Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
        case DDERR_WRONGMODE:
            return "DDERR_WRONGMODE: This surface can not be restored because it was created in a different mode.\0";
        case DDERR_XALIGN:
            return "DDERR_XALIGN: Rectangle provided was not horizontally aligned on required boundary.\0";
        case D3DERR_EXECUTE_LOCKED:
            return "D3DERR_EXECUTE_LOCKED\0";
        case D3DERR_EXECUTE_NOT_LOCKED:
            return "D3DERR_EXECUTE_NOT_LOCKED\0";
        case D3DERR_EXECUTE_CREATE_FAILED:
            return "D3DERR_EXECUTE_CREATE_FAILED\0";
        case D3DERR_EXECUTE_DESTROY_FAILED:
            return "D3DERR_EXECUTE_DESTROY_FAILED\0";
        case D3DERR_EXECUTE_LOCK_FAILED:
            return "D3DERR_EXECUTE_LOCK_FAILED\0";
        case D3DERR_EXECUTE_UNLOCK_FAILED:
            return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
        case D3DERR_EXECUTE_FAILED:
            return "D3DERR_EXECUTE_FAILED\0";
        case D3DERR_EXECUTE_CLIPPED_FAILED:
            return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
        case D3DERR_TEXTURE_NO_SUPPORT:
            return "D3DERR_TEXTURE_NO_SUPPORT\0";
        case D3DERR_TEXTURE_NOT_LOCKED:
            return "D3DERR_TEXTURE_NOT_LOCKED\0";
        case D3DERR_TEXTURE_LOCKED:
            return "D3DERR_TEXTURELOCKED\0";
        case D3DERR_TEXTURE_CREATE_FAILED:
            return "D3DERR_TEXTURE_CREATE_FAILED\0";
        case D3DERR_TEXTURE_DESTROY_FAILED:
            return "D3DERR_TEXTURE_DESTROY_FAILED\0";
        case D3DERR_TEXTURE_LOCK_FAILED:
            return "D3DERR_TEXTURE_LOCK_FAILED\0";
        case D3DERR_TEXTURE_UNLOCK_FAILED:
            return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
        case D3DERR_TEXTURE_LOAD_FAILED:
            return "D3DERR_TEXTURE_LOAD_FAILED\0";
        case D3DERR_MATRIX_CREATE_FAILED:
            return "D3DERR_MATRIX_CREATE_FAILED\0";
        case D3DERR_MATRIX_DESTROY_FAILED:
            return "D3DERR_MATRIX_DESTROY_FAILED\0";
        case D3DERR_MATRIX_SETDATA_FAILED:
            return "D3DERR_MATRIX_SETDATA_FAILED\0";
        case D3DERR_SETVIEWPORTDATA_FAILED:
            return "D3DERR_SETVIEWPORTDATA_FAILED\0";
        case D3DERR_MATERIAL_CREATE_FAILED:
            return "D3DERR_MATERIAL_CREATE_FAILED\0";
        case D3DERR_MATERIAL_DESTROY_FAILED:
            return "D3DERR_MATERIAL_DESTROY_FAILED\0";
        case D3DERR_MATERIAL_SETDATA_FAILED:
            return "D3DERR_MATERIAL_SETDATA_FAILED\0";
        case D3DERR_LIGHT_SET_FAILED:
            return "D3DERR_LIGHT_SET_FAILED\0";
		case D3DRMERR_BADALLOC:
			return "D3DRMERR_BADALLOC - Out of memory.\0";
		case D3DRMERR_BADDEVICE:
			return "D3DRMERR_BADDEVICE - Device is not compatible with renderer.\0";
		case D3DRMERR_BADFILE:
			return "D3DRMERR_BADFILE - Data file is corrupt.\0";
		case D3DRMERR_BADMAJORVERSION:
			return "D3DRMERR_BADMAJORVERSION - Bad DLL major version.\0";
		case D3DRMERR_BADMINORVERSION:
			return "D3DRMERR_BADMINORVERSION - Bad DLL minor version.\0";
		case D3DRMERR_BADOBJECT:
			return "D3DRMERR_BADOBJECT - Object expected in argument.\0";
		case D3DRMERR_BADTYPE:
			return "D3DRMERR_BADTYPE - Bad argument type passed.\0";
		case D3DRMERR_BADVALUE:
			return "D3DRMERR_BADVALUE - Bad argument value passed.\0";
		case D3DRMERR_FACEUSED:
			return "D3DRMERR_FACEUSED - Face already used in a mesh.\0";
		case D3DRMERR_FILENOTFOUND:
			return "D3DRMERR_FILENOTFOUND - File cannot be opened.\0";
		case D3DRMERR_NOTDONEYET:
			return "D3DRMERR_NOTDONEYET - Unimplemented.\0";
		case D3DRMERR_NOTFOUND:
			return "D3DRMERR_NOTFOUND - Object not found in the specified place.\0";
		case D3DRMERR_UNABLETOEXECUTE:
			return "D3DRMERR_UNABLETOEXECUTE - Unable to carry out the specified procedure.\0";
		case DPERR_ACCESSDENIED:
			return "DPERR_ACCESSDENIED - The session is full or an incorrect password was supplied.\0";
		case DPERR_ACTIVEPLAYERS:
			return "DPERR_ACTIVEPLAYERS - The requested operation cannot be performed because there are existing active players.\0";
		case DPERR_ALREADYINITIALIZED:
			return "DPERR_ALREADYINITIALIZED - This object is already initialized.\0";
		case DPERR_CANTADDPLAYER:
			return "DPERR_CANTADDPLAYER - The player cannot be added to the session.\0";
		case DPERR_CANTCREATEPLAYER:
			return "DPERR_CANTCREATEPLAYER - A new player cannot be created.\0";
		case DPERR_CAPSNOTAVAILABLEYET:
			return "DPERR_CAPSNOTAVAILABLEYET - The capabilities of the DirectPlay object have not been determined yet. This error will occur if the DirectPlay object is implemented on a connectivity solution that requires polling to determine available bandwidth and latency.\0";
		case DPERR_EXCEPTION:
			return "DPERR_EXCEPTION - An exception occurred when processing the request.\0";
//		case DPERR_GENERIC:
//			return "DPERR_GENERIC - An undefined error condition occurred.\0";
		case DPERR_INVALIDFLAGS:
			return "DPERR_INVALIDFLAGS - The flags passed to this function are invalid.\0";
		case DPERR_INVALIDOBJECT:
			return "DPERR_INVALIDOBJECT - The DirectPlay object pointer is invalid.\0";
//		case DPERR_INVALIDPARAMS:
//			return "DPERR_INVALIDPARAMS - One or more of the parameters passed to the function are invalid.\0";
		case DPERR_INVALIDPLAYER:
			return "DPERR_INVALIDPLAYER - The player ID is not recognized as a valid player ID for this game session.\0";
		case DPERR_NOCAPS:
			return "DPERR_NOCAPS - The communication link underneath DirectPlay is not capable of this function.\0";
		case DPERR_NOCONNECTION:
			return "DPERR_NOCONNECTION - No communication link was established.\0";
		case DPERR_NOMESSAGES:
			return "DPERR_NOMESSAGES - There are no messages to be received.\0";
		case DPERR_NONAMESERVERFOUND:
			return "DPERR_NONAMESERVERFOUND - No name server could be found or created. A name server must exist in order to create a player.\0";
		case DPERR_NOPLAYERS:
			return "DPERR_NOPLAYERS - There are no active players in the session.\0";
		case DPERR_NOSESSIONS:
			return "DPERR_NOSESSIONS - There are no existing sessions for this game.\0";
//		case DPERR_OUTOFMEMORY:
//			return "DPERR_OUTOFMEMORY - There is insufficient memory to perform the requested operation.\0";
		case DPERR_SENDTOOBIG:
			return "DPERR_SENDTOOBIG - The message buffer passed to the IDirectPlay::Send method is larger than allowed.\0";
		case DPERR_TIMEOUT:
			return "DPERR_TIMEOUT - The operation could not be completed in the specified time.\0";
		case DPERR_UNAVAILABLE:
			return "DPERR_UNAVAILABLE - The requested service provider or session is not available.\0";
//		case DPERR_UNSUPPORTED:
//			return "DPERR_UNSUPPORTED - The function is not available in this implementation.\0";
		case DPERR_USERCANCEL:
			return "DPERR_USERCANCEL - The user canceled the connection process during a call to the IDirectPlay::Open method.\0";
        default:
            return "Unrecognized error value.\0";
    }
}


void CsurfView::OnMove() 
{
	if (!bFullscreen)
	{
		RECT r;
		::GetWindowRect(m_hWnd, &r);

		ModeAx = r.left+2;
		ModeAy = r.top+2;
		ModeBx = ModeCx+ModeAx;
		ModeBy = ModeCy+ModeAy;
	}
	ResetFps();
	bResizedSelect = TRUE;
}

// menu stuff

void CsurfView::OnBreakingwave() 
{
	bBreakingWave = !bBreakingWave;
	if (!bContest)
	{
		if (!bBreakingWave)
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_BREAKINGWAVE, MF_BYCOMMAND | MF_UNCHECKED);
			m_scene->DeleteChild(curl_frame);
			bPitch = FALSE;
			bDrop = FALSE;
			bCloseOut = FALSE;
			for (int i = 0; i < NUMFOAM; i++)
				foam[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
		}
		else
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_BREAKINGWAVE, MF_BYCOMMAND | MF_CHECKED);
			if (!bCharselect)
			{
				m_scene->AddChild(curl_frame);
//				curl_frame->SetOrientation(m_scene, (const float)0, (const float)0, (const float)1, (const float)0, (const float)1, (const float)0);
//				curl_frame->SetRotation(curl_frame, D3DVALUE(-1), D3DVALUE(0), D3DVALUE(0.0), D3DVALUE(0.04));
			}
//			bPitch = TRUE;
		}
	}
	ResetFps();
}

void CsurfView::OnTronmode() 
{
	int old_dither = m_lpDev->GetDither();
	int old_shades = m_lpDev->GetShades();

	if (m_view != NULL)
	{
		m_view->Release();
		m_view = NULL;
	}

	if (bTron)
	{
		bTron = FALSE;
		m_lpDev->SetQuality(D3DRMRENDER_GOURAUD);
	}
	else
	{
		bTron = TRUE;
		m_lpDev->SetQuality(D3DRMRENDER_WIREFRAME);
	}
	m_lpDev->SetDither(old_dither);
	m_lpDev->SetShades(old_shades);
	m_lpDev->SetTextureQuality(TextureFiltering);
//    m_lprm->SetDefaultTextureColors(128);
//    m_lprm->SetDefaultTextureShades(128);

	if (bCharselect)
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
			INTR_VRIGHT, INTR_VBOTTOM, &m_view);

	    m_view->SetBack(D3DVAL(INTR_BACK));
	}
	else
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
			m_lpDev->GetWidth(),
			m_lpDev->GetHeight(), &m_view);
	    m_view->SetBack(D3DVAL(GAME_BACK));
	}
	if (bSoundFx)
		m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);
	ResetFps();
}

void CsurfView::OnHalfres() 
{
	int old_dither = m_lpDev->GetDither();
	D3DRMRENDERQUALITY old_quality = m_lpDev->GetQuality();
	int old_shades = m_lpDev->GetShades();

	BOOL LastError;

	if (m_view != NULL)
	{
		m_view->Release();
		m_view = NULL;
	}
//	m_lpDev->Release();

	if (bHalfres)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_HALFRES, MF_BYCOMMAND | MF_UNCHECKED);
		bHalfres = FALSE;

	    LastError = FindDevice(lpBackBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return;
	    }
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_HALFRES, MF_BYCOMMAND | MF_CHECKED);
		bHalfres = TRUE;

		LastError = FindDevice(lpHalfresBuffer);
	    if(LastError != DD_OK ) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "CreateDeviceFromSurface failed");
	        return;
	    }
	}
	m_lpDev->SetDither(old_dither);
	m_lpDev->SetQuality(old_quality);
	m_lpDev->SetShades(old_shades);
	m_lpDev->SetTextureQuality(TextureFiltering);
//  m_lprm->SetDefaultTextureColors(128);
//  m_lprm->SetDefaultTextureShades(128);
	if (bCharselect)
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
			INTR_VRIGHT, INTR_VBOTTOM, &m_view);
	    m_view->SetBack(D3DVAL(INTR_BACK));
	}
	else
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
			m_lpDev->GetWidth(),
			m_lpDev->GetHeight(), &m_view);
	    m_view->SetBack(D3DVAL(GAME_BACK));
	}

	if (bSoundFx)
		m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);
	SaveStats();
	ResetFps();
}

void CsurfView::OnSkymap() 
{
	if (bSky)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SKYMAP, MF_BYCOMMAND | MF_UNCHECKED);
		m_view->ForceUpdate(0, 0, ModeCx, ModeCy);
		bSky = FALSE;
	}	
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SKYMAP, MF_BYCOMMAND | MF_CHECKED);
		bSky = TRUE;
	}	
	SaveStats();
	ResetFps();
}

void CsurfView::OnWaveTextures() 
{
	if (bWaveTextures)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_WAVE_TEXTURES, MF_BYCOMMAND | MF_UNCHECKED);
		bWaveTextures = FALSE;
		wave_builder->SetColorRGB(D3DVALUE(0.2), D3DVALUE(0.2), D3DVALUE(0.8));
		curlr_builder->SetColorRGB(D3DVALUE(0.2), D3DVALUE(0.2), D3DVALUE(0.8));
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_WAVE_TEXTURES, MF_BYCOMMAND | MF_CHECKED);
		bWaveTextures = TRUE;
		wave_builder->SetColorRGB(D3DVALUE(1), D3DVALUE(1), D3DVALUE(1));
		curlr_builder->SetColorRGB(D3DVALUE(1), D3DVALUE(1), D3DVALUE(1));
	}
	SaveStats();
	ResetFps();
}

void CsurfView::OnSpeedometerToggle() 
{
	if (bSpeedofish)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SPEEDOMETER_TOGGLE, MF_BYCOMMAND | MF_UNCHECKED);
		bSpeedofish = FALSE;
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SPEEDOMETER_TOGGLE, MF_BYCOMMAND | MF_CHECKED);
		bSpeedofish = TRUE;
	}
	SaveStats();
	ResetFps();
}

void CsurfView::OnScoreToggle() 
{
	if (bScoreBlit)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SCORETOGGLE, MF_BYCOMMAND | MF_UNCHECKED);
		bScoreBlit = FALSE;
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SCORETOGGLE, MF_BYCOMMAND | MF_CHECKED);
		bScoreBlit= TRUE;
	}
	SaveStats();
	ResetFps();
}

void CsurfView::OnShowErrors() 
{
	bShowErrors = !bShowErrors;
	if (bShowErrors)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_FILE), ID_SHOW_ERRORS, MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_FILE), ID_SHOW_ERRORS, MF_BYCOMMAND | MF_UNCHECKED);
	}
	SaveStats();
	ResetFps();
}

void CsurfView::UncheckCameraMenu()
{
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_MAIN_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_HELICOPTER_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_TUBE_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_BEACH_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_BEACH_CAMERA2, MF_BYCOMMAND | MF_UNCHECKED);
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_SATELLITE_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_ROCK_VIDEO_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
}

void CsurfView::OnBeachCamera() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_BEACH_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = BEACH_CAMERA;
	SaveStats();
}

void CsurfView::OnBeachCamera2() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_BEACH_CAMERA2, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = BEACH_CAMERA2;
	SaveStats();
}

void CsurfView::OnHelicopterCamera() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_HELICOPTER_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = HELICOPTER_CAMERA;
	SaveStats();
}

void CsurfView::OnMainCamera() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_MAIN_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = MAIN_CAMERA;
	SaveStats();
}

void CsurfView::OnRockVideoCamera() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_ROCK_VIDEO_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = ROCK_VIDEO_CAMERA;
	SaveStats();
}


void CsurfView::OnSatelliteCamera() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_SATELLITE_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = SATELLITE_CAMERA;
	SaveStats();
}

void CsurfView::OnTubeCamera() 
{
	UncheckCameraMenu();
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_TUBE_CAMERA, MF_BYCOMMAND | MF_CHECKED);
	last_camera = camera_type = TUBE_CAMERA;
	SaveStats();
}

void CsurfView::OnAutoCamera() 
{
	bAutoCamera = !bAutoCamera;
	if (bAutoCamera)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_AUTO_CAMERA, MF_BYCOMMAND | MF_CHECKED);
		last_camera = camera_type;
	}
	else
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_CAMERAS), ID_AUTO_CAMERA, MF_BYCOMMAND | MF_UNCHECKED);
	SaveStats();
}

void CsurfView::GoToFullscreen(BOOL bReleased)
{
	char ss[10];
	bFullscreen = TRUE;
	ModeCx = ModeListW[ModeNumber];
	ModeCy = ModeListH[ModeNumber];
	sprintf(ss, "%d",ModeCx);
	WritePrivateProfileString("ScreenMode","Width",ss,"wildride.ini");
	sprintf(ss, "%d",ModeCy);
	WritePrivateProfileString("ScreenMode","Height",ss,"wildride.ini");
// do the funky shit here
	if (!bReleased)
	{
		ReleaseSomeStuff();
		ReleaseSurfaces();
	}
	if (!DDInit())
	{	
		FullscreenFailed(TRUE);
		return;
	}
    if (!DDSetMode())
	{
		FullscreenFailed(TRUE);
        return;
	}
    if (!D3DRMSetMode())
	{
		FullscreenFailed(TRUE);
        return;
	}
	if (bCharselect)
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, INTR_VLEFT, INTR_VTOP,
			INTR_VRIGHT, INTR_VBOTTOM, &m_view);
	    m_view->SetBack(D3DVAL(INTR_BACK));
	}
	else
	{
	    m_lprm->CreateViewport(m_lpDev, m_camera, 0, 0,
			m_lpDev->GetWidth(),
			m_lpDev->GetHeight(), &m_view);
	    m_view->SetBack(D3DVAL(GAME_BACK));
	}

	if (bSoundFx)
		m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);

	RestoreSurfaces();
	if (bCharselect)
		bResizedSelect = TRUE;
	ResetFps();
}

void CsurfView::FullscreenFailed(BOOL bReleased)
{
	int i;
	HRESULT LastError;
	if (!bReleased)
	{
		ReleaseSomeStuff();
		ReleaseSurfaces();
	}
	lpDD->RestoreDisplayMode();	
    
    LastError = lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
    if( LastError != DD_OK )
    {
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Set Cooperation Level failed.");
        return;
    }

	bFullscreen = FALSE;
	if (lpDDGuid[DDDriverNum[D3DDriver]] != NULL)
	{
		i = LastD3DDriver;
		LastD3DDriver = D3DDriver;
		D3DDriver = i;
		if (lpDDGuid[DDDriverNum[D3DDriver]] != NULL)
		{
			LastD3DDriver = D3DDriver;
			D3DDriver = 0;
		}
		ChangeDriver(TRUE);
		return;
	}

	CreateDevice();

	if (bSoundFx)
		m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);

	RestoreSurfaces();
	if (bCharselect)
	{
		bResizedSelect = TRUE;
		fullscreencountdown = 2;
	}
	ResetFps();
}

void CsurfView::OnFullscreen0() 
{
	ModeNumber = 0;
	SaveScreenDimensions();
	GoToFullscreen(FALSE);
}

void CsurfView::OnFullscreen1() 
{
	if (NumModes > 1)
	{
		ModeNumber = 1;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen2() 
{
	if (NumModes > 2)
	{
		ModeNumber = 2;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen3() 
{
	if (NumModes > 3)
	{
		ModeNumber = 3;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen4() 
{
	if (NumModes > 4)
	{
		ModeNumber = 4;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen5() 
{
	if (NumModes > 5)
	{
		ModeNumber = 5;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen6() 
{
	if (NumModes > 6)
	{
		ModeNumber = 6;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen7() 
{
	if (NumModes > 7)
	{
		ModeNumber = 7;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen8() 
{
	if (NumModes > 8)
	{
		ModeNumber = 8;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen9() 
{
	if (NumModes > 9)
	{
		ModeNumber = 9;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen10() 
{
	if (NumModes > 10)
	{
		ModeNumber = 10;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen11() 
{
	if (NumModes > 11)
	{
		ModeNumber = 11;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen12() 
{
	if (NumModes > 12)
	{
		ModeNumber = 12;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen13() 
{
	if (NumModes > 13)
	{
		ModeNumber = 13;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen14() 
{
	if (NumModes > 14)
	{
		ModeNumber = 14;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::OnFullscreen15() 
{
	if (NumModes > 15)
	{
		ModeNumber = 15;
		SaveScreenDimensions();
		GoToFullscreen(FALSE);
	}
}

void CsurfView::ChangeDriver(BOOL bReleased)
{
	int i;
#ifndef NO_VOODOO
	BOOL LastError;
#endif
	lpDD->RestoreDisplayMode();
	LastDDDriver = CurrentDDDriver;
	CurrentDDDriver = DDDriverNum[D3DDriver];

	if (!bReleased)
	{
		ReleaseSomeStuff();
		ReleaseSurfaces();
	}
#ifndef NO_VOODOO
	if (CurrentDDDriver != LastDDDriver)
	{
//		lpDD->Release();
	    LastError = DirectDrawCreate(lpDDGuid[CurrentDDDriver], &lpDD, NULL);
	    if (LastError != DD_OK) 
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "DirectDrawCreate failed.");
			// clean up and exit
			PostQuitMessage(0);
			return;
//		    return FALSE;
	    }
	}
	if (lpDDGuid[CurrentDDDriver] != NULL)
	{
		bFullscreen = TRUE;
		GoToFullscreen(TRUE);
	}
	else
#endif
	{
		bFullscreen = FALSE;
		// save some stats
		for (i = 0; i < NumD3DDrivers; i++)
		{
			::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_DRIVERS), ID_DRIVER0+i, MF_BYCOMMAND | MF_UNCHECKED);
		}
		::CheckMenuItem(::GetSubMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS),MENU_DRIVERS), ID_DRIVER0+D3DDriver, MF_BYCOMMAND | MF_CHECKED);
		CreateDevice();
		if (bSoundFx)
			m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);

		RestoreSurfaces();
		ResetFps();
		if (bCharselect)
		{
			bResizedSelect = TRUE;
			fullscreencountdown = 2;
		}
	}
	SaveStats();
}

void CsurfView::SaveScreenDimensions()
{
	RECT r;
	char ss[10];
	if (!bMinimized && !bMaximized)
	{
		::GetWindowRect(::GetParent(m_hWnd), &r);
		if (((r.right-r.left) < ModeCx) 
			|| ((r.right-r.left) > ModeCx + 100) 
			|| ((r.bottom-r.top) < ModeCy) 
			|| ((r.bottom-r.top) > ModeCy + 100))
				return;
		sprintf(ss, "%d",(r.right-r.left));
		WritePrivateProfileString("ScreenMode","WindowWidth",ss,"wildride.ini");
		sprintf(ss, "%d",(r.bottom-r.top));
		WritePrivateProfileString("ScreenMode","WindowHeight",ss,"wildride.ini");
		sprintf(ss, "%d",r.left);
		WritePrivateProfileString("ScreenMode","WindowXPos",ss,"wildride.ini");
		sprintf(ss, "%d",r.top);
		WritePrivateProfileString("ScreenMode","WindowYPos",ss,"wildride.ini");
		sprintf(ss, "%d",ModeAx);
		WritePrivateProfileString("ScreenMode","ClientX1",ss,"wildride.ini");
		sprintf(ss, "%d",ModeAy);
		WritePrivateProfileString("ScreenMode","ClientY1",ss,"wildride.ini");
		sprintf(ss, "%d",ModeBx);
		WritePrivateProfileString("ScreenMode","ClientX2",ss,"wildride.ini");
		sprintf(ss, "%d",ModeBy);
		WritePrivateProfileString("ScreenMode","ClientY2",ss,"wildride.ini");
	}
}	

void CsurfView::ReleaseSurfaces()
{
	if (lpSkySource)
	{
		lpSkySource->Release();
		lpSkySource = NULL;
	}
	if (lpNavBar)
	{
		lpNavBar->Release();
		lpNavBar = NULL;
	}
	if (lpLogo)
	{
		lpLogo->Release();
		lpLogo = NULL;
	}
	if (lpSpeedometer)
	{
		lpSpeedometer->Release();
		lpSpeedometer = NULL;
	}
	if (lpAlphabet)
	{
		lpAlphabet->Release();
		lpAlphabet = NULL;
	}
	if (lpIntrBkg)
	{
		lpIntrBkg->Release();
		lpIntrBkg = NULL;
	}
}

void CsurfView::OnDriver0() 
{
	if ((lpDDGuid[DDDriverNum[0]] != NULL) && bCharselect)
		return;
	LastD3DDriver = D3DDriver;
	D3DDriver = 0;
	if (LastD3DDriver != D3DDriver)
	{
		SaveScreenDimensions();
		ChangeDriver(FALSE);
	}
	SaveStats();
}

void CsurfView::OnDriver1() 
{
	if (NumD3DDrivers > 1)
	{
		if ((lpDDGuid[DDDriverNum[1]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 1;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver2() 
{
	if (NumD3DDrivers > 2)
	{
		if ((lpDDGuid[DDDriverNum[2]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 2;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver3() 
{
	if (NumD3DDrivers > 3)
	{
		if ((lpDDGuid[DDDriverNum[3]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 3;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver4() 
{
	if (NumD3DDrivers > 4)
	{
		if ((lpDDGuid[DDDriverNum[4]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 4;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver5() 
{
	if (NumD3DDrivers > 5)
	{
		if ((lpDDGuid[DDDriverNum[5]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 5;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver6() 
{
	if (NumD3DDrivers > 6)
	{
		if ((lpDDGuid[DDDriverNum[6]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 6;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver7() 
{
	if (NumD3DDrivers > 7)
	{
		if ((lpDDGuid[DDDriverNum[7]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 7;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver8() 
{
	if (NumD3DDrivers > 8)
	{
		if ((lpDDGuid[DDDriverNum[8]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 8;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver9() 
{
	if (NumD3DDrivers > 9)
	{
		if ((lpDDGuid[DDDriverNum[9]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 9;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver10() 
{
	if (NumD3DDrivers > 10)
	{
		if ((lpDDGuid[DDDriverNum[10]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 10;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver11() 
{
	if (NumD3DDrivers > 11)
	{
		if ((lpDDGuid[DDDriverNum[11]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 11;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver12() 
{
	if (NumD3DDrivers > 12)
	{
		if ((lpDDGuid[DDDriverNum[12]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 12;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver13() 
{
	if (NumD3DDrivers > 13)
	{
		if ((lpDDGuid[DDDriverNum[13]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 13;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver14() 
{
	if (NumD3DDrivers > 14)
	{
		if ((lpDDGuid[DDDriverNum[14]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 14;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnDriver15() 
{
	if (NumD3DDrivers > 15)
	{
		if ((lpDDGuid[DDDriverNum[15]] != NULL) && bCharselect)
			return;
		LastD3DDriver = D3DDriver;
		D3DDriver = 15;
		if (LastD3DDriver != D3DDriver)
		{
			SaveScreenDimensions();
			ChangeDriver(FALSE);
		}
		SaveStats();
	}
}

void CsurfView::OnFps() 
{
	bFps = !bFps;
	if (bFps)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_FPS, MF_BYCOMMAND | MF_CHECKED);
	else
	{
		if (bCharselect)
			bResizedSelect = TRUE;
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_FPS, MF_BYCOMMAND | MF_UNCHECKED);
	}
	ResetFps();
}

void CsurfView::OnViewHiscores() 
{
	char stringy[250];
	if (bContest)
	{
		sprintf(stringy, "CONTEST MODE!\n1st : %d - %s using %s\n2nd : %d - %s using %s\n3rd : %d - %s using %s\n4th : %d - %s using %s\n5th : %d - %s using %s\n6th : %d - %s using %s",
			(int)hiscorec[0],hinamec[0],names[hisurferc[0]],
			(int)hiscorec[1],hinamec[1],names[hisurferc[1]],
			(int)hiscorec[2],hinamec[2],names[hisurferc[2]],
			(int)hiscorec[3],hinamec[3],names[hisurferc[3]],
			(int)hiscorec[4],hinamec[4],names[hisurferc[4]],
			(int)hiscorec[5],hinamec[5],names[hisurferc[5]]);
	}
	else
	{
		sprintf(stringy, "THRASH MODE!\n1st : %d - %s using %s\n2nd : %d - %s using %s\n3rd : %d - %s using %s\n4th : %d - %s using %s\n5th : %d - %s using %s\n6th : %d - %s using %s",
			(int)hiscore[0],hiname[0],names[hisurfer[0]],
			(int)hiscore[1],hiname[1],names[hisurfer[1]],
			(int)hiscore[2],hiname[2],names[hisurfer[2]],
			(int)hiscore[3],hiname[3],names[hisurfer[3]],
			(int)hiscore[4],hiname[4],names[hisurfer[4]],
			(int)hiscore[5],hiname[5],names[hisurfer[5]]);
	}

	MessageBox (stringy, "best surfers");
	ResetFps();
}

void CsurfView::OnUfo() 
{
	if (!bUfo)
	{
		ufo->SetPosition(m_scene, (const float)0, (const float)2000, (const float)2500);
		ufo->SetRotation(m_scene, (const float)0, (const float)1, (const float)0, (const float)0.15);
		m_scene->AddChild(ufo);
		bUfo = TRUE;
		if (bSoundFx)
		{
			m_pDSBuffer[UFOSND]->Play(0, 0, 0);
			m_pDSBuffer[UFOSTOPWAVE]->Play(0, 0, DSBPLAY_LOOPING);
		}
//		if (bShowErrors) MessageBox("ufo!","ufo!");
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_UFO, MF_BYCOMMAND | MF_CHECKED);
	}
	else 
	{
		m_scene->DeleteChild(ufo);
		bUfo = FALSE;
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_UFO, MF_BYCOMMAND | MF_UNCHECKED);
		if (bSoundFx)
			m_pDSBuffer[UFOSTOPWAVE]->Stop();
	}
	bUfoStop = FALSE;
	bUfoStop2 = FALSE;
	bSummoned = FALSE;
}

void CsurfView::OnSpray() 
{
	int i;
	bSprayOn = !bSprayOn;
	if (!bSprayOn)
	{
		for (i = 0; i < NUMSPRAY; i++)
		{
			m_scene->DeleteChild(spray[i]);
		}
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SPRAY, MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		if (!bCharselect)
		{
			for (i = 0; i < NUMSPRAY; i++)
			{
				m_scene->AddChild(spray[i]);
			}
		}
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_SPRAY, MF_BYCOMMAND | MF_CHECKED);
	}
	SaveStats();
	ResetFps();
}

void CsurfView::OnHorizon() 
{
	if (bHorizon)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_HORIZON, MF_BYCOMMAND | MF_UNCHECKED);
		bHorizon = FALSE;
		m_scene->DeleteChild(beach_frame);
	}	
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_HORIZON, MF_BYCOMMAND | MF_CHECKED);
		bHorizon = TRUE;
		if (!bCharselect)
		{
			for (int i = 0; i < NUMSPRAY; i++)
			{
				m_scene->AddChild(beach_frame);
				beach_frame->SetPosition(m_scene, D3DVALUE(0),D3DVALUE(0),D3DVALUE(0));
				beach_frame->SetVelocity(m_scene, D3DVALUE(0),D3DVALUE(0),D3DVALUE(10), FALSE);
			}
		}
	}	
	SaveStats();
	ResetFps();
}
/*
// network nonsense

void CsurfView::OnNetwork0() 
{
	if (NumNetwork > 0)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 0;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork1() 
{
	if (NumNetwork > 1)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 1;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork2() 
{
	if (NumNetwork > 2)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 2;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork3() 
{
	if (NumNetwork > 3)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 3;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork4() 
{
	if (NumNetwork > 4)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 4;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork5() 
{
	if (NumNetwork > 5)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 5;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork6() 
{
	if (NumNetwork > 6)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 6;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork7() 
{
	if (NumNetwork > 7)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 7;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork8() 
{
	if (NumNetwork > 8)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 8;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork9() 
{
	if (NumNetwork > 9)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 9;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork10() 
{
	if (NumNetwork > 10)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 10;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork11() 
{
	if (NumNetwork > 11)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 11;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork12() 
{
	if (NumNetwork > 12)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 12;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork13() 
{
	if (NumNetwork > 13)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 13;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork14() 
{
	if (NumNetwork > 14)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 14;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnNetwork15() 
{
	if (NumNetwork > 15)
	{
		if (NetworkNumber == NO_CONNECTION)
		{
			UncheckNetwork();
			NetworkNumber = 15;
			ConnectNetwork();
		}
	}
}

void CsurfView::OnBreakNetwork() 
{
	UncheckNetwork();
	NetworkNumber = NO_CONNECTION;
	GameServer = TRUE;
	bNetworked = FALSE;
	if (lpDP)
	{
        lpDP->Close();
		lpDP->Release();
		lpDP = NULL;
	}
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_NETWORK), ID_BREAK_NETWORK, MF_BYCOMMAND | MF_CHECKED);
}

void CsurfView::UncheckNetwork()
{
	if (NetworkNumber == NO_CONNECTION)
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_NETWORK), ID_BREAK_NETWORK, MF_BYCOMMAND | MF_UNCHECKED);
	else
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_NETWORK), ID_NETWORK0+NetworkNumber, MF_BYCOMMAND | MF_UNCHECKED);
}

void CsurfView::ConnectNetwork()
{
	DPSESSIONDESC dpDesc;
	int i, j;
	HRESULT LastError = DirectPlayCreate(lpNetworkGuid[NetworkNumber], &lpDP, NULL);
    if (LastError != DD_OK) 
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Create Direct Play Failed.");
		OnBreakNetwork();
		return;
    }
	for (i = 0; i < 6; i++)
		PlayerId[i] = NULL;
	ThisPlayer = 0;
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_NETWORK), ID_NETWORK0+NetworkNumber, MF_BYCOMMAND | MF_CHECKED);

	CNetCreate NetCreateDialog;
	NetCreateDialog.DoModal();

	// join a network game

	if (NetCreateDialog.selection == NET_JOIN)
	{
		delete NetCreateDialog;
		GameServer = FALSE;
        memset(&dpDesc, 0x00, sizeof(DPSESSIONDESC));
        dpDesc.dwSize = sizeof(dpDesc);
        dpDesc.guidSession = WILDRIDE_GUID;
	    dpDesc.dwMaxPlayers = 6;
		dpDesc.dwFlags = DPENUMSESSIONS_ALL;
		NumSessions = 0;
        LastError = lpDP->EnumSessions(&dpDesc, (DWORD)8000, EnumDPSession, this, NULL);
	    if (LastError != DP_OK)
		{
	        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Enumerate Sessions Failed.");
			OnBreakNetwork();
			return;
		}

		CNetSelSession NetSelSession;
		NetSelSession.bFirst = TRUE;
		for (i = 0; i < NumSessions; i++)
		{
			NetSelSession.SessionPlayers[i] = SessionPlayers[i];
			for (j = 0; j < 31; j++)
				NetSelSession.SessionName[i][j] = SessionName[i][j];
			SessionName[i][31] = 0;
		}
		NetSelSession.NumSessions = NumSessions;
		NetSelSession.SessionNumber = SessionNumber;
		NetSelSession.DoModal();
		SessionNumber = NetSelSession.SessionNumber;
		for (int j = 0; j < 31; j++)
			PlayerName[ThisPlayer][j] = NetSelSession.PlayerName[j];
		PlayerName[ThisPlayer][31] = 0;
		delete NetSelSession;
		if (SessionNumber == NET_SEL_SESSION_CANCEL)
		{
			OnBreakNetwork();
			return;
		}
		else
		{
			NumPlayers = 1;
			LastError = lpDP->EnumPlayers(SessionDesc[SessionNumber].dwSession,
					&EnumPlayersCallback, this, DPENUMPLAYERS_SESSION);
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Enumerate Players Failed.");
				OnBreakNetwork();
				return;
			}

  	        SessionDesc[SessionNumber].dwSize = sizeof(DPSESSIONDESC);
			SessionDesc[SessionNumber].dwFlags = DPOPEN_OPENSESSION;

			LastError = lpDP->Open(&SessionDesc[SessionNumber]);
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Join Session Failed.");
				OnBreakNetwork();
				return;
			}

		    LastError = lpDP->CreatePlayer(&PlayerId[ThisPlayer], PlayerName[ThisPlayer],
				"wild ride player", &dphEvent);
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Create Player Failed.");
				OnBreakNetwork();
				return;
		    }

			MSGNEWPLAYER msgNewPlayer;
			MSGCHARSELECT msgCharselect;
			msgNewPlayer.MsgType = MSG_NEW_PLAYER;
			msgCharselect.MsgType = MSG_CHAR_SELECT;
			msgCharselect.SelectedChar = ALANA;
			DPID from = PlayerId[ThisPlayer];
			LastError = lpDP->Send(from, 0, NULL, &msgNewPlayer, sizeof (MSGNEWPLAYER));
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "DP New Player Message Failed.");
		    }

			GameServer = FALSE;
			bNetworked = TRUE;
		}
	}

	// start a new network game

	else if (NetCreateDialog.selection == NET_START)
	{
		delete NetCreateDialog;
		ThisPlayer = 0;
        GameServer = TRUE;
		CNetNames NetNames;
		NumSessions = 1;
		SessionNumber = 0;
		NetNames.SessionNumber = SessionNumber;
		NetNames.DoModal();
		SessionNumber = NetNames.SessionNumber;
		for (int j = 0; j < 31; j++)
		{
			PlayerName[ThisPlayer][j] = NetNames.PlayerName[j];
			SessionName[0][j] = NetNames.SessionName[j];
		}
		PlayerName[ThisPlayer][31] = 0;
		SessionName[0][31] = 0;

		delete NetNames;
		if (SessionNumber == NET_NAMES_CANCEL)
		{
			OnBreakNetwork();
			return;
		}
		else
		{
			memset(&dpDesc, 0x00, sizeof(DPSESSIONDESC));
	        dpDesc.dwSize = sizeof(dpDesc);
		    dpDesc.dwMaxPlayers = 6;
			dpDesc.dwFlags = DPOPEN_CREATESESSION;
	        dpDesc.guidSession = WILDRIDE_GUID;
	  		for (j = 0; j < 32; j++)
			{
				dpDesc.szSessionName[j] = SessionName[SessionNumber][j];
			}
			LastError = lpDP->Open(&dpDesc);
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Create Session Failed.");
				OnBreakNetwork();
				return;
			}

			PlayerId[ThisPlayer] = 1;
		    LastError = lpDP->CreatePlayer(&PlayerId[ThisPlayer], PlayerName[ThisPlayer],
				"wild ride player", &dphEvent);
		    if (LastError != DP_OK)
			{
		        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Create Player Failed.");
				OnBreakNetwork();
				return;
		    }
			bNetworked = TRUE;
		}
	}
	else
	{
		delete NetCreateDialog;
		OnBreakNetwork();
	}
}

static BOOL CALLBACK EnumPlayersCallback(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName,
							DWORD dwFlags, LPVOID lpThat)
{
	CsurfView * view = (CsurfView *)lpThat;
	return view->EnumPlayersFront(dpID, lpFriendlyName);
}
BOOL CsurfView::EnumPlayersFront(DPID dpID, LPSTR lpFriendlyName)
{
	PlayerId[NumPlayers] = dpID;
	for (int i = 0; i < 32; i++)
		PlayerName[NumPlayers][i] = lpFriendlyName[i];
	NumPlayers++;
	if (NumPlayers > 5)
		return FALSE;
	return TRUE;
}

static BOOL CALLBACK EnumDPSession(LPDPSESSIONDESC lpDPSGameDesc, LPVOID lpThat,
							LPDWORD lpdwTimeOut, DWORD dwFlags)
{
	CsurfView * view = (CsurfView *)lpThat;
	return view->EnumDPSessionFront(lpDPSGameDesc);
}
BOOL CsurfView::EnumDPSessionFront(LPDPSESSIONDESC lpDPSGameDesc)
{
	if ((lpDPSGameDesc) && (NumSessions < MAX_NETWORK_SESSIONS))
	{
		SessionDesc[NumSessions] = *lpDPSGameDesc;
		SessionPlayers[NumSessions] = lpDPSGameDesc->dwCurrentPlayers;
		for (int i = 0; i < 32; i++)
			SessionName[NumSessions][i] = lpDPSGameDesc->szSessionName[i];
		NumSessions++;
		return TRUE;
	}
	return FALSE;
}

BOOL CsurfView::SetUpDirectPlay()
{
	HRESULT LastError;

	NumNetwork = 0;
	NetworkNumber = NO_CONNECTION;
	::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_NETWORK), ID_BREAK_NETWORK, MF_BYCOMMAND | MF_CHECKED);

	LastError = DirectPlayEnumerate(EnumDPCallback, this);
	if (LastError != DD_OK)
	{
        if (bShowErrors) MessageBox(MyErrorToString(LastError), "Direct Play Enumerate Failed.");
        return FALSE;
	}
	return TRUE;
}

static BOOL CALLBACK EnumDPCallback(LPGUID lpSPGuid, LPSTR lpFriendlyName,
		DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpThat)
{
	CsurfView * view = (CsurfView *)lpThat;
//	MessageBox (0, "loading texture","check", MB_OK);
	return view->EnumDPCallFront(lpSPGuid, lpFriendlyName);
}

BOOL CsurfView::EnumDPCallFront(LPGUID lpSPGuid, LPSTR lpFriendlyName)
{
	lpNetworkGuid[NumNetwork] = lpSPGuid;
	::AppendMenu(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_NETWORK),MF_STRING, ID_NETWORK0+NumNetwork, lpFriendlyName);
	NumNetwork++;
	if (NumNetwork >= MAX_NETWORK_DRIVERS)
		return FALSE;
	return TRUE;
}
*/

void CsurfView::OnMidiMusic() 
{
	static int ThirdLastNum2 = 121;
	static int ThirdLastNum3 = 122;
	static int ThirdLastNum = 126;
	static int OtherLastNum = 127;
	static int ExtraSong = 11;
	static int LastNum = 0;
	static BOOL bHiscoreSong = FALSE;
	static BOOL bGameOverSong = FALSE;
	static BOOL bNoContestSong = FALSE;
	static BOOL bContestSong = FALSE;
	int i;
	bMIDIMusic = !bMIDIMusic;
	for (i = 0; i < NUMSONGS; i++)
	{
		if (MidiMusic[i])
		{
			MidiMusic[i]->Stop();
		}
	}
	if (bMIDIMusic)
	{
		if (bCDMusic)
			OnCdMusic();
		if (bHiscore)
		{
			if (bHiscoreSong)
				MidiNum = 13;
			else
				MidiNum = 14;
			bHiscoreSong = !bHiscoreSong;
		}
		else if (bGameOver)
		{
			if (bGameOverSong)
				MidiNum = 11;
			else
				MidiNum = 12;
			bGameOverSong = !bGameOverSong;
		}
		else if (bCharselect)
		{
			if (bContest)
			{
				if (bContestSong)
					MidiNum = 9;
				else
					MidiNum = 10;
				bContestSong = !bContestSong;
			}
			else
			{
				if (bNoContestSong)
					MidiNum = 7;
				else
					MidiNum = 8;
				bNoContestSong = !bNoContestSong;
			}
		}
		else
		{
			MidiNum = 1+current_surfer;
		}
		while ((MidiNum == LastNum) 
			|| (MidiNum == OtherLastNum)
			|| (MidiNum == ThirdLastNum2)
			|| (MidiNum == ThirdLastNum3)
			|| (MidiNum == ThirdLastNum))
		{
			MidiNum = ExtraSong;
			ExtraSong++;
			if (ExtraSong >= NUMSONGS)
				ExtraSong = 11;
			if (((MidiNum == LastNum) 
				|| (MidiNum == OtherLastNum)
				|| (MidiNum == ThirdLastNum2)
				|| (MidiNum == ThirdLastNum3)
				|| (MidiNum == ThirdLastNum)
				|| (randInt(0,30) < 2)))
			{
				MidiNum = randInt(0, NUMSONGS);
			}
		}
		MidiMusic[MidiNum]->Play(m_hWnd, FALSE);
		ThirdLastNum3 = ThirdLastNum2;
		ThirdLastNum2 = ThirdLastNum;
		ThirdLastNum = OtherLastNum;
		OtherLastNum = LastNum;
		LastNum = MidiNum;

		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_MIDI_MUSIC, MF_BYCOMMAND | MF_CHECKED);
	}
	else
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_MIDI_MUSIC, MF_BYCOMMAND | MF_UNCHECKED);
	SaveStats();
}

void CsurfView::OnCdMusic() 
{
	bCDMusic = !bCDMusic;
	if (bCDMusic)
	{
		bSecretTrack = FALSE;
		if (bMIDIMusic)
			OnMidiMusic();
		if (bHiscore || bGameOver)
		{
			playCDTrack(10);
		}
		else if (bCharselect)
		{
			playCDTrack(9);
		}
		else
			playCDTrack(current_surfer+3);

		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_CD_MUSIC, MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		stopCD();
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_CD_MUSIC, MF_BYCOMMAND | MF_UNCHECKED);
	}
	SaveStats();
}


void CsurfView::OnSoundFx() 
{
	if (bSoundFxAllowed)
	{
		bSoundFx = !bSoundFx;
		if (bSoundFx)
		{
			if (bCharselect)
			{
				m_pDSBuffer[OCEANSND]->SetVolume(-800);
				m_pDSBuffer[STEAMSHIPWAVE]->SetVolume(-800);
			}
			else
			{
				m_pDSBuffer[OCEANSND]->SetVolume(0);
				m_pDSBuffer[STEAMSHIPWAVE]->SetVolume(0);
			}
			m_pDSBuffer[SPLASH]->SetVolume(-500);
			m_pDSBuffer[SEAGULL1]->SetVolume(-1500);
			m_pDSBuffer[SEAGULL2]->SetVolume(-1000);

			m_pDSBuffer[OCEANSND]->Play(0, 0, DSBPLAY_LOOPING);
			if (bUfo)
				m_pDSBuffer[UFOSTOPWAVE]->Play(0, 0, DSBPLAY_LOOPING);
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_SOUND_FX, MF_BYCOMMAND | MF_CHECKED);
		}
		else
		{
			if (bUfo)
				m_pDSBuffer[UFOSTOPWAVE]->Stop();
			m_pDSBuffer[OCEANSND]->Stop();
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_SOUND_FX, MF_BYCOMMAND | MF_UNCHECKED);
		}
	}
	else
		MessageBox("You have disabled sound effects from loading.  Add the line 'SoundFxAllowed=1' under the heading [Audio] in wildride.ini which is in your windows directory, and then reload Wild Ride.",
			"Sorry.");
	SaveStats();
}

void CsurfView::OnFoam() 
{
	int i;
	if (bFoam)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_FOAM, MF_BYCOMMAND | MF_UNCHECKED);
		bFoam = FALSE;
		for (i = 0; i < NUMFOAM; i++)
			m_scene->DeleteChild(foam[i]);
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_FOAM, MF_BYCOMMAND | MF_CHECKED);
		bFoam = TRUE;
		if (!bCharselect)
		{
			for (i = 0; i < NUMFOAM; i++)
				m_scene->AddChild(foam[i]);
		}
	}
	SaveStats();
	ResetFps();
}

//void CsurfView::OnHelpf() 
//{
//	::WinHelp(m_hWnd, "WILDRIDE.HLP", HELP_CONTENTS, 0L); 
//}

int CsurfView::randInt( int low, int high )
{
    int range = high - low;
	if (range == 0)
		return low;
    int num = rand() % range;
    return( num + low );
}

void CsurfView::OnNaration() 
{
	if (bSoundFxAllowed)
	{
		bNaration = !bNaration;
		if (bNaration)
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_NARATION, MF_BYCOMMAND | MF_CHECKED);
		}
		else
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_NARATION, MF_BYCOMMAND | MF_UNCHECKED);
		}
	}
	else
		MessageBox("You have disabled sound effects from loading.  Add the line 'SoundFxAllowed=1' under the heading [Audio] in wildride.ini which is in your windows directory, and then reload Wild Ride.",
			"Sorry.");
	SaveStats();
}

void CsurfView::OnGore() 
{
	int i;
	if (bGore)
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_GORE, MF_BYCOMMAND | MF_UNCHECKED);
		bGore = FALSE;
		for (i = 0; i < NUMBLOOD; i++)
			m_scene->DeleteChild(blood[i]);
	}
	else
	{
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_GORE, MF_BYCOMMAND | MF_CHECKED);
		bGore = TRUE;
		if (!bCharselect)
		{
			for (i = 0; i < NUMBLOOD; i++)
			{
				m_scene->AddChild(blood[i]);
				blood[i]->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			}
		}
	}
	SaveStats();
	ResetFps();
}

void CsurfView::OnPractice() 
{
	bPractice = !bPractice;
	if (!bContest)
	{
		if (!bPractice)
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_PRACTICE, MF_BYCOMMAND | MF_UNCHECKED);
			if (!bCharselect)
			{
				barrel->SetPosition(m_scene, D3DVALUE(randInt(-BOUNDARY/5, BOUNDARY/5)), frame_y[MAXWAVEFRAME+1], D3DVALUE(-450));
				barrel->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(OBSTACLE_SPEED), NULL);
				barrel->SetRotation(m_scene, D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(0.1));
				barrel->SetOrientation(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0), D3DVALUE(1), D3DVALUE(0));
				rock->SetPosition(m_scene, D3DVALUE(randInt(-BOUNDARY/5, BOUNDARY/5)), frame_y[MAXWAVEFRAME+1], D3DVALUE(-200));
				rock->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(PIER_SPEED), NULL);
				dolphintime = (const float)11;
			}
		}
		else
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_PRACTICE, MF_BYCOMMAND | MF_CHECKED);
			barrel->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			barrel->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			rock->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			rock->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			dolphin->SetPosition(m_scene, D3DVALUE(0), D3DVALUE(-20000), D3DVALUE(-20000));
			dolphin->SetVelocity(m_scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(0), FALSE);
			dolphintime = (const float)0;
		}
	}
	ResetFps();
}

void CsurfView::OnDraw(CDC* pDC) 
{
}

void CsurfView::AddAnnounce(int announcement)
{
	DWORD status;
	int i;
	static int announcebuffer[SIZE_BUFFER] = 
	{
		SOUND_EMPTY,SOUND_EMPTY,SOUND_EMPTY
	};
	
	if (announcement == SOUND_PLAY)
	{
		if (announcebuffer[0] != SOUND_EMPTY)
		{
			m_pDSBuffer[announcebuffer[0]]->GetStatus(&status);
			if ((status & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
			{
				for (i = 0; i < SIZE_BUFFER-1; i ++)
				{
					announcebuffer[i] = announcebuffer[i+1];
				}
				announcebuffer[SIZE_BUFFER-1] = SOUND_EMPTY;
				if (announcebuffer[0] != SOUND_EMPTY)
				{
//					if (!(!bNotDroppedInYet && ((announcebuffer >= SURF1) && (announcebuffer <= SURF3)))
					m_pDSBuffer[announcebuffer[0]]->Play(0,0,0);
				}
			}
		}
	}
	else if (announcebuffer[0] == SOUND_EMPTY)
	{
		announcebuffer[0] = announcement;
		m_pDSBuffer[announcement]->Play(0,0,0);
	}
	else
	{
		if (announcebuffer[0] == SOUND_EMPTY)
		{
			announcebuffer[0] = announcement;
			announcebuffer[1] = SOUND_EMPTY;
			announcebuffer[2] = SOUND_EMPTY;
		}
		else if (announcebuffer[1] == SOUND_EMPTY)
		{
			announcebuffer[1] = announcement;
			announcebuffer[2] = SOUND_EMPTY;
		}
		else if (announcebuffer[2] == SOUND_EMPTY)
		{
			announcebuffer[2] = announcement;
		}
		else
		{
			announcebuffer[1] = announcebuffer[2];
			announcebuffer[2] = announcement;
		}
	}
}

void CsurfView::AddSurferSound(int announcement)
{
	DWORD status;
	int i;
	static int announcebuffer[SIZE_BUFFER] = 
	{
		SOUND_EMPTY,SOUND_EMPTY,SOUND_EMPTY,
	};
	
	if (announcement == SOUND_PLAY)
	{
		if (announcebuffer[0] != SOUND_EMPTY)
		{
			m_pDSBuffer[announcebuffer[0]]->GetStatus(&status);
			if ((status & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
			{
				for (i = 0; i < SIZE_BUFFER-1; i ++)
				{
					announcebuffer[i] = announcebuffer[i+1];
				}
				announcebuffer[SIZE_BUFFER-1] = SOUND_EMPTY;
				if (announcebuffer[0] != SOUND_EMPTY)
				{
					m_pDSBuffer[announcebuffer[0]]->Play(0,0,0);
				}
			}
		}
	}
	else 
	{
		switch (current_surfer)
		{
		case ALANA:
			switch (announcement)
			{
			case WIPEOUT_SOUND:
				if (!bNaration)
					announcement = randInt(WIPEOUTA1,WIPEOUTA1+4);
				else 
					return;
				break;
			case TRICK_SOUND:
				announcement = randInt(TRICKA1,TRICKA1+3);
				break;
			case HOLD_SOUND:
				announcement = HOLDA1;
				break;
			case S360_SOUND:
				announcement = randInt(S360A1,S360A1+2);
				break;
			case TUBE_SOUND:
				announcement = randInt(TUBEA1,TUBEA1+2);
				break;
			case DROPIN_SOUND:
				announcement = randInt(DROPINA1,DROPINA1+3);
				break;
			case INSANITY_SOUND:
				announcement = INSANITYA1;
				break;
			default:
				return;
				break;
			}
			break;
#ifndef SHAREWARE
		case BUCKY:
			switch (announcement)
			{
			case WIPEOUT_SOUND:
				if (!bNaration)
					announcement = randInt(WIPEOUTB1,WIPEOUTB1+4);
				else 
					return;
				break;
			case TRICK_SOUND:
				announcement = randInt(TRICKB1,TRICKB1+3);
				break;
			case HOLD_SOUND:
				announcement = randInt(HOLDB1,HOLDB1+2);
				break;
			case S360_SOUND:
				announcement = randInt(S360B1,S360B1+2);
				break;
			case TUBE_SOUND:
				announcement = randInt(TUBEB1,TUBEB1+2);
				break;
			case DROPIN_SOUND:
				announcement = randInt(DROPINB1,DROPINB1+2);
				break;
			case INSANITY_SOUND:
				announcement = INSANITYB1;
				break;
			default:
				return;
				break;
			}
			break;
#endif
		case LEE:
			switch (announcement)
			{
			case WIPEOUT_SOUND:
				if (!bNaration)
					announcement = randInt(WIPEOUTL1,WIPEOUTL1+4);
				else 
					return;
				break;
			case TRICK_SOUND:
				announcement = randInt(TRICKL1,TRICKL1+4);
				break;
			case HOLD_SOUND:
				announcement = randInt(HOLDL1,HOLDL1+2);
				break;
			case S360_SOUND:
				announcement = randInt(S360L1,S360L1+2);
				break;
			case TUBE_SOUND:
				announcement = randInt(TUBEL1,TUBEL1+2);
				break;
			case DROPIN_SOUND:
				announcement = randInt(DROPINL1,DROPINL1+3);
				break;
			case INSANITY_SOUND:
				announcement = randInt(INSANITYL1,INSANITYL1+2);
				break;
			default:
				return;
				break;
			}
			break;
#ifndef SHAREWARE
		case SANDY:
			switch (announcement)
			{
			case WIPEOUT_SOUND:
				if (!bNaration)
					announcement = randInt(WIPEOUTS1,WIPEOUTS1+3);
				else 
					return;
				break;
			case TRICK_SOUND:
				announcement = randInt(TRICKS1,TRICKS1+4);
				break;
			case HOLD_SOUND:
				announcement = randInt(HOLDS1,HOLDS1+2);
				break;
			case S360_SOUND:
				announcement = randInt(S360S1,S360S1+2);
				break;
			case TUBE_SOUND:
				announcement = TUBES1;
				break;
			case DROPIN_SOUND:
				announcement = randInt(DROPINS1,DROPINS1+3);
				break;
			case INSANITY_SOUND:
				announcement = INSANITYS1;
				break;
			default:
				return;
				break;
			}
			break;
		case TODD:
			switch (announcement)
			{
			case WIPEOUT_SOUND:
				if (!bNaration)
					announcement = randInt(WIPEOUTT1,WIPEOUTT1+2);
				else 
					return;
				break;
			case TRICK_SOUND:
				announcement = randInt(TRICKT1,TRICKT1+2);
				break;
			case HOLD_SOUND:
				announcement = randInt(HOLDT1,HOLDT1+2);
				break;
			case S360_SOUND:
				announcement = randInt(S360T1,S360T1+2);
				break;
			case TUBE_SOUND:
				announcement = randInt(TUBET1,TUBET1+2);
				break;
			case DROPIN_SOUND:
				announcement = randInt(DROPINT1,DROPINT1+2);
				break;
			case INSANITY_SOUND:
				announcement = INSANITYT1;
				break;
			default:
				return;
				break;
			}
			break;
		case VIC:
			switch (announcement)
			{
			case WIPEOUT_SOUND:
				if (!bNaration)
					announcement = randInt(WIPEOUTV1,WIPEOUTV1+4);
				else 
					return;
				break;
			case TRICK_SOUND:
				announcement = randInt(TRICKV1,TRICKV1+3);
				break;
			case HOLD_SOUND:
				announcement = randInt(HOLDV1,HOLDV1+2);
				break;
			case S360_SOUND:
				announcement = randInt(S360V1,S360V1+2);
				break;
			case TUBE_SOUND:
				announcement = randInt(TUBEV1,TUBEV1+2);
				break;
			case DROPIN_SOUND:
				announcement = randInt(DROPINV1,DROPINV1+3);
				break;
			case INSANITY_SOUND:
				announcement = INSANITYV1;
				break;
			default:
				return;
				break;
			}
			break;
#endif
		default:
			return;
			break;
		}

		if (announcebuffer[0] == SOUND_EMPTY)
		{
			announcebuffer[0] = announcement;
			m_pDSBuffer[announcement]->Play(0,0,0);
		}
		else
		{
			for (i = 1; i < SIZE_BUFFER; i++)
			{
				if (announcebuffer[i] == SOUND_EMPTY)
				{
					announcebuffer[i] = announcement;
					i = SIZE_BUFFER+5;
				}
				if (i < SIZE_BUFFER+5)
				{
					announcebuffer[SIZE_BUFFER-1] = announcement;
				}
			}
		}
	}
}

LRESULT CsurfView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case LOADING:
		if (!InitAll())
		{
			if (bWrongDisplayMode)
			{
				MessageBox("You must be in 16 bit (Hi Color) color mode for Wild Ride to work properly.  Right click on the desktop.  Click Properties.  Choose the Settings tab.  Under Color palette select High Color (16 bit).","Warning!");
			}
			PostQuitMessage(0);
			return FALSE;
		}
		return TRUE;
		break;
	case MIDI_STOPPED:
		if (bMIDIMusic)
		{
			bMIDIMusic = FALSE;
			OnMidiMusic();
		}
		return TRUE;
		break;
	}
	return CView::WindowProc(message, wParam, lParam);
}

void CsurfView::OnDestroy() 
{
	if (bOkGo)
		SaveStats();
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CsurfView::OnSurferSounds() 
{
	if (bSoundFxAllowed)
	{
		bSurferSounds = !bSurferSounds;
		if (bSurferSounds)
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_SURFER_SOUNDS, MF_BYCOMMAND | MF_CHECKED);
		}
		else
		{
			::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_AUDIO), ID_SURFER_SOUNDS, MF_BYCOMMAND | MF_UNCHECKED);
		}
	}
	else
		MessageBox("You have disabled sound effects from loading.  Add the line 'SoundFxAllowed=1' under the heading [Audio] in wildride.ini which is in your windows directory, and then reload Wild Ride.",
			"Sorry.");
}

void CsurfView::OnTextureFilter() 
{
	if (TextureFiltering == D3DRMTEXTURE_LINEAR)
	{
		TextureFiltering = D3DRMTEXTURE_NEAREST;
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_TEXTURE_FILTER, MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		TextureFiltering = D3DRMTEXTURE_LINEAR;
		::CheckMenuItem(::GetSubMenu(::GetMenu(::GetParent(m_hWnd)),MENU_DETAILS), ID_TEXTURE_FILTER, MF_BYCOMMAND | MF_CHECKED);
	}
	SaveScreenDimensions();
	ChangeDriver(FALSE);
	SaveStats();
}
