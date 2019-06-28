//CtrlHomeKeyAction.cpp
/*
파일명 : CtrlHomeKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 홈 키
수정 :
*/
#include "CtrlHomeKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

CtrlHomeKeyAction::CtrlHomeKeyAction(CodeEditorForm *codeEditorForm) : KeyAction(codeEditorForm) {
}

CtrlHomeKeyAction::~CtrlHomeKeyAction() {

}
void CtrlHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long memoCurrent;
	memoCurrent = this->codeEditorForm->memo->First();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->First();
}