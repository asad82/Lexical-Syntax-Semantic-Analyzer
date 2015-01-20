// LSS AnalyzerView.h : interface of the CLSSAnalyzerView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES

#if !defined(AFX_LSSANALYZERVIEW_H__90D45AA1_AB95_4F2F_BA69_18C25A861DAC__INCLUDED_)
#define AFX_LSSANALYZERVIEW_H__90D45AA1_AB95_4F2F_BA69_18C25A861DAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define NEWLINE 13
#define LINEFEED 10 
#define KNOWN_WORDS 40
#define SYMBOL_TABLE_SIZE 100
#define POSSILE_LEXEMES 500
#define VARIABLE_LENGTH 16

class CLSSAnalyzerView : public CFormView
{
protected: // create from serialization only
	CLSSAnalyzerView();
	DECLARE_DYNCREATE(CLSSAnalyzerView)

public:
	//{{AFX_DATA(CLSSAnalyzerView)
	enum { IDD = IDD_LSSANALYZER_FORM };
	CListBox	m_ErrorMessage;
	CListBox	m_ErrorCause;
	CListBox	m_LexemeSize;
	CListBox	m_LexemeType;
	CListBox	m_Token;
	CListBox	m_LOR;
	CListBox	m_LOD;
	CListBox	m_Lexeme;
	CString	m_FileName;
	int		m_LinesInSourceFile;
	int		m_Panic_Mode_Count;
	CString	m_Skipped_Characters;
	int		m_MoveWClick;
	CString	m_CFG;
	CMSFlexGrid	m_FirstSet;
	CString	m_Semantics;
	//}}AFX_DATA

// Attributes
public:
	CLSSAnalyzerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSSAnalyzerView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OpenFile();
	virtual ~CLSSAnalyzerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CString AssignmentCompat(CString type1,CString type2);
	CString GetCompatInfo(CString type1,CString opr,CString type2);
	void CheckSemantics(CString lexStmt);
	CString GetLexemeType(char *lexeme,int lexIndex);
	void InitializeFirstSet();
	void Skip_Till_Synchronization();
	void PanicMode();
	void DisplaySymbolTable();
	void InsertLexemeIntoSymbolTable();
	CString LookUp(char lexeme[],int length);
	CString GetNextToken();
	void InitTypes();
	char GetChar();
	int GetHashKey(char tok[],int length);
	int ReferenceCount[POSSILE_LEXEMES];
	int ReferenceLine[POSSILE_LEXEMES][100];
	CString lexemeType;
	int movewithclick;
	bool lexemeLengthError,aStmt;
	bool assignStatement;

	struct LineofReference
	{
		int line_Number;
		LineofReference *next;
	};
	struct SymbolTable
	{
		char lexeme[32],token[32];
		int size;
		CString type;
		int LOD;
		SymbolTable *bucketS,*bucketL,*bucketT,*next;
		LineofReference *lineofrefS,*lineofrefL,*lineofrefT;	
	};

	int SymbolTable_Index;
	SymbolTable ST[SYMBOL_TABLE_SIZE],*symbtabTemp;

	int fsaState;
	char lexeme[50];
	CString bracketStack[50];
	int stackIndex;
	char sourceFileChars[1000];
	int sourceIndex;
	int returnIndex;
	int lexIndex;
	CString identifierType;
	CString saveLexTypes[50];
	int tyIndex;
	CString KnownTypes[KNOWN_WORDS];			
	CString Knownlexeme[KNOWN_WORDS];
	int KnownTypesValue[KNOWN_WORDS];
	bool firstTime;
	bool verify;
	int countDigits;

	CFile InputFileHandle,OutPutTokenFileHandle,OutPutErrorFileHandle;
	UINT BytesRead;
	DWORD BytesRemaining;
	char  lexClass,previousLexClass,nextLexClass;
	CString first_Set_AStmt[10][10];

/*	struct Identifier
	{
		CString lexeme;
		CString type;
	};

	struct Digit
	{
		int number;
		CString type;
	};

	struct Factor
	{
		Identifier * id;
		Digit * digit;
	};

	struct TermDash
	{
		CString oper;	// + , -
		Factor * factor;
		TermDash * termDash;
		bool null;
	};

	struct Term
	{
		Factor * factor;
		TermDash * termDash;
	};

	struct ExpDash
	{
		CString oper; // * , /
		Term * term;
		ExpDash * expDash;
		bool null;
	};

	struct Exp
	{
		Term * term;
		ExpDash * expDash;
	};

	struct AssignStmt
	{
		Identifier * id;
		CString oper; // =
		Exp * exp;
		CString semiColon; // ;
	};

	AssignStmt * assignStmt[20],*tempStmt;
*/

// Generated message map functions
protected:
	//{{AFX_MSG(CLSSAnalyzerView)
	afx_msg void OnReadanalyse();
	afx_msg void OnLineofreference();
	afx_msg void OnKillfocusLexemeIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LSS AnalyzerView.cpp
inline CLSSAnalyzerDoc* CLSSAnalyzerView::GetDocument()
   { return (CLSSAnalyzerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSSANALYZERVIEW_H__90D45AA1_AB95_4F2F_BA69_18C25A861DAC__INCLUDED_)
