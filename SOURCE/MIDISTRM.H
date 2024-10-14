

#ifndef __MIDI_STREAM_CLASS_HEADER__
#define __MIDI_STREAM_CLASS_HEADER__

#include <MMSystem.h>
  //
 // Defines
//
#define MDS_F_NOSTREAMID 0x00000001

  //
 // Types
//
// MIDI callback
typedef void (CALLBACK* PMIDIPROC)(
								HMIDIIN hmidiIn, 
								UINT uiMsg,
								DWORD dwInstance, 
								DWORD dwParam1, 
								DWORD dwParam2);

// MDS 'fmt ' chunk format
typedef struct _MIDSFORMAT
{
	DWORD dwTimeFormat;
	DWORD dwMaxBuffLen;
	DWORD dwFlags;
} 
MIDSFORMAT;

// MDS 'data' chunk buffer header
typedef struct _MIDSBUFFERHDR
{
	DWORD dwTickStart;
	DWORD dwBuffLen;
} 
MIDSBUFFERHDR;


//-----------------------------------------------------------------
// CMIDIStream Class - MIDI Stream Object
//-----------------------------------------------------------------
class CMIDIStream 
{
  // Public Constructor(s)/Destructor
public:
        CMIDIStream();
        CMIDIStream(
			const CString& sFileName);
        CMIDIStream(
			UINT uiResID, 
			HMODULE hmod = AfxGetInstanceHandle());
virtual		
		~CMIDIStream();

  // Public Methods
public:
	BOOL	Create(
				const CString& sFileName);
	BOOL	Create(
				UINT uiResID, 
				HMODULE hmod = AfxGetInstanceHandle());
	BOOL	Stop();
	BOOL	Play(
				HWND parenthwnd, 
				BOOL bLoop = FALSE);
	BOOL	Pause();
	BOOL	Restart();
	BOOL	Close();

	BOOL	m_bPlaying;
	BOOL	m_bLoop;
	HWND	parenthWnd;

  // Protected Methods
protected:
	BOOL	IsValid() const
				{ return (m_pBuffers ? TRUE : FALSE); };
	BOOL	Open();
	void	Free();
	BOOL	InitFormat(
				BYTE* pImageData, 
				DWORD dwImageLen);
	BOOL	InitBuffers(
				BYTE* pImageData, 
				DWORD dwImageLen);
	BOOL	Decompress(
				LPMIDIHDR lpmhDst,
				LPMIDIHDR lpmhSrc);

	static void CALLBACK	StreamProc(
								HMIDIIN hmidiIn, 
								UINT uiMsg,
								DWORD dwInstance, 
								DWORD dwParam1, 
								DWORD dwParam2);
	void					StreamProc(
								HMIDIIN hmidiIn, 
								UINT uiMsg,
								DWORD dwParam1,
								DWORD dwParam2);

  // Private Data
private:
	HMIDISTRM   m_hmidiStream;
	UINT        m_uiStreamID;
	MIDSFORMAT  m_mfFormat;
	DWORD       m_dwNumBuffs;
	BYTE*       m_pBuffers;
	UINT        m_uiCurBuffer;
};

#endif
