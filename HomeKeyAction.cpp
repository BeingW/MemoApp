//HomeKeyAction.cpp

/*
파일명 : HomeKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 홈 키
수정 :
*/

#include "HomeKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

HomeKeyAction::HomeKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

HomeKeyAction::~HomeKeyAction() {
}

void HomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->codeEditorForm->current->First();
}