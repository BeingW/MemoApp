//CtrlEndKeyAction.cpp
/*
파일명 : CtrlEndKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 엔드 키
수정 :
*/
#include "CtrlEndKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

CtrlEndKeyAction::CtrlEndKeyAction(CodeEditorForm *codeEditorForm) : KeyAction(codeEditorForm) {
}

CtrlEndKeyAction::~CtrlEndKeyAction() {

}
void CtrlEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long memoCurrent;
	memoCurrent = this->codeEditorForm->memo->Last();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->Last();
}