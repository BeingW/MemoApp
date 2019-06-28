//LeftKeyAction.cpp

/*
파일명 : LeftKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 왼쪽 방향키
수정 :
*/

#include "LeftKeyAction.h"
#include "CodeEditorForm.h"
#include "RegionController.h"
#include "Glyph.h"

LeftKeyAction::LeftKeyAction(CodeEditorForm *codeEditorForm) 
	:KeyAction(codeEditorForm) {
}

LeftKeyAction:: ~LeftKeyAction() {
}

void LeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long ret;
	Long lineCurrent;
	Long memoCurrent;

	ret = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Previous();

	if (ret == lineCurrent) {
		ret = this->codeEditorForm->memo->GetCurrent();
		memoCurrent = this->codeEditorForm->memo->Previous();

		if (ret != memoCurrent) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			this->codeEditorForm->current->Last();
		}
	}

	this->codeEditorForm->regionController->CleanRegion();
}