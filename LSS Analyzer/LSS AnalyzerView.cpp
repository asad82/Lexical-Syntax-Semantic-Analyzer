// LSS AnalyzerView.cpp : implementation of the CLSSAnalyzerView class
//


#include "stdafx.h"
#include "LSS Analyzer.h"

#include "LSS AnalyzerDoc.h"
#include "LSS AnalyzerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerView

IMPLEMENT_DYNCREATE(CLSSAnalyzerView, CFormView)

BEGIN_MESSAGE_MAP(CLSSAnalyzerView, CFormView)
	//{{AFX_MSG_MAP(CLSSAnalyzerView)
	ON_BN_CLICKED(IDC_READANALYSE, OnReadanalyse)
	ON_BN_CLICKED(IDC_LINEOFREFERENCE, OnLineofreference)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerView construction/destruction

CLSSAnalyzerView::CLSSAnalyzerView()
	: CFormView(CLSSAnalyzerView::IDD)
{
	//{{AFX_DATA_INIT(CLSSAnalyzerView)
	m_FileName = _T("C:\\SourceFile2.txt");
	m_LinesInSourceFile = 1;
	m_Panic_Mode_Count = 0;
	m_Skipped_Characters = _T("");
	m_MoveWClick = 0;
	m_CFG = _T("");
	m_Semantics = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here


}

CLSSAnalyzerView::~CLSSAnalyzerView()
{
}

void CLSSAnalyzerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLSSAnalyzerView)
	DDX_Control(pDX, IDC_ERROR_MESSAGE, m_ErrorMessage);
	DDX_Control(pDX, IDC_ERROR_CAUSE, m_ErrorCause);
	DDX_Control(pDX, IDC_LEXEMESIZE, m_LexemeSize);
	DDX_Control(pDX, IDC_TYPE, m_LexemeType);
	DDX_Control(pDX, IDC_TOKEN, m_Token);
	DDX_Control(pDX, IDC_LOR, m_LOR);
	DDX_Control(pDX, IDC_LOD, m_LOD);
	DDX_Control(pDX, IDC_LEXEME, m_Lexeme);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_LINESINSOURCEFILE, m_LinesInSourceFile);
	DDX_Text(pDX, IDC_NO_OF_TIMES_IN_PANIC_MODE, m_Panic_Mode_Count);
	DDX_Text(pDX, IDC_CHARCTERS_SKIPPED_IN_PANIC_MODE, m_Skipped_Characters);
	DDX_Text(pDX, IDC_LEXEME_INDEX, m_MoveWClick);
	DDX_Text(pDX, IDC_CFG, m_CFG);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_FirstSet);
	DDX_Text(pDX, IDC_SEMANTICS, m_Semantics);
	//}}AFX_DATA_MAP
}

BOOL CLSSAnalyzerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLSSAnalyzerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerView printing

BOOL CLSSAnalyzerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLSSAnalyzerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLSSAnalyzerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLSSAnalyzerView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerView diagnostics

#ifdef _DEBUG
void CLSSAnalyzerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLSSAnalyzerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLSSAnalyzerDoc* CLSSAnalyzerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLSSAnalyzerDoc)));
	return (CLSSAnalyzerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLSSAnalyzerView message handlers

void CLSSAnalyzerView::OnReadanalyse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	InitTypes();
	InitializeFirstSet(); // for parser
	OpenFile();
	firstTime=true;
	verify=false;
	lexemeLengthError=false;
	aStmt=false;
	fsaState=0;
	sourceIndex=0;
	returnIndex=0;
	countDigits=0;
	stackIndex=0;
	SymbolTable_Index=0;
	identifierType=_T("");
	tyIndex=0;
	assignStatement=false;

	CString stmt,tempCh,ldLex,lexStmt;
	stmt=_T("");
	bool inserted=false,fTRight=true,once=true;
	int stmtIndex=0;
	int staticIndex=0;

	// initialize all the indices of symbol table with NULL
	for(int clear=0;clear<100;clear++)
		ST[clear].bucketS=NULL;

	
	while(BytesRemaining > 0)
	{

		lexemeType=GetNextToken();
		if(lexemeType.Compare("NULL")!=0)
			InsertLexemeIntoSymbolTable();
		// parse tree implementation begins here

		ldLex=_T("");
		for(int u=0;u<lexIndex;u++)
			ldLex+=lexeme[u];
		
		if(aStmt)
		{
			
			if(lexemeType=="EQ" && once)
			{
				saveLexTypes[tyIndex++]="=";
				lexStmt+="=";
				stmt+="=";
				stmt+=first_Set_AStmt[1][1];
				stmt+=";";
				stmtIndex=2;
				m_CFG+=stmt;m_CFG+=13; m_CFG+=10;
				once = false;
			}

			else //(lexemeType.Compare("Identifier")==0 || lexemeType.Compare("Digit")==0) && fTRight)
			{
				fTRight=false; 
				inserted=false;

				while(!inserted && stmtIndex<(stmt.GetLength()-1))
				{
					
					tempCh=stmt.GetAt(stmtIndex);
					for(int i=1;i<6;i++)
					{
						if(tempCh.Compare(first_Set_AStmt[i][0])==0)
						{
							// search the appropriate column
							staticIndex=-1;
							for(int k=1;k<8;k++)
							{
								if(lexemeType.Compare(first_Set_AStmt[0][k])==0 && first_Set_AStmt[i][k].Compare("EMPTY")!=0)//"Identifier")==0)
								{
									staticIndex=k;
									break;
								}
							}
							if(staticIndex == -1)
							{
								// increment the stmtIndex (not found)
								stmt.Replace(tempCh.GetAt(0),'N');								
								break;
							}

							stmt.Replace(tempCh.GetAt(0),first_Set_AStmt[i][staticIndex].GetAt(0) );
							if( first_Set_AStmt[i][staticIndex].GetLength() > 1 )
								stmt.Insert( stmtIndex+1,first_Set_AStmt[i][staticIndex].GetAt(1) );
							if( first_Set_AStmt[i][staticIndex].GetLength() > 2 )
								stmt.Insert( stmtIndex+2,first_Set_AStmt[i][staticIndex].GetAt(2) );
							
							tempCh=first_Set_AStmt[i][staticIndex].GetAt(0);
							m_CFG+=stmt;m_CFG+=13; m_CFG+=10;

							if(tempCh=="I" || tempCh=="D")
							{
								lexStmt+=ldLex;
								// for semantics
								if(lexemeType=="Digit")
									saveLexTypes[tyIndex++]="int";
								else
									saveLexTypes[tyIndex++]=GetLexemeType(lexeme,lexIndex);

								inserted=true; break;
							}
							else if(tempCh=="+" || tempCh=="-" || tempCh=="*" || tempCh=="/")
							{
								lexStmt+=" "+tempCh;
								saveLexTypes[tyIndex++]=tempCh;
								inserted=true; break;
							}

							
							// if replaced then search from beginning
							i=1;
						}

					}// end of for loop
					
					stmtIndex++;
					if(inserted)
					{
						break;
					}

					m_CFG+=stmt;m_CFG+=13; m_CFG+=10;
					
				}// end of while
				

			}// end of if


		}//end of if on aStmt

		
		if(lexemeType.Compare(first_Set_AStmt[0][0])==0 && fTRight && assignStatement)
		{
			aStmt=true;
			lexStmt+=ldLex;
			stmt+="I";
			m_CFG+=stmt;m_CFG+=13; m_CFG+=10;
			inserted = true;
			saveLexTypes[tyIndex++]=GetLexemeType(lexeme,lexIndex);
			//assignStatement=false;
		}
		else if (lexemeType.Compare("SC")==0 && assignStatement)
		{	
			lexStmt+=ldLex;
			m_CFG+=stmt;m_CFG+=13; m_CFG+=10;
			m_CFG+=lexStmt;m_CFG+=13; m_CFG+=10;
			m_CFG+="-------------------------------";m_CFG+=13; m_CFG+=10;

			inserted=true;
			aStmt=false;
			stmt=_T("");
			fTRight=true;
			stmtIndex=0;
			staticIndex=0;
			once=true;
			assignStatement=false;
			CheckSemantics(lexStmt);
			tyIndex=0;
			lexStmt="";			

		}

		if(!inserted && assignStatement)
		{
			// Syntax error
			lexStmt+=ldLex;
			m_CFG+=stmt+" Syntax Error";m_CFG+=13; m_CFG+=10;
			m_CFG+=lexStmt;m_CFG+=13; m_CFG+=10;

			aStmt=false;
			stmt=_T("");
			fTRight=true;
			stmtIndex=0;
			staticIndex=0;
			once=true;
			CString er;
			er.Format("Match Failed "+lexemeType+" Syntax Error On Line %d",m_LinesInSourceFile);
			m_CFG+=er; m_CFG+=13; m_CFG+=10;
			m_CFG+="-------------------------------";m_CFG+=13; m_CFG+=10;

			//MessageBox(er);
			lexStmt="";
			tyIndex=0;
		}

		// end of parse tree implementation
		lexIndex=0;
	}// end of while

	
	DisplaySymbolTable();

	if(stackIndex != 0)
		MessageBox("Curley Bracket Missing");


}// end of function

char ch;

CString CLSSAnalyzerView::GetNextToken()
{

	lexIndex=0;
	int tempInt=0;
	CString st;
	char tempBuff[1],buffer[1];
	bool mulComment=false;

	while(BytesRemaining > 0)//(ch=GetChar())!=NULL)
	{	
		if(firstTime)
			ch=GetChar();

		switch(fsaState)
		{
		case 0:
			if(lexClass=='S') fsaState=1;
			else if(lexClass=='T') fsaState=2;
			else if(lexClass=='L') fsaState=3;
			else if(lexClass=='D') fsaState=4;
			else if(lexClass=='A') fsaState=5;
			else if(lexClass=='R') fsaState=6;
			else if(lexClass=='G') fsaState=7;
			else if(lexClass=='P') fsaState=8;
			else if(lexClass=='B') fsaState=9;
			else fsaState=10;

			break;
		case 1:		//SPACE		
			// space
			while(lexClass=='S')
				ch=GetChar();
			if(lexClass=='R') fsaState=11;
			else if(lexClass=='P') fsaState=0;
			else if(lexClass=='A') fsaState=5;			
			else if(lexClass=='L') fsaState=3;
			else if(lexClass=='B') fsaState=9;
			else fsaState=10;
			
			break;
		case 2:
			break;
		case 3:  //LETTER
			lexeme[lexIndex++]=ch;
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			 st=LookUp(lexeme,lexIndex);
			 if(st.Compare("DEC")==0)
			 {
				 assignStatement=false;
				 identifierType="";
				 for(int y=0;y<lexIndex;y++)
					 identifierType+=lexeme[y];

				 fsaState=16;
				 return st;
			 }
			 else if(st.Compare("Identifier")==0)
			 { // handle assignment statements
				assignStatement=true;
				fsaState=26;
				//ch=GetChar();
				return st;
			 }
			 else if(st.Compare("for")==0)
			 {
				fsaState=34;
				//ch=GetChar();
				return st;
			 }
			 else if(st.Compare("while")==0)
			 {
				fsaState=58;
				//ch=GetChar();
				return st;
			 }

			 else
				fsaState=10;
			 
			 break;
		case 4://'P': 
			

			break;
		case 5:// Arithmatic OPERATORS			
			tempBuff[0]=ch;
			st=LookUp(tempBuff,1);
			if(st.Compare("DIV")==0)
			{				
				if(nextLexClass=='A')
					fsaState=13;
			}
			
			
			
			break;
		case 6://'S': 
			ch;
			break;
		case 7://'T': //TERMINATOR 
			ch;
			break;
		case 8:	//PRE-PROCESSOR 
			// it is a preprocessor directive
			assignStatement=false;
			if(nextLexClass=='L')
			{	//include
				lexeme[lexIndex++]=GetChar();
				while(lexClass=='L')
				{
					lexeme[lexIndex++]=GetChar();				
				}
				lexIndex--;
				CString inc;
				for(int h=0;h<lexIndex;h++)
					inc+=lexeme[h];
				
				
				if(lexClass=='R') // <
					fsaState=11;
				else if(lexClass=='S')
					fsaState=1;
				else
					fsaState=10;
				
				if(inc.Compare("include")==0)
					return LookUp(lexeme,lexIndex);
				else
					fsaState=10;
			}// end of if
			else
				// automata failed
				fsaState=10;
			
			break;
		case 9:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();
			
			}
			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("CBO")==0)
				{	lexeme[lexIndex++]=ch;					
					bracketStack[stackIndex++]=st;
					ch=GetChar();
					fsaState=0;
					return st;
				}
				else if(st.Compare("CBC")==0 && stackIndex > 0)
				{
					tempInt=stackIndex;
					if(bracketStack[--tempInt].Compare("CBO")==0 )
					{
						lexeme[lexIndex++]=ch;
						stackIndex--;
						ch=GetChar();
						fsaState=0;
						return LookUp(lexeme,lexIndex);
					}
					else
						fsaState=10;

				}
				else
					fsaState=10;				
			}
			else fsaState=10;

			break;
		case 10: //Unknown
			// lexical error has occured so enter into panic mode
			// exit from panic mode when a synchoronization token
			// is found.
			identifierType="";
			PanicMode();
			assignStatement=false;

			break;
		case 11:
			ch=GetChar();
			if(lexClass=='L')
			{
				fsaState=15;
				lexeme[lexIndex++]=ch;
			}
			else
				fsaState=10;

			break;
		case 12:
			GetChar(); // end of automata for accepting preprocessors
			fsaState=0;
			break;
		case 13:
			if(!mulComment)
			{
				ch=GetChar();
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
			}
			if(st.Compare("DIV")==0)
			{				
				while(buffer[0]!=NEWLINE && BytesRemaining!=0)
				{
					BytesRead=InputFileHandle.Read(buffer,1);
					BytesRemaining-=BytesRead;	
				}// end of while
				//m_LinesInSourceFile++;
				fsaState=0;
				ch=GetChar();
			}// end of if
			else if(st.Compare("MUL")==0)
			{	mulComment=true;
				while(buffer[0]!='*' && BytesRemaining!=0)
				{
					if(buffer[0]==NEWLINE)
						m_LinesInSourceFile++;
					BytesRead=InputFileHandle.Read(buffer,1);
					BytesRemaining-=BytesRead;	
				}// end of while

				fsaState=14;
			}
			else
				fsaState=10;
			
			
			break;
		case 14:
			
			BytesRead=InputFileHandle.Read(buffer,1);
			BytesRemaining-=BytesRead;	
			if(buffer[0]=='/')
			{
				ch=GetChar();
				fsaState=0;
				mulComment=false;
			}
			else fsaState=13;

			break;
		case 15:
			// handle preprocessor here
			while(lexClass=='L' || lexClass=='D' || lexClass=='N')
			{
				lexeme[lexIndex++]=GetChar();
			}//end of while
			
			lexIndex--;
			if(lexClass=='R')
			{
				fsaState=12;
				// return tag after lookUp of header file
				return LookUp(lexeme,lexIndex);
			}
			else
				fsaState=10;

			break;
		case 16:
			// Declarations FSA begins here
			while(lexClass=='S')
				ch=GetChar();
			if(lexClass=='A')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("MUL")==0)
				{	lexeme[lexIndex++]=ch;
					ch=GetChar();
					fsaState=17;
					return LookUp(lexeme,lexIndex);
				}
				else
					fsaState=10;
			}
			else if(lexClass=='L')
			{
				fsaState=18;
				lexeme[lexIndex++]=ch;
			}
			else 
				fsaState=10;

			break;
		case 17:
			while(lexClass=='S')
				ch=GetChar();
			
			if(lexClass=='L')
			{
				fsaState=18;
				lexeme[lexIndex++]=ch;
			}
			else
				fsaState=10;
			
			break;
		case 18:
			while(lexClass=='L' || lexClass=='D' || ch=='[' || ch==']')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			
			if(lexIndex>VARIABLE_LENGTH)
			{
				fsaState=10;
				identifierType="";
				lexemeLengthError=true;
			}
			else
			{
				fsaState=19;
				return LookUp(lexeme,lexIndex);
			}

			break;
		case 19:
		
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();
			
			}
			if(lexClass=='V')
			{
				lexeme[lexIndex++]=ch;
				ch=GetChar();
				fsaState=16;
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='T')
			{	
				lexeme[lexIndex++]=ch;				
				ch=GetChar();
				fsaState=0;
				identifierType=_T("");
				return LookUp(lexeme,lexIndex);
				
			}
			else if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("EQ")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=20;
					return st;
				}
				else
					fsaState=10;
				
			}
			else if(lexClass=='B')
			{ // to handle functions
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRO")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					identifierType="";
					fsaState=22;
					return st;
				}
				else
					fsaState=10;				

			}
			else
				fsaState=10;
			
						
			break;
		case 20:
			
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();
			
			}
			if(lexClass=='D')
			{
				lexeme[lexIndex++]=ch;
				while(lexClass=='D')
				{	
					ch=GetChar();
					lexeme[lexIndex++]=ch;
				}
				lexIndex--;
				fsaState=21;
				return LookUp(lexeme,lexIndex);
			}
			else fsaState = 10; // code added here

			break;
		case 21:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();
			
			}
			if(lexClass=='V')
			{
				lexeme[lexIndex++]=ch;
				ch=GetChar();
				fsaState=16;
				return LookUp(lexeme,lexIndex);

			}
			else if(lexClass=='T')
			{	
				lexeme[lexIndex++]=ch;
				ch=GetChar();
				fsaState=0;
				identifierType=_T("");
				return LookUp(lexeme,lexIndex);
				
			}
			else fsaState=10;

			break;
		case 22:
			// functions FSA begins here
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();
			
			}

			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRC")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=0;
					return st;
				}
				else
					fsaState=10;				
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				while(lexClass=='L')
				{
					ch=GetChar();
					lexeme[lexIndex++]=ch;
				}
				lexIndex--;
				fsaState=23;
				return LookUp(lexeme,lexIndex);
			}
			else fsaState=10;

			break;
		case 23:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();
			
			}
			if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=24;
			}
			else
				fsaState=10;
			
			break;
		case 24:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=25;
			return LookUp(lexeme,lexIndex);
			break;
		case 25:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}

			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRC")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=0;
					return st;
				}
				else
					fsaState=10;				
				
			}
			else if(lexClass=='V')
			{
				lexeme[lexIndex++]=ch;
				fsaState=22;
				ch=GetChar(); // code inserted here
				return LookUp(lexeme,lexIndex);
			}
			else fsaState=10;
			break;
		case 26:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}

			if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("EQ")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=27;
					return st;
				}
				else
					fsaState=10;
							
			}
			else fsaState=10;
			
			break;

		case 27:			
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}

			if(lexClass=='D')
			{
				lexeme[lexIndex++]=ch;
				fsaState=28;
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=29;
			}
			else fsaState=10;


			break;
		case 28:
			while(lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=30;
			return LookUp(lexeme,lexIndex);

			break;
		case 29:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=30;
			return LookUp(lexeme,lexIndex);

			break;
		case 30:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='T')
			{
				lexeme[lexIndex++]=ch;
				fsaState=0;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='A')
			{
				fsaState=27;
				//tempBuff[0]=ch;
				lexeme[lexIndex++]=ch;
				//lexIndex=1;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else 
				fsaState=10; // code added here

			break;
		case 34:
			// handle for statement here
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			
			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRO")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=35;
					return st;
				}
				else
					fsaState=10;				
			}
			else
				fsaState=10;

			break;
		case 35:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			
			if(lexClass=='T')
			{
				lexeme[lexIndex++]=ch;
				fsaState=42;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=36;
			}
			else fsaState = 10;

			break;
		case 36:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=37;
			return LookUp(lexeme,lexIndex);

			break;
		case 37:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
						
			if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("EQ")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=38;
					return st;
				}
				else
					fsaState=10;
							
			}
			else fsaState=10;
			break;
		case 38:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='D')
			{
				lexeme[lexIndex++]=ch;
				fsaState=39;
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=40;
			}
			else fsaState=10;
			break;
		case 39:
			while(lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=41;
			return LookUp(lexeme,lexIndex);

			break;
		case 40:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=41;
			return LookUp(lexeme,lexIndex);

			break;
		case 41:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='V')
			{
				lexeme[lexIndex++]=ch;
				fsaState=35;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='T')
			{				
				lexeme[lexIndex++]=ch;
				fsaState=42;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else fsaState=10;

			break;
			// second portion of for after first semicolon
		case 42:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			
			if(lexClass=='T')
			{
				lexeme[lexIndex++]=ch;
				fsaState=50;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=43;
			}
			else fsaState=10;

			break;
		case 43:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=44;
			return LookUp(lexeme,lexIndex);

			break;
		case 44:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
						
			if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("LT")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=45;
					//return st;
				}
				else if(st.Compare("GT")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=45;
					//return st;
				}

				else
					fsaState=10;
							
			}
			else fsaState=10;
			break;
		case 45:
			if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("EQ")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=46;					
					return LookUp(lexeme,lexIndex);
				}

				else
					fsaState=10;							
			}
			else if(lexClass=='L' || lexClass=='D' || lexClass=='S')
			{
				if(lexIndex > 0)
					return LookUp(lexeme,lexIndex);				
				
				lexeme[lexIndex++]=ch;				
				ch=GetChar();
				fsaState=46; 
			}
			else fsaState=10;
			
			break;
		case 46:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='D')
			{
				lexeme[lexIndex++]=ch;
				fsaState=47;
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=48;
			}
			else fsaState=10;
			break;
		case 47:
			while(lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=49;
			return LookUp(lexeme,lexIndex);

			break;
		case 48:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=49;
			return LookUp(lexeme,lexIndex);

			break;
		case 49:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='V')
			{
				lexeme[lexIndex++]=ch;
				fsaState=42;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='T')
			{				
				lexeme[lexIndex++]=ch;
				fsaState=50;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else fsaState=10;

			break;
			// third portion of for statement after second semicolon
		case 50:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			
			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRC")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=0;
					return st;
				}
				else
					fsaState=10;				
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=51;
			}
			else
				fsaState=10;

			break;
		case 51:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=52;
			return LookUp(lexeme,lexIndex);

			break;
		case 52:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
						
			if(lexClass=='A')
			{
				lexeme[lexIndex++]=ch;					
				ch=GetChar();
				fsaState=53;
			}
			else fsaState=10;
			
			break;
		case 53:
			if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("EQ")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=54;
					return LookUp(lexeme,lexIndex);
				}
				else
					fsaState=10;				
			}
			else 
				fsaState=10;
			
			break;
		case 54:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}

			while(lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=55;
			return LookUp(lexeme,lexIndex);
			break;
		case 55:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			
			if(lexClass=='V')
			{
				lexeme[lexIndex++]=ch;
				fsaState=50;
				ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRC")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=0;
					return st;
				}
				else
					fsaState=10;				
			}
			else fsaState=10;
			
			break;
			// FSA of the while loop
		case 58:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			
			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRO")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=59;
					return st;
				}
				else
					fsaState=10;				
			}
			else
				fsaState=10;

			break;
		case 59:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=60;
			}
			else fsaState=10;
			break;
		case 60:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=61;
			return LookUp(lexeme,lexIndex);

			break;
		case 61:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
						
			if(lexClass=='R')
			{
					lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=62;
							
			}
			else fsaState=10;
			break;
		case 62:
			if(lexClass=='R')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("EQ")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=63;					
					return LookUp(lexeme,lexIndex);
				}

				else
					fsaState=10;							
			}
			else if(lexClass=='L' || lexClass=='D' || lexClass=='S')
			{
				fsaState=63;
				//ch=GetChar();
				return LookUp(lexeme,lexIndex);
			}
			else fsaState=10;
			
			break;
		case 63:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='D')
			{
				lexeme[lexIndex++]=ch;
				fsaState=64;
			}
			else if(lexClass=='L')
			{
				lexeme[lexIndex++]=ch;
				fsaState=65;
			}
			else fsaState=10;
			break;
		case 64:
			while(lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=66;
			return LookUp(lexeme,lexIndex);

			break;
		case 65:
			while(lexClass=='L' || lexClass=='D')
			{
				ch=GetChar();
				lexeme[lexIndex++]=ch;
			}
			lexIndex--;
			fsaState=66;
			return LookUp(lexeme,lexIndex);

			break;
		case 66:
			if(lexClass=='S')
			{
				while(lexClass=='S')
					ch=GetChar();		
			}
			if(lexClass=='B')
			{
				tempBuff[0]=ch;
				st=LookUp(tempBuff,1);
				if(st.Compare("BRC")==0)
				{	lexeme[lexIndex++]=ch;					
					ch=GetChar();
					fsaState=0;
					return st;
				}
				else
					fsaState=10;				
				
			}
			else if(lexClass=='G')
			{
				lexeme[lexIndex++]=ch;
				ch=GetChar();
				fsaState=67;
			}
			else fsaState=10;

			break;
		case 67:
			if(lexClass=='G')
			{
				lexeme[lexIndex++]=ch;					
				ch=GetChar();
				fsaState=59;
				return LookUp(lexeme,lexIndex);				
			}
			else fsaState=10;
			break;

		default :
			break;

		}// end of switch


	}// end of while loop

	//******************** Insert Into Symbol table ***************//
if(BytesRemaining == 0)
{	
	lexIndex=0;
	return "NULL";
}

}// end of function




void CLSSAnalyzerView::OpenFile()
{
	if(!InputFileHandle.Open(m_FileName,CFile::modeRead,NULL))
	{
		MessageBox("Error Opening Input File.");
		return;
	}// end of if
	else
		BytesRemaining = InputFileHandle.GetLength();// get the length of file

}// end of file


char CLSSAnalyzerView::GetChar()
{
	if(firstTime)
		lexClass = NULL;
	
	previousLexClass=lexClass;		
	
	char buffer[2];

Repeat:	
	if(BytesRemaining>0)
	{
		// for double buffering
		if(firstTime==true)
		{
			BytesRead=InputFileHandle.Read (buffer,2);
			//firstTime=false;
		}
		else
			BytesRead=InputFileHandle.Read (buffer,1);

		BytesRemaining-=BytesRead;	
	}
	else
		buffer[0]='\0';

	// first 13 and then 10
	if(buffer[0]==13 || buffer[0]==10)
	{
		if(buffer[0]==10)
			m_LinesInSourceFile++;
		
		goto Repeat;
	}
	// lower case and upper case letters
	if(buffer[0] >=65 && buffer[0]<=90 || buffer[0] >=97 && buffer[0]<=122 || buffer[0]=='_')
	{
		lexClass = 'L';
	}// end of if
	// decimal / literals
	else if(buffer[0]>=48 && buffer[0]<58)
	{
		lexClass = 'D';
		countDigits++;
	}// end of else if
	// language operators
	else if(buffer[0]=='+' || buffer[0]=='-' || buffer[0]=='*' || buffer[0]=='/' || buffer[0]=='%')
	{	// arithmatic operators
		lexClass = 'A';
	}// end of else if
	else if( buffer[0]=='='  || buffer[0]=='<' || buffer[0]=='>' || buffer[0]=='!')
	{	// relational operators
		lexClass = 'R';
	}// end of if
	else if(buffer[0]=='|' || buffer[0]=='&'  )
	{	// logical operators
		lexClass = 'G';
	}// end of if
	else if (buffer[0]==';')
	{
		// seperator or statement terminator
		lexClass = 'T';
	}
	else if(buffer[0]==',')
	{
		lexClass = 'V';
	}
	// preprocessor
	else if(buffer[0]=='#')
	{
		lexClass = 'P';
	}
	else if(buffer[0]==' ')
	{
		// space
		lexClass = 'S';
	}
	else if(buffer[0]=='(' || buffer[0]==')' || buffer[0]=='{' || buffer[0]=='}'  || buffer[0]=='[' || buffer[0]==']' )
	{
		lexClass = 'B';	
	}
	else if(buffer[0]=='"' || buffer[0]=='"')
	{
		lexClass = 'Q';
	}
	else if(buffer[0]=='.')
	{
		lexClass = 'N';
	}
	else
	{	// unknown
		lexClass = 'U';
	}

// determine the class for the next char
	// lower case and upper case letters
if(firstTime)
{
	if(buffer[1] >=65 && buffer[1]<=90 || buffer[1] >=97 && buffer[1]<=122 || buffer[1]=='_')
	{
		nextLexClass = 'L';
	}// end of if
	// decimal / literals
	else if(buffer[1]>=48 && buffer[1]<58)
	{
		nextLexClass = 'D';
	}// end of else if
	// language operators
	else if(buffer[1]=='+' || buffer[1]=='-' || buffer[1]=='*' || buffer[1]=='/' || buffer[1]=='%')
	{	// arithmatic operators
		nextLexClass = 'A';
	}// end of else if
	else if( buffer[1]=='='  || buffer[1]=='<' || buffer[1]=='>' || buffer[1]=='!')
	{	// relational operators
		nextLexClass = 'R';
	}// end of if
	else if(buffer[1]=='|' || buffer[1]=='&'  )
	{	// logical operators
		nextLexClass = 'G';
	}// end of if
	else if (buffer[1]==';')
	{
		// seperator or statement terminator
		nextLexClass = 'T';
	}
	else if(buffer[1]==',')
	{
		nextLexClass = 'V';
	}
	// preprocessor
	else if(buffer[1]=='#')
	{
		nextLexClass = 'P';
	}
	else if(buffer[1]==' ')
	{
		// space
		nextLexClass = 'S';
	}
	else if(buffer[1]=='(' || buffer[1]==')' || buffer[1]=='{' || buffer[1]=='}' || buffer[1]=='[' || buffer[1]==']' )
	{
		nextLexClass = 'B';
	}
	else if(buffer[1]=='"' || buffer[1]=='"')
	{
		nextLexClass = 'Q';
	}
	else
	{	// unknown
		nextLexClass = 'U';
	}

}// end of if on firstTime

	if(firstTime)
	{		
		sourceFileChars[sourceIndex++]=buffer[0];
		sourceFileChars[sourceIndex++]=buffer[1];
		firstTime=false;
	}
	else
	{
		sourceFileChars[sourceIndex++]=buffer[0];
		char tempClass=nextLexClass;
		nextLexClass=lexClass;
		lexClass=tempClass; 		
	}
	
	
	char ch;
	ch=sourceFileChars[returnIndex++];//buffer[0];
	return ch;

}// end of function


void CLSSAnalyzerView::InitTypes()
{
	KnownTypes[0]="float";			Knownlexeme[0]="DEC"; 
	KnownTypes[1]="int";			Knownlexeme[1]="DEC";
	KnownTypes[2]="double";			Knownlexeme[2]="DEC";
	KnownTypes[3]="char";			Knownlexeme[3]="DEC";
	KnownTypes[4]="include";		Knownlexeme[4]="RW";
	KnownTypes[5]="iostream.h";		Knownlexeme[5]="LIB";
	KnownTypes[6]="conio.h";		Knownlexeme[6]="LIB";
	KnownTypes[7]="void";			Knownlexeme[7]="DEC";
	KnownTypes[8]="main";			Knownlexeme[8]="main";
	KnownTypes[9]="for";			Knownlexeme[9]="for";
	KnownTypes[10]="if";			Knownlexeme[10]="if";
	KnownTypes[11]="while";			Knownlexeme[11]="while";
	KnownTypes[12]="struct";		Knownlexeme[12]="struct";
	KnownTypes[13]="do";			Knownlexeme[13]="do";
	KnownTypes[14]="long";			Knownlexeme[14]="DEC";
	KnownTypes[15]="stdio.h";		Knownlexeme[15]="LIB";
	KnownTypes[16]="+";				Knownlexeme[16]="ADD";
	KnownTypes[17]="-";				Knownlexeme[17]="SUB";
	KnownTypes[18]="*";				Knownlexeme[18]="MUL";
	KnownTypes[19]="/";				Knownlexeme[19]="DIV";
	KnownTypes[20]="=";				Knownlexeme[20]="EQ";
	KnownTypes[21]=";";				Knownlexeme[21]="SC";
	KnownTypes[22]="{";				Knownlexeme[22]="CBO";
	KnownTypes[23]="}";				Knownlexeme[23]="CBC";
	KnownTypes[24]="[";				Knownlexeme[24]="SBO";
	KnownTypes[25]="]";				Knownlexeme[25]="SBC";
	KnownTypes[26]="(";				Knownlexeme[26]="BRO";
	KnownTypes[27]=")";				Knownlexeme[27]="BRC";
	KnownTypes[28]="<=";			Knownlexeme[28]="LE";
	KnownTypes[29]=">=";			Knownlexeme[29]="GE";
	KnownTypes[30]="<";				Knownlexeme[30]="LT";
	KnownTypes[31]=">";				Knownlexeme[31]="GT";
	KnownTypes[32]="+=";			Knownlexeme[32]="PEQ";
	KnownTypes[33]="-=";			Knownlexeme[33]="SEQ";
	KnownTypes[34]="*=";			Knownlexeme[34]="MEQ";
	KnownTypes[35]="/=";			Knownlexeme[35]="DEQ";
	KnownTypes[36]="||";			Knownlexeme[36]="OR";
	KnownTypes[37]="&&";			Knownlexeme[37]="AND";
	KnownTypes[38]="!=";			Knownlexeme[38]="NEQ";
	KnownTypes[39]=",";				Knownlexeme[39]="COMMA";
	
	for(int in=0;in<KNOWN_WORDS;in++)
		KnownTypesValue[in]=in;

}// end of function



int CLSSAnalyzerView::GetHashKey(char tok[], int length)
{
int sum=0;
for(int u=0;u<length;u++)
	sum+=tok[u]*u;

return (sum%100);

}// end of function

CString CLSSAnalyzerView::LookUp(char lexeme[], int length)
{
	CString str;
//	bool matched=false;

	for(int i=0;i<length;i++)
		str+=lexeme[i];

	for(i=0;i<KNOWN_WORDS;i++)
	{

		if(str.Compare(KnownTypes[i])==0)
		{
			return Knownlexeme[i];
		}
	}// end of for

		int tempCount=0;
		for(int j=0;j<length;j++)
		{
			if(lexeme[j]>=48 && lexeme[j]<58)
				tempCount++;
		}
		if(tempCount==length)
			str="Digit";
			//countDigits=0;		
		else
			str="Identifier";


return str;

}// end of function

void CLSSAnalyzerView::InsertLexemeIntoSymbolTable()
{
	verify=false;
	if(lexIndex > 0)
	{	// insert the lexeme in the symbol table.
		for(int i=lexIndex;i<50;i++)
			lexeme[i]='\0';

		int hashkey=GetHashKey(lexeme,lexIndex);
		if(ST[hashkey].bucketS==NULL)
		{
			symbtabTemp=new SymbolTable;
			for(int val=0;val<lexIndex;val++)
				symbtabTemp->lexeme[val]=lexeme[val];
			for(val;val<32;val++)
				symbtabTemp->lexeme[val]='\0';

			for(int k=0;k<lexemeType.GetLength();k++)
				symbtabTemp->token[k]=lexemeType.GetAt(k);
			for(k;k<32;k++)
				symbtabTemp->token[k]='\0';
		
			symbtabTemp->LOD=m_LinesInSourceFile;
			symbtabTemp->size=lexIndex;
			if(lexemeType.Compare("Identifier")==0 && identifierType.Compare("")!=0)
				symbtabTemp->type=identifierType;
			else if(lexemeType.Compare("Identifier")==0 && identifierType.Compare("")==0)
				symbtabTemp->type=_T("UD");
			else
				symbtabTemp->type=_T("NK");

			symbtabTemp->next=NULL;
			symbtabTemp->lineofrefS=NULL;
			symbtabTemp->lineofrefL=NULL;
			ST[hashkey].bucketS=symbtabTemp;
			ST[hashkey].bucketL=symbtabTemp;
			//SymbolTable_Index++;
			verify=true;
		}// end of if
		else
		{
			symbtabTemp=ST[hashkey].bucketS;
			while(symbtabTemp!=NULL)
			{
				if(strcmp(lexeme,symbtabTemp->lexeme)==0)
				{ // token found so insert line of reference
					verify=true;
					if(symbtabTemp->lineofrefS==NULL)
					{
						symbtabTemp->lineofrefS=new LineofReference;
						symbtabTemp->lineofrefS->line_Number=m_LinesInSourceFile;
						symbtabTemp->lineofrefS->next=NULL;
						symbtabTemp->lineofrefL=symbtabTemp->lineofrefS;
					}
					else
					{
						symbtabTemp->lineofrefT=new LineofReference;
						symbtabTemp->lineofrefT->line_Number=m_LinesInSourceFile;				
						symbtabTemp->lineofrefT->next=NULL;
						symbtabTemp->lineofrefL->next=symbtabTemp->lineofrefT;
						symbtabTemp->lineofrefL=symbtabTemp->lineofrefT;
					}
				}// end of if
				symbtabTemp=symbtabTemp->next;

			}// end of while

		}// end of else

		if(verify==false)
		{
			// token not found so insert the token and other details.
			symbtabTemp=new SymbolTable;
			for(int val=0;val<lexIndex;val++)
				symbtabTemp->lexeme[val]=lexeme[val];
			for(val;val<32;val++)
				symbtabTemp->lexeme[val]='\0';

			symbtabTemp->LOD=m_LinesInSourceFile;
			symbtabTemp->size=lexIndex;
			if(lexemeType.Compare("Identifier")==0 && identifierType.Compare("")!=0)
				symbtabTemp->type=identifierType;
			else if(lexemeType.Compare("Identifier")==0 && identifierType.Compare("")==0)
				symbtabTemp->type=_T("UD");
			else
				symbtabTemp->type=_T("NK");

			for(int k=0;k<lexemeType.GetLength();k++)
				symbtabTemp->token[k]=lexemeType.GetAt(k);
			for(k;k<32;k++)
				symbtabTemp->token[k]='\0';
			symbtabTemp->next=NULL;
			symbtabTemp->lineofrefS=NULL;
			symbtabTemp->lineofrefL=NULL;

			ST[hashkey].bucketL->next=symbtabTemp;   
			ST[hashkey].bucketL=symbtabTemp;

		}
				

	}// end of if on lexIndex > 0



}// end of function

void CLSSAnalyzerView::DisplaySymbolTable()
{
	SymbolTable_Index=0;
	movewithclick=0;
	char string[25];

	
	for(int kee=0;kee<SYMBOL_TABLE_SIZE;kee++)
	{
		symbtabTemp=ST[kee].bucketS;

		while(symbtabTemp!=NULL)
		{
			
			m_Lexeme.AddString(symbtabTemp->lexeme);
			// save line of reference in an array sequencially
			int localCount=0;
			symbtabTemp->lineofrefT=symbtabTemp->lineofrefS;
			while(symbtabTemp->lineofrefT!=NULL)
			{
				int ln=symbtabTemp->lineofrefT->line_Number;
				ReferenceLine[SymbolTable_Index][localCount++]=ln;
				symbtabTemp->lineofrefT=symbtabTemp->lineofrefT->next;
			}

			ReferenceCount[SymbolTable_Index++]=localCount;
			// end of save line of reference in an array
//			itoa(KnownTypesValue[pare],string,10);
			m_LexemeType.AddString(symbtabTemp->type);
			m_Token.AddString(symbtabTemp->token);
			ltoa(symbtabTemp->size,string,10); // perform conversion
			m_LexemeSize.AddString(string);
			ltoa(symbtabTemp->LOD,string,10); // perform conversion
			m_LOD.AddString(string);
			symbtabTemp=symbtabTemp->next;
		}// end of while loop

	} // end of for loop on Symbol Table


	UpdateData(FALSE);
}// end of function

//error recovery technique
void CLSSAnalyzerView::PanicMode()
{
	m_Panic_Mode_Count++;

	CString err_St;
	if(lexemeLengthError)
	{
		lexemeLengthError=false;
		for(int k=0;k<lexIndex;k++)
			err_St+=lexeme[k];
		m_ErrorCause.AddString(err_St);
		err_St="Identifier Length >";
		m_ErrorMessage.AddString(err_St);		

		Skip_Till_Synchronization();

	}
	else if(lexClass=='U' ) // unknown lexeme class
	{ // start skipping characters until a
		// synchoronizing token is found.

		err_St+=ch;
		m_ErrorCause.AddString(err_St);
		err_St="Invalid Character";
		m_ErrorMessage.AddString(err_St);		

		Skip_Till_Synchronization();
						
	}// end of if
	else if(nextLexClass=='U')
	{ 
		ch=GetChar();
		err_St+=ch;
		m_ErrorCause.AddString(err_St);
		err_St="Invalid Character";
		m_ErrorMessage.AddString(err_St);		

		Skip_Till_Synchronization();
	
	}
	else
	{
		// the automata for some statement has failed
		// it will lead to a possible syntax error later
		// to be detected by the syntax analysis phase
		// but for now we'll skip characters till a synchoronizing
		// token is found
		err_St+=ch;
		m_ErrorCause.AddString(err_St);
		err_St="FSA State Voilation";
		m_ErrorMessage.AddString(err_St);

		Skip_Till_Synchronization();
	}

	fsaState=0;

	ch=GetChar();
	ch=GetChar();
	lexIndex=0;
	UpdateData(FALSE);

}// end of function

void CLSSAnalyzerView::Skip_Till_Synchronization()
{
	char buffer[1];
		
		while(buffer[0]!=59  /*&& buffer[0]!=LINEFEED*/ && BytesRemaining!=0 )
		{
			BytesRead=InputFileHandle.Read (buffer,1);
			BytesRemaining-=BytesRead;
			m_Skipped_Characters+=buffer[0]; // display the characters skipped in panic mode
		}// end of while		
		
		m_Skipped_Characters+="   ##EPM##   "; // move to the new line to seperate each panic mode output
		m_Skipped_Characters+=13;
		m_Skipped_Characters+=10;

}// end of function


void CLSSAnalyzerView::OnLineofreference() 
{
	// TODO: Add your control notification handler code here
	for (int k=0;k<100;k++)
		m_LOR.DeleteString(0); // clear previous data

	char string[25];

	for(int w=0;w<ReferenceCount[movewithclick];w++)
	{
		int ln=ReferenceLine[movewithclick][w];
		itoa(ln,string,10); // perform conversion
		m_LOR.AddString(string);
	}

	m_Lexeme.SetCurSel(movewithclick);
	m_LexemeType.SetCurSel(movewithclick);
	m_LOD.SetCurSel(movewithclick);
	m_Token.SetCurSel(movewithclick);
	m_LexemeSize.SetCurSel(movewithclick);

	m_MoveWClick=movewithclick;

	UpdateData(FALSE);

	movewithclick++;
	if(movewithclick==SymbolTable_Index)
	{
		movewithclick=0;
	}
	
}// end of function

void CLSSAnalyzerView::InitializeFirstSet()
{

	first_Set_AStmt[0][0]="Identifier";
	first_Set_AStmt[0][1]="Identifier";
	first_Set_AStmt[0][2]="Digit";
	first_Set_AStmt[0][3]="ADD";
	first_Set_AStmt[0][4]="SUB";
	first_Set_AStmt[0][5]="MUL";
	first_Set_AStmt[0][6]="DIV";
	first_Set_AStmt[0][7]="NULL";

	first_Set_AStmt[1][0]="E";
	first_Set_AStmt[1][1]="TZ";
	first_Set_AStmt[1][2]="TZ";
	first_Set_AStmt[1][3]="EMPTY";
	first_Set_AStmt[1][4]="EMPTY";
	first_Set_AStmt[1][5]="EMPTY";
	first_Set_AStmt[1][6]="EMPTY";
	first_Set_AStmt[1][7]="EMPTY";

	first_Set_AStmt[2][0]="Z";
	first_Set_AStmt[2][1]="EMPTY";
	first_Set_AStmt[2][2]="EMPTY";
	first_Set_AStmt[2][3]="+TZ";
	first_Set_AStmt[2][4]="-TZ";
	first_Set_AStmt[2][5]="EMPTY";
	first_Set_AStmt[2][6]="EMPTY";
	first_Set_AStmt[2][7]="NULL";

	first_Set_AStmt[3][0]="T";
	first_Set_AStmt[3][1]="FY";
	first_Set_AStmt[3][2]="FY";
	first_Set_AStmt[3][3]="EMPTY";
	first_Set_AStmt[3][4]="EMPTY";
	first_Set_AStmt[3][5]="EMPTY";
	first_Set_AStmt[3][6]="EMPTY";
	first_Set_AStmt[3][7]="EMPTY";

	first_Set_AStmt[4][0]="Y";
	first_Set_AStmt[4][1]="EMPTY";
	first_Set_AStmt[4][2]="EMPTY";
	first_Set_AStmt[4][3]="EMPTY";
	first_Set_AStmt[4][4]="EMPTY";
	first_Set_AStmt[4][5]="*FY";
	first_Set_AStmt[4][6]="/FY";
	first_Set_AStmt[4][7]="NULL";

	first_Set_AStmt[5][0]="F";
	first_Set_AStmt[5][1]="I";
	first_Set_AStmt[5][2]="D";
	first_Set_AStmt[5][3]="EMPTY";
	first_Set_AStmt[5][4]="EMPTY";
	first_Set_AStmt[5][5]="EMPTY";
	first_Set_AStmt[5][6]="EMPTY";
	first_Set_AStmt[5][7]="EMPTY";

	int flexIndex=0;

	for(int row=0;row<6;row++)
	{
		for(int col=0;col<8;col++)
		{
			m_FirstSet.SetTextArray(flexIndex++,first_Set_AStmt[row][col]);
			
		}

	}
//m_FirstSet.SetFocus();
}// end of function

CString CLSSAnalyzerView::GetLexemeType(char *lexeme, int lexIndex)
{

		int hashkey=GetHashKey(lexeme,lexIndex);
		if(ST[hashkey].bucketS!=NULL)
		{
			symbtabTemp=ST[hashkey].bucketS;
			while(symbtabTemp!=NULL)
			{
				if(strcmp(lexeme,symbtabTemp->lexeme)==0)
				{ // token found so insert line of reference
						return symbtabTemp->type;
				}// end of if
				symbtabTemp=symbtabTemp->next;

			}// end of while

		}// end of else
		else return "none";


return "none";
}// end of function

void CLSSAnalyzerView::CheckSemantics(CString lexStmt)
{
	m_Semantics+="-----------------------------";
	m_Semantics+=13;m_Semantics+=10;
	m_Semantics+=lexStmt;
	m_Semantics+=13;m_Semantics+=10;

	CString type1,type2,opr;
	int validJ;
//	saveLexTypes[tyIndex];
	for(int u=0;u<tyIndex;u++)
		m_Semantics+=saveLexTypes[u];
	m_Semantics+=13;m_Semantics+=10;
	
	if(tyIndex > 3)
	{
		for(int j=2;j<tyIndex;j+=2)
		{
			if(j<(tyIndex-1))
			{
				type1=saveLexTypes[j];
				opr=saveLexTypes[j+1];
				type2=saveLexTypes[j+2];
				saveLexTypes[j+2]=GetCompatInfo(type1,opr,type2);
				saveLexTypes[j]=saveLexTypes[j+2];
				m_Semantics+=saveLexTypes[j];
				m_Semantics+=saveLexTypes[j+2];
				m_Semantics+=13;m_Semantics+=10;
				validJ=j+2;
			}
		}
		
		m_Semantics+=saveLexTypes[0];
		m_Semantics+=saveLexTypes[validJ];
		m_Semantics+=13;m_Semantics+=10;
		saveLexTypes[0]=AssignmentCompat(saveLexTypes[0],saveLexTypes[validJ]);
		m_Semantics+=saveLexTypes[0];
		m_Semantics+=13;m_Semantics+=10;

	}// end of if
	else
	{
		saveLexTypes[0]=AssignmentCompat(saveLexTypes[0],saveLexTypes[2]);
		m_Semantics+=saveLexTypes[0];
		m_Semantics+=13;m_Semantics+=10;

	}// end of else

	UpdateData(FALSE);
}// end of function

CString CLSSAnalyzerView::GetCompatInfo(CString type1, CString opr, CString type2)
{

	if(type1=="long" && type2=="long")
		return "long";
	else if(type1=="long" && type2=="float")
		return "long";
	else if(type1=="long" && type2=="int")
		return "long";
	else if(type1=="long" && type2=="char")
		return "error";
	else if(type1=="float" && type2=="long")
		return "long";
	else if(type1=="float" && type2=="float")
		return "float";
	else if(type1=="float" && type2=="int")
		return "float";
	else if(type1=="float" && type2=="char")
		return "error";
	else if(type1=="int" && type2=="long")
		return "long";
	else if(type1=="int" && type2=="float")
		return "float";
	else if(type1=="int" && type2=="int")
		return "int";
	else if(type1=="int" && type2=="char")
		return "error";
	else if(type1=="char" && type2=="long")
		return "error";
	else if(type1=="char" && type2=="float")
		return "error";
	else if(type1=="char" && type2=="int")
		return "error";
	else if(type1=="char" && type2=="char")
		return "char";
	else
		return "error";


}// end of function


CString CLSSAnalyzerView::AssignmentCompat(CString type1, CString type2)
{

	if(type1=="long" && type2=="long")
		return "Valid Assignment";
	else if(type1=="long" && type2=="int")
		return "Valid Assignment";
	else if(type1=="long" && type2=="float")
		return "Valid Assignment (loss of precision)";
	else if(type1=="long" && type2=="char")
		return "error";
	else if(type1=="float" && type2=="long")
		return "error";
	else if(type1=="float" && type2=="float")
		return "Valid Assignment";
	else if(type1=="float" && type2=="int")
		return "Valid Assignment";
	else if(type1=="float" && type2=="char")
		return "error";
	else if(type1=="int" && type2=="long")
		return "error";
	else if(type1=="int" && type2=="float")
		return "error";
	else if(type1=="int" && type2=="int")
		return "Valid Assignment";
	else if(type1=="int" && type2=="char")
		return "error";
	else if(type1=="char" && type2=="long")
		return "error";
	else if(type1=="char" && type2=="float")
		return "error";
	else if(type1=="char" && type2=="int")
		return "error";
	else if(type1=="char" && type2=="char")
		return "Valid Assignment";
	else
		return "error";



}// end of function
