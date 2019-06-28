//CtrlLeftKeyAction.cpp
/*
파일명 : CtrlLeftKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 왼쪽 방향키
수정 :
*/

#include "CtrlLeftKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

CtrlLeftKeyAction::CtrlLeftKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlLeftKeyAction::~CtrlLeftKeyAction() {
}

void CtrlLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* line;
	Glyph* memo;
	Long lineCurrent;

	memo = this->codeEditorForm->memo;
	line = this->codeEditorForm->current;

	line->LeftWord();

	lineCurrent = line->GetCurrent();

	if (lineCurrent == 0) {
		memo->LeftWord();
	}

}

