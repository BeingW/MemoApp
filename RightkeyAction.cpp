/*
파일명 : RightKeyAction.cpp
작성일자 : 2019년 04월 14일
작성자 : 허수진
기능 : RightKeyAction
*/
//RightKeyAction.cpp

/*
파일명 : RightKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 오른쪽 방향키
수정 :
*/

#include "RightKeyAction.h"
#include "CodeEditorForm.h"
#include "RegionController.h"
#include "Glyph.h"


RightKeyAction::RightKeyAction(CodeEditorForm *codeEditorForm):KeyAction(codeEditorForm) {
}

RightKeyAction:: ~RightKeyAction() {

}

void RightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long ret;
	Long lineCurrent;
	Long memoCurrent;

	ret = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Next();

	if (ret == lineCurrent) {
		ret = this->codeEditorForm->memo->GetCurrent();
		memoCurrent = this->codeEditorForm->memo->Next();
		if (memoCurrent != ret) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			this->codeEditorForm->current->First();
		}
	}

	this->codeEditorForm->regionController->CleanRegion();
}