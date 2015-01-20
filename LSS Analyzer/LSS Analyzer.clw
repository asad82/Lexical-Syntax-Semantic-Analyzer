; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLSSAnalyzerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LSS Analyzer.h"
LastPage=0

ClassCount=5
Class1=CLSSAnalyzerApp
Class2=CLSSAnalyzerDoc
Class3=CLSSAnalyzerView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource7=IDD_LSSANALYZER_FORM

[CLS:CLSSAnalyzerApp]
Type=0
HeaderFile=LSS Analyzer.h
ImplementationFile=LSS Analyzer.cpp
Filter=N

[CLS:CLSSAnalyzerDoc]
Type=0
HeaderFile=LSS AnalyzerDoc.h
ImplementationFile=LSS AnalyzerDoc.cpp
Filter=N

[CLS:CLSSAnalyzerView]
Type=0
HeaderFile=LSS AnalyzerView.h
ImplementationFile=LSS AnalyzerView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CLSSAnalyzerView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=LSS Analyzer.cpp
ImplementationFile=LSS Analyzer.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_LSSANALYZER_FORM]
Type=1
Class=CLSSAnalyzerView
ControlCount=39
Control1=IDC_READANALYSE,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FILENAME,edit,1350631552
Control5=IDC_CLEAR,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LINESINSOURCEFILE,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_COMPILATION_PROGRESS,msctls_progress32,1350565889
Control10=IDC_STATIC,button,1342177287
Control11=IDC_LEXEME,listbox,1352728833
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TOKEN,listbox,1352728833
Control14=IDC_TYPE,listbox,1352728833
Control15=IDC_LEXEMESIZE,listbox,1352728833
Control16=IDC_LOD,listbox,1352728833
Control17=IDC_LOR,listbox,1352728833
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_ERROR_CAUSE,listbox,1352728833
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308352
Control28=IDC_NO_OF_TIMES_IN_PANIC_MODE,edit,1350631552
Control29=IDC_CHARCTERS_SKIPPED_IN_PANIC_MODE,edit,1352728708
Control30=IDC_ERROR_MESSAGE,listbox,1352728833
Control31=IDC_STATIC,static,1342308352
Control32=IDC_LINEOFREFERENCE,button,1342242816
Control33=IDC_LEXEME_INDEX,edit,1350631552
Control34=IDC_STATIC,button,1342177287
Control35=IDC_CFG,edit,1352728708
Control36=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,button,1342177287
Control39=IDC_SEMANTICS,edit,1352728708

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

