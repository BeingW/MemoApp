//CodeEditorFormApp.cpp
/*
파일명 : CodeEditorForm.cpp
작성일자 : 2019년 03월 27일
작성자 : 김영재
기능 : 메인
수정 :
*/

#include "CodeEditorFormApp.h"
#include "CodeEditorForm.h"
#include "resource.h"

/*
함수명: Initinstance
기능: MFC 메인
*/
BOOL CodeEditorFormApp::InitInstance() {
	CodeEditorForm *codeEditorForm = new CodeEditorForm;
	codeEditorForm->Create(NULL, (LPCTSTR)"제목없음 - CodeEditorForm", WS_OVERLAPPEDWINDOW, CRect(200, 120, 640, 400), NULL, MAKEINTRESOURCE(IDR_MENU1));
	codeEditorForm->ShowWindow(SW_SHOW);
	codeEditorForm->UpdateWindow();
	this->m_pMainWnd = codeEditorForm;
	return TRUE;
}
CodeEditorFormApp codeEditorFormApp;