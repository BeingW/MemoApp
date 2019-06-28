//CtrlRightKeyAction.cpp
/*
파일명 : CtrlRightKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 오른쪽 방향키
수정 :
*/

#include "CtrlRightKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

CtrlRightKeyAction::CtrlRightKeyAction(CodeEditorForm * codeEditorForm)
	:KeyAction(codeEditorForm) {
	
}

CtrlRightKeyAction::~CtrlRightKeyAction() {
}

void CtrlRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* line;
	Glyph* memo;
	Long lineCurrent;
	Long lineLength;

	memo = this->codeEditorForm->memo;
	line = this->codeEditorForm->current;
	
	line->RightWord();

	lineCurrent = line->GetCurrent();
	lineLength = line->GetLength();

	if (lineCurrent == lineLength) {
		memo->RightWord();
	}

}
