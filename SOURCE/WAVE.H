  //
 // Sasquatch Hiearchy Segment Class - Object
// 

#ifndef __WAVE_HEADER__
#define __WAVE_HEADER__

  //
 // Inclusions
//
#include <MMSystem.h>

  //
 // CSasquatchHiearchySegment Class - Object
//
class CWave : public CObject
{
  // Public Constructor(s)/Destructor
public:
			CWave::CWave();
          CWave(const CString& sFileName);
          CWave(UINT uiResID, HMODULE hmod =
            AfxGetInstanceHandle());
  virtual ~CWave();

  // Public Methods
public:
  BOOL    Create(const CString& sFileName);
  BOOL    Create(UINT uiResID, HMODULE hmod =
            AfxGetInstanceHandle());
  BOOL    IsValid() const { return (m_pImageData ? TRUE :
            FALSE); };
  BOOL    Play(BOOL bAsync = TRUE, BOOL bLooped = FALSE) const;
  BOOL    GetFormat(WAVEFORMATEX& wfFormat) const;
  DWORD   GetDataLen() const;
  DWORD   GetData(BYTE*& pWaveData, DWORD dwMaxToCopy) const;
  void		FreeEmUp();

  // Protected Methods
protected:
  BOOL    Free();

  // Private Data
private:
  BYTE* m_pImageData;
  DWORD m_dwImageLen;
  BOOL  m_bResource;
};

#endif
