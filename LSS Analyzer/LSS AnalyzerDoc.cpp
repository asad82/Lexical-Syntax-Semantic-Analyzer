// LSS AnalyzerDoc.cpp : implementation of the CLSSAnalyzerDoc class
//

#include "stdafx.h"
#include "LSS Analyzer.h"

#include "LSS AnalyzerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerDoc

IMPLEMENT_DYNCREATE(CLSSAnalyzerDoc, CDocument)

BEGIN_MESSAGE_MAP(CLSSAnalyzerDoc, CDocument)
	//{{AFX_MSG_MAP(CLSSAnalyzerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerDoc construction/destruction

CLSSAnalyzerDoc::CLSSAnalyzerDoc()
{
	// TODO: add one-time construction code here

}

CLSSAnalyzerDoc::~CLSSAnalyzerDoc()
{
}

BOOL CLSSAnalyzerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerDoc serialization

void CLSSAnalyzerDoc::Serialize(CArchive& ar)
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
// CLSSAnalyzerDoc diagnostics

#ifdef _DEBUG
void CLSSAnalyzerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLSSAnalyzerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerDoc commands
