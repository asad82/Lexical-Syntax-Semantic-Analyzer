// LSS Analyzer.h : main header file for the LSS ANALYZER application
//

#if !defined(AFX_LSSANALYZER_H__96F2FDFE_F6CA_4BC0_A9FF_03611B593827__INCLUDED_)
#define AFX_LSSANALYZER_H__96F2FDFE_F6CA_4BC0_A9FF_03611B593827__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerApp:
// See LSS Analyzer.cpp for the implementation of this class
//

class CLSSAnalyzerApp : public CWinApp
{
public:
	CLSSAnalyzerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSSAnalyzerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLSSAnalyzerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSSANALYZER_H__96F2FDFE_F6CA_4BC0_A9FF_03611B593827__INCLUDED_)
