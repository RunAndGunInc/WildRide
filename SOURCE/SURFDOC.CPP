// surfDoc.cpp : implementation of the CsurfDoc class
//

#include "stdafx.h"
#include "surf.h"
#include <mmsystem.h>

#include "surfDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CsurfDoc

IMPLEMENT_DYNCREATE(CsurfDoc, CDocument)

BEGIN_MESSAGE_MAP(CsurfDoc, CDocument)
	//{{AFX_MSG_MAP(CsurfDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CsurfDoc construction/destruction

CsurfDoc::CsurfDoc()
{
	// TODO: add one-time construction code here

}

CsurfDoc::~CsurfDoc()
{
}

BOOL CsurfDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CsurfDoc serialization

void CsurfDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CsurfDoc diagnostics

#ifdef _DEBUG
void CsurfDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CsurfDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CsurfDoc commands

