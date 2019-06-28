//EndKeyAction.cpp

/*
파일명 : EndtKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 엔드 키
수정 :
*/

#include "EndKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"


EndKeyAction::EndKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

EndKeyAction::~EndKeyAction() {
}

void EndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->codeEditorForm->current->Last();
}
