// LSS AnalyzerDoc.h : interface of the CLSSAnalyzerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSSANALYZERDOC_H__8B8647C5_A608_435B_8FA1_4E1BF54011F9__INCLUDED_)
#define AFX_LSSANALYZERDOC_H__8B8647C5_A608_435B_8FA1_4E1BF54011F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLSSAnalyzerDoc : public CDocument
{
protected: // create from serialization only
	CLSSAnalyzerDoc();
	DECLARE_DYNCREATE(CLSSAnalyzerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSSAnalyzerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLSSAnalyzerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLSSAnalyzerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSSANALYZERDOC_H__8B8647C5_A608_435B_8FA1_4E1BF54011F9__INCLUDED_)
