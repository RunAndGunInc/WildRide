//-----------------------------------------------------------------
// MIDI Stream Object
// C++ Source - MIDIStrm.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------
#include "StdAfx.h"
//-----------------------------------------------------------------
#include "MIDIStrm.h"
#include "MMIO.h"

//-----------------------------------------------------------------
// MFC Debugging Support
//-----------------------------------------------------------------
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIDI_STOPPED WM_USER+2

//-----------------------------------------------------------------
// CMIDIStream Public Constructor(s)/Destructor
//-----------------------------------------------------------------
CMIDIStream::CMIDIStream()
  : m_hmidiStream(NULL), m_uiStreamID(MIDI_MAPPER),
    m_dwNumBuffs(0), m_pBuffers(NULL), m_bPlaying(FALSE),
    m_bLoop(FALSE)
{
}

CMIDIStream::CMIDIStream(const CString& sFileName)
  : m_hmidiStream(NULL), m_uiStreamID(MIDI_MAPPER),
    m_dwNumBuffs(0), m_pBuffers(NULL), m_bPlaying(FALSE),
    m_bLoop(FALSE)
{
  Create(sFileName);
}

CMIDIStream::CMIDIStream(UINT uiResID, HMODULE hmod)
  : m_hmidiStream(NULL), m_uiStreamID(MIDI_MAPPER),
    m_dwNumBuffs(0), m_pBuffers(NULL), m_bPlaying(FALSE),
    m_bLoop(FALSE)
{
  Create(uiResID, hmod);
}

CMIDIStream::~CMIDIStream()
{
  // Free the stream image data
  Free();
}

//-----------------------------------------------------------------
// CMIDIStream Public Methods
//-----------------------------------------------------------------
BOOL
CMIDIStream::Create(const CString& sFileName)
{
  // Free any previous stream data
  Free();

  // Open the stream file
  CFile fileMIDI;
  if (!fileMIDI.Open(sFileName, CFile::modeRead))
    return FALSE;

  // Get the stream image length
  DWORD dwImageLen = fileMIDI.GetLength();

  // Allocate and lock memory for the image data
  HGLOBAL hgImageData = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,
    dwImageLen);
  BYTE*   pImageData = (BYTE*)::GlobalLock(hgImageData);
  if (!pImageData)
    return FALSE;

  // Read the image data from the file
  fileMIDI.Read(pImageData, dwImageLen);

  // Initialize the stream format info
  InitFormat(pImageData, dwImageLen);

  // Initialize the buffer data
  InitBuffers(pImageData, dwImageLen);

  // Free the stream image data
  ::GlobalUnlock(hgImageData);
  ::GlobalFree(hgImageData);

  return TRUE;
}

BOOL
CMIDIStream::Create(UINT uiResID, HMODULE hmod)
{
  // Free any previous stream data
  Free();

  // Find the stream resource
  HRSRC hresInfo;
  hresInfo = ::FindResource(hmod, MAKEINTRESOURCE(uiResID),
    "MIDS");
  if (!hresInfo)
    return FALSE;

  // Load the stream resource
  HGLOBAL hgImageData = ::LoadResource(hmod, hresInfo);
  if (!hgImageData)
    return FALSE;

  // Get pointer to and length of the stream image data
  BYTE* pImageData = (BYTE *)::LockResource(hgImageData);
  DWORD dwImageLen = ::SizeofResource(hmod, hresInfo);

  // Initialize the stream format info
  InitFormat(pImageData, dwImageLen);

  // Initialize the buffer data
  InitBuffers(pImageData, dwImageLen);

  // Free the stream image data
  ::FreeResource(::GlobalHandle(pImageData));

  return TRUE;
}

BOOL
CMIDIStream::Stop()
{
  if (m_bPlaying)
  {
    m_bPlaying = FALSE;
	m_bLoop = FALSE;
    if (::midiStreamStop(m_hmidiStream) == MMSYSERR_NOERROR)
    {
      Close();
      return TRUE;
    }
  }
  return FALSE;
}

BOOL
CMIDIStream::Play(HWND parenthwnd, BOOL bLoop)
{
	parenthWnd = parenthwnd;
  // Check validity
  if (!IsValid())
    return FALSE;

  // Make sure it's not already playing
  if (m_bPlaying)
    return FALSE;

  // Set playing flag
  m_bPlaying = TRUE;

  // Set loop flag and buffer count
  m_bLoop = bLoop;
  m_uiCurBuffer = 0;

  // Open the stream for output
  if (!Open())
  {
	  m_bPlaying = FALSE;
    return FALSE;
  }

  MIDIHDR* pmhdr = (MIDIHDR*)m_pBuffers;
  for (int i = m_dwNumBuffs; i; --i)
  {
    // Prepare the stream header
    if (::midiOutPrepareHeader((HMIDIOUT)m_hmidiStream,
      pmhdr, sizeof(MIDIHDR)) != MMSYSERR_NOERROR)
    {
      Stop();
	  m_bPlaying = FALSE;
      return FALSE;
    }

    // Queue the stream to play
    if (::midiStreamOut(m_hmidiStream, pmhdr,
      sizeof(MIDIHDR)) != MMSYSERR_NOERROR)
    {
      Stop();
	  m_bPlaying = FALSE;
      return FALSE;
    }

    // Move to the next stream
    pmhdr = (MIDIHDR*)(((BYTE*)pmhdr) + sizeof(MIDIHDR) +
      pmhdr->dwBufferLength);
  }       

  // Restart play so it will actually start playing
  if (::midiStreamRestart(m_hmidiStream) != MMSYSERR_NOERROR)
  {
    Stop();
    m_bPlaying = FALSE;
    return FALSE;
  }

  return TRUE;
}

BOOL
CMIDIStream::Pause()
{
  return (::midiStreamPause(m_hmidiStream) == MMSYSERR_NOERROR);
}

BOOL
CMIDIStream::Restart()
{
  return (::midiStreamRestart(m_hmidiStream) == MMSYSERR_NOERROR);
}

//-----------------------------------------------------------------
// CMIDIStream Protected Methods
//-----------------------------------------------------------------
BOOL
CMIDIStream::Open()
{
  // Close the existing stream, if necessary
  if (m_hmidiStream)
    Close();

  // Open the stream
  if (::midiStreamOpen(&m_hmidiStream, &m_uiStreamID, 1,
    (DWORD)(PMIDIPROC)StreamProc, (DWORD)this, CALLBACK_FUNCTION)
      != MMSYSERR_NOERROR)
    return FALSE;

  // Set the stream time division properties
  MIDIPROPTIMEDIV mptdTimeDiv;
  mptdTimeDiv.cbStruct = sizeof(MIDIPROPTIMEDIV);
  mptdTimeDiv.dwTimeDiv = m_mfFormat.dwTimeFormat;
  if (::midiStreamProperty(m_hmidiStream, (BYTE*)&mptdTimeDiv,
    MIDIPROP_SET | MIDIPROP_TIMEDIV) != MMSYSERR_NOERROR)
  {
    Close();
    return FALSE;
  }

  return TRUE;
}

BOOL
CMIDIStream::Close()
{
  if (!m_hmidiStream)
    return FALSE;

  // Reset the stream
  if (::midiOutReset((HMIDIOUT)m_hmidiStream) == MMSYSERR_NOERROR)
  {
    MIDIHDR* pmhdr = (MIDIHDR*)m_pBuffers;
    for (int i = m_dwNumBuffs; i; --i)
    {
      // Unprepare the stream header
      ::midiOutUnprepareHeader((HMIDIOUT)m_hmidiStream, pmhdr,
        sizeof(MIDIHDR));

      // Move to the next stream
      pmhdr = (MIDIHDR*)(((BYTE*)pmhdr) + sizeof(MIDIHDR) +
        pmhdr->dwBufferLength);
    }       

    // Close the stream
    if (::midiStreamClose(m_hmidiStream) == MMSYSERR_NOERROR)
    {
      m_hmidiStream = NULL;
      m_uiStreamID = MIDI_MAPPER;
      return TRUE;
    }
  }

  return FALSE;
}

void
CMIDIStream::Free()
{
  // Stop (and close) the stream
  Stop();

  // Free any buffer data
  if (m_pBuffers)
  {
    HGLOBAL hgBuffers = ::GlobalHandle(m_pBuffers);
    ::GlobalUnlock(hgBuffers);
    ::GlobalFree(hgBuffers);
    m_pBuffers = NULL;
  }
}

BOOL
CMIDIStream::InitFormat(BYTE* pImageData, DWORD dwImageLen)
{
  if (!pImageData)
    return FALSE;

  // Setup and open the MMINFO structure
  CMMMemoryIOInfo mmioInfo((HPSTR)pImageData, dwImageLen);
  CMMIO           mmio(mmioInfo);

  // Find the MIDS chunk
  CMMTypeChunk mmckParent('M','I','D','S');
  mmio.Descend(mmckParent, MMIO_FINDRIFF);

  // Find and read the format subchunk
  CMMIdChunk mmckSubchunk('f','m','t',' ');
  mmio.Descend(mmckSubchunk, mmckParent, MMIO_FINDCHUNK);
  mmio.Read((HPSTR)&m_mfFormat, sizeof(MIDSFORMAT));
  mmio.Ascend(mmckSubchunk);

  return TRUE;
}

BOOL
CMIDIStream::InitBuffers(BYTE* pImageData, DWORD dwImageLen)
{
  if (!pImageData)
    return FALSE;

  // Setup and open the MMINFO structure
  CMMMemoryIOInfo mmioInfo((HPSTR)pImageData, dwImageLen);
  CMMIO           mmio(mmioInfo);

  // Find the MIDS chunk
  CMMTypeChunk mmckParent('M','I','D','S');
  mmio.Descend(mmckParent, MMIO_FINDRIFF);

  // Find and get the size of the data subchunk
  CMMIdChunk mmckSubchunk('d','a','t','a');
  mmio.Descend(mmckSubchunk, mmckParent, MMIO_FINDCHUNK);
  DWORD dwLenToCopy = mmckSubchunk.cksize;

  // Allocate memory for raw buffer data
  HGLOBAL hgBuffData = ::GlobalAlloc(GMEM_MOVEABLE,
    mmckSubchunk.cksize);
  BYTE* pBuffData = (BYTE*)::GlobalLock(hgBuffData);
  if (!pBuffData)
    return FALSE;

  // Read number of buffers and buffer stream data
  mmio.Read((HPSTR)&m_dwNumBuffs, sizeof(DWORD));
  mmio.Read((HPSTR)pBuffData, mmckSubchunk.cksize - sizeof(DWORD));

  // Allocate memory for stream buffers
  m_pBuffers = (BYTE*)::GlobalLock(::GlobalAlloc(GMEM_MOVEABLE,
    m_dwNumBuffs * (sizeof(MIDIHDR) + m_mfFormat.dwMaxBuffLen)));
  if (!m_pBuffers)
  {
    ::GlobalUnlock(hgBuffData);
    ::GlobalFree(hgBuffData);
    return FALSE;
  }

  // Prepare the buffers
  MIDIHDR*  pmhdr = (MIDIHDR*)m_pBuffers;
  BYTE*     pBuff = pBuffData;
  for (int i = m_dwNumBuffs; i > 0; --i)
  {
    // Setup the buffer header
    pmhdr->lpData = (LPSTR)(pmhdr + 1);
    pmhdr->dwBufferLength = m_mfFormat.dwMaxBuffLen;
    pmhdr->dwFlags = 0;
    pmhdr->dwUser = 0;
    pmhdr->lpNext = NULL;

    MIDSBUFFERHDR* pmhdrBuff = (MIDSBUFFERHDR*)pBuff;
    pBuff += sizeof(MIDSBUFFERHDR);

    if (m_mfFormat.dwFlags & MDS_F_NOSTREAMID)
    {
      // Decompress the buffer data
      MIDIHDR mhdrCmp;
      mhdrCmp.lpData = (LPSTR)pBuff;
      mhdrCmp.dwBufferLength = mhdrCmp.dwBytesRecorded =
        pmhdrBuff->dwBuffLen;
      if (!Decompress(pmhdr, &mhdrCmp))
      {
        ::GlobalUnlock(hgBuffData);
        ::GlobalFree(hgBuffData);
        return FALSE;
      }
    }
    else
    {
      // Copy the buffer data
      pmhdr->dwBytesRecorded = pmhdrBuff->dwBuffLen;
      ::CopyMemory(pmhdr->lpData, pBuff, pmhdrBuff->dwBuffLen);
    }

    // Move to next buffer
    pBuff += pmhdrBuff->dwBuffLen;
    pmhdr = (MIDIHDR*)(((BYTE*)pmhdr) + sizeof(MIDIHDR) +
      m_mfFormat.dwMaxBuffLen);
  }

  // Unlock and free raw buffer data memory
  ::GlobalUnlock(hgBuffData);
  ::GlobalFree(hgBuffData);

  return TRUE;
}

BOOL
CMIDIStream::Decompress(MIDIHDR* pmhdrDst, MIDIHDR* pmhdrSrc)
{
  DWORD*  pSrcData = (DWORD*)pmhdrSrc->lpData;
  DWORD*  pDstData = (DWORD*)pmhdrDst->lpData;
  DWORD   dwSrc = pmhdrSrc->dwBytesRecorded,
          dwDst = pmhdrDst->dwBufferLength,
          dwExtra;

  // Total buffer length must be a DWORD multiple
  if (dwSrc & 3)
    return FALSE;

  while (dwSrc)
  {   
    // Need at least space for delta-time, stream ID, event DWORD
    if (dwDst < (3 * sizeof(DWORD)))
      return FALSE;
                
    // Copy the delta-time
    *pDstData++ = *pSrcData++;                
    dwSrc -= sizeof(DWORD);
    dwDst -= sizeof(DWORD);

    // Set the stream ID to 0
    *pDstData++ = 0;
    dwDst -= sizeof(DWORD);

    // Make sure there is more data
    if (!dwSrc)
      return FALSE;

    // Copy the actual event data
    dwExtra = 0;
    if ((*pSrcData) & 0x80000000L)
      dwExtra = (*pSrcData) & 0x00FFFFFFL;

    // Event length is byte aligned (data is padded to next DWORD)
    dwExtra = (dwExtra + 3) & ~3;

    // Copy the event DWORD itself
    *pDstData++ = *pSrcData++;
    dwSrc -= sizeof(DWORD);
    dwDst -= sizeof(DWORD);

    // Copy event parameter data
    if (dwExtra)
    {
      if (dwExtra > dwSrc || dwExtra > dwDst)
        return FALSE;

      ::CopyMemory(pDstData, pSrcData, dwExtra);
    }

    // Increment pointers and update lengths
    pDstData += (dwExtra / sizeof(DWORD));
    pSrcData += (dwExtra / sizeof(DWORD));
    dwSrc -= dwExtra;
    dwDst -= dwExtra;
  }

  // Calculate total resulting destination bytes
  pmhdrDst->dwBytesRecorded = (((BYTE*)pDstData) - (BYTE*)
    (pmhdrDst->lpData));

  return TRUE;
}

void CALLBACK
CMIDIStream::StreamProc(HMIDIIN hmidiIn, UINT uiMsg, DWORD
  dwInstance, DWORD dwParam1, DWORD dwParam2)
{
  CMIDIStream* pmidiStream = (CMIDIStream*)dwInstance;

  if (pmidiStream)
    pmidiStream->StreamProc(hmidiIn, uiMsg, dwParam1, dwParam2);
}

void
CMIDIStream::StreamProc(HMIDIIN hmidiIn, UINT uiMsg, DWORD
  dwParam1, DWORD dwParam2)
{
  switch(uiMsg)
  {
    case MOM_DONE:
      // Loop the stream, if necessary
      if ((++m_uiCurBuffer >= m_dwNumBuffs) && m_bPlaying)
	  {
  		  m_bPlaying = FALSE;
		  if (m_bLoop)
		  {
			  Play(parenthWnd, m_bLoop);
		  }
		  else 
		  {
			  Close();
			  ::SendMessage(parenthWnd, MIDI_STOPPED,0,0);
		  }
	  }
      break;
  }
}
